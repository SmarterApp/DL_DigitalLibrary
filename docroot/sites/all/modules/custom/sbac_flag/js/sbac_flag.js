(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_flag = {
    attach: function (context, settings) {
      // Hide modal button.
      if ($('#sbac-flag-resource-modal').length) {
        $('#sbac-flag-resource-modal').hide();
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
  var has_run_once = false;
  var clicked = false;
  var pager_count = 0;
  Drupal.behaviors.sbac_flag_load_more = {
    attach: function (context, settings) {
      $('#sbac-load-more').click( function() {
        // On click, hash the url
        pager_count++;
        window.location.hash = 'pager=' + pager_count;
        var pager = $(this).attr('offset');
        clicked = true;
        Drupal.behaviors.sbac_flag_load_more.load_more_content(pager);
        return false;
      });

      var hash = window.location.hash;
      if (hash != '' && !has_run_once && !clicked) {
        var pager = hash.replace('#pager=', '');
        Drupal.behaviors.sbac_flag_load_more.load_more_content(pager);
        has_run_once = true;
      }
    },
    load_more_content: function(offset) {
      if (ajax_request == null) {
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
    }
  };

})(jQuery);
