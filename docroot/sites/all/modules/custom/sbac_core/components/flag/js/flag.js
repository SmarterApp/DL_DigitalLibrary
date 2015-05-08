(function($) {

flag = {
  submit: false,
  review_id: 0
};

Drupal.behaviors.flag = {
  attach: function (context, settings) {
    // hide form initially
      $('.flag-review-end-use-wrap').parent().once('setup-flag', function () {
        var field_wrap = $(this);
        var form = $('.flag-review-end-use-wrap form', field_wrap);
        if (form.length) {
          form = $(form);
          
          if (!$('body').hasClass('page-admin')) {
            form.hide();
          }
        }
      });

    // main forms functionality
      var forms = $('.flag-review-end-use-wrap form');
      if (forms.length) {
        forms.each(function(i, form_item) {
          var form = $(form_item);
          var form_wrap_id = '#' + form.parent().attr('id');

          // position 'details' field after the selected radio button
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

          // show the form when trigger is clicked
            var form_toggle_trigger = $('.field-name-review-vote a.flag-trigger', form.parents('.group-footer'));
            if (form_toggle_trigger.length) {
              var form_toggle_trigger_event = function(e) {
                e.preventDefault();

                if (form.css('display') == 'block') {
                  $('a.flag-cancel', form).click();
                }
                else {
                  form.show();
                }

                return false;
              };

              form_toggle_trigger.unbind('click');
              form_toggle_trigger.click(form_toggle_trigger_event);
            }

          // hide & clear the form when cancel is clicked
            var cancel_trigger = $('a.flag-cancel', form);
            if (cancel_trigger.length) {
              var cancel_trigger_event = function(e) {
                e.preventDefault();

                // remove error/status messages which may have been prepended to the form
                var previous_sibling = form.prev();
                if ($('.alert-box', previous_sibling)) {
                  previous_sibling.remove();
                }

                // remove error labels
                $('.error', form).each(function(i, el) {
                  $(el).removeClass('error');
                });

                issue_type.prop('checked', false);
                details.val('');
                details_wrap.hide();
                form.hide();

                return false;
              };

              cancel_trigger.unbind('click');
              cancel_trigger.click(cancel_trigger_event);
            }

          // form submission & modal
            var submit_button = $('.actions .form-submit', form);
            if (submit_button.length) {
              var submit_button_event = function(e) {
                e.preventDefault();

                // this is the default flag value, prior to form submission
                var default_value = -1;
                
                // this will get called (recursively) to check the current value of the flag, as
                // well as re-set it to the default value after the change_callback has been called
                var value_callback = function (value) {
                  if (typeof value !== 'undefined') {
                    Drupal.settings.flag.form_error = value;
                  }

                  return Drupal.settings.flag.form_error;
                };

                // this will get called when the value has changed (ie. been updated by the form), 
                // and error_status will contain the new flag value
                var change_callback = function (error_status) {
                  // proceed only if there are no form errors
                  if (!error_status) {
                    if (flag.submit) {
                      var flag_wrap = $('#entity-review-' + flag.review_id + ' .flag');
                      flag_wrap.html(Drupal.settings.flag.update_message);
                      flag.submit = false;
                    }
                    else {
                      var modal_anchor = $(form_wrap_id + ' a.use-dialog');
                      if (modal_anchor.length) {
                        modal_anchor.trigger('click');
                      }
                    }
                  }
                };

                // The form itself will return JS which will set a flag to either 1 or 0, and
                // this function will recursively check for that flag value every 200ms.
                Drupal.behaviors.js_watch_value.watch_value(default_value, value_callback, change_callback);

                return false;
              };

              submit_button.unbind('mousedown', submit_button_event);
              submit_button.mousedown(submit_button_event);
            }
        });
      }
  },

  submit_modal_callback_flag: function (data) {
    // set flag so we don't call the modal again
    flag.submit = true;
    flag.review_id = data.review_id;

    // update action taking place
    var select = $(data.review_wrapper + ' select.submit-action option[value="submit"]');
    select.prop('selected', true);

    $(data.review_wrapper + ' form .actions .form-submit').mousedown();
  }
};

})(jQuery);