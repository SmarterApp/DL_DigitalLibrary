<?php
namespace sbac_core\components\review\sections;

class Reviews extends Base {
  const name = 'reviews';
  const title = 'Reviews';
  const permission = 'view reviews';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    // add necessary css
    drupal_add_css(drupal_get_path('module', 'sbac_user') . '/css/profile.css');
      
    // create header & new review form
      $output = '';

      $has_review = user_has_review($this->_node->nid, $this->_account->uid) || ($this->_node->uid == $this->_account->uid);

      $button = '';
      if (!$has_review) { 
        $button = '<a href="#" class="review-form-trigger button medium">' . t('Write your review') . '</a>';
      }

      $output .= '
                    <div class="review-form-header">
                      <div class="section-title">' . t('Tell us what you think of this resource') . '</div>
                      ' . $button . '
                      <div class="clear"></div>
                    </div>
                 ';

      if (!$has_review) {
        $output .= $this->getNewEntityForm('review', 'end_use');
      }

    // reviews summary
      $total_reviews = total_reviews($this->_node->nid);
      $based_text = t('(Based on !count)', array(
        '!count' => format_plural($total_reviews, '1 review', '@count reviews'),
      ));

      // find vocab id of our taxonomy
        $vid = db_query("SELECT vid FROM taxonomy_vocabulary WHERE machine_name = 'applied_category'")->fetchField();
        $tree = taxonomy_get_tree($vid);

      // figure out how many reviews are applicable to each term
        $query = "  SELECT        COUNT(fd.entity_id) AS count,
                                  fd.field_appropriate_for_tid AS tid
                    FROM          eck_review er
                    INNER JOIN    field_data_field_appropriate_for fd
                      ON          fd.bundle = 'end_use'
                      AND         fd.entity_id = er.id
                    WHERE         er.type = 'end_use'
                    AND           er.status = 1
                    AND           er.node_id = :node_id
                    GROUP BY      fd.field_appropriate_for_tid
                    ORDER BY      count DESC
                 ";

        $result = db_query($query, array(':node_id' => $this->_node->nid));
        $i = 0;
        foreach ($result as $row) {
          foreach ($tree as &$term_ref) {
            if ($term_ref->tid == $row->tid) {
              $term_ref->count = $row->count;

              if ($i < 3) {
                $term_ref->highlight = TRUE;
              }

              break;
            }
          }

          $i++;
        }

      // build the 'appropriate for' terms output
        $appropriate_output = '';
        $i = 1;
        $j = 0;
        foreach ($tree as $term) {
          $class = '';
          $suffix = '';

          if (($i - ($j * 3)) % 3 == 0) {
            $j++;
            $class = 'right-col';
            $suffix = '<div class="clear"></div>';
          }
          elseif (($i - ($j * 3)) % 2 == 0) {
            $class = 'mid-col';
          }
          else {
            $class = 'left-col';
          }
          
          // the 'top 3' terms are highlighted
          if (isset($term->highlight)) {
            $class .= ' highlight';
          }

          if (!isset($term->count)) {
            $term->count = 0;
          }

          $appropriate_output .= '
                                  <div class="term ' . $class . '">
                                    ' . $term->name . '
                                    (' . $term->count. ')
                                  </div>
                                 ' . $suffix; 

          $i++;
        }

        $widgets = array(
          array(
            'title' => t('Helps Improve Student Learning'),
            'field' => 'field_student_learning',
            'vote_tag' => 'student_learning',
            'class' => 'left-col',
          ),
          array(
            'title' => t('Helps My Professional Development'),
            'field' => 'field_pro_dev',
            'vote_tag' => 'pro_dev',
            'class' => 'mid-col',
          ),
          array(
            'title' => t('Is Easy To Use'),
            'field' => 'field_ease_use',
            'vote_tag' => 'ease_use',
            'class' => 'right-col',
          ),
        );

        $widgets_content = '';

        foreach ($widgets as &$item) {
          $query =  " SELECT      AVG(fd." . $item['field'] . "_rating)
                      FROM        field_data_" . $item['field'] . " fd
                      INNER JOIN  eck_review er
                        ON        er.id = fd.entity_id
                        AND       er.type = fd.bundle
                      WHERE       fd.bundle = 'end_use'
                      AND         er.node_id = :node_id
                      AND         er.status = 1
                    ";

          $average = db_query($query, array(':node_id' => $this->_node->nid))->fetchField();

          $fivestar = theme('fivestar_formatter_default', array(
            'element' => array(
              '#theme' => 'fivestar_formatter_default',
              '#rating' => $average,
              '#instance_settings' => array(
                'stars' => 4,
                'allow_clear' => 0,
                'target' => 'none',
                'user_register_form' => '',
              ),
              '#display_settings' => array(
                'widget' => array(
                  'fivestar_widget' => '',
                ),
                'style' => 'average',
                'text' => 'average',
                'expose' => 1,
              ),
              '#widget' => array(
                'name' => 'oxygen',
                'css' => drupal_get_path('module', 'fivestar') . '/widgets/oxygen/oxygen.css',
              ),
              '#description' => '',
              '#children' => '',
            ),
          ));

          if ($average >= 75) {
            $label = t('Strongly Agree');
          }
          elseif ($average >= 50) {
            $label = t('Agree');
          }
          elseif ($average >= 25) {
            $label = t('Disagree');
          }
          else {
            $label = t('Strongly Disagree');
          }

          $widgets_content .= '
                              <div class="' . $item['class'] . '">
                                <div class="item-title">' . $item['title']  . '</div>
                                ' . $fivestar . '
                                <div class="rating-label">' . $label . '</div>
                              </div>
                             ';
        }

        $output .= '
                    <div id="summary">
                      <div class="review-section-header">
                        <div class="section-title">
                          ' . t('Summary of All Reviews') . '
                          <span class="secondary">' . $based_text . '</span>
                        </div>
                        <div class="clear"></div>
                      </div>
                      <div class="summary-content">
                        <div class="summary-widgets">
                          ' . $widgets_content . '
                          <div class="clear"></div>
                        </div>
                        <div class="appropriate-for">
                          <div class="item-title">' . t('Appropriate for:') . '</div>
                          ' . $appropriate_output . '
                          <div class="clear"></div>
                        </div>
                      </div>
                    </div>
                   ';

    // existing reviews
      module_load_include('inc', 'sbac_core', 'components/review/review.pages');

      if (!isset($_GET['sort'])) {
        $sort = 'newest';
      }
      else {
        $sort = $_GET['sort'];
      }

      $page = 0;
      if ($reviews = review_load_more($this->_node, $sort, $page)) {
        $sort_links = array();

        $sort_links[] = l('Newest', 'node/' . $this->_node->nid, array(
          'fragment' => 'review-reviews', 
          'query' => array(
            'sort' => 'newest',
          )
        ));

        $sort_links[] = l('Most Helpful', 'node/' . $this->_node->nid, array(
          'fragment' => 'review-reviews',
          'query' => array(
            'sort' => 'helpful',
          )
        ));

        $output .= '
                    <div id="individual-reviews">
                      <div class="review-section-header">
                        <span class="section-title">' . t('Individual Reviews') . '</span>
                        <span class="sorting-order">
                        ' . implode(' | ', $sort_links) . '
                        </span>
                        <div class="clear"></div>
                      </div>
                      ' . $reviews . '
                    </div>
                   ';
      } 

    // wrap & return
      $output = '<div class="review-wrap" id="review-wrap-reviews">' . $output . '</div>';

      return $output;
  }
}

