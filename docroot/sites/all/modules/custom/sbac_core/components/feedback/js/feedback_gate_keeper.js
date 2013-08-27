(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// Gate Keeper data
Feedback.gk = {
  form: '#eck-entity-form-edit-feedback-gate-keeper',

  // meets criteria radio buttons
  meets_criteria: {
    total: 0, // total number of Criteria Sets
    score: 0  // total number of 'yes' selections
  },
  
  // modal button data
  buttons: {
    meet: {
      button: '.action-meet',
      anchor: '#gate-keeper-meet',
    },
    not_meet: {
      button: '.action-not-meet',
      anchor: '#gate-keeper-not-meet',
    }
  },

  /**
   * Updates enabled/disabled button states based on radio values
   * 
   * @return {[type]} [description]
   */
  update_buttons: function() {
    // at least one 'no'
    if (Feedback.gk.meets_criteria.score != Feedback.gk.meets_criteria.total) {
      $(Feedback.gk.buttons.meet.button).attr('disabled', true);
      $(Feedback.gk.buttons.not_meet.button).attr('disabled', false);
    }
    // all options are 'yes'
    else {
      $(Feedback.gk.buttons.meet.button).attr('disabled', false);
      $(Feedback.gk.buttons.not_meet.button).attr('disabled', true);
    }
  }
};

Drupal.behaviors.feedback_gate_keeper = {
  attach: function (context, settings) {
    // make sure we've got a clean start with the scores
      Feedback.gk.meets_criteria.total = 0;
      Feedback.gk.meets_criteria.score = 0;

    // settings data
      if (!(data = Drupal.settings.feedback)) {
        return;
      }

    // set up button enable/disable toggling based on Meets Criterion radios
      $(data.meet_radios).each(function(i, selector) {
        // figure out the initial score/total counts
          Feedback.gk.meets_criteria.total++;

        // find the selected radio in current set and increment score if the
        // option is 'yes'
          if ($(selector + ':checked').val() == 1) {
            Feedback.gk.meets_criteria.score++;
          }

        // update button states when the value is changed; it's important to unbind the 
        // event prior to adding it so that we don't stack the same event multiple times (which
        // can happen with modals loading on the page - they'll trigger this attach
        // behavior, too)
          $(selector).unbind('change');
          $(selector).change(function() {
            Feedback.gk.meets_criteria.score = 0;

            $(data.meet_radios).each(function(j, sub_selector) {
              if ($(sub_selector + ':checked').val() == 1) {
                Feedback.gk.meets_criteria.score++;
              }
            });

            Feedback.gk.update_buttons();
          });
      });

    // after doing the counts above, we need to ensure the buttons are still in their right
    // states, as it's possible to get a discrepancy due to AJAX form reloads (data in form
    // state will be different from node's saved values, so the backend won't set the correct
    // button states, and needs to be fixed with this call)
      Feedback.gk.update_buttons();
  }
};

})(jQuery);