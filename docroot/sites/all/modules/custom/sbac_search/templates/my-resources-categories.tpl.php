<div class="categories-container clearfix">
  <?php ($cf_value ? $class = '' : $class = 'noshow'); ?>
  <?php ($cf_value ? $hide_filters = 'js-hide' : $hide_filters = 'js-show'); ?>
  <div class="categories-filter clearfix slideable <?php print $hide_filters; ?>" <?php print sbac_search_hide_category_style();?> >
    <?php
    $count = 1;
    $total_cols = 3;
    $cols = 3;
    $category_count = count($categories);
    $mod = ceil($category_count / $cols);
    foreach ($categories as $category) {
      // Initialize the loop.
      if ($count == 1) {
        echo '<div class="category-filter-name column large-4">';
        echo '<ul>';
      }
      $category_vid = $category['vocabulary']->vid;
      $display_name = $category['display_name'];
      echo "<li id='filter-header-$category_vid' class='collapsed'><div class='sbac-search-filter-name' id='sbac-search-filter-name-$category_vid' vid='$category_vid'>" . $display_name;
      // The choices per vocabulary.
      echo '<div class="categories-filter-choices">';
      echo "<div vid='$category_vid' class='jstree clearfix category-filter-list category-filter-list-$category_vid " . strtolower($display_name) . "' id='filter-$category_vid'>";
      echo "<h2 class='category-filter-header'>$display_name<i class='gen-enclosed foundicon-remove right'></i></h2>";
      print render($category['tree']);
      echo '</div>';
      echo '</div>';
      echo '</div></li>';


      // Close of the loop.
      if ($count == $mod) {
        // Close the div and reset the variables.
        echo '</ul>';
        echo '</div>';
        $count = 1;
        $cols--;
        $category_count--;
        if ($cols > 0 && $category_count > 0) {
          $mod = ceil($category_count / $cols);
        }
      }
      else {
        // Increment count.
        $count++;
        $category_count--;
      }
    }

    ?>
  </div>
  <?php ($cf_value ? $class = '' : $class = 'noshow'); ?>
  <div class="categories-current-filters clearfix <?php echo $class; ?>" id="sbac-category-current-filters">
    <?php
    if ($cf_html) {
      foreach ($cf_html as $current_filter_html) {
        echo $current_filter_html;
      }
    }
    ?>
  </div>
</div>
