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

  // Parse URLs into the query and search. If url is false, it will use the current page URL.
  function urlParse(url) {
    if (!url) {
      url = window.location;
    }
    var parser = document.createElement('a');
    parser.href = url;
    var query = parser.pathname;
    // IE seems to exclude the leading '/', so we need to check for it.
    if (query.indexOf('/') !== 0) {
      query = '/' + query;
    }
    var search = parser.search;
    // Remove the leading '?' if it's there.
    if (search.indexOf('?') === 0){
      search = search.substr(1);
    }
    return {'query': query, 'search': search};
  }

  // Split the search portion of a URL into key/value pairs.
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

  // Put key/value pairs back together into a search string.
  function searchConcat(variables) {
    var new_search = '';
    $.each(variables, function (i, v) {
      new_search += '&' + i + '=' + v;
    });
    new_search = new_search.substr(1);
    return new_search;
  }

  // Dim the results area of the search page while they are loading via AJAX.
  function searchLoading() {
    var $content_area = $('#main').find('.view-content');
    if (!$content_area.length){
      $content_area = $('#main').find('.view-empty')
    }
    $content_area.append('<div id="search-loading"></div>');
    var $loading = $('#search-loading');
    var height = $content_area.innerHeight();
    var width = $content_area.innerWidth();
    $loading.height(height);
    $loading.width(width + 15);
    $loading.fadeIn();
  }

  // Load the facets from another URL so they don't block loading of the search page.
  function cctLoad(query, search, clicked) {
    //console.log('CCT!');
    var parent = $(clicked).closest('.block-facetapi').find('.item-list > ul').filter(':first');
    var block_id = $(parent).attr('id');
    var $block = $('#' + block_id);

    // Add throbber.
    $(clicked).parent().children().filter(':last').append(' <img class="cct-throbber" src="/misc/throbber-active.gif" />');
    $.get('/cct' + query, search, function (data) {
      $('.cct-throbber').remove();
      // Load the data returned by the request as context for the selectors below.
      var context = $(data);
      // Load the facet blocks.
      $block.html($('#' + block_id, context).html());
      // Remove the '/cct' from these links.
      $block.find('a').each(function () {
        $(this).attr('href', $(this).attr('href').substr(4));
      });
      // Re-attach behaviors.
      Drupal.attachBehaviors('#sidebar-first');
    });
  }

  // Shows the full facet name for truncated items.
  function facetSwap($item) {
    var full_name = $item.attr('data-full-name');
    var trunc_name = $item.html();
    $item.attr('data-full-name', trunc_name);
    $item.html(full_name)
  }

  // Sets up the initial state of the CC and Target tag blocks.
  function cctState() {
    var current_url = urlParse(false);
    if (current_url.query.indexOf('/cc/') !== -1) {
      $('.block-facetapi-ynelajjhesbu04dgezguufidwud0zqlh').addClass('expanded');
    } else {
      $('.block-facetapi-ynelajjhesbu04dgezguufidwud0zqlh').children('.item-list').hide();
    }
    if (current_url.query.indexOf('/t/') !== -1) {
      $('.block-facetapi-car5oq63bgunqwf0g1xh5k6fci7p504o').addClass('expanded');
    } else {
      $('.block-facetapi-car5oq63bgunqwf0g1xh5k6fci7p504o').children('.item-list').hide();
    }
  }

  function initializeFacets() {
    // Set the initial toggle state of the plus/minus icons.
    plusMinusToggler('a .facetapi-collapsible-handle');

    // Set up the show/hide for the CC and Target blocks.
    $('.block-facetapi-ynelajjhesbu04dgezguufidwud0zqlh, .block-facetapi-car5oq63bgunqwf0g1xh5k6fci7p504o').once('fakeCollapsible').each(function () {
      var $block = $(this);
      $(this).children('h2').click(function (e) {
        $block.children('.item-list').toggle();
        $block.toggleClass('expanded');
      })
    });

    // Remove the unused 2nd and third terms in the CC block.
    var $cc_items = $('.facetapi-facet-field-alignment-term > li');
    $cc_items.eq(3).remove();
    $cc_items.eq(2).remove();
    $cc_items.eq(1).addClass('last');

    // Add hovers to truncated items.
    $('.facet-truncate').once('facetHover').hover(function () {
      $(this).toggleClass('facet-hover');
      facetSwap($(this));
    });

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

    // Change all the parent items in the facets to just open, rather than select.
    $('a[class^=facetapi-]').each(function () {
      if (!$(this).parents('.facetapi-facet-field-alignment-term, .facetapi-facet-field-target-term').length) {
        var $parent = $(this).parent();
        if ($parent.siblings('.item-list').length) {
          $parent.parent().css('background', 'none');
          $(this).siblings('.checkbox-spacer').hide();
          $(this).off('click');
          $(this).removeClass('facetapi-inactive facetapi-active');
          $(this).click(function (e) {
            e.preventDefault();
            $('.facetapi-collapsible-handle', this).click();
          });
        }
      }
    });

    // Change how the CC and Target tag parents work.
    $('#sidebar-first').once('cctProcess').on(
      'click',
      '.facetapi-facet-field-alignment-term a, .facetapi-facet-field-target-term a',
      function (e) {
        e.preventDefault();
        // Get the clicked URL and query/search data.
        var clicked_url = $(this).attr('href');
        // Get the clicked URL and parse it into query and search parts.
        var clicked = urlParse(clicked_url);
        cctLoad(clicked.query, clicked.search, this);
      }
    );
  }

  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Click functionality and expansion for facets.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_search_api_facets = {
    attach: function (context, settings) {
      initializeFacets();

      // Get the current URL and parse it.
      var current = urlParse(false);

      // Set up a variable to hold the current AJAX request so we can abort it as needed.
      var currentAJAX = {};

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

      // Set up the base query regex so we can handle the easy ones (where something is just added to the base).
      var base_query = new RegExp('^' + current.query + '\\b');

      // Remove the first part of the URL (instructional, playlist, etc.) from the current and item URLs.
      var base = new RegExp('^/[^/]+/');
      var base_slash = new RegExp('^/[^/]+');
      var base_url = current.query.match(base_slash)[0];
      var current_query_only = current.query.replace(base, '').split('/');

      // Split the query parts up into pairs (i.e. - s/123).
      var current_pairs = [];
      for (var x = 0; x < current_query_only.length; x += 2) {
        current_pairs.push(current_query_only[x] + '/' + current_query_only[x + 1]);
      }

      // Split up the current and item URL search variables.
      var current_search_pairs = searchSplit(current.search);

      // Handle the browser back button.
      window.onpopstate = function (e) {
        // Stop any existing unfinished AJAX requests.
        if (currentAJAX.hasOwnProperty('abort')) {
          currentAJAX.abort();
        }

        // Get the new URL and parse it.
        current = urlParse(false);

        base_url = current.query.match(base_slash)[0];
        current_query_only = current.query.replace(base, '').split('/');

        // Split the query parts up into pairs (i.e. - s/123).
        current_pairs = [];
        for (var x = 0; x < current_query_only.length; x += 2) {
          current_pairs.push(current_query_only[x] + '/' + current_query_only[x + 1]);
        }

        // Split up the current and item URL search variables.
        current_search_pairs = searchSplit(current.search);

        // Put up the dimmer while the AJAX request happens.
        searchLoading();
        // Do the AJAX request with the URL from the history.
        currentAJAX = $.get(current.query, current.search, function (data) {
          // Load the data returned by the request as context for the selectors below.
          var context = $(data);
          // Load the sidebar state, since it's easier than parsing the URL and trying to figure out how to mark everything manually.
          $('#sidebar-first').html($('#sidebar-first', context).html());
          // Load the results, pager, and search blocks in the main area.
          $('#main').html($('#main', context).html());
          // Re-attach behaviors.
          Drupal.attachBehaviors('.main-row');
          cctState();
        });
      };

      var doSearch = function(query, search) {
        // Put up the dimmer while the AJAX request happens.
        searchLoading();
        // Do the AJAX call to get the new results.
        currentAJAX = $.get('/ajax' + query, search, function (data) {
          // Load the data returned by the request as context for the selectors below.
          var context = $(data);
          // Replace the current search results number.
          $('.current-search-item').html($('.current-search-item', context).html());
          // Replace the sort widget, as immediate updating isn't necessary here, and this is easier than doing it in JS.
          $('.search-sort-widget').html($('.search-sort-widget', context).html());
          // Replace the search results and pager.
          $('.view-search-api-resource-views').html($('.view-search-api-resource-views', context).html());
          // Remove the '/ajax' from the pager and sort links.
          $(pager_selectors.concat(sort_selectors)).each(function (i, v) {
            if ($(v).length) {
              $(v).each(function () {
                $(this).attr('href', $(this).attr('href').substr(5));
              });
            }
          });
          // Re-attach behaviors.
          //Drupal.attachBehaviors('#main');
          Drupal.attachBehaviors('.view-search-api-resource-views');
        });
      };

      // Set up the AJAX request for when the keyword search is used.
      $(search_forms).once('submitWrap').submit(function (e) {
        e.preventDefault();

        // Stop any existing unfinished AJAX requests.
        if (currentAJAX.hasOwnProperty('abort')) {
          currentAJAX.abort();
        }

        // Get the value to search for.
        var search = $('#edit-search', $(this)).val();

        // Update the search to the new keywords.
        if (search.length) {
          current_search_pairs['search'] = search;
        } else {
          delete current_search_pairs.search;
        }
        // Reset pager to start at the beginning
        delete current_search_pairs.page;
        // Put the search variables back together.
        var new_search = searchConcat(current_search_pairs);

        // Go through all of the links and update them with the keyword search.
        $(selectors.join(',')).each(function (k, s) {
          // Get the URL for the link and parse it.
          var item_url = $(this).attr('href');
          var item = urlParse(item_url);
          // Build the new URL.
          var new_url = item.query + '?' + new_search;
          // Update the link with the new URL.
          $(this).attr('href', new_url);
        });

        // Update the history.
        history.pushState({}, '', current.query + '?' + new_search);

        // Set the new current URL.
        current = urlParse(false);
        base_url = current.query.match(base_slash)[0];
        current_query_only = current.query.replace(base, '').split('/');
        // Split the query parts up into pairs (i.e. - s/123).
        current_pairs = [];
        for (var x = 0; x < current_query_only.length; x += 2) {
          current_pairs.push(current_query_only[x] + '/' + current_query_only[x + 1]);
        }
        // Split up the current and item URL search variables.
        current_search_pairs = searchSplit(current.search);

        doSearch(current.query, new_search);
      });

      // Add the data-query and data-search values to links (if they don't already have them) so rebuilding them is easier.
      $(selectors.join(',')).not('[data-query]').each(function () {
        var query_data = '';
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
          var item_query_only = item.query.replace(base, '').split('/');

          // Split the query parts up into pairs (i.e. - s/123).
          var item_pairs = [];
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

        // Add the search items if they're missing.
        if (current.search && ! item.search) {
          $(this).attr('href', item_url + '?' + current.search);
        }
      });

      // Add the click event to each link to update the other links.
      $('#sidebar-first').once('ajaxSearchClick').on('click', selectors.join(','), function (e) {
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
          if (clicked.query.match(new RegExp(clicked_query_data + '\\b'))) {
            clicked_query_change = 'add';
          } else {
            clicked_query_change = 'remove';
          }
        }
        var clicked_search_change = false;
        if (clicked_search_data) {
          clicked_search_change = true;
        }

        // If this is a facet item, we need to do some class updates and update the URL correctly.
        if ($(facet_selectors.join(','), $(this).parent()).length) {
          var $parent = $(this).parent();
          // Toggle the link and the parent between active and inactive to be consistent with the normal facet handling.
          $parent.children('a[class^=facetapi-]').toggleClass('facetapi-active facetapi-inactive');
          if ($parent.hasClass('facetapi-active')) {
            $parent.parent().find('.active').each(function () {
              $(this).toggleClass('active');
            });
          }
          $parent.toggleClass('facetapi-active facetapi-inactive');
          // Toggle the LI active class so the checkmarks are set correctly.
          $parent.parent().toggleClass('active');
          // Update the clicked URL for both the clicked link and the text part.
          if (clicked_query_change === 'add') {
            $parent.children('a').attr('href', clicked.query.replace(new RegExp(clicked_query_data + '\\b'), '') + (clicked.search.length ? ('?' + clicked.search) : ''));
          } else if (clicked_query_change === 'remove') {
            $parent.children('a').attr('href', clicked.query + clicked_query_data + (clicked.search.length ? ('?' + clicked.search) : ''));
          }
        }

        // Only process the links if one of the URL parts changed.
        if (clicked_query_change || clicked_search_change) {
          // Update all of the links.
          $(selectors.join(',')).each(function () {
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
                // If the item data is in the clicked URL already, it's active, so we don't want to add it back in.
                if (clicked_url.match(new RegExp(item_query_data + '\\b'))) {
                  new_query = clicked.query;
                } else {
                  // Otherwise, we'll build the URL from the clicked URL, and the item data
                  new_query = clicked.query + item_query_data;
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
              new_url += new_search ? ('?' + new_search) : '';
              // Update the link with the new URL.
              $(this).attr('href', new_url);
            }
          });
        }

        // Update the history.
        history.pushState({}, '', clicked_url);

        // Set the new current URL.
        current = urlParse(false);
        base_url = current.query.match(base_slash)[0];
        current_query_only = current.query.replace(base, '').split('/');
        // Split the query parts up into pairs (i.e. - s/123).
        current_pairs = [];
        for (var x = 0; x < current_query_only.length; x += 2) {
          current_pairs.push(current_query_only[x] + '/' + current_query_only[x + 1]);
        }
        // Split up the current and item URL search variables.
        current_search_pairs = searchSplit(current.search);

        doSearch(clicked.query, clicked.search);
      });

      // Show/hide the sorts on click.
      $('.default-sort').once('defaultSort').click(function (e) {
        $(this).toggleClass('active');
        $('.search-api-sorts').toggle();
      });

      // Set the placeholder in the search box.
      $(search_forms).find('#edit-search').attr('placeholder', 'search within results');
    }
  };

  $(document).ready(function () {
    cctState();
  });
})(jQuery);
