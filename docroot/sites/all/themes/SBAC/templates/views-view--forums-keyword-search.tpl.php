<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
// Adding code inline with this view. Should be in preprocess but no time.
// TODO: cleanup
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
?>
<div class="<?php print $classes; ?>">
<div class="kw-search-back-button-wrapper">
  <?php
    $link_ops = array(
      'attributes' => array(
        'class' => 'kw-search-back-button-link',
      )
    );
    $link_back = l('Back to All Forums', 'forums', $link_ops);
    print $link_back;
  ?>
</div>
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($exposed): ?>
    <div class="view-filters">
      <div class="kw-search-tertiary-nav">
        all forums link.
        my forums link.
      </div>
      <div class="kw-search-keyword-form-element">
        <?php print $exposed; ?>
      </div>
      <div class="kw-search-new-forum-link">
        <?php
          $vocab = taxonomy_vocabulary_machine_name_load('forum');
          $access_to_add = _sbac_forum_add_forum_user_access($vocab);
          if ($access_to_add) {
            $link_options = array(
              'attributes' => array(
                'class'=> 'new-forum-link',
              ),
            );
            $new_forum_link_text = '<div class="forum-subnav-start-link-wrapper">';
            $new_forum_link_text .= l('Start a Forum', 'forums/forum/add', $link_options);
            $new_forum_link_text .= '</div>';
            print $new_forum_link_text;
          }
        ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <div class="kw-search-empty-text">
        <?php
          $empty_text_url = 'forums';
          $link_text = t('Browse all Forums');
          $link_ops = array('attributes' => array('class' => 'forum-list-filter-empty-text-reset-link button'));
          $empty_text_link = l($link_text, $empty_text_url, $link_ops);
          $empty_text_content = '<div class="sbac-forum-filter-no-results-wrapper">';
          $empty_text_content .= '<h2>Your search returned no results</h2>';
          $empty_text_content .= '<p>Please try different search criteria or browse any of the forums below ';
          $empty_text_content .= 'that have been identified for you by using the subject(s) and grade(s) in your profile</p>';
          $empty_text_content .= '<div class="sbac-forum-filter-no-result-button-link">'.$empty_text_link.'</div>';
          $empty_text_content .= '</div>';
          print $empty_text_content;
        ?>
      </div>
      <div class="kw-search-empty-text-view-suggestion">
        <?php
          $view_e = views_get_view('forum_list_empty');
          $view_e->set_display('block');
          sbac_forum_forum_listing_empty_apply_filters($view_e); // Set filters here.
          $view_e->pre_execute();
          $view_e->execute();
          $view_e->_post_execute();
          $forum_list_empty_output = $view_e->preview();
          print $forum_list_empty_output;
        ?>
      </div>
      <?php //print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>
