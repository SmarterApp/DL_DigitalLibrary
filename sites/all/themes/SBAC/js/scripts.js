(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.helpTextify = {
    attach: function (context, settings) {
//      function initTextify(){
//        $('#current-help-topic article .body').textify({
//          numberOfColumn: 2,
//          margin: 20,
//          padding: 32,
//          width: "auto",
//          height: "400",
//          showArrows : true,
//          showNavigation: true
//        });
//      }
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

