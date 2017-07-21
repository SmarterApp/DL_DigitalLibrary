<!-- Header and Nav -->
<div class="page-wrap">
   <nav class="top-bar main-top clearfix">
   <div class="inner-wrap">
  <ul class="title-area">
    <li class="name"><h1>
        <a title="Smarter Balanced Assessment Consortium" href="<?php echo $home_url; ?>">
          <img src="<?php echo $logo; ?>" alt="Smarter Balanced Assessment Consortium Logo" />
        </a>
      </h1></li>
    <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
  </ul>
  <?php if ($user->uid && !in_array('guest', $user->roles)): ?>
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
          <li><?php echo l('Account', 'user', array('attributes' => array('title' => 'Account'))); ?></li>
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
  <?php endif ; ?>
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
    <?php if ($main_menu_links && !in_array(SBAC_SHARE_GUEST, $user->roles)) : ?>
      <?php print $main_menu_links; ?>
    <?php endif; ?>
  </nav>
  <?php if (isset($page['search']) && $page['search']): ?>
    <div class="search right">
      <?php print render($page['search']); ?>
    </div>
<?php endif; ?>
</div>

<?php if (!in_array(SBAC_SHARE_GUEST, $user->roles) && $page['filter']): ?>
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

<?php if (!in_array(SBAC_SHARE_GUEST, $user->roles) && ($page['sub-header'] || $page['toggle'])): ?>
  <div class="top-bar last-top">
    <div class="toggle right">
      <?php print render($page['toggle']); ?>
    </div>
    <div><?php print render($page['sub-header']); ?></div>
  </div>
<?php endif; ?>


<div class="row main-row">
  <div class="main-container clearfix">
    <?php
    global $user;
    if ($user->uid == 1 || array_intersect(array('DLRB member', 'help desk', 'administrator'), $user->roles)) {
        $sections = array();

        // Featured Resources
        $view_feature = views_get_view('featured_content');
        $view_feature->set_display('page');
        $view_feature->execute();

        $sections['tab1'] = array(
          'title' => t('Featured ('. count($view_feature->result) . ') '),
          'content' => '<div id="tab1">' . $view_feature->render(). '</div>',
          'disabled' => FALSE,
          'class' => 'tab1 class',
          'no-ajax' => TRUE,
          'section_loaded' => 'section-loaded',
        );

        // Help Topics
        $view_help = views_get_view('help_topics');
        $view_help->set_display('page_2');
        $view_help->execute();

        $sections['tab2'] = array(
          'title' => t('Help Topics ('. count($view_help->result) . ') '),
          'content' => '<div id="tab2">' . $view_help->render(). '</div>',
          'disabled' => FALSE,
          'class' => 'tab1 class',
          'no-ajax' => TRUE,
          'section_loaded' => 'section-loaded',
        );

        $welcome_block = "<div id='admin-welcome-tab-message'>
            <h3>Helpful Information </h3>
            <p>Welcome Topics are the three help items displayed on the landing page.</p>
            <p>You must remove exising items to allow room for new items</p>
            <p>You can add new items by editing Help Topics</p>
          </div>";

        // Welcome Help Topics
        $view_welcome = views_get_view('help_topics');
        $view_welcome->set_display('page_4');
        $view_welcome->execute();

        $sections['tab3'] = array(
          'title' => t('Welcome Topics ('. count($view_welcome->result) . ') '),
          'content' => '<div id="tab3">' . $welcome_block . $view_welcome->render() . '</div>',
          'disabled' => FALSE,
          'class' => 'tab2 class',
          'no-ajax' => TRUE,
          'section_loaded' => 'section-loaded',
        );
        print theme('sections', array(
          'sections' => $sections,
          'name' => 'topics',
        ));
    }
    else {
        print "<div id='main' class='large-12 columns'>
        <h1 id='page-title' class='title'>Access denied</h1>
        You are not authorized to access this page.
        </div>";
    }
    ?>
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
          <?php if (isset($help_dropdown_footer)) : ?>
            <?php echo $help_dropdown_footer; ?>
          <?php endif; ?>
        </li>
        <li><a title="Terms of Service" class="terms-and-conditions" href="/terms-of-service">Terms of Service</a></li>
      </ul>
      <?php endif; ?>
    </div>
  </div>
  </div>
