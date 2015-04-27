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
    if (isset($fields['sticky']) && $fields['sticky']->raw == 1 && $fields['state']->raw == 'published') {
      $class = 'distinction';
      $text = 'Posted with Distinction';
      $image = '<a href="#" data-dropdown="distinction-drop-' . $fields['nid']->raw . '"><img src="/sites/all/themes/SBAC/images/icons/icon-distinction.png" alt="Posted With Distinction Logo"></a>
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

    <?php if (isset($fields['image'])): ?>
      <?php print $fields['image']; ?>
      <?php print '<span class="' . $fields['file-type-icon'] . '"></span>'; ?>
    <?php endif; ?>

    <div class='resource-stats'>
      <?php if (isset($fields['field_alt_body'])): ?>
        <?php echo $fields['field_alt_body']->content; ?>
      <?php endif; ?>
    </div>

    <?php if (isset($fields['favorites_link'])): ?>
      <div class="favorites-link">
        <?php echo strtoupper($fields['favorites_link']); ?>
      </div>
    <?php endif; ?>
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

    <?php if (isset($fields['subject']) || isset($fields['grades']) || isset($fields['media_types'])): ?>
      <div class="paradata-info">
        <?php if (isset($fields['subject']) && $fields['subject']): ?>
          <div class="info-item">
            <div class="field-subject">Subjects:</div><?php print $fields['subject']; ?></div>
        <?php endif; ?>

        <?php if (isset($fields['grades']) && $fields['grades']): ?>
          <div class="info-item">
            <div class="field-grades">Grades:</div><?php print $fields['grades']; ?></div>
        <?php endif; ?>

        <?php if (isset($fields['media_types']) && $fields['media_types']): ?>
          <div class="info-item">
            <div class="field-media-types">Media Types:</div><?php print $fields['media_types']; ?></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (isset($fields['views']) || isset($fields['downloads']) || isset($fields['collaborators'])): ?>

      <div class="paradata-numbers">
        <?php if (isset($fields['views']) && $fields['views']): ?>
          <div class="stat-views">
            <a href="#" class="sbac-hover" data-dropdown="unique-views-drop-<?php echo $fields['nid']->raw; ?>">
              <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statviews.png" alt="Views">
            </a>
            <ul id="unique-views-drop-<?php echo $fields['nid']->raw ?>" class="f-dropdown" data-dropdown-content>
              <li>Views</li>
            </ul>
            <?php print $fields['views']; ?>
          </div>
        <?php endif; ?>

        <div class="stat-downloads">
          <a href="#" class="sbac-hover" data-dropdown="total-downloads-<?php echo $fields['nid']->raw; ?>">
            <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statdownloads.png" alt="Downloads">
          </a>
          <ul id="total-downloads-<?php echo $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
            <li>Downloads</li>
          </ul>
          <?php if (isset($fields['downloads']) && $fields['downloads']): ?>
            <?php print $fields['downloads']; ?>
          <?php else: ?>
            <div class="field-content">0</div>
          <?php endif; ?>
        </div>

        <?php if (isset($fields['collaborators']) && $fields['collaborators']): ?>
          <?php // print $fields['collaborators']; ?>
        <?php endif; ?>

        <?php if (isset($fields['rating']) && $fields['rating']): ?>
          <div class="rating-count">
            <a href="#" class="sbac-hover" data-dropdown="rating-dropdown-<?php echo $fields['nid']->raw; ?>">
              <?php print $fields['rating']; ?>
            </a>
            <ul id="rating-dropdown-<?php echo $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
              <li>Rating</li>
            </ul>
            <div class="field-content">(<?php isset($fields['rating_count']) ? print $fields['rating_count'] : '0' ?>)</div>
          </div>
        <?php endif; ?>
      </div>

    <?php endif; ?>

  </div>
</div>
