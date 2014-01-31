(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  $(document).ready(function() {
    $('#sbac-flag-session-expire').hide();

    var php_cookie_lifetime = Drupal.settings.sbac_flag_lifetime;
    var session_lifetime = (php_cookie_lifetime - 10) * 1000; // - 10 seconds to give the user time to make a decision.
    var php_session_lifetime = session_lifetime + 10000; // add 10 seconds to the session life time to wait for a user decision.
    setInterval(display_modal, session_lifetime);
    setTimeout(redirectToLogin, php_session_lifetime);
  });

  /**
   * Controls the buttons at the bottom of the resource form.
   */
  function display_modal() {
    if (!$('#sbac-flag-session-expire-form').length) {
      $('#sbac-flag-session-expire').click();
    }
  }

  function redirectToLogin() {
    var url = location.protocol + '//' + location.hostname;
    window.location.assign(url);
  }

})(jQuery);
