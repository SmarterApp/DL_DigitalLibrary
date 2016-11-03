(function($) {

Drupal.behaviors.colorbox = {
  attach: function (context, settings) {
    $('.otherClose').click(function () {
      if ($().colorbox) {
        $().colorbox.close();
      }
    });

    $('.backButton').click(function () {
      history.go(-1);
      return false;
    });
  }
};

})(jQuery);
