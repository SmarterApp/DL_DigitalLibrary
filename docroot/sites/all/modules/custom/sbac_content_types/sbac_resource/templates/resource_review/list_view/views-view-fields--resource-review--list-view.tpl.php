<div class="resource-card">
  <span id="resource-<?php print $fields['nid']->raw; ?>"></span>
  <div class="row">
    <div class="column large-2">
      <?php if (isset($fields['image'])): ?>
        <a href="<?php print $fields['path']->content;?>" class="list-image">
          <?php print $fields['image']; ?>
          <?php print '<span class="' . $fields['file-type-icon'] . '"></span>'; ?>
        </a>
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
        $image =  '<a href="#" data-dropdown="distinction-drop-'. $fields['nid']->raw.'"><img src="/' . drupal_get_path('theme', 'SBAC') . '/images/icons/icon-shield.png" alt="Posted With Distinction Logo"></a>
          <ul id="distinction-drop-'. $fields['nid']->raw.'" class="f-dropdown" data-dropdown-content>
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

  <div class="list-view-info">
    <?php if (isset($fields['views']) && $fields['views']): ?>
      <?php print $fields['views'] . ','; ?>
    <?php endif; ?>

    <?php if (isset($fields['downloads']) && $fields['downloads']): ?>
      <?php print $fields['downloads']; ?>
    <?php endif; ?>

    <?php if (isset($fields['collaborators']) && $fields['collaborators']): ?>
      <?php //print $fields['collaborators'] . ','; ?>
    <?php endif; ?>
  </div>

    </div>

    <?php
    $class = '';
    if ($fields['state']->raw == 'published') {
      $class = ' approved ';
    }
    ?>

    <div class="clearfix resoruce-bottom column large-4 <?php (isset($fields['text']) ? print  strtolower(str_replace(' ', '-', $fields['text'])) : ''); ?>">
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
  </div>
</div>  
