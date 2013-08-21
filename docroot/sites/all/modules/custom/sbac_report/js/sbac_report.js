(function($) {
  Drupal.behaviors.sbac_report = {
    attach: function(context, settings) {
      var $dateRangeField = $('#date-range-field');
      var $dateSelected = $('#date-selected');

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

      $('.date-range-custom #to-date input').on('change', function() {
        var toInput = getDateInput(this);
        var fromInput = getDateInput('.date-range-custom #from-date input');
        if (fromInput && toInput) {
          var value = parseDateInput(fromInput) + '--' + parseDateInput(toInput);
          $dateRangeField.text(value);
          $dateRangeField.attr('value', value);
          $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
        }
      });

      $('.date-range-custom #from-date input').on('change', function() {
        var fromInput = getDateInput(this);
        var toInput = getDateInput('.date-range-custom #to-date input');
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

      $(context).on('click', '.autocomplete-suggestion', function() {
        var uid = $(this).data('uid');
        $('#sne-uid-field').text(uid);
        $('#sne-uid-field').attr('value', uid);
        console.log(uid);
      });

    }
  }
})(jQuery);
