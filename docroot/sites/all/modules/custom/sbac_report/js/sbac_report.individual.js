/**
 * Individual Report.
 */
(function($) {
  // DOM ready.
  $(function() {
    var $uidField = $('#sne-uid-field');

    // Individual Report: Get the id from the autocomplete suggestion.
    $(document).on('click', '#autocomplete li', function() {
      var uid = $(this).find('.autocomplete-suggestion').data('uid');
      $uidField.text(uid);
      $uidField.val(uid);
    });

    $('#autocomplete li').keypress( function(event) {
      var keypressed = event.which;
      if(keypressed == 13){
//        var uid = $(this).find('.autocomplete-suggestion').data('uid');
//        $uidField.text(uid);
//        $uidField.val(uid);
        $(this).click();
      }
    });

    // Individual Report: clear the id on event "input".
    $('#edit-sne').bind('input', function(e) {
      if ($uidField.val() != '') {
        $uidField.text('');
        $uidField.val('');
      }
    });

  });
})(jQuery);
