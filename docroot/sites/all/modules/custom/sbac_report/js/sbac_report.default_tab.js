(function ($) {

  Drupal.behaviors.sbac_report_default_tab = {
    attach: function (context, settings) {
      var tabs = $('.vertical-tabs');
      if (tabs.length && Drupal.settings.sbac_report.default_tab.length) {
        var tab_index = 0;
        $('.vertical-tabs-panes > fieldset', tabs).each(function (i, el) {
          el = $(el);
          if (el.attr('id') == Drupal.settings.sbac_report.default_tab) {
            tab_index = i;
          }
        });

        $('.vertical-tabs-list li a', tabs).each(function (j, el) {
          var el = $(el);
          el.click(function () {
            // update default tab in JS settings
            var tab = Drupal.settings.sbac_report.tabs[j];
            Drupal.settings.sbac_report.default_tab = tab;
            // update default tab in backend
            $.get(Drupal.settings.basePath + 'reports/set_tab/' + tab);
          });

          if (tab_index && j == tab_index) {
            el.click();
          }
        });
      }
    }
  };

})(jQuery);