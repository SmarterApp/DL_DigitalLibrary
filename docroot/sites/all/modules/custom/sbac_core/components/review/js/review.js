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
        if ($('#review .alert-box.alert').length) {
          target_element.attr('style', 'display: block !important;');
        }
      }

    // tooltips
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

    // review yes/no voting
      var reviews = $('.entity-review');
      if (reviews.length) {
        var update_score = function (widget_wrapper) {
          var count = $('.count', widget_wrapper)
        };

        reviews.each(function (i, el) {
          var review = $(el);

          var help_wrapper = $('.field-name-review-helpfulness', review);
          var widget_wrapper = $('.rate-widget-yesno', review);

          if (help_wrapper.length && widget_wrapper.length) {
            $('.vote-yes', widget_wrapper).once('vote-yes').click(function(e) {
              e.preventDefault();

              update_score(widget_wrapper, 0);

              // $('.action-triggers .action-yes a').click();

              return false;
            });

            $('.vote-no', widget_wrapper).once('vote-no').click(function(e) {
              e.preventDefault();

              update_score(widget_wrapper, -1);

              // $('.action-triggers .action-no a').click();

              return false;
            });
          }
        });


        

      }
  },

  submit: function () {
    $(Review.reviews.form + ' .final-submit').click();
  }
};

})(jQuery);