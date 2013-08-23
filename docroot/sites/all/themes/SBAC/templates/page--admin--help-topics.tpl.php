<!-- Header and Nav -->
<div class="page-wrap">
<nav class="top-bar main-top clearfix">
  <ul class="title-area">
    <li class="name"><h1><a href="<?php echo url(''); ?>"><img src="<?php echo $logo; ?>" /></a></h1></li>
    <li><li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li></li>
  </ul>
  <h1 class="title left">Digital Library Beta</h1>
  <?php global $user; ?>
  <?php if ($user->uid): ?>
  <ul class="inline-list right user-nav">
    <li class="user-info">
       <a data-dropdown="drop3" href="">
        <?php
          $user_item = user_load($user->uid);

          if (isset($user_item->picture->uri)) {
            echo theme('image_style', array(
              'path' => $user_item->picture->uri,
              'style_name' => 'small',
              'attributes' => array(
                'class'=>'left'
              )
            ));
          }
          echo $user->name;
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
    <li><a data-dropdown="feedback-dropdown" href="#">Feedback</a>
      <div id="feedback-dropdown" class="f-dropdown content small">
      <a id="disable-feedback" class="small right"> x </a>
      <?php
        $feedback_block = block_load('sbac_central','feedback-box');
        $render_array = _block_get_renderable_array(_block_render_blocks(array($feedback_block)));
        print render($render_array);
        ?>
      </div>
    </li>
    <!-- <li>
    <div class="settings-dropdown">
    <a  data-dropdown="drop2" href=""><i class="gen-enclosed foundicon-settings"></i> Setting</a>
      <ul id="drop2" class="f-dropdown" data-dropdown-content>
        <li><?php echo l('Account','user'); ?></li>
      </ul>
    </div>
    </li> -->
    <li>
      <?php if ($help_dropdown) :?>
        <?php print $help_dropdown; ?>
      <?php endif; ?>
    </li>
  </ul>
  <?php endif ; ?>
</nav>

<div class="top-bar sub-top">
  <nav class="main-nav left">
    <?php if ($main_menu_links) :?>
      <?php print $main_menu_links; ?>
    <?php endif; ?>
  </nav>
</div>

<?php if ($site_slogan): ?>
<div class="row">
    <div class="large-12 columns hide-for-small">
      <h2><?php print $site_slogan; ?></h2>
    </div>
</div>
<?php endif; ?>

<div class="row">
  <div class="main-container clearfix">
    <?php
    global $user;
    if (user_access('administrator') || $user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('help desk', $user->roles)) {
        $sections = array();

        $view_help = views_get_view('help_topics');
        $view_help->set_item('page_2');
        $view_help->execute();

        $sections['tab1'] = array(
          'title' => t('Help Topics ('. count($view_help->result) . ') '),
          'content' => '<div id="tab1">' . $view_help->render(). '</div>',
          'disabled' => FALSE,
          'class' => 'tab1 class',
        );

        $welcome_block = "<div id='admin-welcome-tab-message'><h3>Helpful Information
        </h3><p>Welcome Tutorial consists of help topics. You can create a help topic in <a href='/admin/help-topics'>
        help topics tab</a> and mark it for display in Welcome Tutorial.</p></div>";

        $view_welcome = views_get_view('help_topics');
        $view_welcome->set_item('page_4');
        $view_welcome->execute();

        $sections['tab2'] = array(
          'title' => t('Welcome Tutorial ('. count($view_welcome->result) . ') '),
          'content' => '<div id="tab2">' . $welcome_block . $view_welcome->render() . '</div>',
          'disabled' => FALSE,
          'class' => 'tab2 class',
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

</div>
<div class="bottom-bar">
  <div class="row">
    <div class="large-6 columns">
      <a class="left "href="<?php echo url(''); ?>"><img src="<?php echo $logo; ?>" /></a>
      <p><?php if ($site_name) :?>
        &copy; <?php print t('Copyright') . ' ' . date('Y'); ?>
      <?php endif; ?></p>
    </div>
    <div class="large-6 small-12 columns">
      <?php
        if(!empty($page['bottom_menu'])) {
          print render($page['bottom_menu']);
        }
        // $feedback_block = block_load('sbac_central','feedback-box');
        // $render_array = _block_get_renderable_array(_block_render_blocks(array($feedback_block)));
        // print render($render_array);
        //echo '<div class="block-sbac-central-feedback-box">' . block_render('sbac_central','feedback-box', TRUE) . '</div>';
      ?>
      <ul class="footer-links inline-list right">
        <li><a class="terms-and-conditions" href="/terms-of-service">Terms of Service</a></li>
        <li><a class="feedback" href="#">Feedback</a></li>
        <li>
          <div class="footer-help">
            <a class="help help-dropdown-footer" data-dropdown="drop2" href="#"><span class="sbac-question"></span> Help</a>
            <ul id="drop2" class="f-dropdown" data-dropdown-content>
              <li><a href="#helpmodal" class="help-modal">Welcome Tutorial</a></li>
              <li><?php print l(t('Glossary'), 'glossary', array('absolute' => TRUE)); ?></li>
              <li><a href="help-topics">Help Topics</a></li>
            </ul>
          </div>
        </li>
      </ul>
    </div>
    <div style='display:none'>
      <div id="helpmodal">
      <?php
        global $user;
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
  </div>
  </div>
</div>

</div>



