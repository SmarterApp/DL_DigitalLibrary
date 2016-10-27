(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_resource_js_smart_search = {
    attach: function (context, settings) {

      $('a.ssw-edit-link').once('ssw-edit-link-event', function() {
        $(this).click(function() {
          $(this).parents('.smart-search-welcome-main-wrapper').hide('slow', function() {
            $('.dlr-page-filter-block-wrapper').removeClass('js-hide');
            $('#sbac-search-filter-button').click();
          });
          return false;
        });
      });

    }
  };
})(jQuery);
