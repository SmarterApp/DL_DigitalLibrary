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
        fade:true
      });

      $('.disabled').click(function (e) {
        e.preventDefault();
        //do other stuff when a click happens
      });

      $('.disabler').mousedown(function (e) {
        e.preventDefault();
        // Hide this button and add another in its place that is disabled to prevent the button being re-enabled.
        var button = $(this)[0].outerHTML;
        button = $(button).prop('disabled', true).attr('id', '').removeClass('progress-disabled');
        $(this).hide();
        $(this).after(button);
        $(this).remove();
      });

      $('.sbac-search-toggle').click(function (e) {
        $(this).fadeOut(function () {
          $('.search .block-views').fadeIn();
        })
      })
    }
  };
})(jQuery);
