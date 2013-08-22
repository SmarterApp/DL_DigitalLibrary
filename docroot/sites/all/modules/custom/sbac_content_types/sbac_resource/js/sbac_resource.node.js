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
        else if (type == 'image') {
          var img = $('<img>');
          img.attr('src', $(this).attr('href'));
          img.attr('height', 400);
          img.attr('width', 850);
          resource.empty().html(img);
        }
        else if (type == 'embed') {
          resource.html('<iframe width="500" height="375" src="' + $(this).attr('href') + '" frameborder="0" allowfullscreen="allowfullscreen" mozallowfullscreen="mozallowfullscreen" webkitallowfullscreen="webkitallowfullscreen"></iframe>');
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

      // when the list loses focus.
      $(document).click(function() {
        var selectedDiv = $('.selectedDiv');
        selectedDiv.hide();
        selectedDiv.removeClass('selectedDiv');
        selectedDiv.removeClass('open');
      });

      // when the list is clicked.
      $('.sbac-materials-dropdown').click( function () {
        var sbac_materials = $('#sbac-materials');
        if (sbac_materials.hasClass('open')) {
          sbac_materials.removeClass('open');
          sbac_materials.removeClass('selectedDiv');
          sbac_materials.hide();
        }
        else {
          sbac_materials.addClass('open');
          sbac_materials.addClass('selectedDiv');
          sbac_materials.show();
        }
        return false;
      });

      // when an item in the list is clicked.
      $('#sbac-materials li a').click( function() {
        var selectedDiv = $('.selectedDiv');
        selectedDiv.hide();
        selectedDiv.removeClass('selectedDiv');
        selectedDiv.removeClass('open');
      });
    }
  };

})(jQuery);
