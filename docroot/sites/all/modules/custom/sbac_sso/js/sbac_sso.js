(function ($) {
  var display_modal_timer = null;
  var redirect_to_login = null;
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
      // if timeout exists, reset it.
      if (redirect_to_login != null) {
        clearTimeout(redirect_to_login);
      }
    },
    reset_timers: function () {
      // if interval exists, reset it.
      if (display_modal_timer != null) {
        clearInterval(display_modal_timer);
      }
      // if timeout exists, reset it.
      if (redirect_to_login != null) {
        clearTimeout(redirect_to_login);
      }
      // 300 seconds = 5 minutes, warn at 200 seconds
      var php_cookie_lifetime = 60; // Drupal.settings.sbac_session_lifetime;
      // - 5 minutes to give the user time to make a decision.
      var session_lifetime = (php_cookie_lifetime - 10) * 1000;
      // minus 10 seconds to the session life time to give the system time to kick the user out completely.
      var php_session_lifetime = php_cookie_lifetime * 1000 - 10;
      display_modal_timer = setInterval(Drupal.behaviors.sbac_sso_session_expire.displayModal, session_lifetime);
      redirect_to_login = setTimeout(Drupal.behaviors.sbac_sso_session_expire.redirectToLogin, php_session_lifetime);
    },
    displayModal: function() {
      if (!$('#sbac-sso-session-expire-form').length) {
        $('#sbac-sso-session-expire').click();
      }
    },
    // redirect the user to the main page.
    redirectToLogin: function() {
      ajax_request = $.ajax({
        url: "/sbac-sso-logout",
        data: {'ajax' : true},
        success: function (data) {
          var response = jQuery.parseJSON(data);
          window.location.href = response.url;
        }
      });
    }
  };

})(jQuery);
