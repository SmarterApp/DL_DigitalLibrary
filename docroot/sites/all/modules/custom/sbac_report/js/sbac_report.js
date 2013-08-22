/**
 * @todo: separate out stuff that is only for the individual report.
 * But possibly can reuse the dropdown and date range.
 */
(function($) {
  /**
   * Action on the dropdown.
   *
   * @param {op}
   *   'show' or 'hide'.
   */
  function dropdown($dropdown, op) {
    // Show.
    if (op == 'show') {
      if ($dropdown.hasClass('hide')) {
        $dropdown.removeClass('hide');
        $('#date-selected').addClass('show');
        $dropdown.unbind('hide');
        $dropdown.trigger('show');
      }
    }
    // Hide.
    else {
      if (!$dropdown.hasClass('hide')) {
        $dropdown.addClass('hide');
        $('#date-selected').removeClass('show');
        $dropdown.unbind('show');
        $dropdown.trigger('hide');
      }
    }
  }

  /**
   * Toggle dropdown.
   */
  function toggleDropdown($dropdown) {
    // Show.
    if ($dropdown.hasClass('hide')) {
      dropdown($dropdown, 'show');
    }
    // Hide.
    else {
      dropdown($dropdown, 'hide');
    }
  }

  /**
   * Return the custom date input.
   */
  function getDateInput(el) {
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
    var $dateRangeField = $('#date-range-field');
    var $dateSelected = $('#date-selected');
    var $uidField = $('#sne-uid-field');
    var dropdownId = '#date-range-dropdown';
    var $dropdown = $(dropdownId);

    // Update the text when an item is selected.
    $('.date-range-item').click(function() {
      var value = $(this).data('value');
      var text = $(this).text();
      $dateRangeField.text(value);
      $dateRangeField.val(value);
      $dateSelected.text(text);
    });

    $('.report-dropdown-toggle').click(function(e) {
      e.preventDefault();
      e.stopPropagation();
      toggleDropdown($dropdown);
    });

    // On "show" event.
    $dropdown.on('show', function(e) {
      $(document).on('click keydown', function(e) {
        // ESC closes the dropdown.
        if (e.keyCode === 27) {
          dropdown($dropdown, 'hide');
        }
        // Clicking outside the dropdown will close the dropdown.
        if (!$dropdown.is(e.target) && $dropdown.has(e.target).length === 0 && $('#ui-datepicker-div').has(e.target).length === 0) {
          dropdown($dropdown, 'hide');
        }
      });
    });

    // Update the dropdown text, when the user enters a custom date.
    $('#to-date input').on('change', function() {
      console.log('to-date');
      var toInput = getDateInput(this);
      var fromInput = getDateInput('#from-date input');
      if (fromInput && toInput) {
        var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
        $dateRangeField.text(value);
        $dateRangeField.val(value);
        $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
      }
    });

    // Update the dropdown text, when the user enters a custom date.
    $('#from-date input').on('change', function() {
      console.log('from-date');
      var fromInput = getDateInput(this);
      var toInput = getDateInput('#to-date input');
      if (fromInput && toInput) {
        var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
        $dateRangeField.text(value);
        $dateRangeField.val(value);
        $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
      }
    });

    // Individual Report: Get the id from the autocomplete suggestion.
    $(document).on('click', '#autocomplete li', function() {
      console.log('auto');
      var uid = $(this).find('.autocomplete-suggestion').data('uid');
      $uidField.text(uid);
      $uidField.val(uid);
    });

    // Individual Report: clear the id on event "input".
    $('#edit-sne').bind('input', function(e) {
      console.log('clear');
      $uidField.text('');
      $uidField.val('');
    });

  });
})(jQuery);
