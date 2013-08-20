(function($) {
  Drupal.behaviors.sbac_report = {
    attach: function(context, settings) {
      $('.date-range-item').click(function() {
        var value = $(this).data('value');
        var text = $(this).text();
        $('#date-range-field').text(value);
        $('#date-range-field').attr('value', value);
        var $selected = $('#date-selected');
        $selected.text(text);
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
    }
  }
})(jQuery);
