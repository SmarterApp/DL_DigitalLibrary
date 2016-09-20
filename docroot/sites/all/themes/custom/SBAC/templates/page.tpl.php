<!-- Header and Nav -->
<div class="page-wrap">
   <nav class="top-bar main-top clearfix">
   <div class="inner-wrap">
  <ul class="title-area">
    <li class="name"><h1>
        <a title="Smarter Balanced Assessment Consortium" href="<?php echo $home_url; ?>">
          <img src="<?php echo $logo; ?>" alt="Smarter Balanced Assessment Consortium Logo"/>
        </a>
      </h1></li>
    <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
  </ul>
  <h1 class="title left">Digital Library</h1>
  <?php if ($user->uid && !in_array('guest', $user->roles) && !$conflicting_profile): ?>
    <ul class="inline-list right user-nav">
      <li class="user-info">
        <a title='<?php echo $user->full_name ?>' data-dropdown="drop3" href="#">
          <?php
          if (isset($user->picture->uri)) {
            echo $user->image_thumb;
          }
          echo $user->full_name;
          ?>
        </a>
        <ul id="drop3" class="f-dropdown">
          <li><?php echo l('Account', drupal_get_path_alias('user/' . $user->uid), array('attributes' => array('title' => 'Account'))); ?></li>
          <li><?php echo l('Logout', 'user/logout', array('attributes' => array('title' => 'Logout'))); ?></li>
        </ul>
      </li>
      <li class="notifications">
        <?php
        echo $user->notifications;
        ?>
      </li>
      <li>
        <a title='Feedback' id="feedback-click" data-dropdown="feedback-dropdown" href="#">Feedback</a>
        <?php print render($page['feedback']); ?>
      </li>
      <li>
        <div class="sbac-favorites-menu">
          <?php
          echo $user->favorites_link;
          echo $user->favorites_added;
          ?>
        </div>
      </li>
      <li>
        <?php if (isset($help_dropdown)) : ?>
          <?php print $help_dropdown; ?>
        <?php endif; ?>
      </li>
    </ul>
  <?php endif; ?>
  <?php if ($user->uid && in_array('guest', $user->roles)): ?>
    <ul class="inline-list right user-nav">
      <li class="user-info">
        <a title='Sign In' href="/user">Sign In</a>
      </li>
    </ul>
<?php endif; ?>
            </div>
</nav>

            <div class="top-bar sub-top">
            <div class="inner-wrap">
  <nav class="main-nav left">
    <?php if ($main_menu_links && !in_array(SBAC_SHARE_GUEST, $user->roles) && !$conflicting_profile) : ?>
      <?php print $main_menu_links; ?>
    <?php endif; ?>
  </nav>
   <?php if (isset($goals)): ?>
      <div class="nav-goals">
      <?php if (isset($goals['star_rating'])): ?>
         <?php if ($goals['star_rating'][2]): ?>
         <div class="star-rating-complete goal-completed has-tip" data-tooltip title="<?php print $goals['star_rating'][2]; ?>"><span><?php print $goals['star_rating'][0]; ?></span></div>
         <?php else: ?>
            <div class="star-rating-complete goal-completed"><span><?php print $goals['star_rating'][0]; ?></span></div>
         <?php endif; ?>
            <div class="goal-perc"><a title="rated-goal" href="<?php print $goals['goals_url']; ?>"><strong><?php print $goals['star_rating'][1]; ?>%</strong></a></div>
      <?php endif; ?>
      <?php if (isset($goals['resources_reviewed'])): ?>
         <?php if ($goals['resources_reviewed'][2]): ?>
            <div class="resources-reviewed-complete goal-completed has-tip" data-tooltip title="<?php print $goals['resources_reviewed'][2]; ?>"><span><?php print $goals['resources_reviewed'][0]; ?></span></div>
         <?php else: ?>
            <div class="resources-reviewed-complete goal-completed"><span><?php print $goals['resources_reviewed'][0]; ?></span></div>
         <?php endif; ?>
            <div class="goal-perc"><a title="reviewed-goal" href="<?php print $goals['goals_url']; ?>"><strong><?php print $goals['resources_reviewed'][1]; ?>%</strong></a></div>
      <?php endif; ?>
      <?php if (isset($goals['resources_posted']) && ($goals['resources_posted'][1] !== '0')): ?>
         <?php if ($goals['resources_posted'][2]): ?>
            <div class="resources-posted-complete goal-completed has-tip" data-tooltip title="<?php print $goals['resources_posted'][2]; ?>"><span><?php print $goals['resources_posted'][0]; ?></span></div>
         <?php else: ?>
            <div class="resources-posted-complete goal-completed"><span><?php print $goals['resources_posted'][0]; ?></span></div>
         <?php endif; ?>
         <div class="goal-perc"><a title="contributed-goal" href="<?php print $goals['goals_url']; ?>"><strong><?php print $goals['resources_posted'][1]; ?>%</strong></a></div>
      <?php endif; ?>
      </div>
   <?php endif; ?>
  <?php if (isset($page['search']) && $page['search']): ?>
    <div class="search right">
      <?php print render($page['search']); ?>
    </div>
<?php endif; ?>
            </div>
</div>

<?php if ($user->uid && !in_array(SBAC_SHARE_GUEST, $user->roles) && $page['filter']): ?>
            <div class="filters sbac-filter-cat-area"<?php /* hide category drawer if cookie  print sbac_search_hide_category_style();*/ ?>>
            <div class="inner-wrap">
<?php print render($page['filter']); ?>
            </div>
  </div>
<?php endif; ?>

<?php if ($site_slogan): ?>
  <div class="row">
    <div class="large-12 columns hide-for-small">
      <h2><?php print $site_slogan; ?></h2>
    </div>
  </div>
<?php endif; ?>

<?php if ($user->uid && !in_array(SBAC_SHARE_GUEST, $user->roles) && ($page['sub-header'] || $page['toggle'])): ?>
  <div class="top-bar last-top">
    <div class="toggle right">
      <?php print render($page['toggle']); ?>
    </div>
    <div><?php print render($page['sub-header']); ?></div>
  </div>
<?php endif; ?>


<div class="row main-row">
  <div class="main-container clearfix">
    <div id="main" class="<?php print $main_grid; ?> columns">
      <?php if ($messages): print $messages; endif; ?>
      <?php if (!empty($page['help'])): print render($page['help']); endif; ?>
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlight panel callout">
          <?php print render($page['highlighted']); ?>
        </div>
      <?php endif; ?>

      <a id="main-content"></a>

      <?php // if ($breadcrumb): print $breadcrumb; endif; ?>
      <?php if ($title && !$is_front && arg(0) != 'user' && arg(0) != 'legal_accept'): ?>
        <?php if ($html5) : ?>
          <div class="html5-identifier clearfix" id="html5-identifier-node"><p class="html5-content right"><span><i class="general foundicon-website"></i> Content Module</span></p></div>
        <?php endif; ?>
        <?php print render($title_prefix); ?>
        <h1 id="page-title" class="title"><?php print $title; ?></h1>
        <?php print render($title_suffix); ?>
        <?php if (isset($flag)): ?>
          <div class="resource-preview">
            <?php echo $flag['button']; ?>
          </div>
          <div class="flag-information">
            <div class="flag-status"><?php echo $flag['status']; ?></div>
            <div class="flag-count"><?php echo $flag['count_message']; ?></div>
          </div>
        <?php endif; ?>
      <?php endif; ?>

      <?php if (!empty($tabs) && arg(0) != 'user'): ?>
        <?php print render($tabs); ?>
        <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
      <?php endif; ?>

      <?php if ($action_links): ?>
        <ul class="action-links">
          <?php print render($action_links); ?>
        </ul>
      <?php endif; ?>

      <?php print render($page['content']); ?>
    </div>
    <?php if ($user->uid && !empty($page['sidebar_first'])): ?>
      <div id="sidebar-first" class="<?php print $sidebar_first_grid; ?> columns sidebar ">
        <?php print render($page['sidebar_first']); ?>
      </div>
    <?php endif; ?>
    <?php if ($user->uid && !empty($page['sidebar_second'])): ?>
      <div id="sidebar-second" class="<?php print $sidebar_sec_grid; ?> columns sidebar">
        <?php print render($page['sidebar_second']); ?>
      </div>
    <?php endif; ?>
    <?php /*if ('digital-library-resources' == current_path()): */?><!--
      <div class="experimental-feature">
        <div class="title">EXPERIMENTAL FEATURE</div>
        <div class="additional-resoutces">Need additional resources? You may try searching <a href="/external-resources" title="External Resources" target="_blank">external resources</a></div>
      </div>
    --><?php /*endif; */?>
  </div>
</div>
<?php if (!empty($page['footer_first']) || !empty($page['footer_middle']) || !empty($page['footer_last'])): ?>
  <footer class="row">
    <?php if (!empty($page['footer_first'])): ?>
      <div id="footer-first" class="large-4 columns">
        <?php print render($page['footer_first']); ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($page['footer_middle'])): ?>
      <div id="footer-middle" class="large-4 columns">
        <?php print render($page['footer_middle']); ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($page['footer_last'])): ?>
      <div id="footer-last" class="large-4 columns">
        <?php print render($page['footer_last']); ?>
      </div>
    <?php endif; ?>
  </footer>
<?php endif; ?>

</div>
<div class="bottom-bar">
  <div class="row">
    <div class="large-6 columns">
      <p><?php if ($site_name) : ?>
          &copy; <?php print t('Copyright') . ' ' . date('Y'); ?>
        <?php endif; ?></p>
    </div>
    <div class="large-6 small-12 columns">
      <?php
      if (!empty($page['bottom_menu'])) {
        print render($page['bottom_menu']);
      }
      ?>
      <?php if ($user && !in_array(SBAC_SHARE_GUEST, $user->roles) && !$conflicting_profile) : ?>
        <ul class="footer-links inline-list right">
          <li>
            <?php if (user_is_logged_in() && !in_array('guest', $user->roles)) : ?>
              <div class="footer-help">
                <a title="Help Menu" class="help help-dropdown-footer" data-dropdown="drop2" href="#"><span class="sbac-question"></span> Help</a>
                <ul id="drop2" class="f-dropdown" data-dropdown-content>
                  <li><a title="Welcome Tutorial" href="/welcome-tutorial/nojs" class="ctools-use-ajax use-ajax ctools-modal-sbac-help-welcome-tutorial">Welcome Tutorial</a></li>
                  <li><?php print l(t('Glossary'), 'glossary', array('absolute' => TRUE, 'attributes' => array('title' => 'Glossary'))); ?></li>
                  <li><a title='Help Topics' href="/help-topics">Help Topics</a></li>
                </ul>
              </div>
            <?php endif; ?>
          </li>
          <li><a title="Terms of Service" class="terms-and-conditions" href="/terms-of-service">Terms of Service</a></li>
        </ul>
      <?php endif; ?>
    </div>
  </div>
</div>

<?php if (isset($critical_message_button)): ?>
  <div class="critical-message-button" style="display:none">
    <?php echo $critical_message_button; ?>
  </div>
<?php endif; ?>

<?php if (user_is_logged_in()) : ?>
  <?php if (isset($session_expire)): ?>
    <div class="sbac-sso-session-expire" style="display:none">
      <?php echo $session_expire; ?>
    </div>
  <?php endif; ?>
<?php endif; ?>
