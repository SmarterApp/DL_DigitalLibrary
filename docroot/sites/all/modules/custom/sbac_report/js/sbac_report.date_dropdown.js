// Open the date popup on focus when navigating with the keyboard.
(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.date_popup_focus = {
    attach: function (context) {
      for (var id in Drupal.settings.datePopup) {
        $('#' + id).bind('focus', Drupal.settings.datePopup[id], function (e) {
          $(this).unbind(e);
        });
      }


      /**
       * Date range dropdown.
       */
      // TODO: make this a more general purpose class and pull out of the scope of reports.
      DateDropDown = (function ($, $which) {
        // class attributes
        // ? Do I need to individualize class attributes ?
        var $date_range_item = '.date-range-item';
        var $report_dropdown_toggle = '.report-dropdown-toggle';
        // id attributes
        var $drop_down_id = '#date-range-dropdown' + $which;
        var $selected_id = '#date-selected' + $which;
        var $date_range_field_id = '#date-range-field' + $which;
        var $from_date_input = '#from-date' + $which;
        var $to_date_input = '#to-date' + $which;
        var $ui_datepicker_div = '#ui-datepicker-div';

        /**
         * Action on the dropdown.
         *
         * @param {op}
         *   'show' or 'hide'.
         */
        function dropdown($dropdown, op, $dropdown_id) {
          // Show.
          if (op == 'show') {
            if ($dropdown.hasClass('hide')) {
              $dropdown.removeClass('hide');
              $($dropdown_id).addClass('show');
              $dropdown.unbind('hide');
              $dropdown.trigger('show');
            }
          }
          // Hide.
          else {
            if (!$dropdown.hasClass('hide')) {
              $dropdown.addClass('hide');
              $($dropdown_id).removeClass('show');
              $dropdown.unbind('show');
              $dropdown.trigger('hide');
            }
          }
        }

        /**
         * Toggle dropdown.
         */
        function toggleDropdown($dropdown, $dropdown_id) {
          // Show.
          if ($dropdown.hasClass('hide')) {
            dropdown($dropdown, 'show', $dropdown_id);
          }
          // Hide.
          else {
            dropdown($dropdown, 'hide', $dropdown_id);
          }
        }

        /**
         * Return the custom date input.
         */
        function getInput(el) {
          return $.trim($(el).val());
        }

        /**
         * Parse the custom date input into Ymd format.
         */
        function parseDateInput(input) {
          var dateArr = input.split('/');
          var month = date = year = '';
          if (dateArr[0] && dateArr[1] && dateArr[2]) {
            var month = dateArr[0];
            var date = dateArr[1];
            var year = dateArr[2];
          }
          return year + month + date;
        }

        function hideCustomDateFieldset(elm) {
          var selected = $(elm).find('input[name=date-select]:checked');
          if (selected.val() == 'custom') {
            $(elm).find('fieldset').show();
          }
          else {
            $(elm).find('fieldset').hide();
          }
        }

        function updatCustomoDateRangeField() {
          var toInput = getInput($to_date_input + " input");
          var fromInput = getInput($from_date_input + " input");
          var $dateRangeField = $($date_range_field_id);
          if (fromInput && toInput) {
            var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
            $dateRangeField.val(value);
          }
          else {
            $dateRangeField.val('');
          }
        }

        // DOM ready.
        $(function () {
          // Move the entire From Date and To Date label into one label so that screen readers speak the entire label.
          $('label[for=from-date' + $which + ']').remove();
          $('label[for=to-date' + $which + ']').remove();
          $('label[for=from-date' + $which + '-datepicker-popup-0]').text('From Date');
          $('label[for=to-date' + $which + '-datepicker-popup-0]').text('To Date');

          var fieldset = '#edit-date-range' + $which;
          hideCustomDateFieldset(fieldset);
          $(fieldset).change(function (e) {
            // Hide custom date fields if Custom Date option is not selected.
            hideCustomDateFieldset(e.currentTarget);

            // Update the hidden date range field when an item is selected.
            var selected = $(e.currentTarget).find('input[name=date-select]:checked');
            if (selected.val() == 'custom') {
              updatCustomoDateRangeField();
            }
            else {
              $('#date-range-field' + $which).val(selected.val());
            }
          });

          //var dropdownId = '#date-range-dropdown';
          var $dropdown = $($drop_down_id);

          $($report_dropdown_toggle).click(function (e) {
            e.preventDefault();
            e.stopPropagation();
            toggleDropdown($dropdown, $selected_id);
          });

          // On "show" event.
          $dropdown.on('show', function (e) {
            $(document).on('click keydown', function (e) {
              // ESC closes the dropdown.
              if (e.keyCode === 27) {
                dropdown($dropdown, 'hide', $selected_id);
              }
              // Clicking outside the dropdown will close the dropdown.
              // todo: make the detection of a click on the prev and next month buttons more robust.
              if (!$dropdown.is(e.target) && $dropdown.has(e.target).length === 0 &&
                $($ui_datepicker_div).has(e.target).length === 0 &&
                e.target.className !== "ui-icon ui-icon-circle-triangle-w" &&
                e.target.className !== "ui-icon ui-icon-circle-triangle-e") {
                dropdown($dropdown, 'hide', $selected_id);
              }
            });
          });

          // Update the dropdown text, when the user enters a custom date.
          $($to_date_input + " input").on('change', updatCustomoDateRangeField);

          // Update the dropdown text, when the user enters a custom date.
          $($from_date_input + " input").on('change', updatCustomoDateRangeField);

        });
      });


      // instantiate the drop downs for reports.
      DateDropDown(jQuery, '');
      DateDropDown(jQuery, '1');
    }
  };
})(jQuery);
