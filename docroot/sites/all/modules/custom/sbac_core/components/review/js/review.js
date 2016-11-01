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
        if ($('#review #review-end-use-wrap .alert-box.alert').length) {
          target_element.attr('style', 'display: block !important;');
        }
      }

    // review yes/no voting
      var reviews = $('.entity-review');
      if (reviews.length) {
        var update_score = function (help_wrapper, change) {
          var count_el    = $('.count', help_wrapper);
          var total_el    = $('.total', help_wrapper);
          var percent_el  = $('.percent', help_wrapper);

          var count   = parseInt(count_el.html());
          var total   = parseInt(total_el.html());

          count += change;
          total += 1;

          percent = 0;
          if (total) {
            percent = Math.round(count / total * 100);
          }

          count_el.html(count);
          total_el.html(total);
          percent_el.html(percent);
        };

        reviews.each(function (i, el) {
          var review = $(el);

          var help_wrapper = $('.field-name-review-helpfulness', review);
          var widget_wrapper = $('.rate-widget-yesno', review);

          if (help_wrapper.length && widget_wrapper.length) {
            $('.vote-yes', widget_wrapper).once('vote-yes').click(function(e) {
              e.preventDefault();

              update_score(help_wrapper, 1);

              $('.action-triggers .action-yes a', widget_wrapper).click();

              return false;
            });

            $('.vote-no', widget_wrapper).once('vote-no').click(function(e) {
              e.preventDefault();

              update_score(help_wrapper, 0);

              $('.action-triggers .action-no a', widget_wrapper).click();

              return false;
            });
          }
        });
      }
      // add placeholder text to review form long text details field
      $('#edit-field-details-und-0-value').attr('placeholder','Begin typing your feedback here...');
  },

  submit: function () {
    $(Review.reviews.form + ' .final-submit').click();
  }
};

})(jQuery);