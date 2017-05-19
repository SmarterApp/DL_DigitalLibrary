(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_report_csv = {
    attach: function (context, settings) {
      // Associate the "Choose a state" label with the text field so that screen readers speak the label.
      Drupal.behaviors.sbac_report_csv.updateLabel('edit-state--2', 'edit_state__2_chzn');
      // Associate the "Choose User Groups" label with the text field so that screen readers speak the label.
      Drupal.behaviors.sbac_report_csv.updateLabel('edit-user-group-dropdown', 'edit_user_group_dropdown_chzn');

      $.each([
        '#edit_state__2_chzn', '#edit_user_group_dropdown_chzn',
        '#edit_resource_type_dropdown_chzn', '#edit_resource_status_dropdown_chzn',
        '#edit_resource_subject_dropdown_chzn',
        '#edit_resource_grade_dropdown_chzn', '#edit_resource_attribute_dropdown_chzn'
      ], function (i, v) {
        // Add a title attribute to the delete tags on the User Activity and Detailed Resource tabs.
        Drupal.behaviors.sbac_report_csv.addDeleteButtonTitles(v);
        $(v + ' ul.chzn-choices').bind("propertychange", function (e) {
          Drupal.behaviors.sbac_report_csv.addDeleteButtonTitles(v);
        });

        // Add aria-required attribute to required fields.
        $(v + ' input[type=text').attr('aria-required', 'true');
      });

      // Autocomplete functionality for User Activity Report
      var uidField = $('#uid-field');
  
      // User Activity Report: Get the id from the autocomplete suggestion.
      $(document).on('click', '.form-item-user #autocomplete li', function () {
        var uid = $(this).find('.autocomplete-suggestion').data('uid');
        uidField.text(uid);
        uidField.val(uid);
      });

      // Individual Report: clear the id on event "input".
      $('#edit-user').bind('input', function (e) {
        if (uidField.val() != '') {
          uidField.text('');
          uidField.val('');
        }
      });
    },
    updateLabel: function (label_for, textfield_id) {
      var label = $('label[for=' + label_for + ']');
      var textfield = $('#' + textfield_id + ' input[type=text]');
      if (label.length && textfield.length) {
        label.attr('for', label_for + '_text');
        textfield.attr('id', label_for + '_text');
      }
    },
    addDeleteButtonTitles: function (elm) {
      var selection = null;
      $(elm).find('li').each(function (i, v) {
        selection = $(v).find('span').text();
        if (selection != "" && selection != null) {
          selection = 'Delete ' + selection;
          if ($(v).find('a').length) {
            $(v).find('a').attr('title', selection);
          }
        }
      });
    }
  };

})(jQuery);
