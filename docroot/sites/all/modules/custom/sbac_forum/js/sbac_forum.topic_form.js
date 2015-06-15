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
        // Client initially wanted it to say upload 100MB.
        // $('#edit-field-topic-files button[value^="Upload"]').html('Upload (100MB Max)');
      }

      // Hide upload button by default.
      $('#edit-field-topic-files .form-managed-file button').hide();

      // When a file is selected, dialog box closes, show the upload button
      $('#edit-field-topic-files .form-managed-file input').change(function() {
        $('#edit-field-topic-files .form-managed-file button').show('fast');
      });
    }
  };

})(jQuery);
