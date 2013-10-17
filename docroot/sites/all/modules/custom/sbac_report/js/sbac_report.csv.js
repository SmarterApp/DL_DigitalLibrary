/**
 * CSV Report.
 */
//(function($) {
//  // DOM ready.
//  $(function() {
//    var $uidField = $('#sne-uid-field');
//
//    // CSV Report: Get the id from the autocomplete suggestion.
//    $(document).on('click', '#autocomplete li', function() {
//      var uid = $(this).find('.autocomplete-suggestion').data('uid');
//      $uidField.text(uid);
//      $uidField.val(uid);
//    });
//
//    if (Drupal.jsAC.prototype.onkeydown) {
//      /**
//       * Override the autocomplete handler for the "keydown" event.
//       */
//      Drupal.jsAC.prototype.onkeydown = function (input, e) {
//        if (!e) {
//          e = window.event;
//        }
//        switch (e.keyCode) {
//          case 40: // down arrow.
//            this.selectDown();
//            return false;
//          case 38: // up arrow.
//            this.selectUp();
//            return false;
//          case 13: // enter.
//            $(this.selected).trigger('click');
//            return true;
//          default: // All other keys.
//            return true;
//        }
//      };
//    }
//
//    // CSV Report: clear the id on event "input".
//    $('#edit-sne').bind('input', function(e) {
//      if ($uidField.val() != '') {
//        $uidField.text('');
//        $uidField.val('');
//      }
//    });
//
//  });
//})(jQuery);
