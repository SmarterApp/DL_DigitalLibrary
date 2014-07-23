(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Click functionality of the categories.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_review_categories = {
    attach: function (context, settings) {
      $('.sbac-hover').hover(
        function() {
          $(this).next('ul').addClass('open');
        },
        function() {
          $(this).next('ul').removeClass('open');
        }
      );

      $(document).click(function() {
        if (!$(this).hasClass('selectedDiv')) {
          var selectedDiv = $('.selectedDiv');
          selectedDiv.hide();
          selectedDiv.removeClass('selectedDiv');
        }
      });

      $('#sbac-search-filter-button').click(function() {
        var isEdit = Drupal.settings.sbac_search.isEdit;

        // The button is in edit state.
        if (isEdit) {
          $('.categories-filter.slideable').slideDown('fast');
          $(this).text(Drupal.t('Apply Filters')).removeClass('is-edit');
          Drupal.settings.sbac_search.isEdit = 0;
          return false;
        }
        else {
          $('.categories-filter.slideable').slideUp('slow');
          $(this).text(Drupal.t('Edit Filters')).addClass('is-edit');
          Drupal.settings.sbac_search.isEdit = 1;
        }
      });

      if ($('#sbac-search-current-filters').val() != '') {
        $('#edit-reset-filters').removeClass('js-hide');
        $('#sbac-search-filter-button').removeClass('js-hide');
      }
      else {
        $('.category-hide').removeClass('js-hide');
      }

      // Add filter to current filters
      $('.category-filter').click(function () {
        var filter_name = $(this).children('.filter-name');
        var current_filters = $('#sbac-search-current-filters');
        var reset_filters = $('#edit-reset-filters');
        var search_button = $('#sbac-search-filter-button');
        if (!filter_name.hasClass('current')) {
          var last_filter = $('.categories-current-filters');
          last_filter.append('<div class="current-filter"><span vid="' + filter_name.attr('vid') + '" tid="' + filter_name.attr('tid') + '" class="filter-name">' + filter_name.html() + '</span></div>');
          filter_name.addClass('current');
          filter_name.parent().addClass('current');
          Drupal.behaviors.sbac_resource_review_remove.attach(context, settings);
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

      // Close the individual filter list.
      $('.category-filter-header').click( function () {
        $('.category-filter-list').hide();
        $('.category-filter-list').removeClass('selectedDiv');
        return false;
      });

      // Open / Close the individual filter lists.
      $('.sbac-search-filter-name').click( function (e) {
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

      // Open / Close the filter list.
      $('#sbac-search-cat-button').click( function () {
        // allow open/close category if not on no results page
        close_categories_list();
        $('.filters.sbac-filter-cat-area').show();
        $('.selectedDiv').hide();
        return false;
      });

      // Close the filter list.
      $('#sbac-search-close-button').click( function () {
        close_categories_list();
        $('.selectedDiv').hide();
        return false;
      });

     // Close the filter list.
      $('.category-hide').click( function () {
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

      // Open / Close the filter list.
      close_categories_list = function () {
        var slideableItems = $('.slideable');
        if (slideableItems.is(':visible')) {
          $.cookie("sbac-resource-review-filters-closed", 1);
          slideableItems.slideUp('slow');
          $('.sbac-filter-cat-area').removeClass("active");
        }
        else{
          $.cookie("sbac-resource-review-filters-closed", 0);
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
  Drupal.behaviors.sbac_resource_review_remove = {
    attach: function (context, settings) {
      // Remove's the individual filters.
      $('#sbac-category-current-filters .current-filter').click( function() {
        $('.selectedDiv').hide();
        var reset_filters = $('#edit-reset-filters');
        var search_button = $('#sbac-search-filter-button');
        var current_filters = $('#sbac-search-current-filters');
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
            Drupal.settings.sbac_search.isEdit = 0;
            $('#sbac-search-filter-button').removeClass('is-edit').text(Drupal.t('Apply Filters'));
          }
        }
        return false;
      });
    }
  };

  /**
   * Clears all current filters.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_review_clear_all = {
    attach: function (context, settings) {
      // Removes all individual filters.
      $('.categories-clear-all-button').click(this.clearAllCategories);
      $('#edit-reset-filters').click(this.clearAllCategories);
    },

    clearAllCategories: function() {
      var current_filters = $('#sbac-search-current-filters');
      $('.categories-current-filters').addClass('noshow');
      $('#sbac-category-current-filters .current-filter').remove();
      $('.category-filter-list ul li').removeClass('current');
      current_filters.val('');
      $('.selectedDiv').hide();
      $('.category-hide').removeClass('js-hide');
      window.location.href = 'sbac-search/clear-all?location=resource-review';
      return false;
    }
  };

  /**
   * Clears all current filters.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_review_textbox = {
    attach: function (context, settings) {
      // Moves the text into the hidden field.
      $('.sbac-search-textbox').keypress( function(event) {
        var keypressed = event.which;
        if(keypressed == 13){
          $('#sbac-search-keywords').val($(this).val());
          $('#sbac-search-filter-button').click();
          return false;
        }
      });
      // Moves the text into the hidden field.
      $('.sbac-search-textbox').change( function(event) {
        $('#sbac-search-keywords').val($(this).val());
      });

      // Hide the Keyword field.
      $('#views-exposed-form-resource-review-grid-view').hide();
      $('#views-exposed-form-resource-review-list-view').hide();

      // Hide the Keyword field.
      $('#views-exposed-form-all-resource-review-grid-view').hide();
      $('#views-exposed-form-all-resource-review-list-view').hide();


      if ($('.sbac-search-textbox').val() != '') {
        $('.form-item-search-block-form').append('<span class="sbac-clear-search"></span>');
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
  Drupal.behaviors.sbac_search_load_more = {
    attach: function (context, settings) {
      // Change the button text
      $('.pager-next a').html('Show More Resources').addClass('button');

      // On click, add the hash in the URL.
      $('.pager-next a').click( function() {
        pager_count++;
        window.location.hash = 'pager=' + pager_count;
        clicked = true;
      });

      var hash = window.location.hash;
      if (hash != '' && !has_run_once && !clicked) {
        var pager = hash.replace('#pager=', '');
        if (ajax_request == null) {
          ajax_request = $.ajax({
            type: 'POST',
            url: "/sbac-resource/load-more",
            data: {'view' : 'resource_review', 'page' : pager},
            success: function(data) {
              ajax_request = null;
              var response = jQuery.parseJSON(data);
              $('.row.digital-library').empty().append(response.output);
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

  Drupal.behaviors.sbac_resource_review_clear = {
    attach: function (context, settings) {
      $('.sbac-clear-search').click( function() {
        window.location.href = 'sbac-search/clear-all?location=resource-review';
      });
    }
  };

})(jQuery);
