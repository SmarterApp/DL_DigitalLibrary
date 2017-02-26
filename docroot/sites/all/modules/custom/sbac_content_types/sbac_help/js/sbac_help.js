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
  
  Drupal.behaviors.sbac_help_feature = {
    attach: function (context, settings) {
      $('.flag-action').click(function (e) {
        var featured = $('.unflag-action').length;
        if (featured >= 3) {
          e.preventDefault();
          $('#help-topics-modal-container').foundation('reveal', 'open');
        }
      });
    }
  };

  Drupal.behaviors.sbac_help_modal = {
    attach: function (context, settings) {
      $('.sbac-help-back').hide();
      $('#modal-content .views-field-field-help-icon a').click(function (e) {
        var nid = $(this).parents('.views-field-field-help-icon').next('.views-field-title').next('.views-field-nid').find('.field-content').html();
        Drupal.behaviors.sbac_help_modal.sbacHelpAjax(nid);
        return false;
      });
      $('#modal-content .views-field-title a').click(function (e) {
        var nid = $(this).parents('.views-field-title').next('.views-field-nid').find('.field-content').html();
        Drupal.behaviors.sbac_help_modal.sbacHelpAjax(nid);
        return false;
      });
      $('.sbac-help-back').click( function () {
        $('.sbac-help-topics').show();
        $('.sbac-help-node-content').hide().empty();
        $('.sbac-help-back').hide();
        $('.helpmodal-title').html('Welcome to the Smarter Balanced Digital Library');
        return false;
      });
    },
    sbacHelpAjax: function (nid) {
      $.ajax({
        url: Drupal.settings.basePath + 'get-node-content',
        data: {nid: nid},
        success: function (data, textStatus, jqXHR) {
          var response = jQuery.parseJSON(data);
          $('.sbac-help-topics').hide();
          $('.sbac-help-node-content').show().html(response.results.body);
          $('.sbac-help-back').show();
          $('.helpmodal-title').html(response.results.title);
          Drupal.behaviors.sbac_help_modal.initTextify();
        }
      });
    },
    initTextify: function () {
      $('.sbac-help-node-content')
        .textify({
          numberOfColumn: 2,
          margin: 20,
          padding: 32,
          width: "auto",
          height: "400",
          showArrows: true,
          showNavigation: true
        });
    }
  };

})(jQuery);
