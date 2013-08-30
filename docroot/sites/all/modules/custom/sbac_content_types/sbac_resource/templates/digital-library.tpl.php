<div class='row digital-library'>
  <?php if ($no_results) : ?>
  <div class="no-results">
    <h3>Your search for
    <?php echo '"' . $search_string . '"'; ?>
    returned no results.</h3>
    <p>Please try a different search term or browse any of the resources below that
    have been identified for you using the subject(s) and grade(s) in your profile.</p>
    <a href="/digital-library-resources" class="button">Browse All Resources</a>
  </div>
  <?php endif; ?>
  <div class='column large-12'>
      <?php print $resource_layout_view; ?>
  </div>
</div>
