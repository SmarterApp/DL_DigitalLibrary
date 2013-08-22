(function($) {
  Drupal.behaviors.sbac_report = {
    attach: function(context, settings) {
      var $dateRangeField = $('#date-range-field');
      var $dateSelected = $('#date-selected');
      var $uidField = $('#sne-uid-field');
      var dropdownId = '#date-range-dropdown';
      var $dropdown = $(dropdownId);

      $('.date-range-item').click(function() {
        var value = $(this).data('value');
        var text = $(this).text();
        $dateRangeField.text(value);
        $dateRangeField.attr('value', value);
        $dateSelected.text(text);
      });
      $('.report-dropdown-toggle').click(function(e) {
        e.preventDefault();
        var $dropdown = $('#date-range-dropdown');
        if ($dropdown.hasClass('hide')) {
          $dropdown.removeClass('hide');
        }
        else {
          $dropdown.addClass('hide');
        }
      });

      $('#to-date input').on('change', function() {
        var toInput = getDateInput(this);
        var fromInput = getDateInput('#from-date input');
        if (fromInput && toInput) {
          var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
          $dateRangeField.text(value);
          $dateRangeField.attr('value', value);
          $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
        }
      });

      $('#from-date input').on('change', function() {
        var fromInput = getDateInput(this);
        var toInput = getDateInput('#to-date input');
        if (fromInput && toInput) {
          var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
          $dateRangeField.text(value);
          $dateRangeField.attr('value', value);
          $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
        }
      });

      /**
       * Return the custom date input.
       */
      function getDateInput(el) {
        return $.trim($(el).attr('value'));
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

      /**
       * Action on the dropdown.
       *
       * @param {op}
       *   'show' or 'hide'.
       */
      function dropdown(op) {
        // Show.
        if (op == 'show') {
          if ($dropdown.hasClass('hide')) {
            $dropdown.removeClass('hide');
            $dropdown.unbind('hide');
            $dropdown.trigger('show');
          }
        }
        // Hide.
        else {
          if (!$dropdown.hasClass('hide')) {
            $dropdown.addClass('hide');
            $dropdown.unbind('show');
            $dropdown.trigger('hide');
          }
        }
      }

      /**
       * Toggle dropdown.
       */
      function toggleDropdown() {
        // Show.
        if ($dropdown.hasClass('hide')) {
          dropdown('show');
        }
        // Hide.
        else {
          dropdown('hide');
        }
      }

      // Get the id from the autocomplete suggestion.
      $(context).on('click', '#autocomplete li', function() {
        var uid = $(this).find('.autocomplete-suggestion').data('uid');
        $uidField.text(uid);
        $uidField.attr('value', uid);
      });

    }
  }
})(jQuery);
