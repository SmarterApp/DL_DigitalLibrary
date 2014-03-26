(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};
  var ajax_request = null;
  /**
   * If the material is a doc, load google,
   * else load JwPlayer
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_resource_load_media = {
    check: function (resource, local_url) {
      if (ajax_request == null){
        ajax_request = $.ajax({
          type: 'POST',
          url: "/sbac-resource/url-exists",
          data: {'url' : local_url},
          success: function(data) {
            var response = jQuery.parseJSON(data);
            if (response.result == true) {
              var google_url = 'http://docs.google.com/viewer';
              if (window.location.protocol == 'https:') {
                google_url = 'https://docs.google.com/viewer';
              }
              var google_viewer = '<iframe src="' + google_url + '?url=' + encodeURIComponent(local_url + '&embedded=true') + '" width="850" height="400" style="border: none;"></iframe>';
              resource.empty().append(google_viewer);
              resource.addClass('google-doc');
              $('.infobar .ajax-progress').hide();
            }
            else {
              var url = '/sites/all/modules/custom/sbac_content_types/sbac_resource/images/no-preview.jpg';
              var img = $('<img>');
              img.attr('src', url);
              img.attr('height', 400);
              img.attr('width', 850);
              resource.empty().append(img);
              $('.infobar .ajax-progress').hide();
            }
            ajax_request = null;
          }
        });
      }
    },
    attach: function (context, settings) {
      $('#sbac-materials li a').click( function (event) {
        event.stopPropagation();
        event.preventDefault();
        var local_url = $(this).attr('href');
        var type = $(this).attr('sbac-type');
        var resource = $('#resource-element');
        switch (type) {
          case 'document':
            $('.infobar .ajax-progress').show();
            Drupal.behaviors.sbac_resource_load_media.check(resource, local_url);
            break;
          case 'html5':
            resource.empty().append('<iframe src="' + local_url + '" width="850" height="600" style="border: none;"></iframe>');
            resource.removeClass('google-doc');
            break;
          case 'video':
            resource.empty().append('<div id="sbac-jwplayer"></div>');
            jwplayer('sbac-jwplayer').setup({ file: local_url, height: 400, width: 850, primary: "flash" });
            jwplayer('sbac-jwplayer').play();
            resource.removeClass('google-doc');
            break;
          case 'image':
            var img = $('<img>');
            img.attr('src', local_url);
            img.attr('height', 400);
            img.attr('width', 850);
            resource.empty().append(img);
            resource.removeClass('google-doc');
            break;
          case 'schooltube':
            resource.empty().append('<div class="flex-video"><iframe width="500" height="375" src="' + local_url + '" frameborder="0" allowfullscreen="allowfullscreen" mozallowfullscreen="mozallowfullscreen" webkitallowfullscreen="webkitallowfullscreen"></iframe></div>');
            resource.removeClass('google-doc');
            break;
          case 'teachertube':
            resource.empty().append('<div class="flex-video"><iframe width="560" height="315" src="' + local_url + '" frameborder="0" allowfullscreen/></iframe>');
            resource.removeClass('google-doc');
            break;
          case 'slideshare':
            resource.empty().append('<div class="flex-video"><iframe src="' + local_url + '" width="427" height="356" frameborder="0" marginwidth="0" marginheight="0" scrolling="no" style="border:1px solid #CCC;border-width:1px 1px 0;margin-bottom:5px" allowfullscreen webkitallowfullscreen mozallowfullscreen></iframe></div>');
            resource.removeClass('google-doc');
            break;
          case 'vimeo':
            resource.empty().append('<div class="flex-video"><iframe src="' + decodeURIComponent($(this).attr('href')) + '" width="500" height="281" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen></iframe></div>');
            resource.removeClass('google-doc');
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
              resource.empty().append('<div class="flex-video"><iframe width="560" height="315" src="' + local_url + '" frameborder="0" allowfullscreen></iframe></div>');
              resource.removeClass('google-doc');
            }
            break;
          default:
            var img = $('<img>');
            img.attr('src', local_url);
            img.attr('height', 400);
            img.attr('width', 850);
            resource.empty().append(img);
            resource.removeClass('google-doc');
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
