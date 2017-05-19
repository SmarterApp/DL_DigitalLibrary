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

  function searchLoading() {
    $('#main .view-content').append('<div id="search-loading"></div>');
    var height = $('#main .view-content').innerHeight();
    var width = $('#main .view-content').innerWidth();
    $('#search-loading').height(height);
    $('#search-loading').width(width + 15);
    $('#search-loading').fadeIn();
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

      var current = urlParse(false);
      var current_url = current.query;
      current_url += current.search ? '?' : '';
      current_url += current.search;

      var currentAJAX = {};

      window.onpopstate = function (e) {
        // Stop any existing unfinished AJAX requests.
        if (currentAJAX.hasOwnProperty('abort')) {
          currentAJAX.abort();
        }
        var back = urlParse(false);

        searchLoading();
        currentAJAX = $.get(back.query, back.search, function (data) {
          var context = $(data);
          $('#sidebar-first').html($('#sidebar-first', context).html());
          $('#main').html($('#main', context).html());
          Drupal.attachBehaviors('.main-row');
        });
      };

      var facet_selectors = [
        'a.facetapi-inactive',
        'a.facetapi-active',
        'a.checkbox-spacer'
      ];
      var pager_selectors = [
        '.pager-item a',
        '.pager-next a',
        '.pager-last a',
        '.pager-previous a',
        '.pager-first a'
      ];
      var sort_selectors = ['a.sort-item'];
      var selectors = facet_selectors.concat(pager_selectors, sort_selectors);

      var search_forms = '#views-exposed-form-search-api-resource-views-instructional, #views-exposed-form-search-api-resource-views-professional-learning, #views-exposed-form-search-api-resource-views-playlist';
      $(search_forms).submit(function (e) {
        e.preventDefault();
        var search = $('#edit-search', $(this)).val();
        $.each(selectors, function (key, selector) {
          $(selector).each(function (k, s) {
            var item_url = $(this).attr('href');
            var item = urlParse(item_url);
            var item_search_pairs = searchSplit(item.search);
            item_search_pairs['search'] = search;
            var new_search = '';
            $.each(item_search_pairs, function (i, v) {
              new_search += '&' + i + '=' + v;
            });
            new_search = new_search.substr(1);

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

        var current_search_pairs = searchSplit(current.search);
        current_search_pairs['search'] = search;
        current_search_pairs['page'] = '';
        var new_search = '';
        $.each(current_search_pairs, function (i, v) {
          new_search += '&' + i + '=' + v;
        });
        new_search = new_search.substr(1);

        history.pushState(null, null, current.query + '?' + new_search);

        searchLoading();
        currentAJAX = $.get(current.query, new_search, function (data) {
          var context = $(data);
          $('.current-search-item').html($('.current-search-item', context).html());
          $('.view-search-api-resource-views').html($('.view-search-api-resource-views', context).html());
          Drupal.attachBehaviors('.view-search-api-resource-views');
        });
      });

      // Attach the click event to all of the items.
      $.each(selectors, function (key, selector) {
        $(selector).each(function (k, s) {
          if (!$(this)[0].hasAttribute('data-query')) {
            var query_data = '';
            var base_query = new RegExp('^' + current.query);
            // Get the URL of the current item.
            var item_url = $(this).attr('href');
            // Parse the item URL.
            var item = urlParse(item_url);
            if (item.query.match(base_query)) {
              query_data = item.query.replace(base_query, '');
            } else {
              var base = new RegExp('^/.+?/');
              var current_query_only = current.query.replace(base, '').split('/');
              var item_query_only = item.query.replace(base, '').split('/');
              var current_pairs = [];
              var item_pairs = [];
              for (var x = 0; x < current_query_only.length; x += 2) {
                current_pairs.push(current_query_only[x] + '/' + current_query_only[x + 1]);
              }
              for (x = 0; x < item_query_only.length; x += 2) {
                item_pairs.push(item_query_only[x] + '/' + item_query_only[x + 1]);
              }
              query_data = $(current_pairs).not(item_pairs).get();
              query_data = '/' + query_data[0];
            }
            $(this).attr('data-query', query_data);

            // console.log(query_data);
            var search_vars = [
              'search',
              'sort',
              'order',
              'page'
            ];
            var current_search_pairs = searchSplit(current.search);
            var item_search_pairs = searchSplit(item.search);
            var search_data = [];
            $.each(search_vars, function (i, v) {
              if ((item_search_pairs.hasOwnProperty(v) && current_search_pairs.hasOwnProperty(v) && item_search_pairs[v] !== current_search_pairs[v]) ||
                (item_search_pairs.hasOwnProperty(v) && !current_search_pairs.hasOwnProperty(v))) {
                search_data.push(v + '=' + item_search_pairs[v]);
              }
            });
            $(this).attr('data-search', search_data.join('&'));
          }
        });

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
          var clicked_query_data = $(this).attr('data-query');
          var clicked_search_data = $(this).attr('data-search');
          var clicked_search_pairs = searchSplit(clicked.search);
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

          if ($.inArray(selector, facet_selectors) >= 0) {
            var $parent = $(this).parent();
            $parent.children('a[class^=facetapi-]').toggleClass('facetapi-active');
            $parent.children('a[class^=facetapi-]').toggleClass('facetapi-inactive');
            $parent.toggleClass('facetapi-active');
            $parent.toggleClass('facetapi-inactive');
            $parent.parent().toggleClass('active');
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
                    var search_vars = [
                      'search',
                      'sort',
                      'order',
                      'page'
                    ];
                    var item_search_pairs = searchSplit(item.search);
                    $.each(search_vars, function (i, v) {
                      if (item_search_pairs.hasOwnProperty(v) && clicked_search_pairs.hasOwnProperty(v) && item_search_pairs[v] !== clicked_search_pairs[v]) {
                        item_search_pairs[v] = clicked_search_pairs[v];
                      } else if (!item_search_pairs.hasOwnProperty(v) && clicked_search_pairs.hasOwnProperty(v)){
                        item_search_pairs[v] = clicked_search_pairs[v];
                      } else if (item_search_pairs.hasOwnProperty(v) && !clicked_search_pairs.hasOwnProperty(v)){
                        item_search_pairs[v] = '';
                      }
                    });

                    new_search = '';
                    $.each(item_search_pairs, function (i, v) {
                      new_search += '&' + i + '=' + v;
                    });
                    new_search = new_search.substr(1);
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

          // Do the AJAX call to get the new results.
          searchLoading();
          currentAJAX = $.get(clicked.query, clicked.search, function (data) {
            var context = $(data);
            $('.current-search-item').html($('.current-search-item', context).html());
            $('.search-sort-widget').html($('.search-sort-widget', context).html());
            $('.view-search-api-resource-views').html($('.view-search-api-resource-views', context).html());
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
})(jQuery);
