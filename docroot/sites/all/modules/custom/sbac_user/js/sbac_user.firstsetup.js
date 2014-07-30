(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_user_setup_pi = {
    attach: function (context, settings) {
      $('#sbac-setup-hover-pi').hover(
        function() {
          if ($('#edit-next-form').hasClass('form-disabled')) {
            $('#pi-form-drop').addClass('open');
          }
        },
        function() {
          if ($('#edit-next-form').hasClass('form-disabled')) {
            $('#pi-form-drop').removeClass('open');
          }
        }
      );

      $('#sbac-setup-hover-expertise').hover(
        function() {
          if ($('#edit-next').hasClass('form-disabled')) {
            $('#expertise-form-drop').addClass('open');
          }
        },
        function() {
          if ($('#edit-next').hasClass('form-disabled')) {
            $('#expertise-form-drop').removeClass('open');
          }
        }
      );

    }
  };
}) (jQuery);
