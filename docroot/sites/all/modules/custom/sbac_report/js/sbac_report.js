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
        var toInput = $(this).attr('value');
        var fromInput = getDateInput('.date-range-custom #from-date input');
        if (fromInput && toInput) {
          var value = fromInput.replace(/-/g, '') + '--' + toInput.replace(/-/g, '');
          $dateRangeField.text(value);
          $dateRangeField.attr('value', value);
          $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
        }
      });

      $('.date-range-custom #from-date input').on('change', function() {
        var fromInput = $(this).attr('value').replace(/-/g, '');
        var toInput = $('.date-range-custom #to-date input').attr('value').replace(/-/g, '');
        if (fromInput && toInput) {
          var value = fromInput.replace(/-/g, '') + '--' + toInput.replace(/-/g, '');
          $dateRangeField.text(value);
          $dateRangeField.attr('value', value);
          $dateSelected.text(fromInput + ' ' + Drupal.t('to') + ' ' + toInput);
        }
      });

      function getDateInput(el) {
        return $(el).attr('value');
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
