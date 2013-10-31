(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// About data
Feedback.about = {
  slider: '#review .flexslider',
  slider_child: '.slides li',
  slider_width: 413,

  init_flexslider : function() {
    // set up flexslider on the about page's resource slideshow
    if ((slider = $(Feedback.about.slider)).length) {
      $(slider).css('width', '820px'); // why? because.

      slider.flexslider({
        animation: "slide",
        animationLoop: false,
        itemMargin: 0,
        itemWidth: Feedback.about.slider_width,
        slideshow: false
      });

      $(Feedback.about.slider_child, slider).css('width', Feedback.about.slider_width + 'px');
    }
  }
};

Drupal.behaviors.feedback_about = {
  attach: function (context, settings) {
    Feedback.about.init_flexslider();

    // we need to re-initialize the flexslider when a user clicks on the about tab
    var section = $('#review .section-container .section-1');
    if (section.length) {
      section.bind('classAdded', function(e, css_class) {
        if (css_class == 'active') {
          Feedback.about.init_flexslider();
        }
      });
    }

    // we also need to re-init the slder when a user leaves the browser window and
    // comes back to it, because the slider occasionally chooses to go on vacation
    $(window).focus(function() {
      Feedback.about.init_flexslider();
    });
  }
};

})(jQuery);