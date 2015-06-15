(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  var isDirty = false;
  var clicked = false;

  Drupal.behaviors.sbac_flag_form = {
    attach: function (context, settings) {
      if ($('.drupal-alert-box').length && $('#modal-content').length && $('.flag-modal-cont').length) {
          $('.flag-modal-cont').prepend($('.drupal-alert-box'));
      }

      var flag_moderation = Drupal.settings.flag_moderation;
      if (flag_moderation) {
        var save_button = $('#sbac-resource-save-continue');
        save_button.hide();

        var cancel_button = $('.sbac-resource-cancel-button');
        cancel_button.hide();

        var save_continue = $('#edit-save-continue');
        save_continue.hide();

        var resolve_all_flags = $('#sbac-flag-resolve-all-flags');
        resolve_all_flags.hide();

        var remove_resource = $('#sbac-flag-remove-resource');
        remove_resource.hide();
      }

      $('.sbac-flag-resolve-all-flags').one( "click",  function() {
        $('#chosen-flag-option').val(1);
        var changes_made = 0;
        if (isDirty) {
          changes_made = 1;
        }
        $('#changes-made').val(changes_made);
        clicked = true;
        $('#edit-save-continue').mousedown();
        return false;
      });

      $('.sbac-flag-remove-resource').click( function() {
        $('#chosen-flag-option').val(2);
        $('#edit-save-continue').mousedown();
        return false;
      });
    }
  };

  /**
   * Displays an error message to the user if changes have been made.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_flag_exit_plan = {
    attach: function (context, settings) {
      // don't want to track changes on edit resource tags page
      if ($('#review').length) {
        return;
      }

      var resource_state = Drupal.settings.resource_workbench_current_state;
      $(':input').change( function () {
        if (!isDirty) {
          isDirty = true;
        }
      });

      $('.delete-media a').click( function () {
        isDirty = true;
      });

      $(':input[type=text], textarea').keyup( function () {
        if (!isDirty) {
          isDirty = true;
        }
      });

      if (resource_state == 'creation') {
        isDirty = false;
      }

      $('#resource-help-box .backButton').click(function() {
        isDirty = false;
      });

      $('#sbac-resource-save-continue button').click(function () {
        isDirty = false;
      });

      $('#edit-save-continue').mousedown(function () {
        if (!clicked) {
          isDirty = false;
          clicked = false;
        }
      });
    }
  };

})(jQuery);
