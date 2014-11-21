(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_central_critical_message = {
    attach: function (context, settings) {
      $(window).load( function() {
        if ($('#sbac-central-critical-message').length) {
          $('#sbac-central-critical-message').click();
          return false;
        }
      });
    }
  };

})(jQuery);