(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_alignment_everything = {
    attach: function (context, settings) {
      var valueUpdater = function () {
        var alignmentStandards = [];
        $('#sbac-resource-alignment-tag-view input:checkbox[id*=standard-parent-]:checked').each(function () {
          var id = $(this).attr('id').split('-')[2];
          alignmentStandards.push(id);
        });
        var targetStandards = [];
        $('#sbac-resource-target-tag-view input:checkbox[id*=standard-parent-]:checked').each(function () {
          var id = $(this).attr('id').split('-')[2];
          targetStandards.push(id);
        });
        $('input:hidden[name=alignment_term_values]').val(alignmentStandards.join(':'));
        $('input:hidden[name=target_term_values]').val(targetStandards.join(':'));
      };

      // Handler for syncing the checkboxes and adding parents as needed
      $('.standard-check').click(function (e) {
        // Get the tid so we can check if the parent version of this tid exists
        var tid = $(this).attr('value');
        // Check to see if the parent exists, and if it does, just sync the checkboxes
        var parent = $('#standard-parent-' + tid);
        if (parent.length) {
          // Get the classes for this checkbox, and then get the one that is standard-TID
          var classes = $(this).attr('class').split(' ');
          var checkClass = '';
          $.each(classes, function (key, value) {
            if (value.match(/^standard-\d+$/)) {
              checkClass = '.' + value;
            }
          });
          // Make all of the other checkboxes with this class match the checked status of this one
          $(checkClass).prop('checked', $(this).prop('checked'));
          valueUpdater();
        } else {
          // Use the parent container to figure out the standard type
          var alignment = 'education_alignment';
          if ($(this).parents('#target-tag-container').length) {
            alignment = 'target_alignment';
          }
          // If the parent doesn't already exist, we add it as a new item, and rebuild the tables
          var currentStandards = [];
          // For each item already selected on the page, add them to the array
          $('input:checkbox[id*=standard-parent-]:checked').each(function () {
            var id = $(this).attr('id').split('-')[2];
            currentStandards.push(id);
          });

          // Function for adding the selected items to the page and closing the modal
          var updateTables = function (data) {
            $('#sbac-resource-alignment-tag-view').html(data.ccss_html);
            $('#sbac-resource-target-tag-view').html(data.target_html);

            Drupal.attachBehaviors('.standard-check');
            valueUpdater();
          };

          // Call the helper AJAX function to build the tables of standards
          $.ajax({
            type: 'POST',
            contentType: 'application/json',
            url: '/ajax-alignment-crud',
            success: updateTables,
            data: JSON.stringify({
              'alignment_type': alignment,
              'new_standards': [tid],
              'current_standards': currentStandards,
              'select_all': false
            })
          });
        }
      });

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
        // Get the tid for the clicked term
        var parentId = $(this).attr("tid");

        // Function to add the terms at the selected level to the form
        var update_data = function (data) {
          // Parse the returned data
          var obj = jQuery.parseJSON(data);

          // If this is the bottom level (i.e. - the selectable standards)
          if (obj.depth > 2) {

            $('.alignment-form').show();
            $('.alignment-buttons').hide();
            $('.alignment-filter').html('');

            // Function for creating the bottom level form
            var update_form = function (data) {
              // Pare the JSON representation of the standards
              var obj = jQuery.parseJSON(data);

              // Add the HTML of the form to the page
              $('.alignment-form').html(obj.html);

              // Limit the space taken up by the standards and allow them to be expanded
              $('p[id^=description-]').more({length: 200, moreText: 'read more', lessText: 'read less'});

              // Close the dialog if we cancel
              $('#ccss-cancel').click(function () {
                closeCtoolsModal();
              });

              // Add the onclick to the submit button
              $('#ccss-submit').click(function () {
                // Handler for the alignment/target taxonomy tagging
                var alignmentTargetTagging = function () {
                  // Clear any existing messages (errors), and standards
                  $('#alignment-msg').html('');

                  var newStandards = [];
                  // For each selected standard in the widget, add them to the array
                  $('input:checkbox[id*=edit-term-]:checked').each(function () {
                    var id = $(this).attr('id').split('-')[2];
                    newStandards.push(id);
                  });

                  var currentStandards = [];
                  // For each item already selected on the page, add them to the array
                  $('input:checkbox[id*=standard-parent-]:checked').each(function () {
                    var id = $(this).attr('id').split('-')[2];
                    currentStandards.push(id);
                  });

                  // If there were standards selected, continue
                  if (newStandards.length) {
                    // Function for adding the selected items to the page and closing the modal
                    var closeModal = function (data) {
                      //settings.sbac_alignment_everything.selection = obj.selection;

                      $('#sbac-resource-alignment-tag-view').html(data.ccss_html);
                      $('#sbac-resource-target-tag-view').html(data.target_html);
                      closeCtoolsModal();

                      Drupal.attachBehaviors('.standard-check');
                      valueUpdater();
                    };

                    // Call the helper AJAX function to build the tables of standards
                    $.ajax({
                      type: 'POST',
                      contentType: 'application/json',
                      url: '/ajax-alignment-crud',
                      success: closeModal,
                      data: JSON.stringify({
                        'alignment_type': settings.sbac_alignment_everything.type,
                        'new_standards': newStandards,
                        'current_standards': currentStandards,
                        'select_all': true
                      })
                    });
                  }
                  // Otherwise, just add an error
                  else {
                    $('#modal-content').animate({scrollTop: 0});
                    $('#alignment-msg').append('<div class="alignment-error"><ul></ul></div>');
                    $('#alignment-msg .alignment-error ul').append('<li>Please select a standard.</li>');
                  }
                  return false;
                };
                // Insert other taxonomy handlers here
                if (settings.sbac_alignment_everything.type == 'education_alignment' || settings.sbac_alignment_everything.type == 'target_alignment') {
                  return alignmentTargetTagging();
                }
                // Insert other taxonomy type calls here
              });
            };

            // Call the helper AJAX function to get the bottom level form
            $.ajax({
              type: "POST",
              url: "/ajax-alignment-form",
              success: update_form,
              data: 'tid=' + parentId
            });
          }
          // If it's one of the higher level forms, just add the HTML to the page
          else {
            $('.alignment-form').hide();
            $('.alignment-buttons').show();
            $('.alignment-filter').html(obj.html);

            $('.disabled').click(function (e) {
              e.preventDefault();
            });
          }

          // Re-attach the behaviors
          Drupal.attachBehaviors('.sbac-custom-term');
        };

        // Call the helper AJAX function for the upper level forms
        $.ajax({
          type: "POST",
          url: "/ajax-terms",
          success: update_data,
          data: 'parent=' + parentId
        });

        // Function for updating the breadcrumbs in the form
        var update_breadcrumb = function (data) {
          var obj = jQuery.parseJSON(data);
          $('.alignment-breadcrumb').html(obj.html);

          Drupal.attachBehaviors('.sbac-custom-term-remove');
        };

        // Call the helper AJAX function to get the breadcrumb data
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
