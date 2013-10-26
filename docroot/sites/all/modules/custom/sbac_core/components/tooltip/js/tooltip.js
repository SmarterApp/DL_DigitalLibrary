(function($) {

Drupal.behaviors.tooltip = {
  attach: function (context, settings) {
    // tooltips
    var tooltip = $('.devtools-tooltip');
    if (tooltip.length) {
      $(tooltip).each(function(i, el) {
        var wrapper = $(el);

        $('.devtools-tooltip-trigger', wrapper).once('devtools-tooltip-trigger').mouseover(function() {
          $('.devtools-tooltip-body', wrapper).show();
        });

        $(wrapper).once('devtools-tooltip-trigger').mouseout(function() {
          $('.devtools-tooltip-body', wrapper).hide();
        });
      }); 
    }
  }
};

})(jQuery);