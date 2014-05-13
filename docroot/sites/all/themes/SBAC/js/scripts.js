(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.session_timeout = {
    attach: function (content, settings) {
      var pageTimeout = setTimeout( function() { confirmTimeout(); }, 58 * 60 * 1000);

      function confirmTimeout() {
        if (confirm('')) {
          // reset timer ajax call.
          resetTimeout();
        }
      }

      function resetTimeout() {
        clearTimeout( pageTimeout ) ;
        pageTimeout = setTimeout( function() { confirmTimeout(); }, 58 * 60 * 1000);
      }
    }
  };

  Drupal.behaviors.helpTextify = {
    attach: function (context, settings) {
      function initTextify(){
        jQuery('#current-help-topic article .body').textify({
          numberOfColumn: 2,
          margin: 20,
          padding: 32,
          width: "auto",
          height: "400",
          showArrows : true,
          showNavigation: true
        });
      }
    }
  };

  Drupal.behaviors.accountDropdown = {
    attach: function (context, settings) {
      $(document).click(function() {
        if (!$(this).hasClass('open')) {
          var selectedDiv = $('.open');
          selectedDiv.hide();
          selectedDiv.removeClass('open');
        }
      });
    }
  };

  Drupal.behaviors.helpTextify = {
    attach: function (context, settings) {
      $(function() {
        $('#edit-pass').attr('autocomplete', 'off');
      });
    }
  };

})(jQuery);
