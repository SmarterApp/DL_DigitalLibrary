(function($) {

Drupal.behaviors.sbac_report_default_tab = {
  attach: function (context, settings) {
    var tabs = $('.vertical-tabs');

    if (tabs.length && Drupal.settings.sbac_report.default_tab.length) {
      var tab_index = 0;
      $('.vertical-tabs-panes fieldset', tabs).each(function (i, el) {
        el = $(el);

        if (el.attr('id') == Drupal.settings.sbac_report.default_tab) {
          tab_index = i;
        }
      });

      if (tab_index) {
        $('.vertical-tabs-list li a', tabs).each(function (j, el) {
          if (j == tab_index) {
            $(el).click();
            return;
          }
        }); 
      }
    }
  }
};

})(jQuery);