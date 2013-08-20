<div class="standards-browser subject">
  <div class="row">
    <div class="large-12 columns"><h2><?php print $level_title;?></h2></div>
  </div>
  <?php $count = 0; ?>
    <?php if ($terms): ?>
      <?php foreach ($terms as $term) : ?>
      <?php if($count % 2 == 0): ?><div class="row"><?php endif; ?>
        <div class="large-6 columns">
          <a id="term-<?php print $term->tid; ?>" class="sbac-custom-term button" tid="<?php print $term->tid; ?>" href="#">
          <?php
            $term_data = taxonomy_term_load($term->tid);
            $shortname = $term_data->field_alignment_shortname['und'][0]['value'];
          ?>
            <?php if (!empty($shortname)): ?>
              <?php print $shortname . ' ( ' . $term->name . ' )'; ?>
            <?php else: ?>
              <?php print $term->name; ?>
            <?php endif; ?>
            <?php if(!empty($term->description)): ?>
              <div class="tooltip-b arrow-box">
                  <p><?php print $term->description; ?></p>
              </div>
            <?php endif; ?>
          </a>
        </div>
        <?php if(count($terms) < 2 || ($count % 2 == 1)): ?></div><?php endif; ?>
        <?php $count++; ?>
      <?php endforeach; ?>
    <?php endif; ?>
</div>
