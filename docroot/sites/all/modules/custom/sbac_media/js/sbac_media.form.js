(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Some general JS behavior gets attached to the resource form.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_media_form_element = {
    attach: function (context, settings) {
      $('#sbac-media-internet-confirm').hide();
      var selector = '#sbac-media-list tbody';
      $(selector).sortable({
        items: 'tr'
      }).disableSelection();
    }
  };

})(jQuery);
