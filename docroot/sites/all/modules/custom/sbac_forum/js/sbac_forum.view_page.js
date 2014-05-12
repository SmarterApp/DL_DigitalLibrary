(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_forum_js_view_page = {
    attach: function (context, settings) {

      $('.sbac-forum-vp-controls').mouseenter(function () {
        $('.sbac-forum-vp-controls-popup').show('fast');
      });

      $('.sbac-forum-vp-controls-wrapper').mouseleave(function () {
        $('.sbac-forum-vp-controls-popup').hide('fast');
      });

      $('.read-more').hide();
      $(".read-more-link").click(function () {
        var moreAndLess = $(".read-more").is(':visible') ? 'More Attributes' : 'Less Attributes';
        $(this).text(moreAndLess);
        $(".read-more").slideToggle();
      });

    }
  };

})(jQuery);
