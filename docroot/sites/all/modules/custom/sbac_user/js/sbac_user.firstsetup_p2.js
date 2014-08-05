(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_user_setup_pi = {
    attach: function (context, settings) {

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
      $('#sbac-setup-hover-expertise-button').hover(
        function() {
          sbac_user_check_fields();
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

      $('.active-result').click(function() {
        sbac_user_check_fields();
      });

      $('.chzn-container').mouseout(function() {
        sbac_user_check_fields();
      });

    }
  }
}) (jQuery);
