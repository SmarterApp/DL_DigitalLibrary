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

  <div class="row-comment-content">
    <div class="topic-node-comment-region-left">
      <div class="topic-node-comment-author-img">
        <?php print $picture ?>
      </div>
    </div>

    <div class="topic-node-comment-region-right">
      <?php if ($new): ?>
        <span class="new"><?php //print $new ?></span>
      <?php endif; ?>

      <div class="topic-node-comment-region-right-top">
        <?php print $auth_name_hover; ?>
        <?php print ' ' . $posted_date; ?>
        <?php print $depth_extra; ?>
      </div>
      <!-- END region right top -->


      <div class="content"<?php print $content_attributes; ?>>
        <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['links']);
        hide($content['field_topic_comment_links']);
        hide($content['field_topic_comment_files']);
        print render($content);
        ?>
        <div class="topic-node-comment-materials-wrapper">
          <?php if ($has_materials): ?>
            <div class="topic-node-comment-materials-label">Material(s)</div>
            <?php
            print render($content['field_topic_comment_files']);
            print render($content['field_topic_comment_links']);
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
        <?php if (!empty($content['reply_link'])): ?>
          <?php print $content['reply_link']; ?>
        <?php endif; ?>
				<div class="recommend-box">
        <?php if (!empty($content['recommend_link'])): ?>
          <?php print $content['recommend_link']; ?>
					
        <?php endif; ?>
        <div id="recommend-info-<?php print $comment_id; ?>">
          <?php if (!empty($content['recommend_count'])): ?>
            <?php if (!empty($content['recommend_link'])): ?> - <?php endif; ?><?php print $content['recommend_count']; ?> recommended
          <?php endif; ?>
        </div>
				</div>
        <?php if (!empty($content['edit_link'])): ?>
          <?php print $content['edit_link']; ?>
        <?php endif; ?>
        <?php if (!empty($content['flag_link'])): ?>
          <?php print $content['flag_link']; ?>
        <?php endif; ?>
      </div>
      <div class="topic-node-comment-region-right-bottm-comment flagged-post-for-<?php print $comment->cid; ?>">
        <?php if (!empty($content['flags']['comments'])): ?>
          <div class='flag-section'>
            <?php print render($content['flags']['comments']['reason']); ?>
            <?php print render($content['flags']['comments']['comment']); ?>
          </div>
        <?php endif; ?>
      </div>
      <div class="topic-node-comment-region-right-reply-form">
      </div>
      <!-- END region reply form-->
    </div>
    <!-- END region right-->
  </div>
</div>

