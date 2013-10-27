/**
 * Individual Report.
 */
(function($) {
  // DOM ready.
  $(function() {
    var $uidField = $('#sne-uid-field');

    // todo: do this the right way, fix autocomplete without a timeout call.
    setTimeout(function ()  {  $("#edit-sne").attr( 'autocomplete','ON'); }, 500);

    // Individual Report: Get the id from the autocomplete suggestion.
    $(document).on('click', '#autocomplete li', function() {
      var uid = $(this).find('.autocomplete-suggestion').data('uid');
      $uidField.text(uid);
      $uidField.val(uid);
    });

    if (Drupal.jsAC.prototype.onkeydown) {
      /**
       * Override the autocomplete handler for the "keydown" event.
       */
      Drupal.jsAC.prototype.onkeydown = function (input, e) {
        if (!e) {
          e = window.event;
        }
        switch (e.keyCode) {
          case 40: // down arrow.
            this.selectDown();
            return false;
          case 38: // up arrow.
            this.selectUp();
            return false;
          case 13: // enter.
            $(this.selected).trigger('click');
            return true;
          default: // All other keys.
            return true;
        }
      };
    }

    // Individual Report: clear the id on event "input".
    $('#edit-sne').bind('input', function(e) {
      if ($uidField.val() != '') {
        $uidField.text('');
        $uidField.val('');
      }
    });

  });

  Drupal.behaviors.sbac_report_individual = {
    attach: function (context, settings) {
      var dialog = $('.dialog_sbac_report_individual_modal_form');
      if (dialog.length) {
        var slider_width = 572;

        $('.flexslider', dialog).flexslider({
          animation: "slide",
          animationLoop: false,
          itemMargin: 0,
          itemWidth: slider_width,
          slideshow: false
        });

        $('.flexslider .slides li', dialog).css('width', slider_width + 'px');

        $('.flexslider-continue', dialog).click(function(e) {
          e.preventDefault();

          var next = $('.flex-next', dialog);
          var first = $('.flex-control-paging li:first-child a', dialog);

          if (!next.hasClass('flex-disabled')) {
            next.click();
          }
          else {
            first.click();
          }

          return false;
        });
      }
    }
  };
})(jQuery);



