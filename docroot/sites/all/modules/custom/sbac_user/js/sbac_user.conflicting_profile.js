(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_user_conflicting_profile = {
    attach: function (context, settings) {
      // Set OK button to disabled, user must select something.
      $('.sbac-user-conflict-submit').attr('disabled', 'disabled');
      $('.sbac-user-conflict-choice input').once('conflictingChoice', function() {
        $(this).click( function() {
          // On click of a radio button, enable the submit.
          $('.sbac-user-conflict-submit').removeAttr('disabled');
        });
      });
    }
  };
})(jQuery);
