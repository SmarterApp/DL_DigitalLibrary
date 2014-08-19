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
            $(element).addClass('section-loaded');
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

})(jQuery);