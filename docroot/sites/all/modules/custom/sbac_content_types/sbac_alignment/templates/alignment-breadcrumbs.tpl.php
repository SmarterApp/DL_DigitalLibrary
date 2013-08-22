<div class="breadcrumb">
  <ul class="inline-list">
    <?php if (is_array($terms)): ?>
      <?php foreach ($terms as $term): ?>
        <li id="term-<?php print $term->tid; ?>">
          <a href="#" tid="<?php print $term->tid; ?>" class="sbac-custom-term-remove">
            <span class="b-label">
              <?php ($shortname = $term->field_alignment_shortname['und'][0]['value'])? print $shortname: print $term->name; ?>&nbsp;&nbsp;&nbsp;|&nbsp; x</span><span class="arrow"><span></span></span>
          </a>
        </li>
      <?php endforeach; ?>
    <?php endif; ?>
  </ul>
</div>