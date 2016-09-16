<div class='resource-card'>
  <div class="resource-top">
    <?php
    $class = '';
    $text = '';
    $image = '';
    if (isset($fields['sticky']) && $fields['sticky']->raw == 1) {
      $class = 'distinction';
      $text = 'Posted with Distinction';
      $image =  '<a href="#" data-dropdown="distinction-drop-'. $fields['nid']->raw.'"><img src="/' . drupal_get_path('theme', 'SBAC') . '/images/icons/icon-distinction.png" alt="Posted With Distinction Logo"></a>
          <ul id="distinction-drop-'. $fields['nid']->raw.'" class="f-dropdown" data-dropdown-content>
            <li>Posted with Distinction</li>
          </ul>';
    }
    ?>

    <h3 class='resource-name <?php print $class; ?>'>
      <?php print htmlspecialchars_decode($fields['title']->content); ?>
    </h3>
    <div class="shield-drop"><?php print $image; ?></div>

    <?php if (isset($fields['image'])): ?>
      <?php print $fields['image']; ?>
      <?php print '<span class="' . $fields['file-type-icon'] . '"></span>'; ?>
    <?php endif; ?>

    <div class='resource-stats'>
      <p>
        <?php (isset($fields['field_alt_body']) ? print $fields['field_alt_body']->content : print ''); ?>
      </p>
    </div>
  </div>

  <?php
  $class = '';
  if ($fields['state']->raw == 'published') {
    $class = ' approved ';
  }
  ?>

  <div class="clearfix resoruce-bottom <?php print $class; ?> <?php (isset($fields['text']) ? print  strtolower(str_replace(' ', '-', $fields['text'])) : ''); ?>">
    <?php if (isset($fields['text']) && $fields['text'] != 'approved'): ?>
      <div class="resource-state-description">
        <p>
          <?php print $fields['text'] ?>
        </p>
      </div>
      <?php
      if (isset($fields['buttons']) && is_array($fields['buttons'])) {
        foreach ($fields['buttons'] as $type => $button) {
          print '<div class="resource-button left">';
          print $button;
          print '</div>';
        }
      }
      ?>
    <?php endif; ?>


    <?php if (isset($fields['views']) || isset($fields['downloads']) || isset($fields['collaborators'])): ?>

      <div class="paradata-numbers">
        <?php if (isset($fields['views'])): ?>
          <div class="stat-views">
            <a href="#" class="sbac-hover" data-dropdown="unique-views-drop-<?php echo $fields['nid']->raw; ?>">
              <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statviews.png" alt="Views">
            </a>
            <ul id="unique-views-drop-<?php echo $fields['nid']->raw ?>" class="f-dropdown" data-dropdown-content>
              <li>Views</li>
            </ul>
            <div class="field-content"><?php print $fields['views']; ?></div>
          </div>
        <?php endif; ?>

        <div class="stat-downloads">
          <a href="#" class="sbac-hover" data-dropdown="total-downloads-<?php echo $fields['nid']->raw; ?>">
            <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statdownloads.png" alt="Downloads">
          </a>
          <ul id ="total-downloads-<?php echo $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
            <li>Downloads</li>
          </ul>
          <?php if (isset($fields['downloads']) && $fields['downloads']): ?>
            <div class="field-content"><?php print $fields['downloads']; ?></div>
          <?php else: ?>
            <div class="field-content">0</div>
          <?php endif; ?>
        </div>

        <?php if (isset($fields['collaborators']) && $fields['collaborators']): ?>
          <?php // print $fields['collaborators']; ?>
        <?php endif; ?>

        <?php if (isset($fields['rating']) && $fields['rating']): ?>
          <div class="rating-count">
            <div style="cursor: pointer;" class="sbac-hover" data-dropdown="rating-dropdown-<?php echo $fields['nid']->raw; ?>">
              <?php print $fields['rating']; ?>
            </div>
            <ul id="rating-dropdown-<?php echo $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
              <li>Rating</li>
            </ul>
            <div class="field-content">(<?php isset($fields['rating_count']) ? print $fields['rating_count'] : '0'?>)</div>
          </div>
        <?php endif; ?>
      </div>

    <?php endif; ?>

    <?php if (isset($fields['subject']) || isset($fields['grades']) || isset($fields['media_types'])): ?>
      <div class="paradata-info">
        <?php if (isset($fields['subject']) && $fields['subject']): ?>
          <div class="info-item"><div class="field-subject">Subjects:</div><div class="field-content"><?php print $fields['subject']; ?></div></div>
        <?php endif; ?>

        <?php if (isset($fields['grades']) && $fields['grades']): ?>
          <div class="info-item"><div class="field-grades">Grades:</div><div class="field-content"><?php print $fields['grades']; ?></div></div>
        <?php endif; ?>

        <?php if (isset($fields['media_types']) && $fields['media_types']): ?>
          <div class="info-item"><div class="field-media-types">Media Types:</div><div class="field-content"><?php print $fields['media_types']; ?></div></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php
    if (isset($fields['buttons']) && is_array($fields['buttons'])) {
      foreach ($fields['buttons'] as $type => $button) {
        print '<div class="resource-button left">';
        print $button;
        print '</div>';
      }
    }
    ?>

  </div>
</div>

