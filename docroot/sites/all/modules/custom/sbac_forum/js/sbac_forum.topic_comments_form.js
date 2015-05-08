(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_forum_js_topic_comments_form = {
    attach: function (context, settings) {

      // Hide upload button by default.
      $('#edit-field-topic-comment-files .form-managed-file button').hide();

      // When a file is selected, dialog box closes, show the upload button
      $('#edit-field-topic-comment-files .form-managed-file input').change(function() {
        $('#edit-field-topic-comment-files .form-managed-file button').show('fast');
      });
    }
  };



})(jQuery);
