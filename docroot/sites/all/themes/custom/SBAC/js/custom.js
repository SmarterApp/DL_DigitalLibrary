(function ($) {
  Drupal.behaviors.sbac_custom = {
    attach: function (context, settings) {
      $('#disable-feedback').click(function () {
        $.ajax({
          url: Drupal.settings.basePath + 'disable-feedback',
          success: function (data, textStatus, jqXHR) {
            // if (data == 0) {
              // document.getElementById('feedback-click').click();
              // }
              document.getElementById('feedback-click').click();
              $('#feedback-dropdown').removeClass('open');
          }
        });
      });
	
      $('#featured-content-container').slick({
          dots:true,
          arrows:false,
          autoplay:true,
          autoplaySpeed:4000,
          pauseOnHover:true,
          pauseOnDotsHover:true,
          swipe:false,
	  speed:1000,
	  fade:true,
      });

      $('.disabled').click(function (e) {
                e.preventDefault();
                //do other stuff when a click happens
      });
    }
  };
})(jQuery);
