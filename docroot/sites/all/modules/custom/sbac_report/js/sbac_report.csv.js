(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_report_csv = {
    attach: function (context, settings) {
      function updateLabel(label_for, textfield_id) {
          var label = $('label[for=' + label_for + ']');
          var textfield = $('#' + textfield_id + ' input[type=text]');
          if (label.length && textfield.length) {
            label.attr('for', label_for + '_text');
            textfield.attr('id', label_for + '_text');
          }
      }

      function addDeleteButtonTitles(elm) {
        $(elm).find('li').each(function(i, v) {
            var selection = $(v).find('span').text();
            $(v).find('a').attr('title', 'Delete ' + selection);
        });
      }

      // Associate the "Choose a state" label with the text field so that screen readers speak the label.
      updateLabel('edit-state--2', 'edit_state__2_chzn');
      // Associate the "Choose User Groups" label with the text field so that screen readers speak the label.
      updateLabel('edit-user-group-dropdown', 'edit_user_group_dropdown_chzn');
      // Associate the "Filter for SNE or SLT Members" label with the text field so that screen readers speak the label.
      updateLabel('edit-sne-slt-filter', 'edit_sne_slt_filter_chzn');

      $.each(['#edit_state__2_chzn', '#edit_user_group_dropdown_chzn', '#edit_sne_slt_filter_chzn',
              '#edit_resource_type_dropdown_chzn', '#edit_resource_status_dropdown_chzn', '#edit_resource_subject_dropdown_chzn',
              '#edit_resource_grade_dropdown_chzn', '#edit_resource_attribute_dropdown_chzn'], function(i, v) {

          // Add a title attribute to the delete tags on the User Activity and Detailed Resource tabs.
          addDeleteButtonTitles(v);
          $(v + ' ul.chzn-choices').bind('DOMSubtreeModified', function(e) {
              addDeleteButtonTitles(v);
          });

          // Add aria-required attribute to required fields.
          $(v + ' input[type=text').attr('aria-required', 'true');
      });

//      setTimeout(function(){ $('.sbac-report-download-link').click(); }, 5000);
//      not sure why this is not working...
//      $('.sbac-report-download-link').click(function (e) {
//        alert('hi');
//      });
    }
  };

})(jQuery);
