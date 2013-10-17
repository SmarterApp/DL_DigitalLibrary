/**
 * Date range dropdown.
 */
// TODO: make this a more general purpose class and pull out of the scope of reports.
// TODO: instantiate the html too.
DateDropDown = (function($, $which) {

  // class attributes
  // ? Do I need to individualize class attributes ?
  var $date_range_item='.date-range-item',//+$which,
      $report_dropdown_toggle='.report-dropdown-toggle'; //+$which;
    // id attributes
  var $drop_down_id='#date-range-dropdown'+$which, $selected_id='#date-selected'+$which,
      $date_range_field_id='#date-range-field'+$which, $from_date_input='#from-date'+$which,
      $to_date_input='#to-date'+$which, $ui_datepicker_div='#ui-datepicker-div';//+$which;

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

  // DOM ready.
  $(function() {
    var $dateRangeField = $($date_range_field_id);
    var $dateSelected = $($selected_id);
    //var dropdownId = '#date-range-dropdown';
    var $dropdown = $($drop_down_id);

    // Update the text when an item is selected.
    $($date_range_item).click(function() {
      var value = $(this).data('value');
      var text = $(this).text();
      $dateRangeField.text(value);
      $dateRangeField.val(value);
      $dateSelected.text(text);
    });

    $($report_dropdown_toggle).click(function(e) {
      e.preventDefault();
      e.stopPropagation();
      toggleDropdown($dropdown, $selected_id);
    });

    // On "show" event.
    $dropdown.on('show', function(e) {
      $(document).on('click keydown', function(e) {
        // ESC closes the dropdown.
        if (e.keyCode === 27) {
          dropdown($dropdown, 'hide', $selected_id);
        }
        // Clicking outside the dropdown will close the dropdown.
        if (!$dropdown.is(e.target) && $dropdown.has(e.target).length === 0 && $($ui_datepicker_div).has(e.target).length === 0) {
          dropdown($dropdown, 'hide', $selected_id);
        }
      });
    });

    // Update the dropdown text, when the user enters a custom date.
    $("#"+$to_date_input+" input").on('change', function() {
      var toInput = getInput(this);
      var fromInput = getInput($from_date_input+" input");
      if (fromInput && toInput) {
        var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
        $dateRangeField.text(value);
        $dateRangeField.val(value);
        $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
      }
    });

    // Update the dropdown text, when the user enters a custom date.
    $("#"+$from_date_input+" input").on('change', function() {
      var fromInput = getInput(this);
      var toInput = getInput($to_date_input+" input");
      if (fromInput && toInput) {
        var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
        $dateRangeField.text(value);
        $dateRangeField.val(value);
        $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
      }
    });

  });
});

// instantiate the drop downs for reports.
DateDropDown(jQuery, '');
DateDropDown(jQuery, '1');
