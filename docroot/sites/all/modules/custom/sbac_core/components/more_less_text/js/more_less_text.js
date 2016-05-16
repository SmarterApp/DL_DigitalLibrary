(function($) {

Drupal.behaviors.more_less_text = {
  attach: function (context, settings) {
    var selectors = {
      wrapper:      '.more-less-text',
      summary:      '.more-less-text-summary',
      full:         '.more-less-text-full',
      trigger_more: '.more-less-text-trigger-more',
      trigger_less: '.more-less-text-trigger-less',
    };

    $(selectors.wrapper).each(function(i, wrapper) {
      wrapper = $(wrapper);

      $(selectors.trigger_more, wrapper).click(function(e) {
        e.preventDefault();

        $(selectors.summary, wrapper).hide();
        $(selectors.full, wrapper).show();

        return false;
      });

      $(selectors.trigger_less, wrapper).click(function(e) {
        e.preventDefault();

        $(selectors.full, wrapper).hide();
        $(selectors.summary, wrapper).show();

        return false;
      });
    });
  }  
};

})(jQuery);