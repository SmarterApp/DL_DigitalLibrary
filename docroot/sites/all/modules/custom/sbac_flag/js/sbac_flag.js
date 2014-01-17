(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_flag = {
    attach: function (context, settings) {
      $('#sbac-flag-resource-modal').hide();

      if ($('input[name=flag_options]:radio:checked')) {
        var radio = $('input[name=flag_options]:radio:checked');
        radio.click();
      }

      $('#sbac-flag-options input').click( function() {
        $(this).parent().append($('#sbac-flag-optional-comment'));
        $('#sbac-flag-optional-comment').show();
      });
    }
  };

})(jQuery);
