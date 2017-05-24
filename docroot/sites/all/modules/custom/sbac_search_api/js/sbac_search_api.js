/**
 * Created by jbaker on 4/21/17.
 */
(function ($) {
  // Function to toggle the plus/minus icons for expanded tags.
  function plusMinusToggler(selector) {
    $(selector).each(function () {
      var $clickedlist = $(this).parent().parent().siblings('.item-list').children('ul');
      if ($clickedlist.hasClass('expanded')) {
        if (!$(this).hasClass('minus-sign')) {
          $(this).addClass('minus-sign');
        }
        if ($(this).hasClass('plus-sign')) {
          $(this).removeClass('plus-sign');
        }
      } else {
        if ($(this).hasClass('minus-sign')) {
          $(this).removeClass('minus-sign');
        }
        if (!$(this).hasClass('plus-sign')) {
          $(this).addClass('plus-sign');
        }
      }
    });
  }

  function urlParse(url) {
    if (!url) {
      url = window.location;
    }
    var parser = document.createElement('a');
    parser.href = url;
    return {'query': parser.pathname, 'search': parser.search.substr(1)};
  }

  function searchSplit(search) {
    var pairs = {};
    if (search) {
      var search_temp = search.split('&');
      $.each(search_temp, function (key, value) {
        var pair = value.split('=');
        pairs[pair[0]] = pair[1];
      });
    }
    return pairs;
  }

  function searchConcat(variables) {
    var new_search = '';
    $.each(variables, function (i, v) {
      new_search += '&' + i + '=' + v;
    });
    new_search = new_search.substr(1);
    return new_search;
  }

  function searchLoading() {
    $('#main .view-content').append('<div id="search-loading"></div>');
    var height = $('#main .view-content').innerHeight();
    var width = $('#main .view-content').innerWidth();
    $('#search-loading').height(height);
    $('#search-loading').width(width + 15);
    $('#search-loading').fadeIn();
  }

  function cctLoad(query, search) {
    $.get('/cct' + query, search, function (data) {
      // Load the data returned by the request as context for the selectors below.
      var context = $(data);
      // Load the Target Alignment facet block.
      $('#sidebar-first .block-block').eq(0).html($('.block-facetapi', context).eq(0).html());
      // Load the Common Core facet block.
      $('#sidebar-first .block-block').eq(1).html($('.block-facetapi', context).eq(1).html());
      // Add the facetapi class.
      $('#sidebar-first .block-block').addClass('block-facetapi facetapi-collapsible');
      // Remove the unused 2nd and third terms in the CC block.
      $('.facetapi-facet-field-alignment-term > li').eq(3).remove();
      $('.facetapi-facet-field-alignment-term > li').eq(2).remove();
      $('.facetapi-facet-field-alignment-term > li').eq(1).addClass('last');
      // Remove the '/cct' from these links.
      $('#sidebar-first .block-block a').each(function () {
        $(this).attr('href', $(this).attr('href').substr(4));
      });
      // Need to add these to the collapsible facet settings.
      Drupal.settings.facetapi_collapsible['field_alignment_term'] = {'collapsible_children': 1, 'expand': 0, 'keep_open': 1};
      Drupal.settings.facetapi_collapsible['field_target_term'] = {'collapsible_children': 1, 'expand': 0, 'keep_open': 1};
      // Re-attach behaviors.
      Drupal.attachBehaviors('#sidebar-first');
    });
  }

  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Click functionality and expansion for facets.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_search_api_facets = {
    attach: function (context, settings) {
      // Set the initial toggle state of the plus/minus icons.
      plusMinusToggler('a .facetapi-collapsible-handle');

      // Set the plus/minus state when you click.
      $('a .facetapi-collapsible-handle').once('plusMinus').click(function (e) {
        e.preventDefault();
        e.stopPropagation();
        plusMinusToggler(this);
      });

      // Add a click area to the fake checkboxes.
      $('.facetapi-facet').each(function () {
        var href = $(this).children('a.facetapi-active, a.facetapi-inactive').attr('href');
        $(this).once('checkBoxSpacer').prepend('<a class="checkbox-spacer" href="' + href + '">&nbsp;</a>');
      });

      // Get the current URL and parse it.
      var current = urlParse(false);
      var current_url = current.query;
      current_url += current.search ? '?' : '';
      current_url += current.search;

      // Set up a variable to hold the current AJAX request so we can abort it as needed.
      var currentAJAX = {};

      // Handle the browser back button.
      window.onpopstate = function (e) {
        // Stop any existing unfinished AJAX requests.
        if (currentAJAX.hasOwnProperty('abort')) {
          currentAJAX.abort();
        }

        // Get the URL and parse it.
        var back = urlParse(false);

        // Put up the dimmer while the AJAX request happens.
        searchLoading();
        // Do the AJAX request with the URL from the history.
        currentAJAX = $.get(back.query, back.search, function (data) {
          // Load the data returned by the request as context for the selectors below.
          var context = $(data);
          // Load the sidebar state, since it's easier than parsing the URL and trying to figure out how to mark everything manually.
          $('#sidebar-first').html($('#sidebar-first', context).html());
          // Load the results, pager, and search blocks in the main area.
          $('#main').html($('#main', context).html());
          // Re-attach behaviors.
          Drupal.attachBehaviors('.main-row');
          cctLoad(back.query, back.search);
        });
      };

      // The selectors for the facet-related links.
      var facet_selectors = [
        'a.facetapi-inactive',
        'a.facetapi-active',
        'a.checkbox-spacer'
      ];
      // The selectors for the pager-related links.
      var pager_selectors = [
        '.pager-item a',
        '.pager-next a',
        '.pager-last a',
        '.pager-previous a',
        '.pager-first a'
      ];
      // Selectors for the sort-related links.
      var sort_selectors = ['a.sort-item'];
      // Put all the selectors together.
      var selectors = facet_selectors.concat(pager_selectors, sort_selectors);

      // The available variables that can be in the search section of the URL (except page, as we want that to reset).
      var search_vars = [
        'search',
        'sort',
        'order'
      ];

      // The selectors for the search form on the 3 pages.
      var search_forms = '#views-exposed-form-search-api-resource-views-instructional, #views-exposed-form-search-api-resource-views-professional-learning, #views-exposed-form-search-api-resource-views-playlist';
      // Set up the AJAX request for when the keyword search is used.
      $(search_forms).submit(function (e) {
        e.preventDefault();
        // Get the value to search for.
        var search = $('#edit-search', $(this)).val();
        // Go through all of the links and update them with the keyword search.
        $.each(selectors, function (key, selector) {
          $(selector).each(function (k, s) {
            // Get the URL for the link and parse it.
            var item_url = $(this).attr('href');
            var item = urlParse(item_url);
            // Split the search variables up.
            var item_search_pairs = searchSplit(item.search);
            // Add/update the search value.
            item_search_pairs['search'] = search;
            // Put the search variables back together.
            var new_search = searchConcat(item_search_pairs);
            // Build the new URL.
            var new_url = item.query + '?' + new_search;
            // Update the link with the new URL.
            $(this).attr('href', new_url);
          });
        });

        // Stop any existing unfinished AJAX requests.
        if (currentAJAX.hasOwnProperty('abort')) {
          currentAJAX.abort();
        }

        // Split the current search variables up.
        var current_search_pairs = searchSplit(current.search);
        // Update the search to the new keywords.
        current_search_pairs['search'] = search;
        // Put the search variables back together.
        var new_search = searchConcat(current_search_pairs);

        // Update the history.
        history.pushState(null, null, current.query + '?' + new_search);

        // Put up the dimmer while the AJAX request happens.
        searchLoading();
        currentAJAX = $.get('/ajax' + current.query, new_search, function (data) {
          // Load the data returned by the request as context for the selectors below.
          var context = $(data);
          // Update the current search count.
          $('.current-search-item').html($('.current-search-item', context).html());
          // Update the search results.
          $('.view-search-api-resource-views').html($('.view-search-api-resource-views', context).html());
          // Remove the '/ajax' from the pager and sort links.
          $(pager_selectors).each(function () {
            $(this).attr('href', $(this).attr('href').substr(5));
          });
          $(sort_selectors).each(function () {
            $(this).attr('href', $(this).attr('href').substr(5));
          });
          // Re-attach the behaviors.
          Drupal.attachBehaviors('.view-search-api-resource-views');
        });
      });

      // Attach the click event to all of the links.
      $.each(selectors, function (key, selector) {
        $(selector).each(function (k, s) {
          // Add the data-query and data-search values to links (if they don't already have them) so rebuilding them is easier.
          if (!$(this)[0].hasAttribute('data-query')) {
            var query_data = '';
            // Set up the base query regex so we can handle the easy ones (where something is just added to the base).
            var base_query = new RegExp('^' + current.query);
            // Get the URL of the current item.
            var item_url = $(this).attr('href');
            // Parse the item URL.
            var item = urlParse(item_url);
            // If the link is just adding to the base URL, the part that's being added is the query data.
            if (item.query.match(base_query)) {
              query_data = item.query.replace(base_query, '');
            }
            // Otherwise, we need to figure out what is being taken away, as this must be active already.
            else {
              // Remove the first part of the URL (instructional, playlist, etc.) from the current and item URLs.
              var base = new RegExp('^/.+?/');
              var current_query_only = current.query.replace(base, '').split('/');
              var item_query_only = item.query.replace(base, '').split('/');

              // Split the query parts up into pairs (i.e. - s/123).
              var current_pairs = [];
              var item_pairs = [];
              for (var x = 0; x < current_query_only.length; x += 2) {
                current_pairs.push(current_query_only[x] + '/' + current_query_only[x + 1]);
              }
              for (x = 0; x < item_query_only.length; x += 2) {
                item_pairs.push(item_query_only[x] + '/' + item_query_only[x + 1]);
              }

              // Get the pair from the current URL that isn't in the item URL.
              query_data = $(current_pairs).not(item_pairs).get();
              // Standardize with the slash in front.
              query_data = '/' + query_data[0];
            }
            // Add the data-query value from above to the item.
            $(this).attr('data-query', query_data);

            // Split up the current and item URL search variables.
            var current_search_pairs = searchSplit(current.search);
            var item_search_pairs = searchSplit(item.search);
            var search_data = [];
            // Go through the available search variables to find out their status and determine what this URL changes.
            $.each(search_vars, function (i, v) {
              // If both URLs have the variable set, and they aren't equal, or only the item URL has is set, that variable changes here.
              if ((item_search_pairs.hasOwnProperty(v) && current_search_pairs.hasOwnProperty(v) && item_search_pairs[v] !== current_search_pairs[v]) ||
                (item_search_pairs.hasOwnProperty(v) && !current_search_pairs.hasOwnProperty(v))) {
                search_data.push(v + '=' + item_search_pairs[v]);
              }
            });
            // Set the data-search with the value(s) from above.
            $(this).attr('data-search', search_data.join('&'));
          }
        });

        // Add the click event to each link to update the other links.
        $(selector).once('ajaxSearchClick').click(function (e) {
          // Don't do the normal click.
          e.preventDefault();

          // Stop any existing unfinished AJAX requests.
          if (currentAJAX.hasOwnProperty('abort')) {
            currentAJAX.abort();
          }

          // Get the clicked URL and query/search data.
          var clicked_url = $(this).attr('href');
          // Get the clicked URL and parse it into query and search parts.
          var clicked = urlParse(clicked_url);
          // Get the data that the clicked link changes in the URL.
          var clicked_query_data = $(this).attr('data-query');
          var clicked_search_data = $(this).attr('data-search');
          // Split up the search variables for the clicked link.
          var clicked_search_pairs = searchSplit(clicked.search);
          // Determine if the link changes anything in the query and search parts of the URL.
          var clicked_query_change = false;
          if (clicked_query_data) {
            if (clicked_url.match(new RegExp(clicked_query_data))) {
              clicked_query_change = 'add';
            } else {
              clicked_query_change = 'remove';
            }
          }
          var clicked_search_change = false;
          if (clicked_search_data) {
            clicked_search_change = true;
          }

          // Update the history.
          history.pushState(null, null, clicked_url);

          // If this is a facet item, we need to do some class updates an update the URL correctly.
          if ($.inArray(selector, facet_selectors) >= 0) {
            var $parent = $(this).parent();
            // Toggle the link and the parent between active and inactive to be consistent with the normal facet handling.
            $parent.children('a[class^=facetapi-]').toggleClass('facetapi-active');
            $parent.children('a[class^=facetapi-]').toggleClass('facetapi-inactive');
            $parent.toggleClass('facetapi-active');
            $parent.toggleClass('facetapi-inactive');
            // Toggle the LI active class so the checkmarks are set correctly.
            $parent.parent().toggleClass('active');
            // Update the clicked URL for both the clicked link and the text part.
            if (clicked_query_change === 'add') {
              $parent.children('a').attr('href', clicked_url.replace(new RegExp(clicked_query_data), ''));
            } else if (clicked_query_change === 'remove') {
              $parent.children('a').attr('href', clicked_url + clicked_query_data);
            }
          }

          // Only process the links if one of the URL parts changed.
          if (clicked_query_change || clicked_search_change) {
            // Update all of the links.
            $.each(selectors, function (k, s) {
              $(s).each(function () {
                // Get the URL of the current item.
                var item_url = $(this).attr('href');
                var item_query_data = $(this).attr('data-query');
                var item_search_data = $(this).attr('data-search');

                // Only process this if it isn't the clicked item.
                if (!(clicked_query_data === item_query_data && clicked_search_data === item_search_data)) {
                  // Parse the item URL.
                  var item = urlParse(item_url);
                  // Default the query and search to the current values.
                  var new_query = item.query;
                  var new_search = item.search;
                  // Only change the query if it actually changed.
                  if (clicked_query_change) {
                    // If the clicked URL was adding a filter, we will add the filter to this item.
                    if (clicked_query_change === 'add') {
                      // If the item data is in the clicked URL already, it's active, so we don't want to add it back in.
                      if (clicked_url.match(new RegExp(item_query_data))) {
                        new_query = item.query + clicked_query_data;
                      }
                      // Otherwise, we'll build the URL from the current URL, the clicked data, and the item data, to preserve order.
                      else {
                        new_query = current.query + clicked_query_data + item_query_data;
                      }
                    }
                    // If the clicked URL was removing data, remove it from the item.
                    else if (clicked_query_change === 'remove') {
                      new_query = item.query.replace(new RegExp(clicked_query_data), '');
                    }
                  }

                  // Only change the search if it actually changed.
                  if (clicked_search_change) {
                    // Split up the item's search variables.
                    var item_search_pairs = searchSplit(item.search);
                    // For each variable type, check to see what changes and update appropriately.
                    $.each(search_vars, function (i, v) {
                      // If the variable is set in both and they are different values.
                      if (item_search_pairs.hasOwnProperty(v) && clicked_search_pairs.hasOwnProperty(v) && item_search_pairs[v] !== clicked_search_pairs[v]) {
                        item_search_pairs[v] = clicked_search_pairs[v];
                      }
                      // If it's set in the clicked URL and not the item one.
                      else if (!item_search_pairs.hasOwnProperty(v) && clicked_search_pairs.hasOwnProperty(v)){
                        item_search_pairs[v] = clicked_search_pairs[v];
                      }
                      // If it's set in the item URL but not the clicked one.
                      else if (item_search_pairs.hasOwnProperty(v) && !clicked_search_pairs.hasOwnProperty(v)){
                        item_search_pairs[v] = '';
                      }
                    });

                    new_search = searchConcat(item_search_pairs);
                  }

                  // Build the new URL.
                  var new_url = new_query;
                  new_url += new_search ? '?' : '';
                  new_url += new_search;
                  // Update the link with the new URL.
                  $(this).attr('href', new_url);
                }
              });
            });
          }

          // Set the new current URL.
          current = urlParse(false);
          current_url = current.query;
          current_url += current.search ? '?' : '';
          current_url += current.search;

          // Put up the dimmer while the AJAX request happens.
          searchLoading();
          // Do the AJAX call to get the new results.
          currentAJAX = $.get('/ajax' + clicked.query, clicked.search, function (data) {
            // Load the data returned by the request as context for the selectors below.
            var context = $(data);
            // Replace the current search results number.
            $('.current-search-item').html($('.current-search-item', context).html());
            // Replace the sort widget, as immediate updating isn't necessary here, and this is easier than doing it in JS.
            $('.search-sort-widget').html($('.search-sort-widget', context).html());
            // Replace the search results and pager.
            $('.view-search-api-resource-views').html($('.view-search-api-resource-views', context).html());
            // Remove the '/ajax' from the pager and sort links.
            $(pager_selectors).each(function () {
              $(this).attr('href', $(this).attr('href').substr(5));
            });
            $(sort_selectors).each(function () {
              $(this).attr('href', $(this).attr('href').substr(5));
            });
            // Re-attach behaviors.
            Drupal.attachBehaviors('#main');
          });
        });
      });

      // Show/hide the sorts on click.
      $('.default-sort').once('defaultSort').click(function (e) {
        $(this).toggleClass('active');
        $('.search-api-sorts').toggle();
      });

      // Set the placeholder in the search box.
      $('#views-exposed-form-search-api-resource-views-instructional #edit-search').attr('placeholder', 'search within results');
      $('#views-exposed-form-search-api-resource-views-professional-learning #edit-search').attr('placeholder', 'search within results');
      $('#views-exposed-form-search-api-resource-views-playlist #edit-search').attr('placeholder', 'search within results');
    }
  };

  $(document).ready(function () {
    // Get the current URL and parse it.
    var current = urlParse(false);

    // Load the CC and Target facets.
    cctLoad(current.query, current.search);
  });
})(jQuery);
