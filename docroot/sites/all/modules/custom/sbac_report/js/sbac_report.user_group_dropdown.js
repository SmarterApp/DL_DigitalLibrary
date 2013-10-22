///**
// * User Group dropdown.
// */
//(function($) {
//  /**
//   * Action on the dropdown.
//   *
//   * @param {op}
//   *   'show' or 'hide'.
//   */
//  function dropdown_user_group($dropdown, op) {
//    // Show.
//    if (op == 'show') {
//      if ($dropdown.hasClass('hide')) {
//        $dropdown.removeClass('hide');
//        $('#user-group-selected').addClass('show');
//        $dropdown.unbind('hide');
//        $dropdown.trigger('show');
//      }
//    }
//    // Hide.
//    else {
//      if (!$dropdown.hasClass('hide')) {
//        $dropdown.addClass('hide');
//        $('#user-group-selected').removeClass('show');
//        $dropdown.unbind('show');
//        $dropdown.trigger('hide');
//      }
//    }
//  }
//
//  /**
//   * Toggle dropdown.
//   */
//  function toggleDropdown_user_group($dropdown) {
//    // Show.
//    if ($dropdown.hasClass('hide')) {
//      dropdown_usergroup($dropdown, 'show');
//    }
//    // Hide.
//    else {
//      dropdown_user_group($dropdown, 'hide');
//    }
//  }
//
//  /**
//   * Return the custom date input.
//   */
//  function getInput(el) {
//    return $.trim($(el).val());
//  }
//
//  /**
//   * Parse the custom date input into Ymd format.
//   */
//  function parseDateInput(input) {
//    var dateArr = input.split('/');
//    var month = date = year = '';
//    if (dateArr[0] && dateArr[1] && dateArr[2]) {
//      var month = dateArr[0];
//      var date = dateArr[1];
//      var year = dateArr[2];
//    }
//    return year + month + date;
//  }
//
//  // DOM ready.
//  $(function() {
//    var $dateRangeField = $('#user-group-field');
//    var $dateSelected = $('#date-selected');
//    var dropdownId = '#user-group-dropdown';
//    var $dropdown = $(dropdownId);
//
//    // Update the text when an item is selected.
//    $('.user-group-item').click(function() {
//      var value = $(this).data('value');
//      var text = $(this).text();
//      $dateRangeField.text(value);
//      $dateRangeField.val(value);
//      $dateSelected.text(text);
//    });
//
//    $('.report-dropdown-toggle').click(function(e) {
//      e.preventDefault();
//      e.stopPropagation();
//      toggleDropdown_user_group($dropdown);
//    });
//
//    // On "show" event.
//    $dropdown.on('show', function(e) {
//      $(document).on('click keydown', function(e) {
//        // ESC closes the dropdown.
//        if (e.keyCode === 27) {
//            toggleDropdown_user_group($dropdown, 'hide');
//        }
//        // Clicking outside the dropdown will close the dropdown.
//        if (!$dropdown.is(e.target) && $dropdown.has(e.target).length === 0 && $('#ui-user-grouppicker-div').has(e.target).length === 0) {
//            toggleDropdown_user_group($dropdown, 'hide');
//        }
//      });
//    });
//
//
//
//  });
//})(jQuery);
