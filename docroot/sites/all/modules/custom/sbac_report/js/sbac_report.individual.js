(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_report_individual = {
    attach: function (context, settings) {
      var $uidField = $('#sne-uid-field');

      // Individual Report: Get the id from the autocomplete suggestion.
      $(document).on('click', '#autocomplete li', function () {
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
      $('#edit-sne').bind('input', function (e) {
        if ($uidField.val() != '') {
          $uidField.text('');
          $uidField.val('');
        }
      });


      // Associate the "Choose a state" label with the text field so that screen readers speak the label.
      var state_label = $('label[for=edit-state]');
      var state_textfield = $('#edit_state_chzn input[type=text]');
      if (state_label.length && state_textfield.length) {
        state_label.attr('for', 'edit_state_chzn_text');
        state_textfield.attr('id', 'edit_state_chzn_text');
      }

      // Add aria-required attribute to required fields
      $('#edit_state_chzn_text').attr('aria-required', 'true');

      var dialog = $('.sbac-report-modal');
      if (dialog.length) {
        var slider_width = 655;

        $('.flexslider', dialog).flexslider({
          animation: "slide",
          animationLoop: false,
          itemMargin: 0,
          itemWidth: slider_width,
          slideshow: false
        });

        $('.flexslider .slides li', dialog).css('width', slider_width + 'px');
        $('.flexslider-continue', dialog).click(function (e) {
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



