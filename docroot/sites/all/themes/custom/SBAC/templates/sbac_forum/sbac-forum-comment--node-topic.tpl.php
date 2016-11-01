<?php

/**
 * @file
 * Default theme implementation for comments.
 *
 * Available variables:
 * - $author: Comment author. Can be link or plain text.
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $created: Formatted date and time for when the comment was created.
 *   Preprocess functions can reformat it by calling format_date() with the
 *   desired parameters on the $comment->created variable.
 * - $changed: Formatted date and time for when the comment was last changed.
 *   Preprocess functions can reformat it by calling format_date() with the
 *   desired parameters on the $comment->changed variable.
 * - $new: New comment marker.
 * - $permalink: Comment permalink.
 * - $submitted: Submission information created from $author and $created during
 *   template_preprocess_comment().
 * - $picture: Authors picture.
 * - $signature: Authors signature.
 * - $status: Comment status. Possible values are:
 *   comment-unpublished, comment-published or comment-preview.
 * - $title: Linked title.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - comment: The current template type, i.e., "theming hook".
 *   - comment-by-anonymous: Comment by an unregistered user.
 *   - comment-by-node-author: Comment by the author of the parent node.
 *   - comment-preview: When previewing a new or edited comment.
 *   The following applies only to viewers who are registered users:
 *   - comment-unpublished: An unpublished comment visible only to administrators.
 *   - comment-by-viewer: Comment by the user currently viewing the page.
 *   - comment-new: New comment since last the visit.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * These two variables are provided for context:
 * - $comment: Full comment object.
 * - $node: Node object the comments are attached to.
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_comment()
 * @see template_process()
 * @see theme_comment()
 *
 * @ingroup themeable
 */

?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if (!empty($new_comment_status_message)) : ?>
    <div class="topic-node-comment-region-status-message">
      <?php print $new_comment_status_message; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($flags['moderation'])): ?>
    <?php print render($flags['moderation']['post']['header']); ?>
  <?php endif; ?>
  <div class="row-comment-content">
    <?php if (!$removed): ?>
    <div class="topic-node-comment-region-left">
      <div class="topic-node-comment-author-img">
        <?php print $picture ?>
      </div>
    </div>
    <?php endif; ?>
    <div class="topic-node-comment-region-right">
      <?php if ($new): ?>
        <span class="new"><?php //print $new ?></span>
      <?php endif; ?>

      <div class="topic-node-comment-region-right-top">
        <?php print $auth_name_hover; ?>
        <?php print ' ' . $posted_date; ?>
        <?php print $depth_extra; ?>
        <?php if ($go_to_thread_link): ?>
          <?php print $go_to_thread_link; ?>
        <?php endif; ?>
      </div>
      <!-- END region right top -->


      <div class="content"<?php print $content_attributes; ?>>
        <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['links']);
        hide($content['field_topic_comment_links']);
        hide($content['field_topic_comment_files']);
        hide($content['field_topic_comment_collection']);
        print render($content);
        if (isset($removed)) {
          print $removed;
        }
        ?>
        <div class="topic-node-comment-materials-wrapper">
          <?php if ($has_materials): ?>
            <div class="topic-node-comment-materials-label">Material(s)</div>
            <div class="topic-node-main-content-warning"> <p> <span>Note:</span> Attached materials have not been reviewed by Smarter Balanced.</p> </div>
            <?php
            print render($content['field_topic_comment_files']);
            print render($content['field_topic_comment_links']);
            print render($content['field_topic_comment_collection']);
            ?>
          <?php endif; ?>
        </div>
        <?php if ($signature): ?>
          <div class="user-signature clearfix">
            <?php print $signature ?>
          </div>
        <?php endif; ?>
      </div>

      <div class="topic-node-comment-region-right-bottom reply-links-for-<?php print $comment->cid; ?>">
        <?php if ($reply_link): ?>
          <?php print $reply_link; ?>
        <?php endif; ?>
        <?php if ($recommend_link || $recommend_count): ?>
          <div class="recommend-box">
          </div>
        <?php endif; ?>
        <?php if ($recommend_link): ?>
          <?php print $recommend_link; ?>
        <?php endif; ?>
        <div id="recommend-info-<?php print $comment_id; ?>">
          <?php if ($recommend_count): ?>
            <?php if ($recommend_link): ?> - <?php endif; ?><?php print $recommend_count; ?> recommended
            <?php endif; ?>
        </div>

        <?php if ($edit_link): ?>
          <?php print $edit_link; ?>
        <?php endif; ?>
        <?php if ($flag_link): ?>
          <?php print $flag_link; ?>
        <?php endif; ?>
      </div>
      <div class="topic-node-comment-region-right-bottm-comment flagged-post-for-<?php print $comment->cid; ?>">
        <?php if (!empty($flags['comments'])): ?>
          <div class='flag-section'>
            <?php print render($flags['comments']['reason']); ?>
            <?php print render($flags['comments']['comment']); ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($flags['moderation']['post'])): ?>
          <?php print render($flags['moderation']['post']['content']); ?>
        <?php endif; ?>

      </div>
      <div class="topic-node-comment-region-right-reply-form">
      </div>
      <!-- END region reply form-->
    </div>
    <!-- END region right-->
  </div>
</div>
