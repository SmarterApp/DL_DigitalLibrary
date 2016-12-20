(function($) {
  Drupal.behaviors.resource_guidance = {
    attach: function (context, settings) {
      // check for rating cookie so this doesn't fire after tab changes on resource pages
      if ($.cookie('rating') === null) {
        //no cookie
        // Star Rating Modal
        $('#star-rating-modal-container').foundation('reveal', 'open');
        $.cookie("rating", 1);
      } else {
       return false;
      }
//      $('.reveal-modal-bg').hide();
    }
  };
})(jQuery);