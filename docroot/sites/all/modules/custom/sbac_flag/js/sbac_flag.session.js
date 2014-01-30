(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  $(document).ready(function() {
    $('#sbac-flag-session-expire').hide();

    var session_lifetime = Drupal.settings.sbac_flag_lifetime * 1000;
    var php_session_lifetime = session_lifetime + 10000;
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
