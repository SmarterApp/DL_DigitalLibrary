(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_share = {
    attach: function (context, settings) {
      var clip = new ZeroClipboard(document.getElementById('sbac-permanent-link-button'), {
        moviePath: 'http://' + location.hostname + '/sites/all/libraries/zeroclipboard/ZeroClipboard.swf'
      });

      // clip.glue(document.getElementById('sbac-permanent-link-text'));

      clip.on( 'load', function(client) {
        alert( "movie is loaded" );
      } );

      clip.on( 'complete', function(client, args) {
        alert("Copied text to clipboard: " + args.text );
      } );

      clip.on( 'mouseover', function(client) {
        alert("mouse over");
      } );

      clip.on( 'mouseout', function(client) {
        alert("mouse out");
      } );

      clip.on( 'mousedown', function(client) {
        alert("mouse down");
        return false;
      } );

      clip.on( 'mouseup', function(client) {
        alert("mouse up");
        return false;
      } );


      $('#sbac-temp-link-button').click( function() {
        var nid = $(this).attr('nid');
        generate_link(nid);
        return false;
      });

      /**
       * Submits the request to drupal.
       *
       * @param nid
       */
      generate_link = function (nid) {
        var ajax_request = $.ajax({
          type: 'POST',
          url: "/sbac-share-generate-link",
          data: {'nid':nid},
          success: function(data) {
            var response = jQuery.parseJSON(data);
            $('#sbac-temporary-link-text').val(response.result);
            $('#sbac-temp-link-button').html('Copy Link to Clipboard');
            ajax_request = null;
          },
          error: function(data) {

          }
        });
      };
    }
  };

})(jQuery);
