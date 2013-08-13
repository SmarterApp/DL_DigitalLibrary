(function ($) {
  Drupal.behaviors.flexslider = {
    attach: function (context, settings) {
      initSlider = function() {
        jQuery(".flexslider").flexslider({
          animation: "slide",
          animationLoop: false,
          itemMargin: 0,
          itemWidth: 245,
          slideshow: false
        });
      }
      helpColorBox = function() {
        $(".help-modal").colorbox({
            inline: true,
            width: "80%",
            height: "600px",
            onComplete: initSlider,
        });
      }
      helpColorBox();
    }
  };

  Drupal.behaviors.sbac_help = {
    attach: function (context, settings) {
      $('.view-help-topics .views-field-field-help-icon a').click(function () {
        var nid = $(this).parents('.views-field-field-help-icon').next('.views-field-title').next('.views-field-nid').find('.field-content').html();
        sbacHelpAjax(nid);
        return false;
      });

      $('.view-help-topics .views-field-title a').click(function () {
        var nid = $(this).parents('.views-field-title').next('.views-field-nid').find('.field-content').html();
        sbacHelpAjax(nid);
        return false;
      });

     function initTextify(){
      jQuery('#current-help-topic')
        .textify({
          numberOfColumn: 2,
          margin: 20,
          padding: 32,
          width: "auto",
          height: "400",
          showArrows : true,
          showNavigation: true,
        });
      }

      function sbacHelpAjax(nid) {
        $.ajax({
          url: Drupal.settings.basePath + 'get-node-content',
          data: {nid: nid},
          success: function (data, textStatus, jqXHR) {
            $('#current-help-topic').html(data.results.body);
            $('#sbac-help-title').html(data.results.title);
            $.colorbox({
              open:true,
              inline:true,
              href: '#current-help-topic-modal',
              width:"80%",
              height:"600px",
              onComplete:initTextify,
            });
          }
        });
      }
    }
  };

  Drupal.behaviors.backHelp = {
    attach: function (context, settings) {
      $('.helpBack').click(function () {
        $.colorbox({
          open:true,
          inline:true,
          href: '#helpmodal',
          width:"80%",
          height:"600px",
        });
      })
    }
  };

})(jQuery);
