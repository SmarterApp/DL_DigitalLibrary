<div class="resource-card">
  <div class="row clearfix">
    <div class="column large-2">
      <?php if (isset($fields['image'])): ?>
      <?php print $fields['image']; ?>
      <?php print '<span class="' . $fields['file-type-icon'] . '"></span>'; ?>
      <?php endif; ?>

    </div>

  <div class="column  <?php if (isset($fields['text']) && $fields['text'] != 'approved'): echo 'large-6'; else: echo 'large-10'; endif; ?>" >
    <?php
      $class = '';
      $text = '';
      $image = '';
      if (isset($fields['sticky']) && $fields['sticky']->raw == 1) {
        $class = 'distinction';
        $text = 'Posted with Distinction';
        $image =  '<a href="#" data-dropdown="distinction-drop-'. $fields['nid']->raw.'"><img src="/sites/all/themes/SBAC/images/icons/icon-distinction.png" alt="Posted With Distinction Logo"></a>
          <ul id="distinction-drop-'. $fields['nid']->raw.'" class="f-dropdown" data-dropdown-content>
            <li>Posted with Distinction</li>
          </ul>';
      }
    ?>
    <h3 class='resource-name <?php print $class; ?>'>
      <?php print l(truncate_utf8(htmlspecialchars_decode($fields['title']->raw), 70, TRUE, TRUE), $fields['path']->content); ?>
    </h3>

		
		<div class="resource-stats">
          <?php if (isset($fields['field_alt_body'])): ?>
            <?php echo $fields['field_alt_body']->content; ?>
          <?php endif; ?>
		</div>
		
    <div class="shield-drop"><?php print $image; ?></div>
    <?php if (isset($fields['favorites_link'])): ?>
      <div class="favorites-link">
        <?php echo strtoupper($fields['favorites_link']); ?>
      </div>
    <?php endif; ?>

  <div class="list-view-info">
    <?php if (isset($fields['views']) && $fields['views']): ?>
      <div class="stat-views"><?php print $fields['views']; ?></div>
    <?php endif; ?>

    <?php if (isset($fields['downloads']) && $fields['downloads']): ?>
      <div class="stat-downloads"><?php print $fields['downloads']; ?></div>
    <?php else: ?>
      <div class="stat-downloads"><div class="field-content">0</div></div>
    <?php endif; ?>

    <?php if (isset($fields['rating']) && $fields['rating']): ?>
			<div class="rating">
			  <?php print $fields['rating']; ?> 
				<div class="rating-count">(<?php isset($fields['rating_count']) ? print $fields['rating_count'] : '0'?>)</div>
			</div>
    <?php endif; ?>

    <?php if (isset($fields['collaborators']) && $fields['collaborators']): ?>
      <?php //print $fields['collaborators'] . ','; ?>
    <?php endif; ?>
  </div>

	 <?php
    if (isset($fields['buttons']) && is_array($fields['buttons'])) {
      foreach ($fields['buttons'] as $type => $button) {
        print '<div class="resource-button right">';
        print $button;
        print '</div>';
      }
    }
    ?>

   </div>

    <?php
    $class = '';
    if ($fields['state']->raw == 'published') {
      $class = ' approved ';
    }
    ?>

    <!--<div class="clearfix resoruce-bottom column large-4 <?php (isset($fields['text']) ? print  strtolower(str_replace(' ', '-', $fields['text'])) : ''); ?>">
      <div class="column resource-state-description right">

        <?php if (isset($fields['links']) && $fields['links']): ?>
        <div class="dropdowns">
          <a href="#" data-dropdown="drop-<?php print $fields['nid']->raw; ?>"><i class='sbac-select'></i></a>
          <ul id="drop-<?php print $fields['nid']->raw; ?>" class="f-dropdown" data-dropdown-content>
          <?php
            foreach ($fields['links'] as $link) {
              print '<li>' . $link . '</li>';
            }
          ?>
          </ul>
        </div>

        <?php endif; ?>

    <?php if (isset($fields['text']) && $fields['text'] != 'approved'): ?>
      <div class="resource-state-description">
        <p>
          <?php print $fields['text'] ?>
        </p>
      </div>

    <?php endif; ?>
       
      </div>
    </div>-->
  </div>
</div>  
