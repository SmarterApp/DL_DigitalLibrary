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
        $('#sbac-setup-hover-pi-button').css('z-index', 9999);
      }

      //  When user hovers over invisible div, toggle the popup to show if the 
      //  submit button is disabled.
      $('#sbac-setup-hover-pi-button').hover(
        function() {
          if ($('#edit-next-form').prop('disabled')) {
            $('#pi-form-drop').addClass('open');
          }
          else {
            $('#sbac-setup-hover-pi-button').removeAttr('data-dropdown');
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
          $('#sbac-setup-hover-pi-button').removeAttr('data-dropdown');
          $('#edit-next-form').prop('disabled', false);
        }
        else {
          $('#sbac-setup-hover-pi-button').attr('data-dropdown', 'pi-form-drop');
          $('#edit-next-form').prop('disabled', true);
        }
      });

    }
  }
}) (jQuery);
