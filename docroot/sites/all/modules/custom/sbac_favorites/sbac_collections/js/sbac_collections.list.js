(function($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_collections_list = {
    attach: function (context, settings) {
      $('.sbac-hover').hover(
        function () {
          $(this).next('ul').addClass('open');
        },
        function () {
          $(this).next('ul').removeClass('open');
        }
      );

      $('.view-display-id-user_list_view').addClass('view-display-id-list_view');
    }
  };
})(jQuery);
