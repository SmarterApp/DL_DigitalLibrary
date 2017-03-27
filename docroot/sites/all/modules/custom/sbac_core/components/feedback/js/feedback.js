(function($) {

if (typeof Feedback == 'undefined') {
  Feedback = {};
}

// general elements
Feedback.wrapper =            '.feedback-wrap';
Feedback.messages =           '.alert-box';
Feedback.messages_error =     '.alert-box.alert';
Feedback.messages_existing =  '.row > .main-container #main > .alert-box';
Feedback.messages_container = '#main';
Feedback.action_select =      'select[name=action]';
Feedback.submit_button =      '.button.secondary';

// general utility functions
Feedback.utilities = {
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
      messages.prependTo(Feedback.messages_container);

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
   * @param {[type]} action [description]
   * @param {[type]} name   [description]
   */
  set_action: function (action, name) {
    var selector = '';

    // update the action which took place
    if (Feedback[name] && Feedback[name]['form']) {
      selector += Feedback[name]['form'];
    }

    selector += ' ';
    selector += Feedback.action_select;

    $(selector).val(action);
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
    Feedback.utilities.set_action(val, type);

    // update the action which took place
    if (Feedback[type] && Feedback[type]['form']) {
      if ($('#dialog-feedback_gate_keeper_form-wrapper').val()) {
        var modal_popup = document.getElementById("dialog-feedback_gate_keeper_form-wrapper");
        var buttons = modal_popup.getElementsByTagName("button");
        var button = buttons[0];
        var buttonID = button.getAttribute("id");
      }

      // by triggering the form's submit() and not doing a click/mousedown on an 
      // actual button, we bypass the AJAX form submission and do a regular page
      // reload, which will show the 'completed' version of content
      $(Feedback[type]['form']).submit();

      // Disables button to prevent multiple button presses.
      if ($('#dialog-feedback_gate_keeper_form-wrapper').val()) {
        buttonID.classList.add("form-button-disabled");
      }
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
        Feedback.utilities.set_action('save_close');

        // proceed only if there are no form errors
        if (!error_status) {
          // if we got here via a modal button, we should now open the modal
          if (modal_anchor) {
            $(modal_anchor).trigger('click');
          }
          // otherwise we got here via the Save & Close button, so let's "close" this tab
          // by switching to the About tab
          else {
            // switch to the new tab
            Drupal.behaviors.sections.switch_tab('#review-about');

            // we might as well scroll the user to the top of the page to show any
            // confirmation/status messages
            Feedback.utilities.scroll_to_top();

            Feedback.about.init_flexslider();
          }
        }
      };

      // The form itself will return JS which will set a flag to either 1 or 0, and
      // this function will recursively check for that flag value every 200ms.
      Drupal.behaviors.js_watch_value.watch_value(default_value, value_callback, change_callback);
    });

    // propagate click events on our form buttons to the anchors which will trigger the
    // appropriate modals
    $.each(['gk', 'qc', 'post'], function (key, name) {
      if (Feedback[name] && Feedback[name].buttons) {
        $.each(Feedback[name].buttons, function(button_key, data) {
          $(Feedback[name].form + ' ' + data.button).once('mousedown-event').click(function(e) {
            e.preventDefault();

            // update action
            Feedback.utilities.set_action('validate', name);

            // a modal-triggering button has been clicked, so the first thing we need to do
            // is ajax-submit the form to validate it, and we do this by clicking the Save &
            // Close button
            $(Feedback.wrapper + ' ' + Feedback[name].form + ' ' + Feedback.submit_button).trigger('mousedown', data.anchor);

            return false;
          });
        });
      }
    });

    $('.feedback-section-title').click(function (e) {
      e.preventDefault();
      $(this).toggleClass('more');
      $(this).toggleClass('less');
      $(this).parent().siblings('.feedback-section-drop').slideToggle();
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