(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// Quality Criteria data
Feedback.reviews = {

};

Drupal.behaviors.feedback_reviews = {
  attach: function (context, settings) {
    // settings data
      if (!(data = Drupal.settings.feedback)) {
        return;
      }

    // 
  }
};

})(jQuery);