(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};
  /**
   * Display playlist messaging on Materials tab help text if SLT
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.playlist_template = {
    attach: function (context, settings) {
      $('.playlist-template').show();
    }
  };  

})(jQuery);