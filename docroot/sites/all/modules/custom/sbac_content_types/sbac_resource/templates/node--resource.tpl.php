<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to echo them all, or
 *   echo a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the echoing of a
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

drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
?>
<?php if (isset($resource_type) && $resource_type): ?>
  <span class="resource-type"><?php echo $resource_type; ?></span>
<?php endif; ?>

<?php if (isset($favorites_link)): ?>
  <div class="favorites-link">
    <?php echo $favorites_link; ?>
  </div>
<?php endif; ?>
<?php if (flag_get_flag('featured_node')): ?>
  <div class="featured-resource-link">
    <?php print flag_create_link('featured_node', $node->nid)?>
  </div>
<?php endif; ?>
  <article id="node-<?php echo $node->nid; ?>" class="<?php echo $classes; ?>"<?php echo $attributes; ?>>
  <div class="resource-attributes">
    <?php if (isset($author) && $author): ?>
      <p><span class="author">Author: </span class="publisher"><?php echo $author; ?> | Owner: <?php print $owner; ?></p>
    <?php endif; ?>
    <?php if (isset($contributor)): ?>
      <p class="divider"><span class="contributor">Contributor: </span><?php echo $contributor; ?></p>
    <?php endif; ?>

    <?php if (isset($edit_link) && $edit_link): ?>
      <p><span class="edit-link"><?php echo $edit_link; ?></span></p>
    <?php endif; ?>

    <p class="metadata"></p>
  </div>

  <?php if (isset($viewer)) : ?>
  <div id="resource-element-wrapper">
    <div id="resource-element"><?php echo $viewer; ?></div>
  </div>
    <div class="infobar">
    <div class="row">
      <div class="column large-3">
        <?php echo $materials; ?>
        <div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>
      </div>
<div class="column large-7">
<?php
if ($viewer_filename == "Understanding The Smarter Balanced Individual Student Report"):
      $viewer_filename = str_replace("Understanding The Smarter Balanced Individual Student Report", "Understanding the Smarter Balanced Individual Student Report", $viewer_filename);
endif;
?>
        <p><span id="sbac-filename"><?php echo $viewer_filename; ?></span></p>
      </div>
      <div class="column large-2">
        <?php
          if (isset($download_partial)) {
            echo "<p>This is a <span id='sbac-partial-download'>partial download</span></p>";
          }
          if (isset($download)) {
            echo $download;
          }
        ?>
      </div>

			<?php if (isset($download_partial)): ?>
		    <div class="sbac-download-dropdown f-dropdown" style="display:none;">
		      <p>The resource includes one or more copy-protected files.</p>
		      <p>Copy-protected files are excluded from the download.</p>
		    </div>
		  <?php endif; ?>

    </div>
  </div>
  <?php endif; ?>

  <?php if(isset($edit_resubmit)): ?>
    <p><?php print $edit_resubmit; ?></p>
  <?php endif; ?>
  <?php if (isset($flag['resource']) && count($flag) > 0): ?>
    <div class="resource-flag-information <?php echo $flag['urgent_css']; ?>">
      <div class="flag-status"><?php echo $flag['status']; ?></div>
      <div class="flag-count"><?php echo $flag['count_message']; ?></div>
      <div class="flag-button"><?php echo $flag['button']; ?></div>
    </div>
  <?php endif; ?>

  <?php if (isset($flag['review'])): ?>
    <div class="resource-review-information">
      Review
      <?php echo $flag['review']; ?>
    </div>
    <div class="resource-flag-information <?php echo $flag['urgent_css']; ?>">
      <div class="flag-status"><?php echo $flag['status']; ?></div>
      <div class="flag-count"><?php echo $flag['count_message']; ?></div>
      <?php if (isset($flag['button'])): ?>
        <div class="flag-button"><?php echo $flag['button']; ?></div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if (isset($content['review']) && $content['review']): ?>
    <div id="review"><?php echo render($content['review']); ?></div>
  <?php endif; ?>

</article>
