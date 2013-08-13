<div class="standards-browser subject">
  <h2><?php print $level_title;?></h2>
  <?php $count = 0; ?>
    <?php if ($terms): ?>
      <?php foreach ($terms as $term) : ?>
      <?php if($count % 2 == 0): ?><div class="row"><?php endif; ?>
        <div class="large-6 columns">
          <a id="term-<?php print $term->tid; ?>" class="sbac-custom-term button" tid="<?php print $term->tid; ?>" href="#">
            <?php print $term->name; ?>
            <div class="tooltip-b arrow-box">
                <p><?php print $term->description; ?></p>
            </div>
          </a>
        </div>
        <?php if(count($terms) < 2 || ($count % 2 == 1)): ?></div><?php endif; ?>
        <?php $count++; ?>
      <?php endforeach; ?>
    <?php endif; ?>
</div>
