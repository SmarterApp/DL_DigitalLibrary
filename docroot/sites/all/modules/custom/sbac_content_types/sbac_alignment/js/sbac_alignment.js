(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_alignment_everything = {
    attach: function (context, settings) {
      $('#modal-content').addClass('alignment-container-no-scroll');

      // Close the open modal content and backdrop
      function closeCtoolsModal() {
        // Unbind the events
        // $(window).unbind('resize', modalContentResize);
        
        // Remove the content
        $('#modalContent').remove();
        $('#modalBackdrop').remove();
      }

      // Move and resize the modalBackdrop and modalContent on resize of the window
      // var modalContentResize = function(){
      //   // Get our heights
      //   var docHeight = $(document).height();
      //   var docWidth = $(document).width();
      //   var winHeight = $(window).height();
      //   var winWidth = $(window).width();
      //   if (docHeight < winHeight) {
      //     docHeight = winHeight;
      //   }

      //   // Get where we should move content to
      //   var modalContent = $('#modalContent');
      //   var mdcTop = (winHeight / 2) - (modalContent.outerHeight() / 2);
      //   var mdcLeft = (winWidth / 2) - (modalContent.outerWidth() / 2);

      //   // Apply the changes
      //   $('#modalBackdrop').css('height', docHeight + 'px').css('width', docWidth + 'px').show();
      //   modalContent.css('top', mdcTop + 'px').css('left', mdcLeft + 'px').show();
      // };

      // Clicking on the term name.
      $('.sbac-custom-term').click(function () {
        var parentId = $(this).attr("tid");

        var update_data = function (data) {
          var obj = jQuery.parseJSON(data);

          if ((obj.publication == 'CC-ELA-v1' && obj.depth > 2)
            || (obj.publication == 'CC-MA-v1' && obj.depth > 2)
            || (obj.publication == 'TA-ELA-v1' && obj.depth > 2)
            || (obj.publication == 'TA-MA-v1' && obj.depth > 2)) {
            $('.alignment-form').show();
            $('.alignment-buttons').hide();
            $('.alignment-filter').html('');

            var update_form = function (data) {
              var obj = jQuery.parseJSON(data);
              $('.alignment-form').html(obj.html);
              $('p[id^=description-]').more({length: 200, moreText: 'read more', lessText: 'read less'});

              $('#ccss-cancel').click(function () {
                closeCtoolsModal();
              });

              $('#ccss-submit').click(function () {
                $('#alignment-msg').html('');
                var alignmentStandards = '';

                $('input:checkbox[id*=edit-term-]').each(function () {
                  if ($(this).is(':checked')) {
                    var temp = $(this).attr('id');
                    var id = temp.split('-');
                    id = id[2];
                    alignmentStandards += '|' + id;
                  }
                });

                if (alignmentStandards) {
                  var closeModal = function (data) {
                    var obj = jQuery.parseJSON(data);
                    $(settings.sbac_alignment_everything.container).html(obj.html);
                    closeCtoolsModal();

                    Drupal.attachBehaviors('.alignment-toggle');
                  };

                  $.ajax({
                    type: "POST",
                    url: "/ajax-alignment-crud",
                    success: closeModal,
                    data: 'alignment_type=' + settings.sbac_alignment_everything.type + '&alignment_standards=' + alignmentStandards
                  });
                }
                else {
                  $('#modal-content').animate({ scrollTop: 0 });
                  $('#alignment-msg').append('<div class="alignment-error"><ul></ul></div>');
                  if (alignmentStandards == '') {
                    $('#alignment-msg .alignment-error ul').append('<li>Please select a standard.</li>');
                  }
                }
                return false;
              });
            };

            $.ajax({
              type: "POST",
              url: "/ajax-alignment-form",
              success: update_form,
              data: 'tid=' + parentId
            });
          }
          else {
            $('.alignment-form').hide();
            $('.alignment-buttons').show();
            $('.alignment-filter').html(obj.html);

            $('.disabled').click(function (e) {
              e.preventDefault();
              //do other stuff when a click happens
            });
          }

          //reattached the behaviors
          Drupal.attachBehaviors('.sbac-custom-term');
        };

        $.ajax({
          type: "POST",
          url: "/ajax-terms",
          success: update_data,
          data: 'parent=' + parentId
        });

        var update_breadcrumb = function (data) {
          var obj = jQuery.parseJSON(data);
          $('.alignment-breadcrumb').html(obj.html);

          Drupal.attachBehaviors('.sbac-custom-term-remove');
        };

        $.ajax({
          type: "POST",
          url: "/ajax-alignment-breadcrumbs",
          success: update_breadcrumb,
          data: 'tid=' + parentId
        });


        return false;
      });
    }
  };
})(jQuery);
