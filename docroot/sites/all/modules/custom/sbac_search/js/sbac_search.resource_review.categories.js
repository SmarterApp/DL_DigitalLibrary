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

      $('#edit-rr-sort-order').once('searchfilterbutton', function(){
        $(this).click ( function () {
          window.location.hash = '';
        });
      });

      $(document).click(function () {
        if (!$(this).hasClass('selectedDiv')) {
          var selectedDiv = $('.selectedDiv');
          selectedDiv.hide();
          selectedDiv.removeClass('selectedDiv');
        }
      });

      $('#sbac-search-filter-button').once('searchfilterbutton', function () {
        $(this).click(function () {
          var isEdit = Drupal.settings.sbac_search.isEdit;

          // The button is in edit state.
          if (isEdit) {
            $('.categories-filter.slideable').slideDown('fast');
            $('.category-hide').show();
            $(this).text(Drupal.t('Apply Filters')).removeClass('is-edit');
            Drupal.settings.sbac_search.isEdit = 0;
            return false;
          }
          else {
            $('.categories-filter.slideable').slideUp('slow');
            $('.category-hide').hide();
            $(this).text(Drupal.t('Edit Filters')).addClass('is-edit');
            Drupal.settings.sbac_search.isEdit = 1;
          }
        });
      });

      if ($('#sbac-search-current-filters').val() != '') {
        $('#edit-reset-filters').removeClass('js-hide');
        $('#sbac-search-filter-button').removeClass('js-hide');
      }
      else {
        $('.category-hide').removeClass('js-hide');
        $('.category-hide').show();
      }

      // Add filter to current filters. Wrap in 'once' so ctools modal dosnt attach click handler multiple times.
      $('.category-filter').each(function () {
        $(this).once('cmod-catfilter', function () {
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
              else {
                if (array_pos != 0 && array_pos != (filters_length - 1)) {
                  var last_filter = $('.categories-current-filters .current-filter:nth-child(' + (array_pos + 1) + ')');
                  target_filter = '::' + target_filter;
                }
                else {
                  if (array_pos == (filters_length - 1)) {
                    var last_filter = $('.categories-current-filters .current-filter:last');
                    if (filters_length > 1) {
                      target_filter = '::' + target_filter;
                    }
                  }
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
      });

      // Close the individual filter list.
      $('.category-filter-header').once('cmod-catfilterheader', function () {
        $('.category-filter-header').click(function () {
          $('.category-filter-list').hide();
          $('.category-filter-list').removeClass('selectedDiv');
          return false;
        });
      });

      // Open / Close the individual filter lists.
      $('.sbac-search-filter-name').once('cmod-searchfiltername', function () {
        $('.sbac-search-filter-name').click(function (e) {
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
      // Open / Close the filter list.
      $('#sbac-search-cat-button').once('cmod-searchcatbutton', function () {
        $('#sbac-search-cat-button').click(function () {
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
      $('#sbac-category-current-filters .current-filter').once('cmod-cathide', function() {
        $('#sbac-category-current-filters .current-filter').click(function () {
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
              $('#sbac-search-filter-button').removeClass('is-edit').text(Drupal.t('Apply Filters'));
              Drupal.settings.sbac_search.isEdit = 0;
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
              $('#sbac-search-resource-review-form').submit();
            }
          }
          return false;
        });
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
      current_filters.val('');
      $('.slideable').hide();
      $('.category-hide').hide();
      Drupal.settings.sbac_search.isEdit = 0;
      $('#sbac-search-resource-review-form').submit();
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
  var pager_count = 0;
  Drupal.behaviors.sbac_search_load_more = {
    attach: function (context, settings) {
      // Change the button text
      $('.pager-next a').html('Show More Resources').addClass('button');

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
        var winWidth = $(window).width();
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
            var img_location = '/sites/all/themes/SBAC/images/foundation/orbit/loading.gif';
            var img = '<img src="' + img_location + '" alt="Smiley face" height="42" width="42">';
            $('body').append('<div id="modalBackdrop" style="z-index: 1000; display: block;"></div><div id="modalContent" style="z-index: 1001; position: absolute;">' + img + '</div>');
            // Create our content div, get the dimensions, and hide it
            var modalContent = $('#modalContent').css('top','-1000px');
            var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
            var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);
            $('#modalBackdrop').css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
            modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'});

            // Make the request
            ajax_request = $.ajax({
              type: 'POST',
              url: "/sbac-resource/load-more",
              data: {'view' : 'resource_review', 'page' : pager},
              success: function(data) {
                // Parse the response
                var response = jQuery.parseJSON(data);
                // Inject the content
                $('.row.digital-library').replaceWith(response.rendered_content);
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

  Drupal.behaviors.sbac_resource_review_clear = {
    attach: function (context, settings) {
      $('.sbac-clear-search').click( function() {
        window.location.href = 'sbac-search/clear-all?location=resource-review';
      });
    }
  };

})(jQuery);
