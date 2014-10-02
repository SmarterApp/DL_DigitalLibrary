(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  ajax_request = null;

  Drupal.behaviors.sbac_share = {
    attach: function (context, settings) {
      var load_more_button = $('#taskit-load-more');
      if (load_more_button.length) {
        load_more_button.click( function() {
          if (self.pageYOffset) { // all except Explorer
            var wt = self.pageYOffset;
          } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
            var wt = document.documentElement.scrollTop;
          } else if (document.body) { // all other Explorers
            var wt = document.body.scrollTop;
          }
          // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have a *visible* border below our div
          var docHeight = $(document).height() + 50;
          var docWidth = $(document).width();
          var winHeight = $(window).height();
          var winWidth = $(window).width();
          if( docHeight < winHeight ) docHeight = winHeight;

          // Create CSS attributes
          css = jQuery.extend({
            position: 'absolute',
            left: '0px',
            margin: '0px',
            background: '#000',
            opacity: '.55'
          }, {});

          // Add opacity handling for IE.
          css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';
          var img_location = '/sites/all/themes/SBAC/images/foundation/orbit/loading.gif';
          var img = '<img src="' + img_location + '" alt="Smiley face" height="42" width="42">';
          $('body').append('<div id="modalBackdrop" style="z-index: 1000; display: block;"></div><div id="modalContent" style="z-index: 1001; position: absolute;">' + img + '</div>');
          // Create our content div, get the dimensions, and hide it
          var modalContent = $('#modalContent').css('top','-1000px');
          var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
          var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);
          $('#modalBackdrop').css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
          modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'});


          if (ajax_request == null) {
            var page = load_more_button.attr('page');
            var role = load_more_button.attr('role');
            var interval = load_more_button.attr('interval');
            ajax_request = $.ajax({
              type: 'POST',
              url: "/taskit-load-more",
              data: {'page' : page, 'role' : role, 'interval' : interval},
              success: function(data) {
                page++;
                var response = jQuery.parseJSON(data);
                if("intervals" in response) {
                  for (var i=0;i<response.intervals.length;i++) {
                    var current_interval = response.intervals[i];
                    if (current_interval.name != interval) {
                      $('.taskit-interval.' + interval).after(current_interval.content);
                    }
                    else {
                      $('.taskit-interval.' + interval).append(current_interval.content);
                    }
                  }
                  load_more_button.attr('interval', current_interval.name);
                }
                load_more_button.attr('page', page);
                if (response.remove_load_more == true) {
                  load_more_button.hide();
                }
                ajax_request = null;

                $('#modalBackdrop').remove();
                $('#modalContent').remove();
              },
              error: function(data) {
                ajax_request = null;
              }
            });
          }
          return false;
        });
      }
    }
  };

})(jQuery);
