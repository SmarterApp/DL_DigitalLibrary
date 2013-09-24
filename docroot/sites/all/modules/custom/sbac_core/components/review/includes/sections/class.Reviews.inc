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
    // create header & new review form
      $output = '';

      $has_review = user_has_review($this->_node->nid, $this->_account->uid);
      $has_review = FALSE;

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
      $based_text = t('(Based on !count)', array(
        '!count' => format_plural(total_reviews($this->_node->nid), '1 review', '@count reviews'),
      ));

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
                      <br /><br /><br /><br /><br /><br /><br /><br />
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

