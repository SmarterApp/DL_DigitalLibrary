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
                if (response.new_interval != interval) {
                  $('.taskit-interval.' + interval).after(response.result);
                }
                else {
                  $('.taskit-interval.' + interval).append(response.result);
                }
                load_more_button.attr('interval', response.new_interval);
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
