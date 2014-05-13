(function ($) {
  var display_modal_timer = null;
  var once = false;
  Drupal.behaviors.sbac_sso_session_expire = {
    attach: function (context, settings) {
      // attach the timeout and interval.
      if (!once) {
        Drupal.behaviors.sbac_sso_session_expire.reset_timers();
        once = true;
      }
    },
    detach: function (context, settings, trigger) {
      // if interval exists, reset it.
      if (display_modal_timer != null) {
        clearInterval(display_modal_timer);
      }
    },
    reset_timers: function () {
      // if interval exists, reset it.
      if (display_modal_timer != null) {
        clearInterval(display_modal_timer);
      }

      // 600 seconds = 10 minutes, warn at 5 mins.
      var php_cookie_lifetime = 400;
      // - 5 minutes to give the user time to make a decision.
      var session_lifetime = (php_cookie_lifetime - 300) * 1000;
      // minus 10 seconds to the session life time to give the system time to kick the user out completely.
      display_modal_timer = setInterval(Drupal.behaviors.sbac_sso_session_expire.display_modal, session_lifetime);
    },
    display_modal: function() {
      $('#sbac-sso-session-expire').click();
    }
  };

})(jQuery);
