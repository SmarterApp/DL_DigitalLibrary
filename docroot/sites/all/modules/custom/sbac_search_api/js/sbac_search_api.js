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
      $('a .facetapi-collapsible-handle').once().click(function (event) {
        plusMinusToggler(this);
      });

      // Add a click area to the fake checkboxes.
      $('.facetapi-facet').each(function () {
        var href = $(this).children('a.facetapi-active, a.facetapi-inactive').attr('href');
        $(this).prepend('<a class="checkbox-spacer" href="' + href + '">&nbsp;</a>');
      });

      // Show/hide the sorts on click.
      $('.default-sort').once().click(function (e) {
        $(this).toggleClass('active');
        $('.search-api-sorts').toggle();
      });

      // Set the placeholder in the search box.
      $('#views-exposed-form-search-api-resource-views-instructional #edit-search').attr('placeholder', 'search within results');
    }
  };
})(jQuery);