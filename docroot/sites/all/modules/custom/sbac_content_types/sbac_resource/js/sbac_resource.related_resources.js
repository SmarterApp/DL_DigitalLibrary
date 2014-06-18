(function($) {

  if (typeof SBAC_Related_Resource == 'undefined') {
    SBAC_Related_Resource = {};
  }

  SBAC_Related_Resource.related_resources = {
    slider: '.resources-container',
    slider_child: '.slides li',
    slider_width: 280,

    init_flexslider : function() {
      if ((slider = $(SBAC_Related_Resource.related_resources.slider)).length) {
        $(slider).css('width', '840px');
        slider.flexslider({
          animation: "slide",
          animationLoop: false,
          itemMargin: 0,
          itemWidth: SBAC_Related_Resource.related_resources.slider_width,
          slideshow: false
        });
        $(SBAC_Related_Resource.related_resources.slider_child, slider).css('width', SBAC_Related_Resource.related_resources.slider_width + 'px');
      }
    }
  };

  Drupal.behaviors.SBAC_Related_Resources = {
    attach: function (context, settings) {
      $('.sbac-hover').hover(
        function() {
          $(this).next('ul').addClass('open');
        },
        function() {
          $(this).next('ul').removeClass('open');
        }
      );

      SBAC_Related_Resource.related_resources.init_flexslider();
      // we need to re-initialize the flexslider when a user clicks on the related resources tab
      var section = $('#review .section-container .section-5');
      if (section.length) {
        section.bind('classAdded', function(e, css_class) {
          if (css_class == 'active') {
            SBAC_Related_Resource.related_resources.init_flexslider();
          }
        });
      }
      // we also need to re-init the slder when a user leaves the browser window and
      // comes back to it, because the slider occasionally chooses to go on vacation
      $(window).focus(function() {
        SBAC_Related_Resource.related_resources.init_flexslider();
      });
    }
  };

})(jQuery);