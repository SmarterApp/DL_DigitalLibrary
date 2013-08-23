/**
 * Individual Report.
 */
(function($) {
  // DOM ready.
  $(function() {
    var $uidField = $('#sne-uid-field');

    // Individual Report: Get the id from the autocomplete suggestion.
    $(document).on('click', '#autocomplete li', function() {
      console.log('complete');
      var uid = $(this).find('.autocomplete-suggestion').data('uid');
      $uidField.text(uid);
      $uidField.val(uid);
    });

    // Individual Report: clear the id on event "input".
    $('#edit-sne').bind('input', function(e) {
      console.log('clear');
      if ($uidField.val() != '') {
        $uidField.text('');
        $uidField.val('');
      }
    });

  });
})(jQuery);
