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
          selectedDiv.hide();
          selectedDiv.removeClass('selectedDiv');
        }
      });

      $('#sbac-forum-filter-button').once('forum-filter-button', function () {
        $(this).click( function() {
          var isEdit = Drupal.settings.sbac_forum.isEdit;

          // The button is in edit state.
          if (isEdit) {
            $('.categories-filter.slideable').slideDown('fast');
            $(this).text(Drupal.t('Apply Filters')).removeClass('is-edit');
            Drupal.settings.sbac_forum.isEdit = 0;
            return false;
          }
          else {
            $('.categories-filter.slideable').slideUp('slow');
            $(this).text(Drupal.t('Edit Filters')).addClass('is-edit');
            Drupal.settings.sbac_forum.isEdit = 1;
          }
        });
      });

      if ($('#sbac-forum-current-filters').val() != '') {
        $('#edit-reset-filters').removeClass('js-hide');
        $('#sbac-forum-filter-button').removeClass('js-hide');
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
      $('.category-filter-header').once('category-filter-header-click', function () {
        $(this).click( function () {
          $(this).hide();
          $(this).removeClass('selectedDiv');
          return false;
        });
      });

      // Open / Close the individual filter lists.
      $('.sbac-forum-filter-name').once('sbac-forum-filter-name-click', function () {
        $(this).click( function (e) {
          var vid = $(this).attr('vid');
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
          var slideableItems = $('.slideable');
          if (slideableItems.is(':visible')) {
            $(this).text(Drupal.t('Show Categories'));
            $(this).toggleClass('active');
          }
          else {
            $(this).text(Drupal.t('Hide Categories'));
            $(this).toggleClass('active');
          }
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
            $.cookie("sbac-forum-my-forum-filters-closed", 1);
          }
          slideableItems.slideUp('slow');
          $('.sbac-filter-cat-area').removeClass("active");
        }
        else{
          if (allForumsActive) {
            $.cookie("sbac-forum-filters-closed", 0);
          }else {
            $.cookie("sbac-forum-my-forum-filters-closed", 0);
          }
          slideableItems.slideDown('fast');
          $('.sbac-filter-cat-area').addClass("active");
        }
      }
    }
  };


  /**
   * When the user removes the filter from the current filters.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_forum_js_remove = {
    attach: function (context, settings) {
      // Remove's the individual filters.
      $('#sbac-category-current-filters .current-filter').once('sbac-category-current-filters-click', function () {
        $(this).click( function() {
          $('.selectedDiv').hide();
          var reset_filters = $('#edit-reset-filters');
          var search_button = $('#sbac-forum-filter-button');
          var current_filters = $('#sbac-forum-current-filters');
          var vid = $(this).children().attr('vid');
          var tid = $(this).children().attr('tid');
          var first_try = '::' + vid + ':' + tid;
          var second_try = vid + ':' + tid;
          if (current_filters.val() != '') {
            var current_filters_string = current_filters.val();
            var pos = current_filters_string.indexOf(first_try);

            if (pos >= 0) {
              var newvalue = current_filters_string.replace(first_try, '');
              current_filters.val(newvalue);
              $(this).remove();
              $('.category-filter-' + vid + '-' + tid).removeClass('current');
            }
            else {
              var pos2 = current_filters_string.indexOf(second_try);
              if (pos2 >= 0) {
                var newvalue = current_filters_string.replace(second_try, '');
                current_filters.val(newvalue);
                $(this).remove();
                $('.category-filter-' + vid + '-' + tid).removeClass('current');
              }
            }

            if (current_filters.val() == '') {
              $('.categories-current-filters').addClass('noshow');
              reset_filters.addClass('js-hide');
              search_button.addClass('js-hide');
              $('.category-hide').text(Drupal.t('Show Categories'));
              $('.category-hide').removeClass('active');
              $('.category-hide').removeClass('js-hide');
              $('.slideable').hide();
              Drupal.settings.sbac_forum.isEdit = 0;
              $('#sbac-forum-filter-button').removeClass('is-edit').text(Drupal.t('Apply Filters'));
              $('#sbac-forum-category-forum-form').submit();
            }
          }
          return false;
        });
      });
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
          pager_count++;
          window.location.hash = 'pager=' + pager_count;
          clicked = true;
        });
      });

      var hash = window.location.hash;
      if (hash != '' && !has_run_once && !clicked) {
        var pager = hash.replace('#pager=', '');
        if (ajax_request == null) {
          ajax_request = $.ajax({
            type: 'POST',
            url: "/sbac-forum/load-more",
            data: {'page' : pager},
            success: function(data) {
              var response = jQuery.parseJSON(data);
              $('.sbac-forum-main-container').prev().remove();
              $('.sbac-forum-main-container').empty();
              $('.sbac-forum-main-container').replaceWith(response.output);
              Drupal.attachBehaviors();
              has_run_once = true;
            },
            error: function(data) {
            }
          });
        }
      }
    }
  };

})(jQuery);
