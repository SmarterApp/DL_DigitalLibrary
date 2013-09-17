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
      $(selector).sortable({
        items: 'tr'
      }).disableSelection();

      // On change, take the input and replace the modal HREF.
      $('#edit-field-embed-video').change( function () {
        var embed_code = $(this).val();
        var modal_link = $('#sbac-media-internet-confirm');
        var href = $(modal_link).attr('href');
        var new_href = href.replace("SBAC-MEDIA-EMBEDDED", embed_code);
        modal_link.attr('href', new_href);
      });
    }
  };

})(jQuery);
