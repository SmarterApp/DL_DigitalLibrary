(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  ajax_request = null;

  Drupal.behaviors.sbac_share = {
    attach: function (context, settings) {
      var load_more_button = $('#taskit-load-more');
      if (load_more_button.length) {
        load_more_button.click( function() {
          if (ajax_request == null) {
            ajax_request = $.ajax({
              type: 'POST',
              url: "/taskit-load-more",
              data: {'page' : load_more_button.attr('page'), 'role' : load_more_button.attr('role')},
              success: function(data) {
                var response = jQuery.parseJSON(data);
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
