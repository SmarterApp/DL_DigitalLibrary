(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * If the material is a doc, load google,
   * else load JwPlayer
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_load_media = {
    attach: function (context, settings) {
      $('#sbac-materials li a').click( function (event) {
        event.preventDefault();
        var type = $(this).attr('sbac-type');
        var resource = $('#resource-element');
        if (type == 'document') {
          var google_viewer = '<iframe src="http://docs.google.com/viewer?url=' + $(this).attr('href') + '&embedded=true" width="850" height="400" style="border: none;"></iframe>';
          resource.empty().html(google_viewer);
        }
        else if (type == 'video') {
          resource.html('<div id="sbac-jwplayer"></div>');
          jwplayer('sbac-jwplayer').setup({ file: $(this).attr('href'), height: 400, width: 850 });
          jwplayer('sbac-jwplayer').play();
        }
        else {
          var img = $('<img>');
          img.attr('src', $(this).attr('href'));
          img.attr('height', 400);
          img.attr('width', 850);
          resource.empty().html(img);
        }
        var doc_type = $('#sbac-resource-doc-type');
        var filename = $('#sbac-filename');
        filename.html($(this).html());
        doc_type.removeClass();
        doc_type.addClass(type);
        doc_type.html(type);
        return false;
      });
    }
  };

})(jQuery);
