(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_share = {
    attach: function (context, settings) {
      var clip = new ZeroClipboard(document.getElementById('sbac-permanent-link-button'), {
        moviePath: 'http://' + location.hostname + '/sites/all/libraries/zeroclipboard/ZeroClipboard.swf'
      });

      $('#sbac-temp-link-button').one('click', function(event) {
        if ($('.temporary-link-container').hasClass('active')) {
          var nid = $(this).attr('nid');
          generate_link(nid);
        }
        return false;
      });

      $('.temp-link-clear').one('click', function(event) {
        var key = $('#sbac-temporary-link-text').val();
        remove_link(key);
        return false;
      });

      /**
       * Submits the request to drupal.
       *
       * @param nid
       */
      generate_link = function (nid) {
        var ajax_generate_request = $.ajax({
          type: 'POST',
          url: "/sbac-share-generate-link",
          data: {'nid':nid},
          success: function(data) {
            var response = jQuery.parseJSON(data);
            $('#sbac-temporary-link-text').val(response.result);
            $('#sbac-temp-link-button').html('Copy Link to Clipboard');
            var clipper = new ZeroClipboard(document.getElementById('sbac-temp-link-button'), {
              moviePath: 'http://' + location.hostname + '/sites/all/libraries/zeroclipboard/ZeroClipboard.swf'
            });
            clipper.on( 'dataRequested', function (client, args) {
              client.setText(response.result);
            });
            $('#sbac-temporary-link-text').after('<span class="temp-link-clear"></span>');
            Drupal.attachBehaviors('.temp-link-clear');
            ajax_generate_request = null;
          },
          error: function(data) {

          }
        });
      };

      /**
       * Submits the request to drupal.
       *
       * @param key
       */
      remove_link = function (key) {
        var ajax_remove_request = $.ajax({
          type: 'POST',
          url: "/sbac-share-remove-link",
          data: {'key': key},
          success: function(data) {
            $('#sbac-temporary-link-text').val('');
            $('#sbac-temp-link-button').html('Generate Temporary Link');
            $('.temp-link-clear').remove();
            ZeroClipboard.destroy();
            ajax_remove_request = null;
          },
          error: function(data) {

          }
        });
      };

    }
  };

})(jQuery);
