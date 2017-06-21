<?php
  $count = 0;
  $terms = array();

  foreach($form as $key => $val) {
    if (strpos($key, 'term') !== FALSE) {
      $terms[] = $key;
    }
  }

?>
<!--<div id="alignment-node-form">-->
  <!-- other stuff -->
  <div class="standards-browser select">
    <h2><?php sbac_alignment_type_description(); ?></h2>
      <!-- print out the checkboxes -->
      <?php foreach($terms as $checkbox): ?>
          <?php if($count % 2 == 0): ?><div class="row"><?php endif; ?>
            <?php print drupal_render($form[$checkbox]); ?>
          <?php if(count($terms) < 2 || ($count % 2 == 1)): ?></div><?php endif; ?>
          <?php $count++; ?>
          <?php if(count($terms) == $count): ?></div><?php endif; ?>
      <?php endforeach; ?>
  </div>

  <?php // print drupal_render($form['alignment_type']); ?>

  <div class="alignment-buttons">
    <?php print drupal_render($form['submit']); ?>
    <?php print drupal_render($form['cancel']); ?>
  </div>
  <?php print drupal_render_children($form); ?>
<!--</div>-->
