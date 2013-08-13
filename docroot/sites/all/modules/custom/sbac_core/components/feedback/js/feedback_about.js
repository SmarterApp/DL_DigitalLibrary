(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// About data
Feedback.about = {
  slider: '.flexslider'
};

Drupal.behaviors.feedback_about = {
  attach: function (context, settings) {
    // set up flexslider on the about page's resource slideshow
    if ((slider = $(Feedback.about.slider)).length) {
      slider.flexslider({
        animation: "slide",
        animationLoop: false,
        itemMargin: 0,
        itemWidth: 413,
        slideshow: false
      });
    }
  }
};

})(jQuery);