<?php if ($smart_search_welcome) : ?>
  <?php print $smart_search_welcome; ?>
<?php endif; ?>

<div class='row digital-library <?php echo $pwd; ?>'>
  <?php if ($no_results) : ?>
    <div class="no-results">
      <?php echo $no_results; ?>
      <a href="/digital-library-resources" class="button">Browse All Resources</a>
    </div>
  <?php endif; ?>
  <div class='column large-12'>
    <?php print $digital_library_output; ?>
      <?php if (!$pwd && $pwd_highlights): ?>
        <div class="pwd-highlights-container">
          <div class="pwd-highlights-header">
            <div class="pwd-left">
              <span class="pwd-title">
                Posted with Distinction
              </span>
            </div>
            <div class="pwd-right">
              <?php print $pwd_showhide; ?>
            </div>
          </div>
          <div class="pwd-collapsable">
            <div class="pwd-highlights-cards">
              <?php print $pwd_highlights; ?>
            </div>
            <div class="pwd-footer-link">
              <?php print $pwd_showmore; ?>
            </div>
          </div>
        </div>
      <?php endif; ?>
    <?php if ($pwd): ?>
      <?php print $pwd_showmore; ?>
    <?php endif; ?>
  </div>
</div>
