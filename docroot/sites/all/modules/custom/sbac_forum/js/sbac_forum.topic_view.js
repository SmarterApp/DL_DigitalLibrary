(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_forum_js_topic_node_view_page = {
    attach: function (context, settings) {


      $('.sbac-forum-topic-node-view-controls').mouseenter(function() {
        $('.sbac-forum-topic-node-view-controls-popup').show('fast');
      });

      $('.sbac-forum-topic-node-view-controls-wrapper').mouseleave(function() {
        $('.sbac-forum-topic-node-view-controls-popup').hide('fast');
      });


      var direct_comment_open = function(e) {
        //remove all already open comment forms
        $(".topic-node-comment-region-right-reply-form").each(function() {
          $(this).hide('fast');
          $(this).remove(".comment-form");
          $(this).prev().show('fast');
        });

        var href = $(this).attr('href');
        var formCont = $('.topic-node-reply-direct-wrapper');
        $(this).hide(); // Hide the control button.

        // Load the page callback contents (form). Re-attach all behaviours
        formCont.load(href,function(){
          Drupal.behaviors.sbac_forum_js_topic_node_view_page.expand(formCont);
          Drupal.attachBehaviors(formCont, Drupal.settings);
        });

        return false;
      };

      var comment_open = function(e) {
        //remove all already open comment forms
        $(".topic-node-comment-region-right-reply-form").each(function() {
          $(this).hide('fast');
          $(this).remove(".comment-form");
        });
        $(".topic-node-reply-direct-wrapper").hide('slow');
        $(".topic-node-reply-direct-wrapper").html('');
        $(".topic-node-controls a").each(function(){ $(this).show('fast'); });

        var title = $(this).attr('title');
        var href = $(this).attr('href');
        var formLinksCont = $(this).parents("[class~=topic-node-comment-region-right-bottom]");
        var formCont = $(this).parents("[class~=topic-node-comment-region-right-bottom]").next();

        formLinksCont.hide('slow'); // Hide links.

        // Load the page callback contents (form). Re-attach all behaviours
        formCont.load(href,function(){
          Drupal.behaviors.sbac_forum_js_topic_node_view_page.expand(formCont);
          Drupal.attachBehaviors(formCont, Drupal.settings);
        });

        return false;
      };

      var comment_reply_cancel = function(e) {
        var linkContSelector = '.' + $(this).attr('comment-form-sec');
        var activeFormCont = $(this).parents("[class~=topic-node-comment-region-right-reply-form]");
        activeFormCont.slideUp('1000', function(){
          activeFormCont.html('');
          $(linkContSelector).show('fast');
        });
        return false;
      };

      var comment_reply_direct_cancel = function(e) {
        var directLinkSelector = '.sbac-forum-topic-node-direct-comment-link';
        var activeDirectFormCont = $('.topic-node-reply-direct-wrapper');
        activeDirectFormCont.slideUp('5000', function(){
          activeDirectFormCont.html('');
          $(directLinkSelector).slideDown('fast');
        });
        return false;
      }

      $('.sbac-forum-topic-node-direct-comment-link').once('direct-comment-click', function() {
        $(this).click(direct_comment_open);
      });

      $(".comment-reply a, .comment-add a").once('comment-click', function() {
        $(this).click(comment_open);
      });

      $(".comment-reply-form-cancel-link").once('cancel-comment-click', function() {
        $(this).click(comment_reply_cancel);
      });

      $(".comment-direct-reply-form-cancel-link").once('cancel-comment-direct-click', function() {
        $(this).click(comment_reply_direct_cancel);
      });

    }, // End attach
    expand: function(formCont) {
      formCont.show('slow');
      formCont.animate({
        'min-height': ['220px', "swing"],
      });
    } // End expand.
  };
})(jQuery);
