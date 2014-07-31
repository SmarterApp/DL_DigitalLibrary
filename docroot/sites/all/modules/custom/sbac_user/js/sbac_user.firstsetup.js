(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_user_setup_pi = {
    attach: function (context, settings) {
      $('#sbac-setup-hover-pi').hover(
        function() {
          if ($('#edit-next-form').hasClass('form-disabled')) {
            $('#pi-form-drop').addClass('open');
          }
          else {
            $('#sbac-setup-hover-pi').css('z-index', -9999);
          }
        },
        function() {
          if ($('#edit-next-form').hasClass('form-disabled')) {
            $('#pi-form-drop').removeClass('open');
          }
        }
      );

      $('#edit-user-title').change(function() {
        if ($('#edit-next-form').hasClass('form-disabled')) {
          $('#sbac-setup-hover-pi').css('z-index', 9999);
        }
      });

      $('#sbac-setup-hover-expertise').hover(
        function() {
          if ($('#edit-next').hasClass('form-disabled')) {
            $('#expertise-form-drop').addClass('open');
          }
          else {
            $('#sbac-setup-hover-expertise').css('z-index', -9999);
          }
        },
        function() {
          if ($('#edit-next').hasClass('form-disabled')) {
            $('#expertise-form-drop').removeClass('open');
          }
        }
      );

      $('#edit-is-complete').change(function() {
        if ($('#edit-next').hasClass('form-disabled')) {
          $('#sbac-setup-hover-pi').css('z-index', 9999);
        }
      });

    }
  };
}) (jQuery);
