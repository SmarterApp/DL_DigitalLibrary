(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_sso_conflicting_profile = {
    attach: function (context, settings) {
      // Set OK button to disabled, user must select something.
      $('.sbac-sso-conflict-submit').attr('disabled', 'disabled');
      $('.sbac-sso-conflict-choice input').once('conflictingChoice', function() {
        $(this).click( function() {
          // On click of a radio button, enable the submit.
          $('.sbac-sso-conflict-submit').removeAttr('disabled');
        });
      });
    }
  };
})(jQuery);
