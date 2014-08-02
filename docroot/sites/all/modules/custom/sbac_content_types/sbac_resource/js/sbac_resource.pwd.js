(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_resource_pwd_toggle = {
    attach: function (context, settings) {
      if ($.cookie('sbac-pwd-reel-hide') == 1) {
        // $('#sbac-pwd-show-hide').click();
        $('.pwd-collapsable').hide();
        $('#sbac-pwd-show-hide').toggleClass('toggle-closed');
        $('#sbac-pwd-show-hide').text('Show');
      };
      $('#sbac-pwd-show-hide').once('pwd-toggle-event', function() {
        $(this).click(function() {
          $('.pwd-collapsable').toggle();
          $(this).toggleClass('toggle-closed');
          var text = $(this).text();
          if (text == 'Hide') {
            $(this).text('Show');
            $.cookie('sbac-pwd-reel-hide', 1);
          }
          else {
            $(this).text('Hide');
            $.cookie('sbac-pwd-reel-hide', 0);
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
          window.location.hash = '';
          $('#edit-dl-pwd').click();
          return false;
        });
      });
      $('#sbac-pwd-show-fewer').once('pwd-show-fewer', function() {
        $(this).click(function() {
          window.location.hash = '';
          $('#edit-dl-pwd').click();
          window.scrollTo(0, 0);
          return false;
        });
      });
      $('#sbac-pwd-hide-pwd').once('pwd-show-fewer', function() {
        $(this).click(function() {
          window.location.hash = '';
          $.cookie('sbac-pwd-reel-hide', 1);
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
