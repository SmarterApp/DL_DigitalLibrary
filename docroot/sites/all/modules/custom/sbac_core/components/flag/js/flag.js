(function($) {

Drupal.behaviors.flag = {
  attach: function (context, settings) {
    var forms = $('.flag-review-end-use-wrap form');
    if (forms.length) {
      forms.each(function(i, form) {
        form = $(form);

        var details_wrap = $('.field-name-field-details', form);
        var details = $('textarea', details_wrap);
        var issue_type = $('.field-name-field-issue-type input', form);

        if (details.val() == '') {
          details_wrap.hide();
        }

        var on_change = function(event, clear) {
          if (typeof event == 'undefined') {
            event = {};
          }

          if (typeof clear == 'undefined') {
            clear = true;
          }

          if (clear) {
            // clear value & trigger change() so that maxlength_js updates counters
            details.val('').change();
          }

          // move Details field to immediately after selected radio
          var selected = $('.field-name-field-issue-type input:checked', form);
          if (selected.length) {
            details_wrap.show().insertAfter(selected.parent());
          }
        };

        on_change(false, false);

        issue_type.change(on_change);
      });
    }
  }
};

})(jQuery);