(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_help_main = {
    attach: function (context, settings) {
      $('#sbac-help-welcome-tutorial').hide();
      $('.sbac-help-welcome-tutorial-modal').click( function() {
        $('#sbac-help-welcome-tutorial').click();
      });

      $(".flexslider").flexslider({
        animation: "slide",
        animationLoop: false,
        itemMargin: 0,
        itemWidth: 245,
        slideshow: false
      });
    }
  };

  Drupal.behaviors.sbac_help_modal = {
    attach: function (context, settings) {
      $('#modal-content .views-field-field-help-icon a').click(function (e) {
        var nid = $(this).parents('.views-field-field-help-icon').next('.views-field-title').next('.views-field-nid').find('.field-content').html();
        sbacHelpAjax(nid);
        return false;
      });

      $('#modal-content .views-field-title a').click(function (e) {
        var nid = $(this).parents('.views-field-title').next('.views-field-nid').find('.field-content').html();
        sbacHelpAjax(nid);
        return false;
      });

     function initTextify(){
      $('.sbac-help-node-content')
        .textify({
          numberOfColumn: 2,
          margin: 20,
          padding: 32,
          width: "auto",
          height: "400",
          showArrows : true,
          showNavigation: true
        });
      }

      function sbacHelpAjax(nid) {
        $.ajax({
          url: Drupal.settings.basePath + 'get-node-content',
          data: {nid: nid},
          success: function (data, textStatus, jqXHR) {
            var response = jQuery.parseJSON(data);
            $('.sbac-help-topics').hide();
            $('.sbac-help-node-content').html(response.results.body);
            $('.helpmodal-title').html(response.results.title);
            initTextify();
          }
        });
      }
    }
  };

})(jQuery);
