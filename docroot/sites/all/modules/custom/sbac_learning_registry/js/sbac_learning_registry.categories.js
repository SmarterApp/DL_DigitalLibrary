(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Click functionality of the categories.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_learning_registry_categories = {
    attach: function (context, settings) {
      $(document).click(function() {
        if (!$(this).hasClass('selectedDiv')) {
          var selectedDiv = $('.selectedDiv');
          selectedDiv.hide();
          selectedDiv.removeClass('selectedDiv');
        }
      });

      $('#sbac-search-filter-button').once('searchfilterbutton', function(){
        $('#sbac-search-filter-button').click(function() {
          var isEdit = Drupal.settings.sbac_learning_registry.isEdit;

          // The button is in edit state.
          if (isEdit) {
            $('.categories-filter.slideable').slideDown('fast');
            $(this).text(Drupal.t('Apply Filters')).removeClass('is-edit');
            Drupal.settings.sbac_learning_registry.isEdit = 0;
            return false;
          }
          else {
            $('.categories-filter.slideable').slideUp('slow');
            $(this).text(Drupal.t('Edit Filters')).addClass('is-edit');
            Drupal.settings.sbac_learning_registry.isEdit = 1;
          }
        });
      });

      if ($('#sbac-search-current-filters').val() != '') {
        $('#edit-reset-filters').removeClass('js-hide');
        $('#sbac-search-filter-button').removeClass('js-hide');
      }
      else {
        $('.category-hide').removeClass('js-hide');
      }

      // Add filter to current filters. Wrap in 'once' so ctools modal dosnt attach click handler multiple times.
      $('.category-filter').each(function() {
        $(this).once('cmod-catfilter', function() {
          $(this).click(function () {
            var filter_name = $(this).children('.filter-name');
            var current_filters = $('#sbac-search-current-filters');
            var reset_filters = $('#edit-reset-filters');
            var search_button = $('#sbac-search-filter-button');
            if (!filter_name.hasClass('current')) {
              var last_filter = $('.categories-current-filters');
              last_filter.append('<div class="current-filter"><span vid="' + filter_name.attr('vid') + '" tid="' + filter_name.attr('tid') + '" class="filter-name">' + filter_name.html() + '</span></div>');
              filter_name.addClass('current');
              filter_name.parent().addClass('current');
              Drupal.behaviors.sbac_remove_categories.attach(context, settings);
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
              var last_filter = $('.categories-current-filters .current-filter:last');
              last_filter.remove();
              filter_name.removeClass('current');
              filter_name.parent().removeClass('current');

              // Remove the tid to the filter list
              var filters = current_filters.val();
              var pos = filters.lastIndexOf("::");
              if (pos != -1) {
                var new_filters = filters.substr(0, pos);
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
          }); // End click
        }); // End once
      }); // End each


      // Close the individual filter list.
      $('.category-filter-header').once('cmod-catfilterheader', function() {
        $('.category-filter-header').click( function () {
          $('.category-filter-list').hide();
          $('.category-filter-list').removeClass('selectedDiv');
          return false;
        });
      });

      // Open / Close the individual filter lists.
      $('.sbac-search-filter-name').once('cmod-searchfiltername', function() {
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
      $('.category-hide').once('cmod-cathide', function() {
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
      });

      // Open / Close the filter list.
      close_categories_list = function () {
        var slideableItems = $('.slideable');
        if (slideableItems.is(':visible')) {
          $.cookie("sbac-digital-library-filters-closed", 1);
          slideableItems.slideUp('slow');
          $('.sbac-filter-cat-area').removeClass("active");
        }
        else{
          $.cookie("sbac-digital-library-filters-closed", 0);
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
  Drupal.behaviors.sbac_remove_categories = {
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
            Drupal.settings.sbac_learning_registry.isEdit = 0;
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
  Drupal.behaviors.sbac_clear_all_categories = {
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
      window.location.href = 'external-resources/clear-all';
      return false;
    }
  };

  /**
   * Clears all current filters.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_learning_registry_textbox = {
    attach: function (context, settings) {
      // Moves the text into the hidden field.
      $('#sbac-search-textbox').keypress( function(event) {
        var keypressed = event.which;
        if(keypressed == 13){
          $('#sbac-search-keywords').val($(this).val());
          $('#sbac-search-filter-button').click();
          return false;
        }
      });

      // Moves the text into the hidden field.
      $('#sbac-search-textbox').change( function(event) {
        $('#sbac-search-keywords').val($(this).val());
      });

      // Hide the Keyword field.
      $('#views-exposed-form-resources-grid-view').hide();
      $('#views-exposed-form-resources-list-view').hide();

      if ($('#edit-solr-keywords').val() != '') {
        $('.form-item-solr-keywords').append('<span class="sbac-clear-search"></span>');
      }

      $('.pager-next a').html('Load More Resources').addClass('button');
    }
  };

  Drupal.behaviors.sbac_learning_registry_clear = {
    attach: function (context, settings) {
      $('.sbac-clear-search').click( function() {
        window.location.href = 'external-resources/clear-all';
      });
    }
  };

  /**
   * Reattach the ajax for the load more button
   */
  $(document).ajaxComplete(function(){
    Drupal.attachBehaviors($('.load-more'));
  });
})(jQuery);
