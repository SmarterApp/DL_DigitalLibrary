<div class='row digital-library'>
<?php //if (isset($_SESSION['sbac_search_count']) && !$_SESSION['sbac_search_count']): ?>
<!--<div class="no-results">-->
<!--<h3>Your search for -->
<?php //echo (isset($_SESSION['sbac-search-keywords']) && $_SESSION['sbac-search-keywords'] ? '"' . $_SESSION['sbac-search-keywords'] . '"' : ''); ?><!-- -->
<!--returned no results.</h3>-->
<!--<p>Please try a different search term or browse any of the resources below that -->
<!--have been identified for you using the subject(s) and grade(s) in your profile.</p>-->
<!--<a href="#" class="button">Browse All Resources</a>-->
<!--</div>-->
<?php //endif; ?>
<div class='column large-12'>
    <?php print $resource_layout_view; ?>
</div>
</div>
