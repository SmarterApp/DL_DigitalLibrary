(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Some general JS behavior gets attached to the resource form.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_forum_subnav_form = {
    attach: function (context, settings) {
      // Forum Modal
      $('.new-forum-link').click(function() {
        $('#forum-modal-container').foundation('reveal', 'open');
        $('.reveal-modal-bg').show();       
      });
    }
  };

})(jQuery);
