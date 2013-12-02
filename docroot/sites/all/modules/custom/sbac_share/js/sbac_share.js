(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_share = {
    attach: function (context, settings) {
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
            ajax_request = null;
          },
          error: function(data) {

          }
        });
      };

//      var emcode;
//      var emid;

//      $('.embed-textarea').bind('mouseover', function(){
//        emcode = this.value;
//        emid = $(this).attr('id');
//        this.select();
//      });
//
//      $('.embed-textarea').keyup(function(){
//        this.value = emcode;
//        this.select();
//      });
//
//      /* ZeroClipboard https://github.com/zeroclipboard/ZeroClipboard */
//      var hasFlash = false; try { var fo = (navigator.mimeTypes && navigator.mimeTypes['application/x-shockwave-flash']) ? navigator.mimeTypes['application/x-shockwave-flash'].enabledPlugin : 0; if(fo) hasFlash = true; }catch(e){ if(navigator.mimeTypes ['application/x-shockwave-flash'] != undefined) hasFlash = true; }
//      if (hasFlash) { //only proceed if Flash is enabled
//        ZeroClipboard.setDefaults( { moviePath: 'http://' + location.hostname + '/sites/all/libraries/zeroclipboard/ZeroClipboard.swf' } );
//        var clipsmall = new ZeroClipboard($("#embed-textarea-small"));
//        clipsmall.glue( document.getElementById('embed-textarea-small') );
//        //all 3 clips call this function when complete
//        clipsmall.on( 'complete', function ( client, args ) {
//          $('#zeroclipmessage').text("Copied " + emid.substr(15) + " embed code to clipboard: " + args.text);
//        });
//        var clipmedium = new ZeroClipboard($("#embed-textarea-medium"));
//        clipmedium.glue( document.getElementById('embed-textarea-medium') );
//        var cliplarge = new ZeroClipboard($("#embed-textarea-large"));
//        cliplarge.glue( document.getElementById('embed-textarea-large') );
//      }
    }
  };

})(jQuery);
