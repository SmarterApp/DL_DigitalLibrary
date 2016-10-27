(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_flag = {
    attach: function (context, settings) {
      // Hide modal button.
      if ($('#sbac-flag-collaboration-modal').length) {
        $('#sbac-flag-collaboration-modal').hide();
      }

      // If there is an error, click the radio button so that the
      // textarea moves to the right location.
      if ($('input[name=flag_options]:radio:checked')) {
        var radio = $('input[name=flag_options]:radio:checked');
        radio.click();
      }

      // On click of radio button, move textarea.
      $('#sbac-flag-options input').click( function() {
        $(this).parent().append($('#sbac-flag-optional-comment'));
        $('#sbac-flag-optional-comment').show();
      });
    }
  };

  var ajax_request = null;
  Drupal.behaviors.sbac_flag_load_more = {
    attach: function (context, settings) {
      $('#sbac-load-more').click( function() {
        if (ajax_request == null) {
          var offset = $(this).attr('offset');
          ajax_request = $.ajax({
            type: 'POST',
            url: "/sbac-flag/load-more",
            data: {'offset' : offset},
            success: function(data) {
              ajax_request = null;
              var response = jQuery.parseJSON(data);
              $('#sbac-flag-mod-cont').append(response.list_output);
              $('#sbac-load-more').attr('offset', response.offset);
              if (response.remove_button == true) {
                $('#sbac-load-more').hide();
              }
              Drupal.attachBehaviors();
            },
            error: function(data) {

            }
          });
        }
        return false;
      });
    }
  };

})(jQuery);
