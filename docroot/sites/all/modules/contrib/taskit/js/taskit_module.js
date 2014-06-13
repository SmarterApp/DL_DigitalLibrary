(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  ajax_request = null;

  Drupal.behaviors.sbac_share = {
    attach: function (context, settings) {
      var load_more_button = $('#taskit-load-more');
      if (load_more_button.length) {
        load_more_button.click( function() {
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
