(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_filter_alignment_everything = {
    attach: function (context, settings) {
      read_more_less = function (element) {
        var term_id = $(element).attr('term');
        var container = $(element).parent().parent();
        var less = $(container).children('.checkbox-less-' + term_id);
        var more = $(container).children('.checkbox-more-' + term_id);
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

      // Function that the submit buttons call to cleanup.
      var closeModal = function (data) {
        var obj = jQuery.parseJSON(data);

        var currentActiveFilters = $('#sbac-category-current-filters').html();
        $('#sbac-category-current-filters').html(currentActiveFilters+obj.html);

        var current_filters = $('#sbac-search-current-filters');
        if (current_filters.val() == '') {
        $('#sbac-category-current-filters').removeClass('noshow');
          current_filters.val(obj.filters);
        }
        else {
          var filter_tids = current_filters.val();
          filter_tids += '::' + obj.filters;
          current_filters.val(filter_tids);
        }

        $('#edit-reset-filters').removeClass('js-hide');
        $('.category-hide').addClass('js-hide');

        closeCtoolsModal();
        Drupal.attachBehaviors('.ccss-term-delete');
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
            || (obj.publication == 'CC-MA-v1' && obj.depth > 2)) {
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
              $('#ccss-cancel2').click(function () {
                closeCtoolsModal();
              });

              $('#ccss-submit').click(function () {
                var countType = countStandard = 0;
                $('#alignment-msg').html('');
                //count standards
                $('input[id^=edit-term-]').each(function () {
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
                  $('input[id^=edit-term-]').each(function () {
                    if ($(this).is(':checked')) {
                      var temp = $(this).attr('id');
                      var id = temp.split('-');
                      id = id[2];
                      alignmentStandards += '|' + id;
                    }
                  });

                  $.ajax({
                    type: "POST",
                    url: "/ajax-filter-alignment-finish-set",
                    success: closeModal,
                    data: 'alignment_standards=' + alignmentStandards,
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

              // Remove initial click handler. Needs to check what type of behavior happens.
              $( ".sbac-custom-term-remove").unbind( "click" );
              // Add custom behavior to last breadcrumb X if this is the last form.
              $('.sbac-custom-term-remove').click(function(event) {
                // Check if anythings been selected.
                var countStandard = 0;
                $('input[id^=edit-term-]').each(function () {
                  if ($(this).is(':checked')) {
                    countStandard++;
                  }
                });

                // If no standards are met then behave as normal. Rebind everything.
                if (countStandard == 0) {
                  $(this).unbind( "click" );
                  Drupal.attachBehaviors('.sbac-custom-term-remove');
                  $(this).click();
                } else { // Get, show and attach behaviors for confirm dialog.
                  var parentTerm = $(this);
                  var parentId = $(this).attr("tid");
                  var confirmDialogForm = function (data) {
                    var obj = jQuery.parseJSON(data);
                    $('.alignment-filter').html(obj.html);
                    $('.alignment-form').hide(); // Hide main form.

                    $('#cmod-confirm-cancel').click(function() {
                      // Reuse the click handler for the initial breadcrumb.
                      $(parentTerm).unbind("click");
                      Drupal.attachBehaviors('.sbac-custom-term-remove');
                      $(parentTerm).click();
                      return false;
                    }); // End click.

                    // If confirm, add the selected filters.
                    $('#cmod-confirm-submit').click(function() {
                      var alignmentStandards = '';
                      var alignmentType = $('#edit-alignment-type').val();

                      //get ref
                      var alignmentRef = $('input[id=alignment_ref]').val();
                      //count standards
                      $('input[id^=edit-term-]').each(function () {
                        if ($(this).is(':checked')) {
                          var temp = $(this).attr('id');
                          var id = temp.split('-');
                          id = id[2];
                          alignmentStandards += '|' + id;
                        }
                      });

                      $.ajax({
                        type: "POST",
                        url: "/ajax-filter-alignment-finish-set",
                        success: closeModal,
                        data: 'alignment_standards=' + alignmentStandards,
                      });
                      return false;
                    }); // End click.
                  }
                  // Do the custom ajax thing.
                  $.ajax({
                    type: "POST",
                    url: "/ajax-filter-alignment-confirm-remove",
                    success: confirmDialogForm,
                    data: 'empty=0',
                  });
                }

              });

            } // end submit.

            var refNode = $('input#ref_node').val();

            $.ajax({
              type: "POST",
              url: "/ajax-alignment-filter-form",
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
      }); // End clicking on the term name.

    }
  };
})(jQuery);
