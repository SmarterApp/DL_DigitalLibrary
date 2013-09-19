(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// Post data
Feedback.post = {
  form: '#eck-entity-form-edit-feedback-post',

  decision_link:     '#post-complete',
  decision_options:  '.form-item-field-post-options-und input',

  buttons: {
    complete: {
      button: '.action-complete',
      anchor: '#post-complete'
    }
  }
};

Drupal.behaviors.feedback_post = {
  attach: function (context, settings) {
    // settings data
      if (!(data = Drupal.settings.feedback)) {
        return;
      }

      if (!data.post || data.post.is_disabled) {
        return;
      }

    // set up Post Options radios
      if (data.post.decision_radio_states) {
        Feedback.utilities.bind_decision_radios(
          Feedback.post.decision_link,
          Feedback.post.decision_options,
          data.post.decision_radio_states,
          'post-complete'
        );
      }
  }
};


})(jQuery);