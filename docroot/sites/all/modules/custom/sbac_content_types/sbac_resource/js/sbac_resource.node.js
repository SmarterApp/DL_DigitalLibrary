(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};
  found = false;
  /**
   * If the material is a doc, load google,
   * else load JwPlayer
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_load_media = {
    attach: function (context, settings) {
      // on click of the menu item
      // display the loader, do the check once loaded, and display the correct content
      // then hide the loader gif.
      $('#sbac-google-previewer').load( function() {
        if ('#sbac-google-previewer:contains("we were unable to find the document at the original source")') {
          var url = '/sites/all/modules/custom/sbac_content_types/sbac_resource/images/no-preview.jpg';
          var img = $('<img>');
          img.attr('src', url);
          img.attr('height', 400);
          img.attr('width', 850);
          $('#sbac-google-previewer').hide();
          $('#resource-element').append(img);
        }
        $('#sbac-loader-image').hide();
      });


      $('#sbac-materials li a').click( function (event) {
        event.stopPropagation();
        event.preventDefault();
        var local_url = $(this).attr('href');
        var type = $(this).attr('sbac-type');
        var resource = $('#resource-element');
        switch (type) {
          case 'document':
            $('#sbac-loader-image').show();

            var google_url = 'http://docs.google.com/viewer';
            if (window.location.protocol == 'https:') {
              google_url = 'https://docs.google.com/viewer';
            }
            local_url +=  '&embedded=true';
            var google_viewer = '<iframe id="sbac-google-previewer" title="resource-preview" src="' + google_url + '?url=' + encodeURIComponent(local_url) + '&embedded=true' + '" width="880" height="400" style="border: none;">Alternative Content</iframe>';
            resource.empty().append(google_viewer);
            break;
          case 'html5':
            resource.empty().append('<iframe title="resource-preview" src="' + local_url + '" width="880" height="600" style="border: none;"></iframe>');
            break;
          case 'video':
            resource.empty().append('<div id="sbac-jwplayer"></div>');
            jwplayer('sbac-jwplayer').setup({ file: local_url, height: 400, width: 880, primary: "flash" });
            jwplayer('sbac-jwplayer').play();
            break;
          case 'image':
            var img = $('<img>');
            img.attr('src', local_url);
            img.attr('height', 400);
            img.attr('width', 850);
            resource.empty().append(img);
            break;
          case 'schooltube':
            resource.empty().append('<div class="flex-video"><iframe title="resource-preview" width="500" height="375" src="' + local_url + '" frameborder="0" allowfullscreen="allowfullscreen" mozallowfullscreen="mozallowfullscreen" webkitallowfullscreen="webkitallowfullscreen">Alternative Content</iframe></div>');
            break;
          case 'teachertube':
            resource.empty().append('<div class="flex-video"><iframe title="resource-preview" width="560" height="315" src="' + local_url + '" frameborder="0" allowfullscreen/>Alternative Content</iframe>');
            break;
          case 'slideshare':
            resource.empty().append('<div class="flex-video"><iframe title="resource-preview" src="' + local_url + '" width="427" height="356" frameborder="0" marginwidth="0" marginheight="0" scrolling="no" style="border:1px solid #CCC;border-width:1px 1px 0;margin-bottom:5px" allowfullscreen webkitallowfullscreen mozallowfullscreen>Alternative Content</iframe></div>');
            break;
          case 'vimeo':
            resource.empty().append('<div class="flex-video"><iframe title="resource-preview" src="' + decodeURIComponent($(this).attr('href')) + '" width="500" height="281" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen>Alternative Content</iframe></div>');
            break;
          case 'youtube':
            if (local_url.indexOf('youtube') == -1) {
              var url = '/sites/all/modules/custom/sbac_content_types/sbac_resource/images/no-preview.jpg';
              var img = $('<img>');
              img.attr('src', url);
              img.attr('height', 400);
              img.attr('width', 850);
              resource.empty().append(img);
            }
            else {
              resource.empty().append('<div class="flex-video"><iframe title="resource-preview" width="560" height="315" src="' + local_url + '" frameborder="0" allowfullscreen>Alternative Content</iframe></div>');
            }
            break;
          default:
            var img = $('<img>');
            img.attr('src', local_url);
            img.attr('height', 400);
            img.attr('width', 850);
            resource.empty().append(img);
            break;
        }

        var doc_type = $('#sbac-resource-doc-type');
        var filename = $('#sbac-filename');
        var transcript = $(this).attr('transcript');
        var filename_output = $(this).html();
        if (transcript == 1) {
          filename_output = $(this).html() + " (Transcript Included)";
        }
        filename.empty().append(filename_output);
        doc_type.removeClass();
        doc_type.addClass(type);
        doc_type.empty().append(type);

        if (type == 'document') {
          $('#sbac-google-previewer').load( function() {
            if ('#sbac-google-previewer:contains("we were unable to find the document at the original source")') {
              var url = '/sites/all/modules/custom/sbac_content_types/sbac_resource/images/no-preview.jpg';
              var img = $('<img>');
              img.attr('src', url);
              img.attr('height', 400);
              img.attr('width', 850);
              $('#sbac-google-previewer').hide();
              $('#resource-element').append(img);
            }
            $('#sbac-loader-image').hide();
          });
        }

        return false;
      });

      $('#sbac-partial-download').hover( function() {
        $('.sbac-download-dropdown').toggle();
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
