(function ($) {
  Drupal.behaviors.sbac_featured_content = {
    attach: function (context, settings) {
      // If JS is working, turn cursor into a pointer and redirect on click
      $('.featured-content-inner').css( 'cursor', 'pointer' );
      $('.featured-content-inner').click(function(){
         window.location = '/' + $(this).attr('url');
      });
    }
  };
})(jQuery);