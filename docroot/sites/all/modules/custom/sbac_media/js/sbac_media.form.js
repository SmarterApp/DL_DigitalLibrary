(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Some general JS behavior gets attached to the resource form.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_media_form_element = {
    attach: function (context, settings) {
      // Hide the modal button.
      $('#sbac-media-internet-confirm').hide();
      $('#sbac-media-modal-duplicates').hide();

      // Make the table sortable.
      var selector = '#sbac-media-list tbody';
      if ($(selector).length) {
        $(selector).sortable({
        items: "tr:not(.ui-state-disabled)",
        placeholder: "ui-state-highlight",
        update: function( event, ui ) {
            // Update the weights.
            var rows = $("#sbac-media-list tr").not('thead tr'); // skip the header row
            var json = { };
            rows.each(function(index) {
              json[$(this).attr('id')] = index;
            });
            var string = JSON.stringify(json);
            $('#sbac-media-weights').val(string);
          }
        }).disableSelection();
      }

      // On change, take the input and replace the modal HREF.
      $('#edit-field-embed-video').on('change blur', function() {
        var embed_code = $(this).val();
        var modal_link = $('#sbac-media-internet-confirm');
        var href = $(modal_link).attr('href');
        var new_href = href.replace("SBAC-MEDIA-EMBEDDED", embed_code);
        modal_link.attr('href', new_href);
      });

      if ($('#edit-field-content-module-upload').length) {
        $('#edit-field-content-module-upload').html('Upload (100MB Max)');
      }
    }
  };


  if (Drupal.ajax) {
    /**
     * Handle an event that triggers an AJAX response.
     *
     * We unfortunately need to override this function, which originally comes from
     * misc/ajax.js.
     */
    Drupal.ajax.prototype.eventResponse = function (element, event) {
      var ajax = this;

      if (ajax.ajaxing) {
        return false;
      }

      try {
        if (ajax.form) {
          if (ajax.setClick) {
            element.form.clk = element;
          }
          var element_id = element.id;
          if (typeof element_id == 'string' && element_id.indexOf('file-upload-button') > -1) {
            $('.video-embed-button').attr('disabled', 'disabled');
            $('#edit-cancel').attr('disabled', 'disabled');
            $('#sbac-resource-save-continue button').attr('disabled', 'disabled');
            $('#edit-save-continue').attr('disabled', 'disabled');
          }
          if (typeof element_id == 'string' && element_id.indexOf('embed-video-button') > -1) {
            $('.sbac-file-upload-button').attr('disabled', 'disabled');
            $('#edit-cancel').attr('disabled', 'disabled');
            $('#sbac-resource-save-continue button').attr('disabled', 'disabled');
            $('#edit-save-continue').attr('disabled', 'disabled');
          }
          ajax.form.ajaxSubmit(ajax.options);
        }
        else {
          ajax.beforeSerialize(ajax.element, ajax.options);
          $.ajax(ajax.options);
        }
      }
      catch (e) {
        ajax.ajaxing = false;
        alert("An error occurred while attempting to process " + ajax.options.url + ": " + e.message);
      }

      // For radio/checkbox, allow the default event. On IE, this means letting
      // it actually check the box.
      if (typeof element.type != 'undefined' && (element.type == 'checkbox' || element.type == 'radio')) {
        return true;
      }
      else {
        return false;
      }
    };

    /**
     * Handler for the form redirection completion.
     */
    Drupal.ajax.prototype.success = function (response, status) {
      // Remove the progress element.
      if (this.progress.element) {
        $(this.progress.element).remove();
      }
      if (this.progress.object) {
        this.progress.object.stopMonitoring();
      }
      $(this.element).removeClass('progress-disabled').removeAttr('disabled');

      Drupal.freezeHeight();

      for (var i in response) {
        if (response.hasOwnProperty(i) && response[i]['command'] && this.commands[response[i]['command']]) {
          this.commands[response[i]['command']](this, response[i], status);
        }
      }

      // Reattach behaviors, if they were detached in beforeSerialize(). The
      // attachBehaviors() called on the new content from processing the response
      // commands is not sufficient, because behaviors from the entire form need
      // to be reattached.
      if (this.form) {
        var settings = this.settings || Drupal.settings;
        Drupal.attachBehaviors(this.form, settings);
      }

      Drupal.unfreezeHeight();

      // Remove any response-specific settings so they don't get used on the next
      // call by mistake.
      this.settings = null;

      var element_id = this.selector;
      if (typeof element_id == 'string' && element_id.indexOf('file-upload-button') > -1) {
        $('.video-embed-button').removeAttr('disabled');
        $('#edit-cancel').removeAttr('disabled');
        $('#sbac-resource-save-continue button').removeAttr('disabled');
        $('#edit-save-continue').removeAttr('disabled');
      }
      if (typeof element_id == 'string' && element_id.indexOf('embed-video-button') > -1) {
        $('.sbac-file-upload-button').removeAttr('disabled');
        $('#edit-cancel').removeAttr('disabled');
        $('#sbac-resource-save-continue button').removeAttr('disabled');
        $('#edit-save-continue').removeAttr('disabled');
      }
    };
  }

})(jQuery);
