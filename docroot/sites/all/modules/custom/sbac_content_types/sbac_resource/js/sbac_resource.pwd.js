(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_resource_pwd_toggle = {
    attach: function (context, settings) {

      $('#sbac-pwd-show-hide').once('pwd-toggle-event', function() {
        $(this).click(function() {
          $('.pwd-collapsable').toggle();
          $(this).toggleClass('toggle-closed');
          var text = $(this).text();
          if (text == 'Hide') {
            $(this).text('Show');
          }
          else {
            $(this).text('Hide');
          }
          return false;
        });
      });
    }
  };

  Drupal.behaviors.sbac_resource_show_pwd = {
    attach: function (context, settings) {

      $('#sbac-pwd-show-more').once('pwd-show-more', function() {
        $(this).click(function() {
          $('#edit-dl-pwd').click();
          return false;
        });
      });
      $('#sbac-pwd-show-fewer').once('pwd-show-fewer', function() {
        $(this).click(function() {
          $('#edit-dl-pwd').click();
          return false;
        });
      });
    }
  };

  Drupal.behaviors.sbac_resource_hide_checkbox = {
    attach: function (context, settings) {
      $(document).ready(function() {
        if ($('.pwd-highlights-container').length == 0 && ($('.pwd-highlight').length == 0)) {
          $('#sbac-pwd-check').hide();
        }
      });
    }
  };

})(jQuery);
