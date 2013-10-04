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
        event.stopPropagation();
        event.preventDefault();

        var type = $(this).attr('sbac-type');
        var resource = $('#resource-element');
        if (type == 'document') {
          var google_url = 'http://docs.google.com/viewer';
          if (window.location.protocol == 'https') {
            google_url = 'https://docs.google.com/viewer';
          }
          var google_viewer = '<iframe src="' + google_url + '?url=' + $(this).attr('href') + '&embedded=true" width="850" height="400" style="border: none;"></iframe>';
          resource.empty().append(google_viewer);
        }
        else if (type == 'video') { // includes youtube
          resource.empty().append('<div id="sbac-jwplayer"></div>');
          jwplayer('sbac-jwplayer').setup({ file: $(this).attr('href'), height: 400, width: 850, primary: "flash" });
          jwplayer('sbac-jwplayer').play();
        }
        else if (type == 'image') {
          var img = $('<img>');
          img.attr('src', $(this).attr('href'));
          img.attr('height', 400);
          img.attr('width', 850);
          resource.empty().append(img);
        }
        else if (type == 'schooltube') {
          resource.empty().append('<div class="flex-video"><iframe width="500" height="375" src="' + $(this).attr('href') + '" frameborder="0" allowfullscreen="allowfullscreen" mozallowfullscreen="mozallowfullscreen" webkitallowfullscreen="webkitallowfullscreen"></iframe></div>');
        }
        else if (type == 'teachertube') {
          resource.empty().append('<div class="flex-video"><iframe width="560" height="315" src="' + $(this).attr('href') + '" frameborder="0" allowfullscreen/></iframe>');
        } 
        else if (type == 'slideshare') {
          resource.empty().append('<div class="flex-video"><iframe src="' + $(this).attr('href') + '" width="427" height="356" frameborder="0" marginwidth="0" marginheight="0" scrolling="no" style="border:1px solid #CCC;border-width:1px 1px 0;margin-bottom:5px" allowfullscreen webkitallowfullscreen mozallowfullscreen></iframe></div>');
        }
        else if (type == 'vimeo') {
          resource.empty().append('<div class="flex-video"><iframe src="' + decodeURIComponent($(this).attr('href')) + '" width="500" height="281" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen></iframe></div>');
        }
        else if (type == 'youtube') {
          resource.empty().append('<div class="flex-video"><iframe width="560" height="315" src="' + $(this).attr('href') + '" frameborder="0" allowfullscreen></iframe></div>');
        }        
        else {
          var img = $('<img>');
          img.attr('src', $(this).attr('href'));
          img.attr('height', 400);
          img.attr('width', 850);
          resource.empty().append(img);
        }

        var doc_type = $('#sbac-resource-doc-type');
        var filename = $('#sbac-filename');
        filename.empty().append($(this).html());
        doc_type.removeClass();
        doc_type.addClass(type);
        doc_type.empty().append(type);

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
