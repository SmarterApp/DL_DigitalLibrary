(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_node_form = {
    attach: function (context, settings) {
      if ($('.drupal-alert-box').length && $('#modal-content').length && $('.flag-modal-cont').length) {
        $('.flag-modal-cont').prepend($('.drupal-alert-box'));
      }
    }
  };

})(jQuery);
