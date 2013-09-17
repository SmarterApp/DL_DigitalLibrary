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

      // Make the table sortable.
      var selector = '#sbac-media-list tbody';
      if ((selector).length) {
        $(selector).sortable({
          items: 'tr',
          update: function( event, ui ) {
            // Update the weights.
            var rows = $("#sbac-media-list tr:gt(0)"); // skip the header row
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
    }
  };

})(jQuery);
