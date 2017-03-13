(function($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.forumSelect = {
    attach: function(context, settings) {
      $(function() {
        $('.forum-goal-select').change(function () {
          $('.regional .view').hide();
          $('.'+$(this).val()).show();
        });
      });
    }
  };

  Drupal.behaviors.accountDropdown = {
    attach: function(context, settings) {
      $('.user-info').click(function() {
        if (!$('.user-info .f-dropdown').hasClass('open')) {
          var selectedDiv = $('.open');
          selectedDiv.hide();
          selectedDiv.removeClass('open');
        }
      });
    }
  };

  Drupal.behaviors.rolesAdmin = {
    attach: function(context, settings) {
      $(function() {
      // Rename user role selections
      $(".form-item-roles-7 label").text("lead SLT");
      $(".form-item-roles-13 label").text("resource moderator");
      });
    }
  };

  Drupal.behaviors.helpTextify = {
    attach: function(context, settings) {
      $(function() {
        $('#edit-pass').attr('autocomplete', 'off');
      });
    }
  };

  Drupal.behaviors.toggleGrid = {
    attach: function(context, settings) {

      $(document).ready(function() {

        // Indicate previously selected items.
        $('#modal-content').change(function() {
          var keyedItems = JSON.parse(sessionStorage.getItem('ccssKeys'));
          $(keyedItems).each(function() {
            $('#edit-term-' + this).once().attr('checked', true);
            $('#edit-term-' + this).parents('label').css({
              'background': 'red',
            });
          });
        })

        // Switcharoo between Facets CCSS and custom CCSS filter.
        url = window.location.href;
        var s = url.split('f[').pop().charAt(0);

        urlLibArg = 'digital-library-resources';

        if (url.indexOf(urlLibArg) == -1) {
          sessionStorage.removeItem('lastClicked');
          sessionStorage.removeItem('ccssSet');
        }

        // Controls the search box and plugs in a clear all x.
        if (0 == $('#search-x-clear').length) {
          $('.form-item-sbac-digital-library-resources-text').append('<div id="search-x-clear"></div>');
        }
        if ($('#edit-sbac-digital-library-resources-text').length) {
          if ($('#edit-sbac-digital-library-resources-text').val().length) {
            $('#search-x-clear').text('x');
          }
        }
        $('#search-x-clear').click(function() {
          location.href = window.location.pathname;
        })

        $('#edit-sbac-digital-library-resources-text').on('keyup', function() {
          if ($('#edit-sbac-digital-library-resources-text').val().length) {
            $('#search-x-clear').text('x');
          } else {
            $('#search-x-clear').empty();
          }
        })

        // Toggle between distinguished and all.
        $('#faux-click-sbac').click(function() {
          if (window.location.href.indexOf('distinguished') > -1) {
            location.href = '/digital-library-resources';
          } else {
            location.href = '/digital-library-resources/distinguished';
          }

        })
        if (sessionStorage['gridview'] == 'list') {
          $('.view-digital-library-resources .views-row, #click-toggle-a').addClass('list');
        }

        // Toggle cards list and grid view.
        $('#click-toggle-a').click(function(e) {
          $(this).toggleClass('list');
          $('.view-digital-library-resources .views-row').toggleClass('list');
          if (!$(this).hasClass('list')) {
            sessionStorage['gridview'] = 'grid';
            $(this).text('List View');
          } else {
            $(this).text('Grid View');
            sessionStorage['gridview'] = 'list';
          }
        });

        // This is where we create the plus and minus signs for item list expansion.
        $('.expanded, .collapsed').each(function() {
          if ($(this).children('.facetapi-checkbox').hasClass('facetapi-inactive')) {
            $(this).removeClass('minus-sign');
            $(this).addClass('plus-sign');
          } else {
            $(this).removeClass('plus-sign');
            $(this).addClass('minus-sign');
          }
        })

        $('.expanded, .collapsed').each(function() {
          $(this).addClass('plus-sign');
          $(this).removeClass('minus-sign');
          $(this).click(function(event) {
            $(this).children('.item-list').toggleClass('item-list-size');

            if ($(this).hasClass('plus-sign')) {
              $(this).not($(this).parents().parents()).addClass('minus-sign');
              $(this).not($(this).parents().parents()).removeClass('plus-sign');
            } else {
              $(this).not($(this).parents().parents()).addClass('plus-sign');
              $(this).not($(this).parents().parents()).removeClass('minus-sign');
            }
            event.stopPropagation();
          })
        })

        // Tracks the last active facet block to display open on page load.
        //$('#' + sessionStorage.getItem('lastClicked') + ' .facet-label a.category-hide').addClass('activated');
        $('#' + sessionStorage.getItem('lastClicked') + ' .item-list').css({
          //'height': '300px',
        });

        $('a.facetapi-checkbox').each(function() {
          $(this).text().replace('/(-)/', '');
        })

        $('.facetapi-checkbox').each(function() {
          $(this).click(function() {
            var theId = $(this).closest('.facet-block').attr('id');
            sessionStorage.setItem('lastClicked', theId);
            $('#spinner-load').css({
              'display': 'block'
            })
          })
        })

        // When user clicks outside of facets, close facet blocks.
        $('.filters, .top-bar, .page-wrap').click(function(event) {
          if (event.target === this) {
            $('*').removeClass('activated');

            $('.facet-block .item-list').css({
              'height': '0',
            });
          }
        });


        $('a.category-hide').each(function() {

          // Tracks active filter selections, changes styles accordingly.
          var targetList = $(this).parents().siblings().children().children().children(':checkbox:checked').length;
          if (targetList > 0) {
            $(this).addClass('selected');
          } else {
            $(this).removeClass('selected');
          }

          $(this).click(function() {
            $('*').not(this).removeClass('activated');
            $('.item-list').addClass('not-activated').css({
              'height': '0',
            });
            if ($(this).hasClass('activated')) {
              $(this).removeClass('activated').addClass('not-activated');
              $(this).parents().siblings('.item-list').css({
                'height': '0',
              });
            } else {
              $(this).addClass('activated');
              $(this).removeClass('not-activated');
              $(this).parents().siblings('.item-list').css({
                'height': 'auto',
                'max-height': '300px'
              });
            }
          });

        });

        // Add selected to our ccss container
        if ($('#facet-common-core-state-standards .facet-label a').hasClass('selected')) {
          $('.categories-container .large-4 ul li').addClass('selected');
        }

      });
    }
  };

})(jQuery);
