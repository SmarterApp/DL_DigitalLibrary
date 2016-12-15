(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_alignment_everything = {
    attach: function (context, settings) {
      $('#modal-content').addClass('alignment-container-no-scroll');
      read_more_less = function (element) {
        var term_id = $(element).attr('term');
        var container = $(element).parent().parent();
        var less = $(container).children('.checkbox-less-' + term_id);
        var more = $(container).children('.checkbox-more-' + term_id)
        if ($(less).hasClass('active')) {
          $(less).removeClass('active');
          $(less).hide();
          $(more).addClass('active');
          $(more).show();
        }
        else {
          $(more).removeClass('active');
          $(more).hide();
          $(less).addClass('active');
          $(less).show();
        }
      };

      // Close the open modal content and backdrop
      function closeCtoolsModal() {
        // Unbind the events
        $(window).unbind('resize',  modalContentResize);
        
        // Remove the content
        $('#modalContent').remove();
        $('#modalBackdrop').remove();
      }

      // Move and resize the modalBackdrop and modalContent on resize of the window
      modalContentResize = function(){
        // Get our heights
        var docHeight = $(document).height();
        var docWidth = $(document).width();
        var winHeight = $(window).height();
        var winWidth = $(window).width();
        if( docHeight < winHeight ) docHeight = winHeight;

        // Get where we should move content to
        var modalContent = $('#modalContent');
        var mdcTop = ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
        var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);

        // Apply the changes
        $('#modalBackdrop').css('height', docHeight + 'px').css('width', docWidth + 'px').show();
        modalContent.css('top', mdcTop + 'px').css('left', mdcLeft + 'px').show();
      };

      // Modal Delete callback.
      $('.ccss-term-delete').click(function () {
        var nid = $(this).attr('nid');
        var update_form = function (data) {
          $('tr#term-' + nid).hide();
        }
        var current_nid = Drupal.settings.resource_nid;
        $.ajax({
          type: "POST",
          url: "/ajax-alignment-crud",
          success: update_form,
          data: 'op=delete&nid=' + nid + '&current_nid=' + current_nid
        });
        return false;
      });

      // Remove callback.
      $('.sbac-custom-term-remove').click(function () {
        var parentTerm = $(this);
        var parentId = $(this).attr("tid");
        var update_data = function (data) {
          var obj = jQuery.parseJSON(data);
          if ((obj.publication == 'CC-ELA-v1' && obj.depth <= 2)
            || (obj.publication == 'CC-MA-v1' && obj.depth <= 2)
            || (obj.publication == '0')) {
            $('.alignment-form').hide();
            $('.alignment-buttons').show();
          }

          $('.alignment-filter').html(obj.html);
          var attr = parentTerm.parent('li').attr('id');
          $("#" + attr + " ~ li").remove();
          parentTerm.parent('li').remove();

          //reattached the behaviors
          Drupal.attachBehaviors('.sbac-custom-term-remove');
          $('.disabled').click(function (e) {
            e.preventDefault();
            //do other stuff when a click happens
          });
        }

        $.ajax({
          type: "POST",
          url: "/ajax-terms",
          success: update_data,
          data: 'parent=' + parentId + '&remove=true',
        });

        return false;
      });

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
                // $('#modalBackdrop').hide();
                // $('#modalContent').hide();
              });

              $('#ccss-submit').click(function () {
                var countType = countStandard = 0;
                $('#alignment-msg').html('');
                //count standards
                // $('input[id^=edit-term-]').each(function () {
                $('input:checkbox[id*=edit-term-]').each(function () {
                  if ($(this).is(':checked')) {
                    countStandard++;
                  }
                });

                if (countStandard > 0) {
                  var alignmentStandards = '';
                  var alignmentType = $('#edit-alignment-type').val();

                  //get ref
                  var alignmentRef = $('input[id=alignment_ref]').val();
                  //count standards
                  // $('input[id^=edit-term-]').each(function () {
                  $('input:checkbox[id*=edit-term-]').each(function () {
                    if ($(this).is(':checked')) {
                      var temp = $(this).attr('id');
                      var id = temp.split('-');
                      id = id[2];
                      alignmentStandards += '|' + id;
                    }
                  });

                  var closeModal = function (data) {
                    var obj = jQuery.parseJSON(data);
                    $('#sbac-resource-alignment-tag-view').html(obj.html);
                    closeCtoolsModal();
                    // $('#modalBackdrop').hide();
                    // $('#modalContent').hide();
                    Drupal.attachBehaviors('.ccss-term-delete');

                    var field = $('.node-resource-form .field-name-field-alignment-term input[type=text]');
                    var vals = [];
                    if (field.val() != '') {
                      vals.push(field.val());
                    }
                    vals = $.merge(vals, obj.terms);
                    field.val(vals.join());
                  }

                  $.ajax({
                    type: "POST",
                    url: "/ajax-alignment-crud",
                    success: closeModal,
                    data: 'op=create&alignment_type=' + alignmentType + '&alignment_ref=' + alignmentRef + '&alignment_standards=' + alignmentStandards,
                  });
                }
                else {
                  $('#modal-content').animate({ scrollTop: 0 });
                  $('#alignment-msg').append('<div class="alignment-error"><ul></ul></div>');
                  if (countStandard < 1) {
                    $('#alignment-msg .alignment-error ul').append('<li>Please select a standard.</li>');
                  }
                }
                return false;
              });
            }

            var refNode = $('input#ref_node').val();

            $.ajax({
              type: "POST",
              url: "/ajax-alignment-form",
              success: update_form,
              data: 'tid=' + parentId + '&ref_node=' + refNode
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
        }

        $.ajax({
          type: "POST",
          url: "/ajax-terms",
          success: update_data,
          data: 'parent=' + parentId,
        });

        var update_breadcrumb = function (data) {
          var obj = jQuery.parseJSON(data);
          $('.alignment-breadcrumb').html(obj.html);

          Drupal.attachBehaviors('.sbac-custom-term-remove');
        }

        $.ajax({
          type: "POST",
          url: "/ajax-alignment-breadcrumbs",
          success: update_breadcrumb,
          data: 'tid=' + parentId,
        });


        return false;
      });
    }
  };
})(jQuery);
