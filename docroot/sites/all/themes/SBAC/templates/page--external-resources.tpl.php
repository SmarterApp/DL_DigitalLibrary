<?php
global $user;
?>
<!-- Header and Nav -->
<div class="page-wrap">

  <div class="top-bar sub-top">
    <div class="sbac-external-logo"><h1>Search External Resources</h1></div>
    <?php if (isset($page['search']) && $page['search']): ?>
      <div class="search right">
        <?php print render($page['search']); ?>
      </div>
    <?php endif; ?>
  </div>

  <?php if (!in_array(SBAC_SHARE_GUEST, $user->roles) && $page['filter']): ?>
    <div class="filters sbac-filter-cat-area"<?php /* hide category drawer if cookie  print sbac_search_hide_category_style();*/ ?>>
      <?php print render($page['filter']); ?>
    </div>
  <?php endif; ?>

  <div class="row main-row">
    <div class="main-container clearfix">
      <div id="main" class="<?php print $main_grid; ?> columns">
        <?php if ($messages): print $messages; endif; ?>
        <a id="main-content"></a>
        <?php print render($page['content']); ?>
      </div>
    </div>
  </div>
  <div class="sbac-back-button">
    <a href='/'>Back to Smarter Balanced Digital Library</a>
  </div>
</div>
