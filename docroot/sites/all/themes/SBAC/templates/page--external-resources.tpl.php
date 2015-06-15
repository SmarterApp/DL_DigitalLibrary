<?php
global $user;
?>
<!-- Header and Nav -->
<div class="page-wrap">

  <div class="top-bar sub-top">
  <div class="inner-wrap">
    <div class="sbac-external-logo"><h1>Search External Resources</h1></div>
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

  <div class="row main-row">
    <div class="main-container clearfix">
      <div id="main" class="<?php print $main_grid; ?> columns">
        <?php if ($messages): print $messages; endif; ?>
        <a id="main-content"></a>
        <?php print render($page['content']); ?>
      </div>

			<div class="sbac-back-button">
		    <a href='/' title="Back to Smarter Balanced Digital Library">Back to Smarter Balanced Digital Library</a>
		  </div>
    </div>
  </div>
 
</div>

<?php if (user_is_logged_in()) : ?>
  <div style='display:none;'>
    <div id="external-resource-help-box">
      <h2 class="external-resource-help-box-title">Search External Resources</h2>

      <div id="external-resource-help-body">
        <p>You are about to search resources that are outside the Smarter Balanced Digital Library.</p>
        <p>Smarter Balanced does not review or evaluate the quality of these resources.</p>
      </div>
      <a class="button right blue next otherClose">Continue</a>
      <a class="button right gray secondary cancel backButton" href="#">Cancel</a>
    </div>
  </div>
<?php endif; ?>
