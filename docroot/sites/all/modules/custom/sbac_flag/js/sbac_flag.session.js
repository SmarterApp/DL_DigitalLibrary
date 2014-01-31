(function ($) {

  var display_modal_timer = null;
  var redirect_to_login = null;
  var once = false;

  Drupal.behaviors.sbac_node_form = {
    attach: function (context, settings) {
      // hide the modal button.
      $('#sbac-flag-session-expire').hide();
      // attach the timeout and interval.
      if (!once) {
        Drupal.behaviors.sbac_node_form.reset_timers();
        once = true;
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

      // 600 seconds = 10 minutes, warn at 5 mins.
      var php_cookie_lifetime = Drupal.settings.sbac_flag_lifetime; // cookie lifetime set by PHP session timeout.
      var session_lifetime = (php_cookie_lifetime - 10) * 1000; // - 10 seconds to give the user time to make a decision.
      var php_session_lifetime = php_cookie_lifetime * 1000; // add 10 seconds to the session life time to wait for a user decision.
      display_modal_timer = setInterval(Drupal.behaviors.sbac_node_form.display_modal, session_lifetime);
      redirect_to_login = setTimeout(Drupal.behaviors.sbac_node_form.redirectToLogin, php_session_lifetime);
    },
    // click the hidden modal button.
    display_modal: function() {
      if (!$('#sbac-flag-session-expire-form').length) {
        $('#sbac-flag-session-expire').click();
      }
    },
    // redirect the user to the main page.
    redirectToLogin: function() {
      ajax_request = $.ajax({
        type: 'POST',
        url: "/sbac-flag/logout-user",
        success: function(data) {
          var url = location.protocol + '//' + location.hostname;
          window.location.assign(url);
        }
      });
    }
  };

})(jQuery);
