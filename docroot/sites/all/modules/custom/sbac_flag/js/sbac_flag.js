(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_flag = {
    attach: function (context, settings) {
      // Hide modal button.
      $('#sbac-flag-resource-modal').hide();

      // If there is an error, click the radio button so that the
      // textarea moves to the right location.
      if ($('input[name=flag_options]:radio:checked')) {
        var radio = $('input[name=flag_options]:radio:checked');
        radio.click();
      }

      // On click of radio button, move textarea.
      $('#sbac-flag-options input').click( function() {
        $(this).parent().append($('#sbac-flag-optional-comment'));
        $('#sbac-flag-optional-comment').show();
      });
    }
  };

})(jQuery);
