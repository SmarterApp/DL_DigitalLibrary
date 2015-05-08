(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// Quality Criteria data
Feedback.qc = {
  form: '#eck-qc-form form',

  decision_link:     '#qc-complete',
  decision_options:  '.form-item-field-rec-options-und input',

  buttons: {
    complete: {
      button: '.action-complete',
      anchor: '#qc-complete'
    }
  }
};

Drupal.behaviors.feedback_quality_criteria = {
  attach: function (context, settings) {
    // settings data
      if (!(data = Drupal.settings.feedback)) {
        return;
      }

      if (!data.qc || data.qc.is_disabled) {
        return;
      }

    // set up descriptions for Quality Criterion Level radios
      $(data.level_radios).each(function(i, selector) {
        $(selector).unbind('change');
        $(selector).change(function() {
          var val = $(this).val();
          var wrapper = $(this).closest('.criteria-set-radios');
          var text = $.parseJSON(data.level_desc[val]);

          var desc = $('.desc', wrapper);
          desc.html(text).removeClass('hidden');
        });
      });

    // set up Recommendation Options radios
      if (data.qc.decision_radio_states) {
        Feedback.utilities.bind_decision_radios(
          Feedback.qc.decision_link,
          Feedback.qc.decision_options,
          data.qc.decision_radio_states,
          'qc-complete'
        );
      }
  }
};

})(jQuery);