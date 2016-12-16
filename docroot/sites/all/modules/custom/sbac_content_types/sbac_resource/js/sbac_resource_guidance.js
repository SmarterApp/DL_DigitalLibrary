(function($) {
  Drupal.behaviors.resource_guidance = {
    attach: function (context, settings) {
       // Star Rating Modal
      $('#star-rating-modal-container').foundation('reveal', 'open');
//      $('.reveal-modal-bg').hide();
    }
  };
})(jQuery);