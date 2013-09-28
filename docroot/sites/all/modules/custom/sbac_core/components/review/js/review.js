(function($) {

if (typeof Drupal.settings.review == 'undefined') {
  Drupal.settings.review = {};
}

if (typeof Review == 'undefined') {
  Review = {};
}

Review.reviews = {
  form_trigger: '.review-form-trigger',
  form: '#review-end-use-wrap form',
};

Drupal.behaviors.review = {
  attach: function (context, settings) {
    console.log('attach behavior');

    // form showing functionality on 'Write Review' button
    var trigger_element = $(Review.reviews.form_trigger);
    var target_element = $(Review.reviews.form);

    if (trigger_element.length && target_element.length) {
      trigger_element.click(function(e) {
        e.preventDefault();

        trigger_element.hide();
        target_element.show();
        target_element.attr('style', 'display: block !important;');

        return false;
      });

      // if errors are found on the page, force the form to display
      if ($('#review .alert-box.alert').length) {
        target_element.attr('style', 'display: block !important;');
      }
    }

    var tooltip = $('.account-tooltip');
    if (tooltip.length) {
      $(tooltip).each(function(i, el) {
        var wrapper = $(el);

        $('.account-tooltip-trigger', wrapper).once('tooltip-trigger').mouseover(function () {
          $('.account-tooltip-body', wrapper).show();
        });

        $(wrapper).once('tooltip-trigger').mouseout(function () {
          $('.account-tooltip-body', wrapper).hide();
        });
      }); 
    }
  },

  submit: function () {
    $(Review.reviews.form + ' .final-submit').click();
  }
};

})(jQuery);