<div class="categories-container clearfix">
  <?php ($cf_value ? $hide_filters = 'js-hide' : $hide_filters = 'js-show'); ?>
  <div class="categories-filter clearfix slideable <?php print $hide_filters; ?>" <?php print sbac_search_hide_category_style(); ?> >
    <?php
    $count = 1;
    $total_cols = 3;
    $cols = 3;
    $category_count = count($categories);
    $mod = ceil($category_count / $cols);
    foreach ($categories as $category_name => $category) {
      // Initialize the loop.
      if ($count == 1) {
        echo '<div class="category-filter-name column large-4">';
        echo '<ul>';
      }

      // Added a different type of entry.
      if (isset($category['link'])) {
        echo '<li><div class="sbac-search-filter-custom-link">' . $category['link'] . '</div></li>';
      }
      else {
        echo '<li><div class="sbac-search-filter-name" vid="' . $category_name . '">' . $category['display_name'];
        // The choices per vocabulary.
        echo '<div class="categories-filter-choices">';
        echo '<div vid="' . $category_name . '" class="clearfix category-filter-list category-filter-list-' . $category_name . ' ' . strtolower($category['display_name']) . '">';
        echo '<h2 class="category-filter-header">' . $category['display_name'] . '<i class="gen-enclosed foundicon-remove right"></i></h2>';
        echo '<ul>';
        $i = 0;
        foreach ($category['terms'] as $term) {
          $class = '';
          if (strpos($cf_value, $category_name . ':' . $i) !== FALSE) {
            $class = ' current ';
          }
          echo '<li class="category-filter category-filter-' . $category_name . '-' . $i . ' ' . $class . '" vid="' . $category_name . '" tid="' . $i . '"><span class="highlight"></span><span class="filter-name ' . $class . '" vid="' . $category_name . '" tid="' . $i . '">' . $term . '</span></li>';
          $i++;
        }
        echo '</ul>';
        echo '</div>';
        echo '</div>';
        echo '</div></li>';
      }


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
