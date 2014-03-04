(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Some general JS behavior gets attached to the resource form.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_forum_topic_form = {
    attach: function (context, settings) {

      if ($('#edit-field-topic-files button').length) {
        $('#edit-field-topic-files button[value^="Upload"]').html('Upload (100MB Max)');
      }
    }
  };

})(jQuery);
