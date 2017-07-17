<?php

/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user module
 *     is responsible for handling the default user navigation block. In that case
 *     the class would be "block-user".
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 */

// Add links to the instructional, professional-learning, and playlist description blocks
$titleLink = null;
$pre_filters = null;
$titleClass = [];
if ('resource_feature' === $block->region) {
  if (module_exists('sbac_search_api')) {
    $menu_links = menu_tree_output(menu_tree_all_data('main-menu'));
    $pre_filters = _sbac_search_api_get_pre_filters();
  }
}

if (null !== $pre_filters && is_array($menu_links)) {
  foreach ($menu_links as $link) {
    if (!empty($link['#href']) && preg_match("/\b{$link['#href']}\b/", $block->pages)){
      $titleLink = $link['#href'] . $pre_filters;
      $titleClass = ['resource_feature_link'];
      break;
    }
  }
}
?>
<?php if ($block->delta !== 'main'):  ?>
  <div class="<?php print $classes; ?>"<?php print $attributes; ?>>
<?php endif; ?>

  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <h2<?php print $title_attributes; ?>><?php print ($titleLink ? l($block->subject, $titleLink, array('attributes' => array('class' => $titleClass))) : $block->subject) ?></h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <?php if (!empty($content_attributes)) print '<div ' .  $content_attributes . '>'; ?>
    <?php print $content ?>
  <?php if (!empty($content_attributes)) print '</div>'; ?>

<?php if ($block->delta !== 'main') print '</div>'; ?>
