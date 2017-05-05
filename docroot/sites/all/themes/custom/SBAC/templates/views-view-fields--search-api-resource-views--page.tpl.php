<div class="row clearfix">
    <div class="resource-main">
      <?php if (isset($fields['image'])): ?>
          <a href="<?php print $fields['url']->raw; ?>">
            <?php print $fields['image']; ?>
            <?php print '<span class="' . $fields['file-type-icon'] . '"></span>'; ?>
          </a>
      <?php endif; ?>
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
        <div class="resource-summary">
            <h2 class='resource-name <?php print $class; ?>'>
              <?php print l(truncate_utf8(htmlspecialchars_decode($fields['title']->raw), 70, TRUE, TRUE), $fields['url']->raw); ?>
            </h2>
            <div class="resource-tags">
              <?php if (isset($fields['subject_icons'])): ?>
                <?php foreach ($fields['subject_icons'] as $info) { ?>
                      <img class="subject-icon" src="<?php print $info['url']; ?>" alt="<?php print $info['alt']; ?>" title="<?php print $info['alt']; ?>" />
                <?php } ?>
              <?php endif; ?>
              <?php if (isset($fields['field_grades']->raw)): ?>
                  Grade <?php print $fields['field_grades']->raw; ?>
              <?php endif; ?>
            </div>
            <div class="resource-about">
              <?php if (isset($fields['field_alt_body'])): ?>
                <?php if (isset($fields['created'])): ?>
                  <?php echo $fields['created']->content . ' &mdash; '; ?>
                <?php endif; ?>
                <?php echo truncate_utf8($fields['field_alt_body']->content, 150, TRUE, TRUE); ?>
              <?php endif; ?>
            </div>
        </div>
    </div>
    <div class="shield-drop"><?php print $image; ?></div>
    <div class="resource-stats">
      <?php if (isset($fields['views']) && $fields['views']): ?>
          <div class="stat-views">
<!--              <a href="#" class="sbac-hover" data-tooltipp="Views">-->
                  <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statviews.png" alt="Views">
<!--              </a>-->
            <?php print $fields['views']; ?>
          </div>
      <?php endif; ?>

        <div class="stat-downloads">
<!--            <a href="#" class="sbac-hover" data-tooltipp="Downloads">-->
                <img src="/sites/all/modules/custom/sbac_content_types/sbac_resource/images/icons/icon-statdownloads.png" alt="Downloads">
<!--            </a>-->
          <?php if (isset($fields['downloads']) && $fields['downloads']): ?>
            <?php print $fields['downloads']; ?>
          <?php else: ?>
              <div class="field-content">0</div>
          <?php endif; ?>
        </div>

      <?php if (isset($fields['rating']) && $fields['rating']): ?>
          <div class="rating">
              <div class="rating-count">
                  &nbsp;(<?php print isset($fields['rating_count']) ? $fields['rating_count'] : '0'; ?>)
              </div>
              <div class="rating-stars">
<!--                  <a href="#" class="sbac-hover" data-tooltipp="Rating">-->
                    <?php print $fields['rating']; ?>
<!--                  </a>-->
              </div>
          </div>
      <?php endif; ?>
    </div>
</div>
