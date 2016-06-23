<?php
    $count = 1;
    $total_cols = 4;
    $cols = 4;
    $category_count = count($categories);
    $mod = ceil($category_count / $cols);
    ($cf_value ? $hide_filters = 'js-hide' : $hide_filters = 'js-show');
    $i = 0;
?>
<div class="categories-container clearfix">
  <div class="categories-filter clearfix slideable" >
    <?php
    foreach ($categories as $category) {
      // Initialize the loop.
      $i++;
      $class = array();
      $class[] = 'col-' . $i;
      if($i === 1){
        $class[] = 'col-first';
      }
      if($i === $total_cols) {
        $class[] = 'col-last';
      }
      if ($count == 1) {
        echo '<div class="category-filter-name column large-4 ' . implode(' ', $class) .'">';
        echo '<ul>';
      }
      // Added a different type of entry.
      if (isset($category['link']) && !empty($category['vocabulary'])) :
        echo '<li><div class="sbac-search-filter-custom-link">' . $category['link'] . '</div></li>';
      else:
        $category_vid = $category['vocabulary']->vid;
        $display_name = $category['display_name'];
        ?>
        <li id='filter-header-<?php print $category_vid; ?>' class='collapsed'>
          <div class='sbac-search-filter-name' id='sbac-search-filter-name-<?php print $category_vid; ?>' vid='<?php print $category_vid; ?>'>
            <span class="display-name"><?php print $display_name; ?></span>
            <div class="categories-filter-choices">
              <div class='category-filter-list category-filter-list-<?php print $category_vid; ?> vid='<?php print $category_vid;?>'>
                <h2 class='category-filter-header' vid='<?php print $category_vid; ?>'>
                  <i class='gen-enclosed foundicon-remove right'></i>
                </h2>
                <div vid='<?php print $category_vid;?>' class='jstree clearfix <?php print strtolower($display_name); ?>' id='filter-<?php print $category_vid; ?>'>
                  <?php print render($category['tree']);?>
                </div>
              </div>
            </div>
          </div>
        </li>
        <?php 
      endif;

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
  <div class="categories-current-filters clearfix" id="sbac-category-current-filters" style="display: none;">
    <?php
    if ($cf_html) {
      foreach ($cf_html as $current_filter_html) {
        echo $current_filter_html;
      }
    }
    ?>
  </div>
</div>
