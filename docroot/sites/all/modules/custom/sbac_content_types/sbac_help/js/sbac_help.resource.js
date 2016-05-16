(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  var loaded = false;
  Drupal.behaviors.sbac_help_resource_main = {
    attach: function (context, settings) {
      $('#sbac-resource-help-modal').hide();
      if (!loaded) {
        $('#sbac-resource-help-modal').click();
        loaded = true;
      }
      $('#resource-help-body').textify({
        numberOfColumn: 2,
        margin: 20,
        padding: 32,
        width: "auto",
        height: "400",
        showArrows: true,
        showNavigation: true,
      });
    }
  };

})(jQuery);
