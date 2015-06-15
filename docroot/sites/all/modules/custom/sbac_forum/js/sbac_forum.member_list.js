(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_forum_js_member_list = {
    attach: function (context, settings) {

      $('.member-control-icon').mouseenter(function() {
        $(this).next('.member-control-popup').show('fast');
      });

      $('.member-controls-wrapper').mouseleave(function() {
        $(this).children('.member-control-popup').hide('fast');
      });

    }
  };
})(jQuery);
