(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Click functionality of the categories.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_forum_js_filter_categories = {
    attach: function (context, settings) {
      $('#views-exposed-form-forum-list-block-2').hide();
      $('#views-exposed-form-forum-list-block-3').hide();

      $(document).click(function() {
        if (!$(this).hasClass('selectedDiv')) {
          var selectedDiv = $('.selectedDiv');
          var vid = selectedDiv.attr('vid');
          $('.expanded').removeClass('expanded').addClass('collapsed');
          selectedDiv.hide();
          selectedDiv.removeClass('selectedDiv');
        }
      });

      $('#edit-forum-sort-order').once('searchfilterbutton', function(){
        $(this).click ( function () {
          window.location.hash = '';
        });
      });

      if ($('#sbac-forum-current-filters').val() != '') {
        $('#edit-reset-filters').removeClass('js-hide');
      }
      else {
        $('.category-hide').removeClass('js-hide');
      }

      // Add filter to current filters
      $('.category-filter').once('category-filter-click', function () {
        $(this).click( function() {
          var filter_name = $(this).children('.filter-name');
          var current_filters = $('#sbac-forum-current-filters');
          var reset_filters = $('#edit-reset-filters');
          var search_button = $('#sbac-forum-filter-button');
          if (!filter_name.hasClass('current')) {
            var last_filter = $('.categories-current-filters');
            last_filter.append('<div class="current-filter"><span vid="' + filter_name.attr('vid') + '" tid="' + filter_name.attr('tid') + '" class="filter-name">' + filter_name.html() + '</span></div>');
            filter_name.addClass('current');
            filter_name.parent().addClass('current');

            Drupal.behaviors.sbac_forum_js_remove.attach(context, settings);
            // Add the tid to the filter list
            if (current_filters.val() == '') {
              last_filter.removeClass('noshow');
              current_filters.val(filter_name.attr('vid') + ':' + filter_name.attr('tid'));
            }
            else {
              var filter_tids = current_filters.val();
              filter_tids += '::' + filter_name.attr('vid') + ':' + filter_name.attr('tid');
              current_filters.val(filter_tids);
            }
            reset_filters.removeClass('js-hide');
            search_button.removeClass('js-hide');
            $('.category-hide').addClass('js-hide');
          }
          else {
            var filters = current_filters.val();
            var filters_array = filters.split('::');
            var filters_length = filters_array.length;

            var target_filter = filter_name.attr('vid') + ':' + filter_name.attr('tid');
            var array_pos = filters_array.indexOf(target_filter);

            if (array_pos == 0) {
              var last_filter = $('.categories-current-filters .current-filter:first');
              if (filters_length > 1) {
                target_filter = target_filter + '::';
              }
            }
            else if (array_pos != 0 && array_pos != (filters_length - 1)) {
              var last_filter = $('.categories-current-filters .current-filter:nth-child(' + (array_pos + 1) +')');
              target_filter = '::' + target_filter;
            }
            else if (array_pos == (filters_length - 1)) {
                var last_filter = $('.categories-current-filters .current-filter:last');
                if (filters_length > 1) {
                  target_filter = '::' + target_filter;
                }
              }
            last_filter.remove();

            filter_name.removeClass('current');
            filter_name.parent().removeClass('current');

            if (array_pos != -1) {
              var new_filters = filters.replace(target_filter, '');
              current_filters.val(new_filters);
            }
            else {
              $('.categories-current-filters').addClass('noshow');
              reset_filters.addClass('js-hide');
              search_button.addClass('js-hide');
              current_filters.val('');
            }
          }
          return false;
        });
      });

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
      $('.sbac-forum-filter-name').once('sbac-forum-filter-name-click', function () {
        $(this).click( function (e) {
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
            console.log(style);
            $('.categories-filter.slideable').attr('style', style);
          }
          e.stopPropagation();
          return false;
        });
      });

      // Open / Close the filter list.
      $('#sbac-forum-cat-button').once('sbac-forum-cat-button-click', function () {
        $(this).click( function () {
          // allow open/close category if not on no results page
          close_categories_list();
          $('.filters.sbac-filter-cat-area').show();
          $('.selectedDiv').hide();
          return false;
        });
      });

      // Close the filter list.
      $('#sbac-forum-close-button').once('sbac-forum-close-button-click', function () {
        $(this).click( function () {
          close_categories_list();
          $('.selectedDiv').hide();
          return false;
        });
      });

      // Close the filter list.
      $('.category-hide').once('category-hide-click', function () {
        $(this).click( function () {
          $('.expanded').removeClass('expanded').addClass('collapsed');
          $(this).toggleClass('active');
          close_categories_list();
          $('.selectedDiv').hide();
          return false;
        });
      });

      // Open / Close the filter list.
      close_categories_list = function () {
        var allForumsActive = $('#sbac-forum-sub-nav-form #edit-all-forums').hasClass('is-pressed');
        var slideableItems = $('.slideable');
        if (slideableItems.is(':visible')) {
          if (allForumsActive) {
            $.cookie("sbac-forum-filters-closed", 1);
          }else {
          }
          slideableItems.slideUp('slow');
          $('.sbac-filter-cat-area').removeClass("active");
        }
        else{
          if (allForumsActive) {
            $.cookie("sbac-forum-filters-closed", 0);
          }else {
          }
          slideableItems.slideDown('fast');
          $('.sbac-filter-cat-area').addClass("active");
        }
      }
    }
  };

  /**
   * Handles ajax pager via hash in URL
   *
   * @type {{attach: Function}}
   */
  var ajax_request = null;
  var has_run_once = false;
  var clicked = false;
  var pager_count = 0;
  Drupal.behaviors.sbac_forum_load_more = {
    attach: function (context, settings) {
      // On click, add the hash in the URL.
      $('.pager-next a').once('pager-next-click', function () {
        $(this).click( function() {
          var href = $(this).attr('href');
          var pos = href.indexOf('?');
          if (pos > -1) {
            var query = href.substring(pos);
            var vars = query.split("&");
            for (var i=0;i<vars.length;i++) {
              var pair = vars[i].split("=");
              if (pair[0] == 'page') {
                pager_count = pair[1];
              }
            }
          }
          else {
            pager_count++;
          }
          window.location.hash = 'pager=' + pager_count;
          clicked = true;
        });
      });

      // Move and resize the modalBackdrop on resize of the window
      modalBackdropResize = function(){
        // Get our heights
        var docHeight = $(document).height();
        var docWidth = $(document).width();
        var winHeight = $(window).height();
        if( docHeight < winHeight ) docHeight = winHeight;
        // Apply the changes
        $('#modalBackdrop').css('height', docHeight + 'px').css('width', docWidth + 'px').show();
      };
      $(window).bind('resize', modalBackdropResize);

      var hash = window.location.hash;
      if (hash != '' && !has_run_once && !clicked) {
        if (hash.indexOf('#pager=') > -1) {
          var pager = hash.replace('#pager=', '');
          if (ajax_request == null) {
            if (self.pageYOffset) { // all except Explorer
              var wt = self.pageYOffset;
            } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
              var wt = document.documentElement.scrollTop;
            } else if (document.body) { // all other Explorers
              var wt = document.body.scrollTop;
            }
            // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have a *visible* border below our div
            var docHeight = $(document).height() + 50;
            var docWidth = $(document).width();
            var winHeight = $(window).height();
            var winWidth = $(window).width();
            if( docHeight < winHeight ) docHeight = winHeight;

            // Create CSS attributes
            css = jQuery.extend({
              position: 'absolute',
              left: '0px',
              margin: '0px',
              background: '#000',
              opacity: '.55'
            }, {});

            // Add opacity handling for IE.
            css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';
            var img_location = '/sites/all/themes/custom/SBAC/images/foundation/orbit/loading.gif';
            var img = '<img src="' + img_location + '" alt="Smiley face" height="128" width="128">';
            $('body').append('<div id="modalBackdrop" style="z-index: 1000; display: block;"></div><div id="modalContent" style="z-index: 1001; position: absolute;">' + img + '</div>');
            // Create our content div, get the dimensions, and hide it
            var modalContent = $('#modalContent').css('top','-1000px');
            var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
            var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);
            $('#modalBackdrop').css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
            modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'});

            ajax_request = $.ajax({
              type: 'POST',
              url: "/sbac-forum/load-more",
              data: {'page' : pager},
              success: function(data) {
                // Parse the response
                var response = jQuery.parseJSON(data);
                // Inject the content
                $('.sbac-forum-main-container').prev().remove();
                $('.sbac-forum-main-container').empty();
                $('.sbac-forum-main-container').replaceWith(response.rendered_content);
                // Create fake setting to attach new view_dom_id to handlers.
                var dom_id = 'views_dom_id:' + response.view_dom_id;
                var setting = {};
                setting[dom_id] = {
                  'pager_element' : response.pager_element,
                  'view_args' : response.view_args,
                  'view_base_path' : response.view_base_path,
                  'view_display_id' : response.view_display_id,
                  'view_dom_id' : response.view_dom_id,
                  'view_name' : response.view_name,
                  'view_path' : response.view_path
                };

                // Attach new behavior.
                settings.views.ajaxViews = setting;
                Drupal.attachBehaviors($('.row.digital-library'), settings);
                has_run_once = true;
                $('#modalBackdrop').remove();
                $('#modalContent').remove();
              },
              error: function(data) {
              }
            });
          }
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
      var original_filters = $('#sbac-forum-original-filters').val();
      var $clear_all_div = $('<div id="clear-all"><span>Applied Filters</span></div>');
      var $clear_all_link = $('<a href="/sbac-forum/clear-filters">Clear All</a>');
      $clear_all_div.append($clear_all_link);
      current_filter_clicked = function () {
        var tid = $(this).attr('tid');
        var vid = $(this).attr('vid');
        $.jstree.reference('filter-' + vid).deselect_node(vid + ':' + tid);
        build_current_filters();
        $('#sbac-forum-filter-button').removeClass('js-hide');
        $('#clear-all > span').html('Your selections');
      };

      // build the current filter list
      build_current_filters = function () {
        var $current_filter_div = $('.categories-current-filters');
        $current_filter_div.empty();

        $current_filter_div.append($clear_all_div);
        var $filter_item = $('<div class="filter-type-item"></div>');
        $current_filter_div.append($filter_item);
        // Get all the trees
        var current_filters_array = [];
        $('.jstree').each(function (i, element) {
          var $tree = $.jstree.reference(element.id);
          // get selected terms
          var selected = $tree.get_selected();
          if (selected.length > 0) {
            $current_filter_div.removeClass('noshow');
            $.each(selected, function (i, selected_id) {
              current_filters_array.push(selected_id);
              var parent_id = $tree.get_parent(selected_id);
              if (!$tree.is_selected(parent_id)) {
                var selected_node = $tree.get_node(selected_id);
                var vid = selected_node.li_attr.vid;
                var filter_name = $('#sbac-search-filter-name-' + vid).contents().filter(function () {
                  return this.nodeType == 3;
                }).text();
                var current_search_filter_group_id = 'current-search-filter-name-' + vid;
                if($('#' + current_search_filter_group_id).length){
                  var $current_search_filter_group_div = $('#' + current_search_filter_group_id);
                }
                else {
                  var $current_search_filter_group_div = $('<div id="' + current_search_filter_group_id + '"><h5>' + filter_name + '</h5></div>');
                }
                var changed_class = 'original';
                if (original_filters.indexOf(selected_id) == -1){
                  changed_class = 'changed';
                  $('#sbac-forum-filter-button').removeClass('js-hide');
                  $('#clear-all > span').html('Your selections');
                }
                var $new_filter = $('<div class="current-filter ' + changed_class + '" vid="' + vid + '" tid="' + selected_node.li_attr.tid + '">' + selected_node.li_attr.term + '</div>').click(current_filter_clicked);
                $current_search_filter_group_div.append($new_filter);
                $filter_item.append($current_search_filter_group_div);
              }
            });
          }
        });
        // save the selected filters to the hidden field
        $('#sbac-forum-current-filters').val(current_filters_array.join('::'));
      };

      // initialize all the jstrees
      $('.jstree')
        .on('changed.jstree', build_current_filters)
        .on('deselect_node.jstree', function(){
          $('#sbac-forum-filter-button').removeClass('js-hide');
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
