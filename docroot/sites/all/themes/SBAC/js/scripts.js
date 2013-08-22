(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /** Drupal.behaviors.textify = {
    attach: function (context, settings) {
      jQuery('.terms').textify({
        numberOfColumn: 2,
        margin: 20,
        padding: 32,
        width: "auto",
        height: "400",
        showArrows : true,
        showNavigation: true
      });
    }
  }; **/

  Drupal.behaviors.helpTextify = {
    attach: function (context, settings) {
      function initTextify(){
        jQuery('#current-help-topic article .body').textify({
          numberOfColumn: 2,
          margin: 20,
          padding: 32,
          width: "auto",
          height: "400",
          showArrows : true,
          showNavigation: true
        });
      }

      // if (jQuery().foundation) {
      //   jQuery('#current-help-topic-modal').foundation('reveal', {
      //     'opened': initTextify,
      //   });
      // }
      // jQuery.colorbox({
      //   inline:true,
      //   href:'#current-help-topic-modal',
      //   width:'80%',
      //   height:'80%',
      //   onComplete: initTextify,
      // });
    }
  };

  Drupal.behaviors.accountDropdown = {
    attach: function (context, settings) {
      $(document).click(function() {
        if (!$(this).hasClass('open')) {
          var selectedDiv = $('.open');
          selectedDiv.hide();
          selectedDiv.removeClass('open');
        }
      });
    }
  };

Drupal.behaviors.helpTextify = {
  attach: function (context, settings) {
    $(function() {
      $('#edit-pass').attr('autocomplete', 'off');
    });
  }
};

// Window load event used just in case window height is dependant upon images
//  $(window).bind("load", function() {
//
//    var footerHeight = 0,
//      footerTop = 0,
//      $footer = $(".bottom-bar");
//
//    positionFooter();
//
//    function positionFooter() {
//
//      footerHeight = $footer.height();
//      footerTop = ($(window).scrollTop()+$(window).height()-footerHeight)+"px";
//
//      if ( ($(document.body).height()+footerHeight) < $(window).height()) {
//        $footer.css({
//          position: "absolute"
//        }).animate({
//            top: footerTop
//          })
//      } else {
//        $footer.css({
//          position: "static"
//        })
//      }
//
//    }
//
//    $(window)
//      .scroll(positionFooter)
//      .resize(positionFooter)
//


})(jQuery);
