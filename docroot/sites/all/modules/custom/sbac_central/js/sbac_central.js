(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_central_critical_message = {
    attach: function (context, settings) {
      $(window).load( function() {
        // If the user clicked esc key, check if we need to fire the
        // Welcome Tutorial window by looking for a hidden element.
        $(document).keyup(function(e) {
          if (e.keyCode == 27) {
            if ($('#sbac-central-click-welcome-tutorial').length) {
              $('#sbac-help-welcome-tutorial').click();
              $('#sbac-central-click-welcome-tutorial').remove();
              return false;
            }
          }
        });

        // Click the button for the critical message modal.
        if ($('#sbac-central-critical-message').length) {
          $('#sbac-central-critical-message').click();
          return false;
        }
      });
    }
  };

})(jQuery);