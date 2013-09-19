(function($) {

if (typeof Drupal.settings.review == 'undefined') {
  Drupal.settings.review = {};
}

if (typeof Review == 'undefined') {
  Review = {};
}

Review.reviews = {
  form_trigger: '.review-form-trigger',
  form: '#eck-entity-form-add-review-end-use',
};

Drupal.behaviors.review = {
  attach: function (context, settings) {
    // form showing functionality on 'Write Review' button
    var trigger_element = $(Review.reviews.form_trigger);
    var target_element = $(Review.reviews.form);

    if (trigger_element.length && target_element.length) {
      trigger_element.click(function(e) {
        e.preventDefault();

        trigger_element.hide();
        target_element.show();

        return false;
      });
    }
  },

  clear_review: function() {
    console.log('clearing!');
  }
};

})(jQuery);