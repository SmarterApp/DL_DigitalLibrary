(function($){
  $(document).on('ready', function() {
    $('.resource-feature').on('click', '.block', function (e) {
      $(location).attr('href', $(this).find('.block-title a.resource_feature_link').attr('href'));
      return false;
    })
  });
})(jQuery);
