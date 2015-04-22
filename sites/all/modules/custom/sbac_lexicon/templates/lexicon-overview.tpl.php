<?php
/**
 * @file
 * Default theme implementation for displaying the Lexicon overview.
 *
 * This template renders a the Lexicon overview.
 *
 * Available variables:
 * - $lexicon_overview: Lexicon overview object.
 *    - $lexicon_overview->voc_name: vocabulary name.
 *    - $lexicon_overview->description: vocabulary description.
 *    - $lexicon_overview->introduction: introduction text for Lexicon.
 *    - $lexicon_overview->go_to_top_link: Optional "go-to-top" link information
 *      in named array containing go_to_top_link["name"],
 *      go_to_top_link["path"], go_to_top_link["fragment"], and
 *      go_to_top_link["attributes"].
 * - $lexicon_alphabar: Lexicon alphabar as rendered by
 *   lexicon-alphabar.tpl.php.
 * - $lexicon_overview_sections: Lexicon overview sections as rendered by
 *   lexicon-overview-section.tpl.php.
 *
 */
?>
<div id="<?php print $lexicon_overview->voc_name ?>" class="ds-2col-stacked <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <div class="group-header<?php print (isset($header_classes)) ? $header_classes : ''; ?>">
    <?php if (isset($lexicon_overview->description)) : ?>
      <div class="lexicon-description">
        <?php print $lexicon_overview->description; ?>
      </div>
    <?php endif;?>
    <?php if (isset($lexicon_overview->introduction)) : ?>
      <div class="lexicon-introduction">
        <?php print $lexicon_overview->introduction; ?>
      </div>
    <?php endif;?>
  </div>

  <div class="group-left<?php print (isset($left_classes)) ? $left_classes : ''; ?>">
    <?php print $lexicon_alphabar ?>
  </div>

  <div class="group-right lexicon-list<?php print (isset($right_classes)) ? $right_classes : ''; ?>">
   <h2 class="lexicon-letter"><?php print drupal_get_title(); ?></h2>
    <?php if(isset($edit_link)) : ?>
      <div class="edit"><?php print $edit_link; ?></div>
    <?php endif; ?>
    <div class="contents">
      <?php foreach ($lexicon_overview_sections as $section) : ?>
        <?php print $section; ?>
      <?php endforeach; ?>
    </div>
    
    <div class="group-right-footer">
      <div class="foot-item last">
      <?php if(isset($next)) : ?>
        <div class="next"><?php print $next; ?></div>
      <?php endif; ?>
      </div>
      <div class="foot-item first">
      <?php if(isset($prev)) : ?>
        <div class="prev"><?php print $prev; ?></div>
      <?php endif; ?>
      </div>
      <div class="foot-item">
      <?php if (isset($lexicon_overview->go_to_top_link)) : ?>
        <div class="top">
          <?php print l($lexicon_overview->go_to_top_link["name"], '#', array(
            'fragment' => $lexicon_overview->go_to_top_link["fragment"],
            'attributes' => $lexicon_overview->go_to_top_link["attributes"],
            'external' => TRUE,
          )); ?>
        </div>
      <?php endif; ?>
      </div>
    </div>
  </div>

  <div class="group-footer<?php print (isset($footer_classes)) ? $footer_classes : ''; ?>">
  </div>

</div>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
