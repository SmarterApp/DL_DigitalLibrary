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

  function getParameterByName(name, url) {
    if (!url) {
      url = window.location.href;
    }
    name = name.replace(/[\[\]]/g, "\\$&");

    var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
      results = regex.exec(url);

    if (!results) {
      return null;
    }

    if (!results[2]) {
      return '';
    }

    return decodeURIComponent(results[2].replace(/\+/g, " "));
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

      var doSearch = function(reset) {
        // Stop any existing unfinished AJAX requests.
        if (currentAJAX.hasOwnProperty('abort')) {
          currentAJAX.abort();
        }

        // Put up the dimmer while the AJAX request happens.
        searchLoading();

        var facets = [];
        $('a.facetapi-active').each(function () {
          facets.push($(this).data('query'));
        });

        var forms = $(search_forms);
        if (0 === forms.length) {
          forms = $('#views-exposed-form-search-api-resource-views-search-resources');
        }

        var term;
        if (0 < forms.length) {
          term = $(forms).find('#edit-search').val();
        } else {
          term = getParameterByName('search');
        }
        if (term) {
          current_search_pairs['search'] = term;
        } else {
          delete current_search_pairs.search;
        }

        // Reset pager to start at the beginning
        if (reset) {
          delete current_search_pairs.page;
        }

        var query = base_url + facets.join('');
        var search = searchConcat(current_search_pairs);

        // Update the history.
        history.pushState({}, '', query + (search.length ? ('?' + search) : ''));

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

        doSearch(true);
      });

      // Load the facets from another URL so they don't block loading of the search page.
      function cctLoad(clicked) {
        var parent = $(clicked).closest('.block-facetapi').find('.item-list > ul').filter(':first');
        var block_id = $(parent).attr('id');
        var $block = $('#' + block_id);

        var facets = [];
        $('a.facetapi-active').each(function () {
          facets.push($(this).data('query'));
        });
        console.log('facets', facets);

        var term = $(search_forms).find('#edit-search').val();
        if (term) {
          current_search_pairs['search'] = term;
        } else {
          delete current_search_pairs.search;
        }

        // Reset pager to start at the beginning
        delete current_search_pairs.page;

        var query = base_url + facets.join('');
        var search = searchConcat(current_search_pairs);

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
      $('#sidebar-first').once('facetClick').on('click', facet_selectors.join(','), function (e) {
        // Don't do the normal click.
        e.preventDefault();

        var $parent = $(this).parent();
        // Toggle the link and the parent between active and inactive to be consistent with the normal facet handling.
        $parent.children('a').filter('.facetapi-active,.facetapi-inactive').toggleClass('facetapi-active facetapi-inactive');
        if ($parent.hasClass('facetapi-active')) {
          $parent.parent().find('.active').each(function () {
            // Toggle the LI active class so the checkmarks are set correctly.
            $(this).toggleClass('active');
          });
          $parent.parent().find('.item-list .facetapi-active').each(function () {
            $(this).toggleClass('facetapi-active facetapi-inactive');
          });
        }
        $parent.toggleClass('facetapi-active facetapi-inactive');
        // Toggle the LI active class so the checkmarks are set correctly.
        $parent.parent().toggleClass('active');

        // Change how the CC and Target tag parents work.
        if ($(this).closest('.facetapi-facet-field-alignment-term, .facetapi-facet-field-target-term').length) {
          cctLoad(this);
        }

        doSearch(true);
      });

      $('.view-search-api-resource-views').once('pageClick').on('click', pager_selectors.join(','), function(e) {
        e.preventDefault();

        var item_url = $(this).attr('href');
        // Parse the item URL.
        var item = urlParse(item_url);

        // Split up the current and item URL search variables.
        var item_search_pairs = searchSplit(item.search);
        if (item_search_pairs.hasOwnProperty('page')) {
          current_search_pairs['page'] = item_search_pairs['page'];
        } else {
          delete current_search_pairs.page;
        }

        doSearch(false);
      });

      $('.block-search-api-sorts').once('sortClick').on('click', sort_selectors.join(','), function(e) {
        e.preventDefault();

        var item_url = $(this).attr('href');
        // Parse the item URL.
        var item = urlParse(item_url);

        // Split up the current and item URL search variables.
        var item_search_pairs = searchSplit(item.search);
        if (item_search_pairs.hasOwnProperty('sort')) {
          current_search_pairs['sort'] = item_search_pairs['sort'];
        } else {
          delete current_search_pairs.sort;
        }
        if (item_search_pairs.hasOwnProperty('order')) {
          current_search_pairs['order'] = item_search_pairs['order'];
        } else {
          delete current_search_pairs.order;
        }

        doSearch(true);
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
