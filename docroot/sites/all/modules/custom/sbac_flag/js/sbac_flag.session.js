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

      // 600 seconds = 10 minutes, warn at 5 mins.
      // cookie lifetime set by PHP session timeout.
      var php_cookie_lifetime = Drupal.settings.sbac_flag_lifetime;
      // - 5 minutes to give the user time to make a decision.
      var session_lifetime = (php_cookie_lifetime - 300) * 1000;
      // minus 10 seconds to the session life time to give the system time to kick the user out completely.
      var php_session_lifetime = php_cookie_lifetime * 1000 - 10;
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
      var temp_url = window.location.href;
      var nid = Drupal.settings.sbac_flag_node;
      var review = Drupal.settings.sbac_flag_resource_review_id;

      var type = 'resource';
      if (temp_url.indexOf('resource-review')) {
        type = 'resource-review';
      }
      ajax_request = $.ajax({
        type: 'POST',
        url: "/sbac-flag/logout-user",
        data: {'type' : type, 'nid' : nid, 'eck_review': review},
        success: function(data) {
          var response = jQuery.parseJSON(data);
          window.location.href = response.url;
        }
      });
    }
  };

})(jQuery);
