(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Some general JS behavior gets attached to the resource form.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_media_form_element = {
    attach: function (context, settings) {
      $("#sortable").sortable();
      $("#sortable").disableSelection();
    }
  };

})(jQuery);
