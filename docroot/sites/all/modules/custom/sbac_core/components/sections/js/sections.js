(function($) {

var ajax_request = null;

Drupal.behaviors.sections = {
  attach: function (context, settings) {
    // check for tab hash and switch the active tab
    if (window.location.hash) {
      $('body').once('switch-section', function() {
        var hash = window.location.hash;
        Drupal.behaviors.sections.switch_tab(hash);
      });
    }

    // add support for disabling sections via class name
    var container = $('.section-container');
    if (container.length) {
      $('section', container).each(function(i, el) {
        var section = $(el);

        section.click(function(e) {
          if (section.hasClass('disabled')) {
            e.preventDefault();
            return false;
          }

          var section_href = $(this).find('a');
          var title = section_href.attr('title');
          var section_id = section_href.attr('section_id');
          var source = section_href.attr('source');
          var tab = section_href.attr('tab');
          var nid = section_href.attr('nid');
          if (ajax_request == null && !$.trim( $('#' + section_id).html() ).length) {
            ajax_request = $.ajax({
              url: "/section-get-content",
              data: {'source' : source, 'tab' : tab, 'nid' : nid},
              success: function (data) {
                var response = jQuery.parseJSON(data);
                if (response.response != null) {
                  $('#' + section_id).empty().append(response.response);
                  Drupal.attachBehaviors(context, settings);
                }
                ajax_request = null;
              }
            });
          }
        });
      });
    }
  },

  /**
   * Switches ZURB tab to specified tab hash
   * 
   * @param  {[type]} hash [description]
   * @return {[type]}      [description]
   */
  switch_tab: function(hash) {
    if (hash == '#profile-notifications') {
      Drupal.behaviors.sbac_taskit.mark_notifications_read();
    }
    else if (hash == '#review-gk') {
      $('section.section-1').css('width', '100%');
      Feedback.about.init_flexslider();
    }

    var tab = $('a[href=' + hash + ']');
    if (tab.length) {
      var section_container = tab.closest('.section-container');
      var section = tab.closest('section');

      // ensure data exists and that we're not switching to a disabled section
      if (section_container.length && section.length && !section.hasClass('disabled')) {
        // disable all sections
        $('section', section_container).removeClass('active').css('padding-top', 0);

        // enable the one we're interested in
        section.addClass('active').css('padding-top', '45px');

        // simulate a click on the tab
        tab.click();

        // update hash value in browser for bookmarking purposes and general consistency
        window.location.hash = hash;
      }
    }
  }
};

})(jQuery);