jQuery(document).ready(function () {

  function initTextify() {
    jQuery('#resource-help-body').textify({
      numberOfColumn: 2,
      margin: 20,
      padding: 32,
      width: "auto",
      height: "400",
      showArrows : true,
      showNavigation: true,
    });
  }

  if (!(Drupal.settings.settings_php && Drupal.settings.settings_php.no_resource_modal)) {
    jQuery.colorbox({
      inline: true,
      href: '#resource-help-box',
      width:'80%',
      height:'80%',
      onComplete: initTextify,
      escKey: false,
      overlayClose: false
    });
  }

});
