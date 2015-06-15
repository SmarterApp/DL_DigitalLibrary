(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};
  /**
   * Click functionality of the categories.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_search_categories = {
    attach: function (context, settings) {
      $('.sbac-hover').hover(
        function() {
          $(this).next('ul').addClass('open');
        },
        function() {
          $(this).next('ul').removeClass('open');
        }
      );

      $('#edit-dl-sort-order').once('searchfilterbutton', function(){
        $(this).click ( function () {
          window.location.hash = '';
        });
      });

      $(document).click(function () {
        if (!$(this).hasClass('selectedDiv')) {
          var selectedDiv = $('.selectedDiv');
          var vid = selectedDiv.attr('vid');
          $('.expanded').removeClass('expanded').addClass('collapsed');
          selectedDiv.hide();
          selectedDiv.removeClass('selectedDiv');
        }
      });

      if ($('#sbac-search-current-filters').val() != '') {
        $('#edit-reset-filters').removeClass('js-hide');
      }
      else {
        $('.category-hide').removeClass('js-hide');
        $('.category-hide').show();
      }

      // Close the individual filter list.
      $('.category-filter-header').once('cmod-catfilterheader', function() {
        $('.category-filter-header').click( function () {
          var vid = $(this).attr('vid');
          $('.category-filter-list').hide();
          $('.category-filter-list').removeClass('selectedDiv');
          $('#filter-header-' + vid).removeClass('expanded');
          $('#filter-header-' + vid).addClass('collapsed');
          return false;
        });
      });

      // Open / Close the individual filter lists.
      $('.sbac-search-filter-name').once('cmod-searchfiltername', function() {
        $('.sbac-search-filter-name').click( function (e) {
          var vid = $(this).attr('vid');
          $('.expanded').removeClass('expanded').addClass('collapsed');
          $('#filter-header-' + vid).removeClass('collapsed').addClass('expanded');
          $('.category-filter-list').hide();
          $('.category-filter-list-' + vid).show();
          $('.category-filter-list-' + vid).addClass('selectedDiv');
          // Added to remove the overflow issue on Chrome and Safari.
          var style = $('.categories-filter.slideable').attr('style');
          if (style !== undefined) {
            style = style.replace('overflow: hidden');
            $('.categories-filter.slideable').attr('style', style);
          }
          e.stopPropagation();
          return false;
        });
      });

      // Open / Close the filter list.
      $('#sbac-search-cat-button').once('cmod-searchcatbutton', function() {
        $('#sbac-search-cat-button').click( function () {
          // allow open/close category if not on no results page
          close_categories_list();
          $('.filters.sbac-filter-cat-area').show();
          $('.selectedDiv').hide();
          return false;
        });
      });

      // Close the filter list.
      $('#sbac-search-close-button').once('cmod-searchclosebutton', function() {
        $('#sbac-search-close-button').click( function () {
          close_categories_list();
          $('.selectedDiv').hide();
          return false;
        });
      });

      // Close the filter list.
      $('.category-hide').once('cmod-cathide', function () {
        $('.category-hide').click(function () {
          $('.expanded').removeClass('expanded').addClass('collapsed');
          $(this).toggleClass('active');
          close_categories_list();
          $('.selectedDiv').hide();
          return false;
        });
      });

      // Open / Close the filter list.
      close_categories_list = function () {
        var slideableItems = $('.slideable');
        if (slideableItems.is(':visible')) {
          slideableItems.slideUp('slow');
          $('.sbac-filter-cat-area').removeClass("active");
        }
        else{
          slideableItems.slideDown('fast');
          $('.sbac-filter-cat-area').addClass("active");
        }
      }
    }
  };
})(jQuery);

/**
 * jstree requires jQuery 1.9 and above so we are using jQuery 1.9.0 here
 */
(function ($) {
  Drupal.behaviors.sbac_search_filters = {
    attach: function (context, settings) {

      var original_filters = $('#sbac-search-original-filters').val();
      var $clear_all_div = $('<div id="clear-all"><span>Applied Filters</span></div>');
      var $clear_all_link = $('<a href="sbac-search/clear-all?location=digital-library-resources">Clear All</a>');
      $clear_all_div.append($clear_all_link);
      current_filter_clicked = function () {
        var tid = $(this).attr('tid');
        var vid = $(this).attr('vid');
        $.jstree.reference('filter-' + vid).deselect_node(vid + ':' + tid);
        build_current_filters();
        $('#sbac-search-filter-button').removeClass('js-hide');
        $('#clear-all > span').html('Your selections');
      };

      // build the current filter list
      build_current_filters = function () {
        var $filter_item = $('<div class="filter-type-item"></div>');
        $('.sbac-search-filter-name').removeClass('filters-selected');
        // Get all the trees
        var current_filters_array = [];
        $('.jstree').each(function (i, element) {
          var $tree = $.jstree.reference(element.id);
          // get selected terms
         var selected = $tree.get_selected();
          if (selected.length > 0) {
            // Show the buttons
            
            $.each(selected, function (i, selected_id) {
              current_filters_array.push(selected_id);
              var parent_id = $tree.get_parent(selected_id);
              if (!$tree.is_selected(parent_id)) {
                var selected_node = $tree.get_node(selected_id);
                var vid = selected_node.li_attr.vid;
                $('#sbac-search-filter-name-'+vid).addClass('filters-selected');
              }
            });
          }
        });
        // save the selected filters to the hidden field
        $('#sbac-search-current-filters').val(current_filters_array.join('::'));
      };

      // initialize all the jstrees
      $('.jstree')
        .on('changed.jstree', build_current_filters)
        .on('deselect_node.jstree', function(){
          $('#sbac-search-filter-button').removeClass('js-hide');
          $('#clear-all > span').html('Your selections');
        })
        .jstree({
          "plugins": ["checkbox"]
        });

      // look at the current filters and select the jstree values (because initially the tree will be empty, we are just repopulating according to the current filters)
      $('#sbac-category-current-filters .current-filter').each(function(i, value) {
        var vid = $(value).attr('vid');
        var tid = $(value).attr('tid');
        var node_id = vid + ':' + tid;
        var this_tree = $.jstree.reference('filter-' + vid);
        var name = $(value).text();
        var node = {
          'text': name,
          'id': node_id,
          'li_attr': {
            'tid': tid,
            'vid': vid,
            'term': name
          },
          'state': {
            'selected': true
          }
        };
        if (this_tree) {
          // if the tree exists then select the node
          this_tree.select_node(node_id);
          if (!this_tree.is_selected(node_id)) {
            // if the node doesn't exist, then create it and select it
            this_tree.create_node('#', node);
          }
        }
        else {
          // if the tree doesn't exist then create it
          var tree_id = 'filter-' + vid;
          var $temp = $('#' + tree_id).length ? $('#' + tree_id) : $('<div id="' + tree_id + '" class="jstree js-hide"></div>');
          $('.categories-container').append($temp);
          $temp
            .on('changed.jstree', build_current_filters)
            .jstree({'core': {'check_callback': true}, "plugins": ["checkbox"]});
          // and create the node
          $.jstree.reference(tree_id).create_node('#', node)
        }
      });

      build_current_filters();

    }
  };

})(jq190);