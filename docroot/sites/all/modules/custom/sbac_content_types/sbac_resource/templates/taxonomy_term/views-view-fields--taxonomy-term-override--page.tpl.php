<div class='resource-card'>
  <div class="resource-top">
    <span id="resource-<?php print $fields['nid']->raw; ?>"></span>
    <?php if (isset($fields['links'])): ?>
      <div class="dropdowns">
        <a href="#" data-dropdown="drop-<?php print $fields['nid']->raw; ?>"><i class='sbac-select'>options</i></a>
        <ul id="drop-<?php print $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
          <?php foreach ($fields['links'] as $key => $link) {
            print '<li>' . $link . '</li>'; ?>
          <?php } ?>
        </ul>
      </div>
    <?php endif; ?>
    <?php
    $class = '';
    $text = '';
    $image = '';
    if (isset($fields['sticky']) && $fields['sticky']->raw == 1) {
      $class = 'distinction';
      $text = 'Posted with Distinction';
      $image = '<a href="#" data-dropdown="distinction-drop-' . $fields['nid']->raw . '"><img src="/' . drupal_get_path('theme', 'SBAC') . '/images/icons/icon-distinction.png" alt="Posted With Distinction Logo"></a>
          <ul id="distinction-drop-' . $fields['nid']->raw . '" class="f-dropdown" data-dropdown-content>
            <li>Posted with Distinction</li>
          </ul>';
    }
    ?>

    <h3 class='resource-name <?php print $class; ?>'>
      <?php
      print l(htmlspecialchars_decode($fields['title']->raw), $fields['path']->content);
      ?>
    </h3>
    <div class="shield-drop"><?php print $image; ?></div>

    <?php if (isset($fields['image']) && $fields['image']): ?>
      <a href="<?php print $fields['path']->content; ?>">
        <?php print $fields['image']; ?>
        <?php print '<span class="' . $fields['file-type-icon'] . '"></span>'; ?>
      </a>
    <?php endif; ?>

    <div class='resource-stats'>
      <?php if (isset($fields['field_alt_body'])): ?>
        <?php echo sbac_resource_truncate($fields['field_alt_body']->content, 140); ?>
      <?php endif; ?>
    </div>

    <?php if (isset($fields['favorites_link'])): ?>
      <div class="favorites-link">
        <?php echo strtoupper($fields['favorites_link']); ?>
      </div>
    <?php endif; ?>
  </div>

  <div class="clearfix resoruce-bottom">
    <?php if (isset($fields['field_subject']) || isset($fields['field_grades']) || isset($fields['field_digital_media_type'])): ?>
      <div class="paradata-info">
        <?php if (isset($fields['field_subject']) && $fields['field_subject']->content): ?>
          <div class="info-item">
            <div class="field-subject">Subjects:</div><?php print $fields['field_subject']->content; ?></div>
        <?php endif; ?>

        <?php if (isset($fields['field_grades']) && $fields['field_grades']->content): ?>
          <div class="info-item">
            <div class="field-grades">Grades:</div><?php print $fields['field_grades']->content; ?></div>
        <?php endif; ?>

        <?php if (isset($fields['field_digital_media_type']) && $fields['field_digital_media_type']->content): ?>
          <div class="info-item">
            <div class="field-media-types">Media Types:</div><?php print $fields['field_digital_media_type']->content; ?></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (isset($fields['field_unique_views']) || isset($fields['field_asset_downloads']) || isset($fields['rating'])): ?>

      <div class="paradata-numbers">
        <?php if (isset($fields['field_unique_views']) && $fields['field_unique_views']->content): ?>
          <div class="stat-views">
            <a href="#" class="sbac-hover" data-dropdown="unique-views-drop-<?php echo $fields['nid']->raw; ?>">
              <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statviews.png" alt="Views">
            </a>
            <ul id="unique-views-drop-<?php echo $fields['nid']->raw ?>" class="f-dropdown" data-dropdown-content>
              <li>Views</li>
            </ul>
            <?php print $fields['field_unique_views']->content; ?>
          </div>
        <?php endif; ?>

        <div class="stat-downloads">
          <a href="#" class="sbac-hover" data-dropdown="total-downloads-<?php echo $fields['nid']->raw; ?>">
            <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statdownloads.png" alt="Downloads">
          </a>
          <ul id="total-downloads-<?php echo $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
            <li>Downloads</li>
          </ul>
          <?php if (isset($fields['field_asset_downloads']) && $fields['field_asset_downloads']->content): ?>
            <?php print $fields['field_asset_downloads']->content; ?>
          <?php else: ?>
            <div class="field-content">0</div>
          <?php endif; ?>
        </div>

        <?php if (isset($fields['rating']) && $fields['rating']): ?>
          <div class="rating-count">
            <a href="#" class="sbac-hover" data-dropdown="rating-dropdown-<?php echo $fields['nid']->raw; ?>">
              <?php print $fields['rating']; ?>
            </a>
            <ul id="rating-dropdown-<?php echo $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
              <li>Rating</li>
            </ul>
            <div class="field-content">(<?php isset($fields['rating_count']) ? print $fields['rating_count'] : print '0' ?>)</div>
          </div>
        <?php endif; ?>
      </div>

    <?php endif; ?>

  </div>
</div>
