/**
 * This is the HTML output for the modal.
 *
 * sbac_flag.module, function hook_form_alter, line 255
 * this is where I add the modalTheme which declares this
 * theme output for that modal.
 *
 * @returns {string}
 * @constructor
 */

Drupal.theme.prototype.CtoolSbacWelcomeTutorial = function () {
  var html = ''
  html += '  <div id="ctools-modal" class="sbac-welcome">'
  html += '    <div class="ctools-modal-content sbac-welcome">' // panels-modal-content
  html += '      <div class="modal-header">';
  html += '        <a class="close" href="#">';
  html +=            Drupal.CTools.Modal.currentSettings.closeText + Drupal.CTools.Modal.currentSettings.closeImage;
  html += '        </a>';
  html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
  html += '      </div>';
  html += '      <div id="modal-content" class="modal-content">';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';

  return html;
}

;
/**
 * @file
 *
 * Implement a modal form.
 *
 * @see modal.inc for documentation.
 *
 * This javascript relies on the CTools ajax responder.
 */

(function ($) {
  // Make sure our objects are defined.
  Drupal.CTools = Drupal.CTools || {};
  Drupal.CTools.Modal = Drupal.CTools.Modal || {};

  /**
   * Display the modal
   *
   * @todo -- document the settings.
   */
  Drupal.CTools.Modal.show = function(choice) {
    var opts = {};

    if (choice && typeof choice == 'string' && Drupal.settings[choice]) {
      // This notation guarantees we are actually copying it.
      $.extend(true, opts, Drupal.settings[choice]);
    }
    else if (choice) {
      $.extend(true, opts, choice);
    }

    var defaults = {
      modalTheme: 'CToolsModalDialog',
      throbberTheme: 'CToolsModalThrobber',
      animation: 'show',
      animationSpeed: 'fast',
      modalSize: {
        type: 'scale',
        width: .8,
        height: .8,
        addWidth: 0,
        addHeight: 0,
        // How much to remove from the inner content to make space for the
        // theming.
        contentRight: 25,
        contentBottom: 45
      },
      modalOptions: {
        opacity: .55,
        background: '#fff'
      }
    };

    var settings = {};
    $.extend(true, settings, defaults, Drupal.settings.CToolsModal, opts);

    if (Drupal.CTools.Modal.currentSettings && Drupal.CTools.Modal.currentSettings != settings) {
      Drupal.CTools.Modal.modal.remove();
      Drupal.CTools.Modal.modal = null;
    }

    Drupal.CTools.Modal.currentSettings = settings;

    var resize = function(e) {
      // When creating the modal, it actually exists only in a theoretical
      // place that is not in the DOM. But once the modal exists, it is in the
      // DOM so the context must be set appropriately.
      var context = e ? document : Drupal.CTools.Modal.modal;

      if (Drupal.CTools.Modal.currentSettings.modalSize.type == 'scale') {
        var width = $(window).width() * Drupal.CTools.Modal.currentSettings.modalSize.width;
        var height = $(window).height() * Drupal.CTools.Modal.currentSettings.modalSize.height;
      }
      else {
        var width = Drupal.CTools.Modal.currentSettings.modalSize.width;
        var height = Drupal.CTools.Modal.currentSettings.modalSize.height;
      }

      // Use the additionol pixels for creating the width and height.
      $('div.ctools-modal-content', context).css({
        'width': width + Drupal.CTools.Modal.currentSettings.modalSize.addWidth + 'px',
        'height': height + Drupal.CTools.Modal.currentSettings.modalSize.addHeight + 'px'
      });
      $('div.ctools-modal-content .modal-content', context).css({
        'width': (width - Drupal.CTools.Modal.currentSettings.modalSize.contentRight) + 'px',
        'height': (height - Drupal.CTools.Modal.currentSettings.modalSize.contentBottom) + 'px'
      });
    }

    if (!Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.modal = $(Drupal.theme(settings.modalTheme));
      if (settings.modalSize.type == 'scale') {
        $(window).bind('resize', resize);
      }
    }

    resize();

    $('span.modal-title', Drupal.CTools.Modal.modal).html(Drupal.CTools.Modal.currentSettings.loadingText);
    Drupal.CTools.Modal.modalContent(Drupal.CTools.Modal.modal, settings.modalOptions, settings.animation, settings.animationSpeed);
    $('#modalContent .modal-content').html(Drupal.theme(settings.throbberTheme));

    // Position autocomplete results based on the scroll position of the modal.
    $('#modalContent .modal-content').delegate('input.form-autocomplete', 'keyup', function() {
      $('#autocomplete').css('top', $(this).position().top + $(this).outerHeight() + $(this).offsetParent().filter('#modal-content').scrollTop());
    });
  };

  /**
   * Hide the modal
   */
  Drupal.CTools.Modal.dismiss = function() {
    if (Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.unmodalContent(Drupal.CTools.Modal.modal);
    }
  };

  /**
   * Provide the HTML to create the modal dialog.
   */
  Drupal.theme.prototype.CToolsModalDialog = function () {
    var html = ''
    html += '  <div id="ctools-modal">'
    html += '    <div class="ctools-modal-content">' // panels-modal-content
    html += '      <div class="modal-header">';
    html += '        <a class="close" href="#">';
    html +=            Drupal.CTools.Modal.currentSettings.closeText + Drupal.CTools.Modal.currentSettings.closeImage;
    html += '        </a>';
    html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
    html += '      </div>';
    html += '      <div id="modal-content" class="modal-content">';
    html += '      </div>';
    html += '    </div>';
    html += '  </div>';

    return html;
  }

  /**
   * Provide the HTML to create the throbber.
   */
  Drupal.theme.prototype.CToolsModalThrobber = function () {
    var html = '';
    html += '  <div id="modal-throbber">';
    html += '    <div class="modal-throbber-wrapper">';
    html +=        Drupal.CTools.Modal.currentSettings.throbber;
    html += '    </div>';
    html += '  </div>';

    return html;
  };

  /**
   * Figure out what settings string to use to display a modal.
   */
  Drupal.CTools.Modal.getSettings = function (object) {
    var match = $(object).attr('class').match(/ctools-modal-(\S+)/);
    if (match) {
      return match[1];
    }
  }

  /**
   * Click function for modals that can be cached.
   */
  Drupal.CTools.Modal.clickAjaxCacheLink = function () {
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return Drupal.CTools.AJAX.clickAJAXCacheLink.apply(this);
  };

  /**
   * Handler to prepare the modal for the response
   */
  Drupal.CTools.Modal.clickAjaxLink = function () {
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return false;
  };

  /**
   * Submit responder to do an AJAX submit on all modal forms.
   */
  Drupal.CTools.Modal.submitAjaxForm = function(e) {
    var $form = $(this);
    var url = $form.attr('action');

    setTimeout(function() { Drupal.CTools.AJAX.ajaxSubmit($form, url); }, 1);
    return false;
  }

  /**
   * Bind links that will open modals to the appropriate function.
   */
  Drupal.behaviors.ZZCToolsModal = {
    attach: function(context) {
      // Bind links
      // Note that doing so in this order means that the two classes can be
      // used together safely.
      /*
       * @todo remimplement the warm caching feature
       $('a.ctools-use-modal-cache', context).once('ctools-use-modal', function() {
         $(this).click(Drupal.CTools.Modal.clickAjaxCacheLink);
         Drupal.CTools.AJAX.warmCache.apply(this);
       });
        */

      $('area.ctools-use-modal, a.ctools-use-modal', context).once('ctools-use-modal', function() {
        var $this = $(this);
        $this.click(Drupal.CTools.Modal.clickAjaxLink);
        // Create a drupal ajax object
        var element_settings = {};
        if ($this.attr('href')) {
          element_settings.url = $this.attr('href');
          element_settings.event = 'click';
          element_settings.progress = { type: 'throbber' };
        }
        var base = $this.attr('href');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
      });

      // Bind buttons
      $('input.ctools-use-modal, button.ctools-use-modal', context).once('ctools-use-modal', function() {
        var $this = $(this);
        $this.click(Drupal.CTools.Modal.clickAjaxLink);
        var button = this;
        var element_settings = {};

        // AJAX submits specified in this manner automatically submit to the
        // normal form action.
        element_settings.url = Drupal.CTools.Modal.findURL(this);
        if (element_settings.url == '') {
          element_settings.url = $(this).closest('form').attr('action');
        }
        element_settings.event = 'click';
        element_settings.setClick = true;

        var base = $this.attr('id');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);

        // Make sure changes to settings are reflected in the URL.
        $('.' + $(button).attr('id') + '-url').change(function() {
          Drupal.ajax[base].options.url = Drupal.CTools.Modal.findURL(button);
        });
      });

      // Bind our custom event to the form submit
      $('#modal-content form', context).once('ctools-use-modal', function() {
        var $this = $(this);
        var element_settings = {};

        element_settings.url = $this.attr('action');
        element_settings.event = 'submit';
        element_settings.progress = { 'type': 'throbber' }
        var base = $this.attr('id');

        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
        Drupal.ajax[base].form = $this;

        $('input[type=submit], button', this).click(function(event) {
          Drupal.ajax[base].element = this;
          this.form.clk = this;
          // Stop autocomplete from submitting.
          if (Drupal.autocompleteSubmit && !Drupal.autocompleteSubmit()) {
            return false;
          }
          // An empty event means we were triggered via .click() and
          // in jquery 1.4 this won't trigger a submit.
          if (event.bubbles == undefined) {
            $(this.form).trigger('submit');
            return false;
          }
        });
      });

      // Bind a click handler to allow elements with the 'ctools-close-modal'
      // class to close the modal.
      $('.ctools-close-modal', context).once('ctools-close-modal')
        .click(function() {
          Drupal.CTools.Modal.dismiss();
          return false;
        });
    }
  };

  // The following are implementations of AJAX responder commands.

  /**
   * AJAX responder command to place HTML within the modal.
   */
  Drupal.CTools.Modal.modal_display = function(ajax, response, status) {
    if ($('#modalContent').length == 0) {
      Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(ajax.element));
    }
    $('#modal-title').html(response.title);
    // Simulate an actual page load by scrolling to the top after adding the
    // content. This is helpful for allowing users to see error messages at the
    // top of a form, etc.
    $('#modal-content').html(response.output).scrollTop(0);

    // Attach behaviors within a modal dialog.
    var settings = response.settings || ajax.settings || Drupal.settings;
    Drupal.attachBehaviors('#modalContent', settings);
  }

  /**
   * AJAX responder command to dismiss the modal.
   */
  Drupal.CTools.Modal.modal_dismiss = function(command) {
    Drupal.CTools.Modal.dismiss();
    $('link.ctools-temporary-css').remove();
  }

  /**
   * Display loading
   */
  //Drupal.CTools.AJAX.commands.modal_loading = function(command) {
  Drupal.CTools.Modal.modal_loading = function(command) {
    Drupal.CTools.Modal.modal_display({
      output: Drupal.theme(Drupal.CTools.Modal.currentSettings.throbberTheme),
      title: Drupal.CTools.Modal.currentSettings.loadingText
    });
  }

  /**
   * Find a URL for an AJAX button.
   *
   * The URL for this gadget will be composed of the values of items by
   * taking the ID of this item and adding -url and looking for that
   * class. They need to be in the form in order since we will
   * concat them all together using '/'.
   */
  Drupal.CTools.Modal.findURL = function(item) {
    var url = '';
    var url_class = '.' + $(item).attr('id') + '-url';
    $(url_class).each(
      function() {
        var $this = $(this);
        if (url && $this.val()) {
          url += '/';
        }
        url += $this.val();
      });
    return url;
  };


  /**
   * modalContent
   * @param content string to display in the content box
   * @param css obj of css attributes
   * @param animation (fadeIn, slideDown, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   */
  Drupal.CTools.Modal.modalContent = function(content, css, animation, speed) {
    // If our animation isn't set, make it just show/pop
    if (!animation) {
      animation = 'show';
    }
    else {
      // If our animation isn't "fadeIn" or "slideDown" then it always is show
      if (animation != 'fadeIn' && animation != 'slideDown') {
        animation = 'show';
      }
    }

    if (!speed) {
      speed = 'fast';
    }

    // Build our base attributes and allow them to be overriden
    css = jQuery.extend({
      position: 'absolute',
      left: '0px',
      margin: '0px',
      background: '#000',
      opacity: '.55'
    }, css);

    // Add opacity handling for IE.
    css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';
    content.hide();

    // If we already have modalContent, remove it.
    if ($('#modalBackdrop').length) $('#modalBackdrop').remove();
    if ($('#modalContent').length) $('#modalContent').remove();

    // position code lifted from http://www.quirksmode.org/viewport/compatibility.html
    if (self.pageYOffset) { // all except Explorer
    var wt = self.pageYOffset;
    } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
      var wt = document.documentElement.scrollTop;
    } else if (document.body) { // all other Explorers
      var wt = document.body.scrollTop;
    }

    // Get our dimensions

    // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have a *visible* border below our div
    var docHeight = $(document).height() + 50;
    var docWidth = $(document).width();
    var winHeight = $(window).height();
    var winWidth = $(window).width();
    if( docHeight < winHeight ) docHeight = winHeight;

    // Create our divs
    $('body').append('<div id="modalBackdrop" style="z-index: 1000; display: none;"></div><div id="modalContent" style="z-index: 1001; position: absolute;">' + $(content).html() + '</div>');

    // Keyboard and focus event handler ensures focus stays on modal elements only
    modalEventHandler = function( event ) {
      target = null;
      if ( event ) { //Mozilla
        target = event.target;
      } else { //IE
        event = window.event;
        target = event.srcElement;
      }

      var parents = $(target).parents().get();
      for (var i = 0; i < parents.length; ++i) {
        var position = $(parents[i]).css('position');
        if (position == 'absolute' || position == 'fixed') {
          return true;
        }
      }

      if ($(target).is('#modalContent, body') || $(target).filter('*:visible').parents('#modalContent').length) {
        // Allow the event only if target is a visible child node
        // of #modalContent.
        return true;
      }
      else {
        $('#modalContent').focus();
      }

      event.preventDefault();
    };
    $('body').bind( 'focus', modalEventHandler );
    $('body').bind( 'keypress', modalEventHandler );

    // Create our content div, get the dimensions, and hide it
    var modalContent = $('#modalContent').css('top','-1000px');
    var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
    var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);
    $('#modalBackdrop').css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
    modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'}).hide()[animation](speed);

    // Bind a click for closing the modalContent
    modalContentClose = function(){close(); return false;};
    $('.close').bind('click', modalContentClose);

    // Bind a keypress on escape for closing the modalContent
    modalEventEscapeCloseHandler = function(event) {
      if (event.keyCode == 27) {
        close();
        return false;
      }
    };

    $(document).bind('keydown', modalEventEscapeCloseHandler);

    // Close the open modal content and backdrop
    function close() {
      // Unbind the events
      $(window).unbind('resize',  modalContentResize);
      $('body').unbind( 'focus', modalEventHandler);
      $('body').unbind( 'keypress', modalEventHandler );
      $('.close').unbind('click', modalContentClose);
      $('body').unbind('keypress', modalEventEscapeCloseHandler);
      $(document).trigger('CToolsDetachBehaviors', $('#modalContent'));

      // Set our animation parameters and use them
      if ( animation == 'fadeIn' ) animation = 'fadeOut';
      if ( animation == 'slideDown' ) animation = 'slideUp';
      if ( animation == 'show' ) animation = 'hide';

      // Close the content
      modalContent.hide()[animation](speed);

      // Remove the content
      $('#modalContent').remove();
      $('#modalBackdrop').remove();
    };

    // Move and resize the modalBackdrop and modalContent on resize of the window
     modalContentResize = function(){

      // position code lifted from http://www.quirksmode.org/viewport/compatibility.html
      if (self.pageYOffset) { // all except Explorer
      var wt = self.pageYOffset;
      } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
        var wt = document.documentElement.scrollTop;
      } else if (document.body) { // all other Explorers
        var wt = document.body.scrollTop;
      }

      // Get our heights
      var docHeight = $(document).height();
      var docWidth = $(document).width();
      var winHeight = $(window).height();
      var winWidth = $(window).width();
      if( docHeight < winHeight ) docHeight = winHeight;

      // Get where we should move content to
      var modalContent = $('#modalContent');
      var mdcTop = wt + ( winHeight / 2 ) - ( modalContent.outerHeight() / 2);
      var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);

      // Apply the changes
      $('#modalBackdrop').css('height', docHeight + 'px').css('width', docWidth + 'px').show();
      modalContent.css('top', mdcTop + 'px').css('left', mdcLeft + 'px').show();
    };
    $(window).bind('resize', modalContentResize);

    $('#modalContent').focus();
  };

  /**
   * unmodalContent
   * @param content (The jQuery object to remove)
   * @param animation (fadeOut, slideUp, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   */
  Drupal.CTools.Modal.unmodalContent = function(content, animation, speed)
  {
    // If our animation isn't set, make it just show/pop
    if (!animation) { var animation = 'show'; } else {
      // If our animation isn't "fade" then it always is show
      if (( animation != 'fadeOut' ) && ( animation != 'slideUp')) animation = 'show';
    }
    // Set a speed if we dont have one
    if ( !speed ) var speed = 'fast';

    // Unbind the events we bound
    $(window).unbind('resize', modalContentResize);
    $('body').unbind('focus', modalEventHandler);
    $('body').unbind('keypress', modalEventHandler);
    $('.close').unbind('click', modalContentClose);
    $(document).trigger('CToolsDetachBehaviors', $('#modalContent'));

    // jQuery magic loop through the instances and run the animations or removal.
    content.each(function(){
      if ( animation == 'fade' ) {
        $('#modalContent').fadeOut(speed, function() {
          $('#modalBackdrop').fadeOut(speed, function() {
            $(this).remove();
          });
          $(this).remove();
        });
      } else {
        if ( animation == 'slide' ) {
          $('#modalContent').slideUp(speed,function() {
            $('#modalBackdrop').slideUp(speed, function() {
              $(this).remove();
            });
            $(this).remove();
          });
        } else {
          $('#modalContent').remove();
          $('#modalBackdrop').remove();
        }
      }
    });
  };

$(function() {
  Drupal.ajax.prototype.commands.modal_display = Drupal.CTools.Modal.modal_display;
  Drupal.ajax.prototype.commands.modal_dismiss = Drupal.CTools.Modal.modal_dismiss;
});

})(jQuery);
;
(function($) {

var clicked = false;

Drupal.behaviors.sections = {
  attach: function (context, settings) {
    $('.section-link').once('sbacLinkClick', function() {
      $(this).click(function(e) {
        if ($(this).parents('.specific-section').hasClass('disabled')) {
          return false;
        }
        $('.specific-section').removeClass('active').css('padding-top', 0);
        $(this).parents('.specific-section').addClass('active').css('padding-top', '45px');
        $(this).removeClass('use-ajax');
      });
    });


    // On click of menu item, click the section if it exists.
    $('.inline-list.right.user-nav .notifications a').once('sbacNotificationsMenuClick', function(){
      $(this).click(function () {
        var section = $('.section-notifications a');
        if (section.length) {
          if (!$.trim($('#section-notifications').html() ).length) {
            section.click();
          }
          else {
            $('.specific-section').removeClass('active').css('padding-top', 0);
            $('.specific-section.section-notifications').addClass('active').css('padding-top', '45px');
          }
        }
        else {
          window.location.href = $(this).attr('href');
        }
        return false;
      });
    });

    // On click of menu item, click the section if it exists.
    $('.inline-list.right.user-nav .sbac-favorites-menu a').once('sbacFavoritesMenuClick', function(){
      $(this).click(function() {
        var section = $('.section-favorites a');
        if (section.length) {
          if (!$.trim($('#section-favorites').html() ).length) {
            section.click();
          }
          else {
            $('.specific-section').removeClass('active').css('padding-top', 0);
            $('.specific-section.section-favorites').addClass('active').css('padding-top', '45px');
          }
        }
        else {
          window.location.href = $(this).attr('href');
        }
        return false;
      });
    });

    // check for tab hash and switch the active tab
    var hash = window.location.hash;
    if (window.location.hash) {
      if (hash == '#profile-favorites' && !$.trim($('#section-favorites').html() ).length) {
        $('.section-favorites a').click();
      }
      else if (hash == '#profile-notifications' && !$.trim($('#section-notifications').html() ).length) {
        $('.section-notifications a').click();
      }
      else if (hash != '#profile-favorites' && hash != '#profile-notifications') {
        $('body').once('switch-section', function() {
          var hash = window.location.hash;
          Drupal.behaviors.sections.switch_tab(hash);
        });
      }
    }

    // add support for disabling sections via class name
    var container = $('.section-container');
    if (container.length) {
      $('section', container).each(function(i, el) {
        var section = $(el);
        section.find('a').click(function(e) {
          var href = $(this);
          if (href.attr('section_id') == 'section-favorites') {
            window.location.hash = 'profile-favorites';
          }
          if (href.attr('section_id') == 'section-notifications') {
            window.location.hash = 'profile-notifications';
          }
          if (href.attr('section_id') == 'section-account') {
            window.location.hash = '';
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
      $('.specific-section').removeClass('active').css('padding-top', 0);
      $('section.section-gate-keeping-criteria-review').addClass('active').css('padding-top', '45px');
      Feedback.about.init_flexslider();
    }
    else if (hash == '#review-qc') {
      $('section.section-1').css('width', '100%');
      $('.specific-section').removeClass('active').css('padding-top', 0);
      $('section.section-quality-criteria-review').addClass('active').css('padding-top', '45px');
    }
    else if (hash == '#review-post') {
      $('section.section-1').css('width', '100%');
      $('.specific-section').removeClass('active').css('padding-top', 0);
      $('section.section-quality-criteria-review').addClass('active').css('padding-top', '45px');
    }
    else if (hash == '#review-Moderate_flag') {
      $('section.section-1').css('width', '100%');
      $('.specific-section').removeClass('active').css('padding-top', 0);
      $('section.section-resource-flags').addClass('active').css('padding-top', '45px');
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
          if ($('#main').find($(element)).length > 0) {
            var section_id = $(element).attr('section_id')
            if (typeof section_id !== typeof undefined && section_id !== false) {
              $(element).addClass('section-loaded');
            }
          }
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

  /**
   * Prepare the Ajax request before it is sent.
   *
   * This code is pulled from misc/ajax.js. We needed to do this to override
   * the placement of the default drupal throbber.
   */
  Drupal.ajax.prototype.beforeSend = function (xmlhttprequest, options) {
    // For forms without file inputs, the jQuery Form plugin serializes the form
    // values, and then calls jQuery's $.ajax() function, which invokes this
    // handler. In this circumstance, options.extraData is never used. For forms
    // with file inputs, the jQuery Form plugin uses the browser's normal form
    // submission mechanism, but captures the response in a hidden IFRAME. In this
    // circumstance, it calls this handler first, and then appends hidden fields
    // to the form to submit the values in options.extraData. There is no simple
    // way to know which submission mechanism will be used, so we add to extraData
    // regardless, and allow it to be ignored in the former case.
    if (this.form) {
      options.extraData = options.extraData || {};

      // Let the server know when the IFRAME submission mechanism is used. The
      // server can use this information to wrap the JSON response in a TEXTAREA,
      // as per http://jquery.malsup.com/form/#file-upload.
      options.extraData.ajax_iframe_upload = '1';

      // The triggering element is about to be disabled (see below), but if it
      // contains a value (e.g., a checkbox, textfield, select, etc.), ensure that
      // value is included in the submission. As per above, submissions that use
      // $.ajax() are already serialized prior to the element being disabled, so
      // this is only needed for IFRAME submissions.
      var v = $.fieldValue(this.element);
      if (v !== null) {
        options.extraData[this.element.name] = Drupal.checkPlain(v);
      }
    }

    // Disable the element that received the change to prevent user interface
    // interaction while the Ajax request is in progress. ajax.ajaxing prevents
    // the element from triggering a new request, but does not prevent the user
    // from changing its value.
    $(this.element).addClass('progress-disabled').attr('disabled', true);

    // Insert progressbar or throbber.
    if (this.progress.type == 'bar') {
      var progressBar = new Drupal.progressBar('ajax-progress-' + this.element.id, eval(this.progress.update_callback), this.progress.method, eval(this.progress.error_callback));
      if (this.progress.message) {
        progressBar.setProgress(-1, this.progress.message);
      }
      if (this.progress.url) {
        progressBar.startMonitoring(this.progress.url, this.progress.interval || 1500);
      }
      this.progress.element = $(progressBar.element).addClass('ajax-progress ajax-progress-bar');
      this.progress.object = progressBar;
      $(this.element).after(this.progress.element);
    }
    else if (this.progress.type == 'throbber') {
      var url = this.url;
      if (url.indexOf('section-get-content') > -1) {
        var title = this.element.title;
        this.progress.element = $('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
        if (this.progress.message) {
          $('.throbber', this.progress.element).after('<div class="message">' + this.progress.message + '</div>');
        }
        switch (title) {
          case 'Notifications':
            $('#section-notifications').append(this.progress.element);
            break;
          case 'Favorites':
            $('#section-favorites').append(this.progress.element);
            break;
          case 'Collaboration':
            $('#section-collaboration').append(this.progress.element);
            break;
          case 'Reviews':
            $('#section-reviews').append(this.progress.element);
            break;
          case 'Share':
            $('#section-share').append(this.progress.element);
            break;
          case 'Related Resources':
            $('#section-related-resources').append(this.progress.element);
            break;
          case 'Flag':
            $('#section-flag').append(this.progress.element);
            break;
        }
      }
      else {
        this.progress.element = $('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
        if (this.progress.message) {
          $('.throbber', this.progress.element).after('<div class="message">' + this.progress.message + '</div>');
        }
        $(this.element).after(this.progress.element);
      }
    }
  };

}

})(jQuery);;
