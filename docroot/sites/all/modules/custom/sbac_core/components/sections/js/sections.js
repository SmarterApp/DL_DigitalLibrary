(function($) {

var clicked = false;

Drupal.behaviors.sections = {
  attach: function (context, settings) {
    $('.section-link').click(function(e) {
      $('.specific-section').removeClass('active').css('padding-top', 0);
      $(this).parents('.specific-section').addClass('active').css('padding-top', '45px');
      $(this).removeClass('use-ajax');
    });

    // On click of menu item, click the section if it exists.
    $('.inline-list.right.user-nav .notifications a').once('sbacNotificationsMenuClick', function(){
      $(this).click(function () {
        var section = $('.section-notifications a');
        if (section.length) {
          section.click();
//          window.location.href = section.attr('href');
        }
      });
    });

    // On click of menu item, click the section if it exists.
    $('.inline-list.right.user-nav .sbac-favorites-menu a').once('sbacFavoritesMenuClick', function(){
      $(this).click(function() {
        var section = $('.section-favorites a');
        if (section.length) {
          section.click();
//          window.location.href = section.attr('href');
        }
      });
    });

    // check for tab hash and switch the active tab
    var hash = window.location.hash;
    if (window.location.hash) {
      if (hash == '#profile-favorites' && $('#section-favorites').is(':empty')) {
        $('.section-favorites a').click();
      }
      else if (hash == '#profile-notifications' && $('#section-notifications').is(':empty')) {
        $('.section-notifications a').click();
      }
      else {
        $('body').once('switch-section', function() {
          var hash = window.location.hash;
          Drupal.behaviors.sections.switch_tab(hash);
        });
      }
    }

    // add support for disabling sections via class name
    var container = $('.section-container');
    if (container.length) {
      console.log(container);
      $('section', container).each(function(i, el) {
        var section = $(el);
        section.find('a').click(function(e) {
          var href = $(this);
          console.log(href.attr('section_id'));
          if (href.attr('section_id') == 'section-favorites') {
            window.location.hash = 'profile-favorites';
          }
          if (href.attr('section_id') == 'section-notifications') {
            window.location.hash = 'profile-notifications';
          }
          if (href.attr('section_id') == 'section-account') {
            window.location.hash = '';
          }
          console.log(section);
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

if (Drupal.ajax) {
  /**
   * Handle an event that triggers an AJAX response.
   *
   * We unfortunately need to override this function, which originally comes from
   * misc/ajax.js, in order to be able to cache loaded tabs, i.e. once a tab
   * content has loaded it should not need to be loaded again.
   */
  Drupal.ajax.prototype.eventResponse = function (element, event) {
    var ajax = this;
    if (ajax.ajaxing) {
      return false;
    }
    try {
      if (ajax.form) {
        if (ajax.setClick) {
          element.form.clk = element;
        }
        ajax.form.ajaxSubmit(ajax.options);
      }
      else {
        if (!$(element).hasClass('section-loaded')) {
          ajax.beforeSerialize(ajax.element, ajax.options);
          $.ajax(ajax.options);
          $(element).addClass('section-loaded');
        }
      }
    }
    catch (e) {
      ajax.ajaxing = false;
      alert("An error occurred while attempting to process " + ajax.options.url + ": " + e.message);
    }
    if (typeof element.type != 'undefined' && (element.type == 'checkbox' || element.type == 'radio')) {
      return true;
    }
    else {
      return false;
    }
  };
}

})(jQuery);