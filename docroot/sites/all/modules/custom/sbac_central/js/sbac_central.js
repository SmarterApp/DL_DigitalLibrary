(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_central_critical_message = {
    attach: function (context, settings) {
      $(window).load( function() {
        // Click the button for the critical message modal.
        if ($('#sbac-central-critical-message').length) {
          $('#sbac-central-critical-message').click();
          return false;
        }
      });
    }
  };

})(jQuery);