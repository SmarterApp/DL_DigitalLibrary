(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// general elements
Feedback.wrapper =            '.review-wrap';
Feedback.messages =           '.alert-box';
Feedback.messages_error =     '.alert-box.alert';
Feedback.messages_existing =  '.row > .main-container > .alert-box';
Feedback.messages_container = '#main';
Feedback.action_select =      'select[name=action]';
Feedback.submit_button =      '.button.secondary';

// general utility functions
Feedback.utilities = {
  /**
   * This implements a custom success/fail callback for our AJAX form, since there
   * isn't anything out of the box with Drupal's AJAX/FAPI implementation.
   *
   * The form itself will return JS which will set a flag to either 1 or 0, and
   * this function will recursively check for that flag value every 200ms.
   * 
   * @param  {[type]} default_value   Default value to identify a non-set flag (ex. -1).
   * @param  {[type]} value_callback  Callback function which will return the current
   *                                  flag value, and optionally change it to the passed value.
   * @param  {[type]} change_callback Callback function which will receive the new
   *                                  flag value (to act upon it) when it's detected.
   * @return {[type]}                 [description]
   */
  watch_value: function(default_value, value_callback, change_callback) {
    // current_value = value_callback();
    // while (current_value == default_value) {
    //   setTimeout(function() {
    //    current_value = value_callback();
    //   }, 200);
    // }

    // change_callback(current_value);
    // value_callback(default_value);

    setTimeout(function() {
      var current_value = value_callback();
      // target value is still set to the default, so call self again
      if (current_value == default_value) {
        Feedback.utilities.watch_value(default_value, value_callback, change_callback);
      }
      // target value has changed, so pass it to the callback and reset
      else {
        change_callback(current_value);
        value_callback(default_value);
        return;
      }
    }, 200);
  },

  /**
   * When the Gate Keeper form is submitted and returned, we check for messages and
   * move them to the "standard" locaton in DOM. If the messages contain errors (which
   * prevented form submission), we also scroll the user to the top of the page so
   * they can see the errors.
   * 
   * @return {[type]} [description]
   */
  move_messages: function () {
    // remove existing messages to avoid stacking of multiple form submissions' errors
    var existing_messages = $(Feedback.messages_existing);
    if (existing_messages) {
      existing_messages.detach();
    }

    var messages = $(Feedback.wrapper + ' ' + Feedback.messages);
    if (messages.length) {
      messages.insertBefore(Feedback.messages_container);

      // if there are errors, scroll to the top
      if ($(Feedback.messages_error).length) {
        Feedback.utilities.scroll_to_top();
      }
    }
  },

  /**
   * Scrolls the viewpoint to the top of the page.
   * 
   * @return {[type]} [description]
   */
  scroll_to_top: function () {
    $('html, body').animate({scrollTop: 0}, 300);
  },

  /**
   * Sets the form action.
   * 
   * @param {[type]} type [description]
   * @param {[type]} val  [description]
   */
  set_action: function (type, val) {
    // update the action which took place
    if (Feedback[type] && Feedback[type]['form']) {
      $(Feedback[type]['form'] + ' ' + Feedback.action_select).val(val);
    }
  },

  /**
   * JS callback for modal form submissions.
   * We set the form's action select to identify the form action being performed
   * (button being clicked).
   * 
   * @param  {[type]} type [description]
   * @param  {[type]} val  [description]
   * @return {[type]}      [description]
   */
  submit_modal_callback: function (type, val) {
    Feedback.utilities.set_action(type, val);

    // update the action which took place
    if (Feedback[type] && Feedback[type]['form']) {
      // by triggering the form's submit() and not doing a click/mousedown on an 
      // actual button, we bypass the AJAX form submission and do a regular page
      // reload, which will show the 'completed' version of content
      $(Feedback[type]['form']).submit();
    }
  },

  /**
   * Binds to the Change even of given radio button set and updates
   * the AJAX event on the 'complete review' functionality to load
   * the correct modal.
   * 
   * @param  {[type]} link      [description]
   * @param  {[type]} options   [description]
   * @param  {[type]} states    [description]
   * @param  {[type]} ajax_base [description]
   * @return {[type]}           [description]
   */
  bind_decision_radios: function (link, options, states, ajax_base) {
    var link = $(link);

    $(options).each(function(i, el) {
      $(el).unbind('change');

      $(el).change(function() {
        var val = $(this).val();

        // update new state
        var parts = link.attr('href').split('/');
        parts[5] = states[val];
        var new_url = parts.join('/');
        link.attr('href', new_url);

        // bind new ajax behavior to all items showing the class.
        var element_settings = {};
        element_settings.progress = { 'type': 'throbber' };
        element_settings.url = new_url;
        element_settings.event = 'click';

        link.removeClass('use-dialog-processed').removeClass('ajax-processed');
        link.unbind(element_settings.event);

        Drupal.ajax[ajax_base] = new Drupal.ajax(ajax_base, link, element_settings);
      });
    });
  }
};

Drupal.behaviors.feedback = {
  attach: function (context, settings) {
    // catch the submit button's submit behaviour and assign form error-watching functionality
      $(Feedback.wrapper + ' ' + Feedback.submit_button).once('mousedown-trigger').mousedown(function(e, modal_anchor) {
        // this is the default flag value, prior to form submission
        var default_value = -1;
        
        // this will get called (recursively) to check the current value of the flag, as
        // well as re-set it to the default value after the change_callback has been called
        var value_callback = function (value) {
          if (typeof value !== 'undefined') {
            Drupal.settings.feedback.form_error = value;
          }

          return Drupal.settings.feedback.form_error;
        };

        // this will get called when the value has changed (ie. been updated by the form), 
        // and error_status will contain the new flag value
        var change_callback = function (error_status) {
          Feedback.utilities.move_messages();

          // now that the form submission is complete, we set the action back to default
          // state; this must happen in the change callback!!
          Feedback.utilities.set_action('gk', 'save_close');

          // proceed only if there are no form errors
          if (!error_status) {
            // if we got here via a modal button, we should now open the modal
            if (modal_anchor) {
              console.log('triggering anchor: ' + modal_anchor);
              $(modal_anchor).trigger('click');
            }
            // othewise we got here via the Save & Close button, so let's "close" this tab
            // by switching to the About tab
            else {
              var hash = 'review-about';
              // update hash value in browser for bookmarking purposes and general consistency
              window.location.hash = hash;
              // switch to the new tab
              Drupal.behaviors.sections.switch_tab('#' + hash);

              // we might as well scroll the user to the top of the page to show any
              // confirmation/status messages
              Feedback.utilities.scroll_to_top();
            }
          }
        };

        Feedback.utilities.watch_value(default_value, value_callback, change_callback);
      });

    // propagate click events on our form buttons to the anchors which will trigger the
    // appropriate modals
      $.each(['gk', 'qc', 'post'], function (key, name) {
        if (Feedback[name] && Feedback[name].buttons) {
          $.each(Feedback[name].buttons, function(button_key, data) {
            $(data.button).once('mousedown-event').click(function(e) {
              e.preventDefault();

              // update action to the one taking place
              Feedback.utilities.set_action(name, data.action);

              // a modal-triggering button has been clicked, so the first thing we need to do
              // is ajax-submit the form to validate it, and we do this by clicking the Save &
              // Close button
              $(Feedback.wrapper + ' ' + Feedback[name].form + ' ' + Feedback.submit_button).trigger('mousedown', data.anchor);

              return false;
            });
          });
        }
      });
  },

  /**
   * Callbacks triggered by modal form submissions. 
   * 
   * @return {[type]} [description]
   */
  submit_modal_callback_not_meet: function () {
    Feedback.utilities.submit_modal_callback('gk', 'not_meet');
  },
  submit_modal_callback_meet: function () {
    Feedback.utilities.submit_modal_callback('gk', 'meet');
  },
  submit_modal_callback_not_recommend: function () {
    Feedback.utilities.submit_modal_callback('qc', 'complete');
  },
  submit_modal_callback_recommend_reservation: function () {
    Feedback.utilities.submit_modal_callback('qc','complete');
  },
  submit_modal_callback_recommend: function () {
    Feedback.utilities.submit_modal_callback('qc','complete');
  },
  submit_modal_callback_recommend_distinction: function () {
    Feedback.utilities.submit_modal_callback('qc','complete');
  },
  submit_modal_callback_reject: function () {
    Feedback.utilities.submit_modal_callback('post','reject');
  },
  submit_modal_callback_post: function () {
    Feedback.utilities.submit_modal_callback('post','post');
  },
  submit_modal_callback_post_distinction: function () {
    Feedback.utilities.submit_modal_callback('post','post_distinction');
  }
};

})(jQuery);