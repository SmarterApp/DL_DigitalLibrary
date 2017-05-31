<!-- Header and Nav -->
<div class="page-wrap">
   <nav class="top-bar main-top clearfix">
   <div class="inner-wrap">
  <ul class="title-area">
    <li class="name"><h1><img src="<?php echo $logo; ?>" /></h1></li>
    <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
  </ul>
   <div class="inner-wrap">
</nav>
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
      <div class="left"><img src="<?php echo $logo; ?>" /></div>
      <p><?php if ($site_name) :?>
        &copy; <?php print t('Copyright') . ' ' . date('Y'); ?>
      <?php endif; ?></p>
    </div>
    <div class="large-6 small-12 columns">
    </div>
  </div>
</div>
