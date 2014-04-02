<div class='row digital-library'>
  <?php if ($smart_search_welcome) : ?>
    <?php print $smart_search_welcome; ?>
  <?php endif; ?>
  <?php if ($no_results) : ?>
  <div class="no-results">
    <?php echo $no_results; ?>
    <a href="/digital-library-resources" class="button">Browse All Resources</a>
  </div>
  <?php endif; ?>
  <div class='column large-12'>
      <?php print $digital_library_output; ?>
  </div>
</div>
