<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $display_submitted: whether submission information should be displayed.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="sbac-forum-confirm-message-region">
    <?php if (!empty($parent_forum_markup['welcome_message'])) : ?>
      <div style="display:block">
        <?php print $parent_forum_markup['welcome_message']; ?>
      </div>
    <?php endif; ?>
  </div>

  <div class="topic-node--forum-parent-info">

    <div class="topic-node-forum-parent-name-wrapper">
      <h1><?php print $parent_forum_markup['forum_name']; ?></h1>
    </div>

    <div class="sbac-forum-topic-node-view-controls-wrapper">
      <?php if (!empty($parent_forum_markup['controls']['markup'])) : ?>
        <div class="sbac-forum-topic-node-view-controls">
          <?php print t('Forum Settings'); ?>
        </div>
        <div class="sbac-forum-topic-node-view-controls-popup <?php print $parent_forum_markup['controls']['classes']; ?>">
          <?php print $parent_forum_markup['controls']['markup']; ?>
        </div>
      <?php endif; ?>
    </div>
    <!-- end vp-controls-wrapper -->
  </div>
  <!-- end parent-info -->

  <div class="topic-node-view-tertiary-nav">
    <div class="topic-node-view-tertiary-nav-left">
      <?php print $tertiary_nav['back']; ?>
    </div>
    <div class="topic-node-view-tertiary-nav-right">
      <?php print $tertiary_nav['favorite'];?>
      <div class="action">
        <?php print $tertiary_nav['edit']; ?>
        <?php print $tertiary_nav['delete']; ?>
      </div>
    </div>
  </div>
  <!-- end tertiary-nav -->
  <?php print $moderation['topic']['header']; ?>
  <div class="topic-node-main-content">

    <div class="topic-node-main-content-left">
      <div class="topic-node-auhor-pane">
        <?php print $main_content['author_image']; ?>
      </div>
      <div class="topic-node-author-pane-name">
        <?php print $main_content['author_name_popup']; ?>
      </div>
      <div class="topic-node-author-pane-post-date">
        <?php print $main_content['posted']; ?>
      </div>
    </div>
    <!-- end main content left-->

    <div class="topic-node-main-content-right">
      <?php print render($title_prefix); ?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php print render($title_suffix); ?>

      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_tags']);
      hide($content['field_topic_links']);
      hide($content['field_topic_files']);
      print render($content);
      ?>
      <?php print $tertiary_nav['flag']; ?>

      <div class="topic-node-main-content-materials-wrapper">
        <?php if ($main_content['has_materials']): ?>
          <div class="topic-node-main-content-materials-label">Material(s)</div>
         <div class="topic-node-main-content-warning"> <p> Note: Attached materials have not been reviewed by Smarter Balanced.</p> </div>
          <?php
          print render($content['field_topic_files']);
          print render($content['field_topic_links']);
          ?>
        <?php endif; ?>
      </div>
      <?php if (!empty($flags)): ?>
      <div class='flag-section'>
        <div class='flag-header flag-header-reason'>
          <?php print $flags['reason']; ?>
        </div>
        <div class='flag-header flag-header-comment'>
          <?php print render($flags['comment']); ?>
        </div>
      </div>
      <?php endif; ?>
      <?php print $moderation['topic']['content']; ?>
    </div>
    <!-- end main content right-->
  </div>
  <!-- end main content-->

  <div class="topic-node-comments-region">
    <div class="topic-node-reply-direct-wrapper">
      <?php //print render($content['comments']['comment_form']); ?>
    </div>
    <div class="topic-node-controls">
      <?php print $action_section; ?>
    </div>

    <?php if (!empty($content['field_tags']) && !$is_front): ?>
      <?php print render($content['field_tags']) ?>
    <?php endif; ?>

    <?php if (!empty($comment_count)): ?>
      <div class="topic-node-comments-counter">
        <h2><?php print format_plural($comment_count, '1 Reply', '@count Replies'); ?></h2>
      </div>
    <?php endif ?>
  <?php if (!empty($sort_by) && !empty($comment_count)): ?>
    <?php print $sort_by; ?>
  <?php endif; ?>
    <?php //print render($content['links']); ?>
    <?php print render($content['comments']); ?>
  </div>
  <!--end comments-section -->


</article>
