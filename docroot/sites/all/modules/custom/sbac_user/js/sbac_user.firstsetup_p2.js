(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_user_setup_pi = {
    attach: function (context, settings) {

      /**
       * SBAC User Setup - Page 2
       */
      function sbac_user_check_fields() {
        if ($('#edit_subject_options_chzn .search-choice').length == 0 || $('#edit_grade_options_chzn .search-choice').length == 0) {
          $('#edit-next').prop('disabled', true);
          $('#sbac-setup-hover-expertise').css('z-index', 9999);
        } else {
          $('#edit-next').prop('disabled', false);
          $('#sbac-setup-hover-expertise').css('z-index', -9999);
        }
      }

      // On page load, if there are no selections, disable the submit button and
      // put hoverover on top.
      $(document).ready(function() {
        sbac_user_check_fields();
      });

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

      $('.chzn-container').hover(function() {
        sbac_user_check_fields();
      });

      $('#edit-subject-options').change(function() {
        sbac_user_check_fields();
      });

      $('#edit-grade-options').change(function() {
        sbac_user_check_fields();
      });
    }
  }
}) (jQuery);
