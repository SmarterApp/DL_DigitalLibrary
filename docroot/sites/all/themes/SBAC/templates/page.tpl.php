<?php
global $user;
?>
<!-- Header and Nav -->
<div class="page-wrap">
<nav class="top-bar main-top clearfix">
  <ul class="title-area">
    <li class="name"><h1>
        <?php
          global $base_url;
          $home_url = $base_url;
          if ($user->uid && in_array(SBAC_SHARE_GUEST, $user->roles)) {
            $home_url = '#';
          }
        ?>
        <a href="<?php echo $home_url; ?>">
          <img src="<?php echo $logo; ?>" alt="Smarter Balanced ASsessment Consortium Logo" />
        </a>
      </h1></li>
    <li><li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li></li>
  </ul>
  <h1 class="title left">Digital Library Beta</h1>
  <?php if ($user->uid && !in_array('guest', $user->roles)): ?>
  <ul class="inline-list right user-nav">
    <li class="user-info">
       <a data-dropdown="drop3" href="">
        <?php
          $user_item = user_load($user->uid);
          if (isset($user_item->picture->uri)) {
            $uri = $user_item->picture->uri;
            $path = drupal_realpath($uri);
            if (file_exists($path)) {
              echo theme('image_style', array(
                'path' => $user_item->picture->uri,
                'style_name' => 'small',
                'attributes' => array(
                  'class'=>'left'
                )
              ));
            }
          }
          echo sbac_user_format_username($user);
        ?>
        </a>
        <ul id="drop3" class="f-dropdown">
          <li><?php echo l('Account','user'); ?></li>
          <li><?php echo l('Logout','user/logout');?></li>
        </ul>
    </li>
    <li class="notifications">
      <?php
        $taskit_counts = taskit_count_tasks($user->uid, array_keys($user->roles), TRUE);
        $text = t('Notifications');

        if ($taskit_counts['_no_role_'] != 0) {
          $text .= ' <span>' . $taskit_counts['_no_role_'] . '</span>';
        }

        echo l($text, 'user', array(
          'html' => TRUE,
          'fragment' => 'profile-notifications',
        ));
      ?>
    </li>
    <li><a id="feedback-click" data-dropdown="feedback-dropdown" href="#">Feedback</a>
      <?php
      // set $class_feedback open if variable enable_feedback is on and the user hasn't disabled feedback flag on their profile yet, otherwise empty
      $class_feedback = (variable_get('enable_feedback') == 1 && !$user_item->field_feedback_flag['und'][0]['value'] ? ' open' : ''); 
      ?>
      <div id="feedback-dropdown" class="f-dropdown content small<?php print $class_feedback; ?>">
        <a id="disable-feedback" class="small right"> x </a>
      <?php
        $feedback_block = block_load('sbac_central','feedback-box');
        $render_array = _block_get_renderable_array(_block_render_blocks(array($feedback_block)));
        print render($render_array);
        ?>
      </div>
    </li>
    <li>
      <div class="sbac-favorites-menu">
      <?php
        $favorites_count = sbac_favorites_get_count($user->uid);
        $text = t('Favorites');
        if (!$favorites_count) {
          $favorites_count = 0;
        }
        $text .= ' (<span>' . $favorites_count . '</span>)';
        echo l($text, 'user', array(
          'html' => TRUE,
          'fragment' => 'profile-favorites',
        ));
        echo '<div class="sbac-favorites-menu-tooltip f-dropdown right" style="display:none;">Added to Favorites</div>';
      ?>
      </div>
    </li>
    <li>
      <?php if ($help_dropdown) :?>
        <?php print $help_dropdown; ?>
      <?php endif; ?>
    </li>
  </ul>
  <?php endif; ?>
  <?php if ($user->uid && in_array('guest', $user->roles)): ?>
  <ul class="inline-list right user-nav">
    <li class="user-info">
      <a href="/user">Sign In</a>
    </li>
  </ul>
  <?php endif; ?>
</nav>

<div class="top-bar sub-top">
  <nav class="main-nav left">
    <?php if ($main_menu_links && !in_array(SBAC_SHARE_GUEST, $user->roles)) :?>
      <?php print $main_menu_links; ?>
    <?php endif; ?>
  </nav>
</div>
<?php if(!in_array(SBAC_SHARE_GUEST, $user->roles) && ($page['sub-header'] || $page['search'] || $page['toggle'])): ?>
<div class="top-bar last-top">
  <div class="toggle right">
    <?php print render($page['toggle']); ?>
  </div>
<!--   <div class="filter-categories right">
    <a href="#" class="category active">Category</a>
  </div>
  <div class="filter-sort right">
    <a href="#" class="sort">Sort</a>
  </div> -->
  <div class="search right">
    <?php print render($page['search']); ?>
  </div>
  <div><?php print render($page['sub-header']); ?></div>
</div>
<?php if($page['filter']): ?>
<div class="filters sbac-filter-cat-area"<?php /* hide category drawer if cookie */ print sbac_search_hide_category_style(); ?>>
      <?php print render($page['filter']); ?>
</div>
<?php endif; ?>

<?php endif; ?>
<?php if ($site_slogan): ?>
<div class="row">
    <div class="large-12 columns hide-for-small">
      <h2><?php print $site_slogan; ?></h2>
    </div>
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
  <?php if (!empty($page['sidebar_first'])): ?>
    <div id="sidebar-first" class="<?php print $sidebar_first_grid; ?> columns sidebar ">
      <?php print render($page['sidebar_first']); ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($page['sidebar_second'])): ?>
    <div id="sidebar-second" class="<?php print $sidebar_sec_grid;?> columns sidebar">
      <?php print render($page['sidebar_second']); ?>
    </div>
  <?php endif; ?>
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
      <p><?php if ($site_name) :?>
        &copy; <?php print t('Copyright') . ' ' . date('Y'); ?>
      <?php endif; ?></p>
    </div>
    <div class="large-6 small-12 columns">
      <?php
        if(!empty($page['bottom_menu'])) {
          print render($page['bottom_menu']);
        }
      ?>
      <?php if ($user && !in_array(SBAC_SHARE_GUEST, $user->roles)) : ?>
      <ul class="footer-links inline-list right">
        <li>
          <?php if (user_is_logged_in() && !in_array('guest', $user->roles)) : ?>
          <div class="footer-help">
            <a class="help help-dropdown-footer" data-dropdown="drop2" href="#"><span class="sbac-question"></span> Help</a>
            <ul id="drop2" class="f-dropdown" data-dropdown-content>
              <li><a href="#helpmodal" class="help-modal">Welcome Tutorial</a></li>
              <li><?php print l(t('Glossary'), 'glossary', array('absolute' => TRUE)); ?></li>
              <li><a href="help-topics">Help Topics</a></li>
            </ul>
          </div>
          <?php endif; ?>
        </li>
        <li><a class="terms-and-conditions" href="/terms-of-service">Terms of Service</a></li>
      </ul>
      <?php endif; ?>
    </div>
  </div>
</div>

<?php if (user_is_logged_in()) : ?>
<div style='display:none;'>
  <div id="helpmodal">
    <?php
      if (user_access('administrator') || $user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('help desk', $user->roles)) : ?>
      <div class="sort-link"><a href="/admin/help-topics" class="small button radius">Reorganize Help</a></div>
    <?php endif; ?>
    <center>
      <h2>Welcome to the Smarter Balanced Digital Library</h2>
      <p>The Digital Library is an online, user-friendly, searchable library for educators that contains only high-quality vetted resources. It is interactive and allows educators from member states to use and rate resources and collaborate. To learn more, click through the various welcome tutorials provided below:</p>
    </center>
    <?php print views_embed_view('help_topics','block'); ?>
    <?php $form = drupal_get_form('sbac_help_disable_help');?>
    <?php print drupal_render($form);?>
    </ul>
  </div>
  <div id="resource-help-box">
    <center>
      <h2>You're About to Create a Resource</h2>
    </center>
    <div id= "resource-help-body">
    <?php print views_embed_view('resource_tutorial','resource_tutorial'); ?>
    </div>
    <a class="otherClose button right">Continue</a>
    <a class ="button right secondary backButton" href="#">Cancel</a>
  </div>
  <div id="current-help-topic-modal">
    <a class= "helpBack small button left" >Back</a>
    <center>
      <h2><span id="sbac-help-title">Welcome to the Smarter Balanced Digital Library</span></h2>
    </center>
    <div id= "current-help-topic">
    </div>
    <?php $form = drupal_get_form('sbac_help_disable_help');?>
    <?php print drupal_render($form);?>
  </div>
</div>
<?php endif; ?>
