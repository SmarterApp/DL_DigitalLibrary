(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};
  var clicked = false;

  Drupal.behaviors.sbac_user_first_time_login = {
    attach: function (context, settings) {
      $('#sbac-user-warn-user').hide();
      var required_fields = Drupal.settings.sbac_user_required_fields;

      $('#sbac-user-warn-user-form button').click(function () {
        clicked = false;
      });

      $('#user-profile-form button').click(function () {
        clicked = true;
      });

      if (required_fields == 0) {
        $('.main-top,.sub-top,.bottom-bar').click(function (event) {
          var login_count = Drupal.settings.sbac_user_login_count;
          if (login_count != null && login_count == 1 && clicked == false) {
            var position = $('#edit-field-position-und').val();
            var subjects = $('#edit-field-subject-s-und').val();
            var grades = $('#edit-field-grade-level-s-und').val();
            var student_populations = $('#edit-field-special-populations-und').val();
            if (position == '_none' || subjects == null || grades == null || student_populations == null) {
              event.stopPropagation();
              event.preventDefault();
              clicked = true;
              $('#edit-submit').removeAttr('disabled');
              $('#edit-submit').click();
            }
            else {
              event.stopPropagation();
              event.preventDefault();
              clicked = true;
              $('#edit-submit').removeAttr('disabled');
              $('#sbac-user-warn-user').click();
            }
          }
        });
      }
    }
  };

  Drupal.behaviors.sbac_user = {
    attach: function (context, settings) {
      $("#legal-login #edit-save").attr('disabled', 'disabled');
      $('#legal-login #edit-legal-accept').click(function () {
        var legalCheckbox = $(this);
        if (legalCheckbox.is(':checked')) {
          $('#legal-login #edit-save').removeAttr('disabled');
        }
        else {
          $("#legal-login #edit-save").attr('disabled', 'disabled');
        }
      });

      // set the default vertical tab on user profile form
      $("form#user-profile-form #edit-submit").click(function () {
        if ($('#edit-group_expertise[style*="display: block;"]').length) {
          $("#vertical-tabs-default").val("edit-group_expertise");
        }
        if ($('#edit-group_privacy[style*="display: block;"]').length) {
          $("#vertical-tabs-default").val("edit-group_privacy");
        }
      });

      // user field privacy, cannot modify these fields
      $("#edit-field-privacy-und-field-first-name").prop('disabled', true);
      $("#edit-field-privacy-und-field-position").prop('disabled', true);
      $("#edit-field-privacy-und-field-state").prop('disabled', true);
      $("#edit-field-privacy-und-field-grade-level-s-").prop('disabled', true);
      $("#edit-field-privacy-und-field-subject-s-").prop('disabled', true);
      $("#edit-field-privacy-und-field-special-populations").prop('disabled', true);

      var placeholder = ($('#edit-picture').has('div.form-item-picture-delete').length) ? 'Change Picture' : 'Add Picture';
      $('.row #edit-picture-upload').after('<input id="upload-cover" value="' + placeholder + '" type="text">');
      $(".row #edit-picture-upload").change(function () {
        if ($(this).val() == "") {
          var fname = $("#upload-cover").val();
          $(this).val(fname);
        }
      });

      $('.row #edit-picture-upload').mouseover(function () {
        $('.row #upload-cover').addClass('hovered');
      });

      $('.row #edit-picture-upload').mouseleave(function () {
        $('.row #upload-cover').removeClass('hovered');
      });

      // has to append email field description here as the problem lies deep inside the theme element function
      $('#user-profile-form #edit-account .form-item-mail div.description').insertAfter('#user-profile-form #edit-account .form-item-mail label');

      // $(".row.second button:submit:not(#sbac-favorites-resource-submit, #sbac-favorites-resource-cancel, #sbac-favorites-forum-submit, #sbac-favorites-forum-cancel)").attr("disabled", true);
      $("input, textarea, select").live('keydown change', function () {
        $(".row.second button:submit").removeAttr("disabled");
      });

      // Don't show the Submit button on the Manage Subscriptions tab (will only work as long as it is the last tab).
      $("#user-profile-form .vertical-tab-button a").click(function (e) {
        if ($(this).parent().hasClass('last')) {
          $("#edit-actions--2").hide();
        } else {
          $("#edit-actions--2").show();
        }
      });
    }
  };
})(jQuery);
