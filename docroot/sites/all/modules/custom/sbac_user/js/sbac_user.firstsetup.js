(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_user_setup_pi = {
    attach: function (context, settings) {

      /**
       * SBAC User Setup - Page 1
       */

       // On page load, if there is no selection, disable the submit button and
       // put hoverover on top.
      if ($('#edit-user-title').val() != '') {
        $('#edit-next-form').prop('disabled', false);
      }
      else {
        $('#edit-next-form').prop('disabled', true);
        $('#sbac-setup-hover-pi').css('z-index', 9999);
      }

      //  When user hovers over invisible div, toggle the popup to show if the 
      //  submit button is disabled.
      $('#sbac-setup-hover-pi').hover(
        function() {
          if ($('#edit-next-form').prop('disabled')) {
            $('#pi-form-drop').addClass('open');
          }
          else {
            $('#sbac-setup-hover-pi').css('z-index', -9999);
          }
        },
        function() {
          if ($('#edit-next-form').prop('disabled')) {
            $('#pi-form-drop').removeClass('open');
          }
        }
      );

      //  When the user changes their title, enable/disable the submit button 
      //  based on their choice.
      $('#edit-user-title').change(function() {
        if ($('#edit-user-title').val() != '') {
          $('#edit-next-form').prop('disabled', false);
        }
        else {
          $('#sbac-setup-hover-pi').css('z-index', 9999);
          $('#edit-next-form').prop('disabled', true);
        }
      });

      /**
       * SBAC User Setup - Page 2
       */

      // On page load, if there are no selections, disable the submit button and
      // put hoverover on top.
      sbac_user_check_fields();
      function sbac_user_check_fields() {
        if ($('#edit_subject_options_chzn .search-choice').length == 0 || $('#edit_grade_options_chzn .search-choice').length == 0 || $('#edit_student_population_options_chzn .search-choice').length == 0) {
          $('#edit-next').prop('disabled', true);
          $('#sbac-setup-hover-expertise').css('z-index', 9999);
        } else {
          $('#edit-next').prop('disabled', false);
          $('#sbac-setup-hover-expertise').css('z-index', -9999);
        }
      }

      //  When user hovers over invisible div, toggle the popup to show if the 
      //  submit button is disabled.
      $('#sbac-setup-hover-expertise').hover(
        function() {
          if ($('#edit-next').prop('disabled')) {
            $('#expertise-form-drop').addClass('open');
          }
          else {
            $('#sbac-setup-hover-expertise').css('z-index', -9999);
          }
        },
        function() {
          if ($('#edit-next').prop('disabled')) {
            $('#expertise-form-drop').removeClass('open');
          }
        }
      );

      $('#edit_subject_options_chzn :input').blur(function() {
        sbac_user_check_fields();
      });

      $('#edit_grade_options_chzn :input').blur(function() {
        sbac_user_check_fields();
      });

      $('#edit_student_population_options_chzn :input').blur(function() {
        sbac_user_check_fields();
      });

      $('#edit-next').hover(function() {
        sbac_user_check_fields();
      });

    }
  }
}) (jQuery);
