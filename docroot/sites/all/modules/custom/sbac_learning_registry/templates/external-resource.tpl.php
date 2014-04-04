<div class="results-view">
  <div class="feature-message">
    <p>This is a Digital Library experimental feature. Smarter Balanced does not review or evaluate the quality of these resources.</p>
  </div>
  <?php if (!empty($results) && $results != SBAC_LEARNING_REGISTRY_INBLOOM_NO_RESULTS): ?>
    <div class="results">
      <?php print $results; ?>
    </div>
  <?php elseif ($results == SBAC_LEARNING_REGISTRY_INBLOOM_NO_RESULTS): ?>
    <div class="no-result-message">
      <h2>Your search returned no results.</h2>
      <p>Please try a different search term.</p>
    </div>
  <?php else: ?>
    <div class="keyword-search-message">
      <p>You may use the keyword search and filters above to search for external resources that are in the Learning Registry.</p>
      <p>The Learning Registry is a searchable set of external online education-related resources from participating libraries.</p>
    </div>
  <?php endif; ?>
</div>