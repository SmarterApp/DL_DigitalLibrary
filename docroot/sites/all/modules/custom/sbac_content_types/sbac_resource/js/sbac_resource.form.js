(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};
  var isDirty = false;
  var button_clicked = false;

  /**
   * Some general JS behavior gets attached to the resource form.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_all = {
    attach: function (context, settings) {
      if (Drupal.settings.sbac_save_continue_tab != null) {
        $(Drupal.settings.sbac_save_continue_tab).click();
        Drupal.settings.sbac_save_continue_tab = null;
      }

      control_form_buttons();
      $('.vertical-tabs-list li:nth-child(4) a').click(function () {
        control_form_buttons();
      });

      $('#submission-general-guidelines').more({length: 300, moreText: 'read more', lessText: 'read less'});
      $('#submission-summary-guidelines').more({length: 300, moreText: 'read more', lessText: 'read less'});
      $('#submission-materials-guidelines').more({length: 300, moreText: 'read more', lessText: 'read less'});
      $('#submission-tags-guidelines').more({length: 300, moreText: 'read more', lessText: 'read less'});
    }
  };

  /**
   * Controls the buttons at the bottom of the resource form.
   */
  control_form_buttons = function () {
    var cancel_button = $('#edit-cancel');
    var resource_state = Drupal.settings.resource_workbench_current_state;
    var submit_resource = $('#sbac-resource-modal-submit-resource');
    var active_tab = $('.vertical-tab-button.selected a strong').html();
    submit_resource.hide();
    cancel_button.hide();
    if (active_tab == 'General' && resource_state == 'creation') {
      cancel_button.show();
    }

    if (active_tab == 'Tags') {
      $('#edit-save-continue').html('Submit Resource');
    }
  };

  /**
   * Moves the error messages to the correct location when displayed.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_error_message = {
    attach: function (context, settings) {
      var alert_box = $('.sbac-resource-alert-box');
      if (alert_box.length) {
        var content = alert_box.html();
        var newdiv = $("<div>");
        newdiv.addClass('sbac-general-alert-box alert-box alert');
        newdiv.html(content);
        $('#submission-general-guidelines').after(newdiv);

        newdiv = $("<div>");
        newdiv.addClass('sbac-summary-alert-box alert-box alert');
        newdiv.html(content);
        $('#submission-summary-guidelines').after(newdiv);

        newdiv = $("<div>");
        newdiv.addClass('sbac-materials-alert-box alert-box alert');
        newdiv.html(content);
        $('#submission-materials-guidelines').after(newdiv);

        newdiv = $("<div>");
        newdiv.addClass('sbac-tags-alert-box alert-box alert');
        newdiv.html(content);
        $('#submission-tags-guidelines').after(newdiv);
        alert_box.remove();
      }
    }
  };

  /**
   * Displays an error message to the user if changes have been made.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_exit_plan = {
    attach: function (context, settings) {
      $(":input").change( function () {
        if (!isDirty) {
          isDirty = true;
        }
      });

      $(":input[type=text], textarea").keyup( function () {
        if (!isDirty) {
          isDirty = true;
        }
      });

      $(window).bind('beforeunload', function () {
        if (isDirty) {
          return 'You will lose all unsaved changes made to this page.';
        }
      });

      $('#edit-submit').click(function () {
        isDirty = false;
      });

      $('#edit-save-continue').mousedown(function () {
        isDirty = false;
      });
    }
  };

  /**
   * Submit resource button click behavior.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.submit_resource = {
    attach: function (context, settings) {
      $('#edit-cancel-overlay').mousedown( function() {
        button_clicked = false;
      });

      var state = Drupal.settings.sbac_resource_valid_state;
      if (state != null && state == true && !button_clicked) {
        submit_resource_click();
        button_clicked = true;
      }
    }
  };

  /**
   * Function to click the resource button.
   */
  submit_resource_click = function () {
    var submit_resource = $('#sbac-resource-modal-submit-resource');
    submit_resource.show();
    submit_resource.click();
    submit_resource.hide();
  };

  /**
   * Controls the click event on the tabs.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.control_click_ability = {
    attach: function (context, settings) {  
      if (Drupal.settings.settings_php && Drupal.settings.settings_php.enable_all_tabs) {
        return;
      }

      if (!Drupal.settings.sbac_summary) {
        $('.vertical-tabs-list li:nth-child(4) a').unbind('click');
        $('.vertical-tabs-list li:nth-child(4) a').addClass('sbac-disabled');
      }
      if (!Drupal.settings.sbac_materials) {
        $('.vertical-tabs-list li:nth-child(3) a').unbind('click');
        $('.vertical-tabs-list li:nth-child(3) a').addClass('sbac-disabled');
      }
      if (!Drupal.settings.sbac_general) {
        $('.vertical-tabs-list li:nth-child(2) a').unbind('click');
        $('.vertical-tabs-list li:nth-child(2) a').addClass('sbac-disabled');
      }
    }
  };

  /**
   * Displays or hides the permissions field.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_permissions = {
    attach: function (context, settings) {
      if ($('#edit-field-view-permissions-und-all-consortium-state').is(':checked')) {
        $('#edit-field-view-permissions-per-state').hide();
      }
      $('#edit-field-view-permissions-und-all-consortium-state').click(function () {
        $('#edit-field-view-permissions-per-state').hide();
      });
      $('#edit-field-view-permissions-und-only-consortium-states-i-choose').click(function () {
        $('#edit-field-view-permissions-per-state').show();
      });
    }
  };

  /**
   * Manipulates the license field.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_license = {
    attach: function (context, settings) {
      var checked = $('#sbac-license-information-field :checked');
      $("#no-license-text").hide();
      $('#field_static_license_text').hide();
      $("#no-license-text").appendTo($('#sbac-2-appender'));
      if (checked.length) {
        if ($(checked).attr('id') == 'edit-field-license-information-und-0') {
         
          var name = $('#sbac-resource-user-name').children().val();
          if ($('#edit-field-author-und-0-value').val() == '') {
            $('#edit-field-author-und-0-value').val(name);
          }

          if ($('#edit-field-publisher-und-0-value').val() == '') {
            $('#edit-field-publisher-und-0-value').val(name);
          }

          $('#license-information-group').appendTo($('#sbac-0-appender'));
          $('#field_static_license_text').show();
        }
        else if ($(checked).attr('id') == 'edit-field-license-information-und-1') {
          $('#license-information-group').appendTo($('#sbac-1-appender'));
        }
        else {
          $('#license-information-group').appendTo($('#sbac-2-appender'));
        }

        if ($(checked).attr('id') == 'edit-field-license-information-und-2') {
          $("#no-license-text").show();
        }
      }

      var save_continue = $('#edit-save-continue');
      $('#edit-field-license-information-und-0').click(function () {
        $('#field_static_license_text').show();
        $('#license-information-group').show();
        $('#sbac-resource-license-url').hide();
        $('#license-information-group').appendTo($('#sbac-0-appender'));
        $("#no-license-text").hide();

        var name = $('#sbac-resource-user-name').children().val();
        if ($('#edit-field-author-und-0-value').val() == '') {
          $('#edit-field-author-und-0-value').val(name);
        }

        if ($('#edit-field-publisher-und-0-value').val() == '') {
          $('#edit-field-publisher-und-0-value').val(name);
        }
        
        save_continue.removeAttr('disabled');
        save_continue.bind('click');
      });
      $('#edit-field-license-information-und-1').click(function () {
        $('#field_static_license_text').hide();
        $('#license-information-group').show();
        $('#sbac-resource-license-url').show();
        $('#license-information-group').appendTo($('#sbac-1-appender'));
        $("#no-license-text").hide();
        $('#edit-field-author-und-0-value').val('');
        $('#edit-field-publisher-und-0-value').val('');
        save_continue.removeAttr('disabled');
        save_continue.bind('click');
      });
      $('#edit-field-license-information-und-2').click(function () {
        $('#field_static_license_text').hide();
        $('#license-information-group').hide();
        $("#no-license-text").show();
        $('#edit-field-author-und-0-value').val();
        $('#edit-field-publisher-und-0-value').val('');
        save_continue.attr('disabled', 'disabled');
        save_continue.unbind('click');
      });
    }
  };

})(jQuery);
