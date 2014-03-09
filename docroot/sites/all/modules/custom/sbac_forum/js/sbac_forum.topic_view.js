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


      var comment_open = function(e) {
        //remove all already open comment forms
        $(".topic-node-comment-region-right-reply-form").each(function() {
          $(this).hide('fast');
          $(this).remove(".comment-form");
        });

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


      $(".comment-reply a, .comment-add a").once('comment-click', function() {
        $(this).click(comment_open);
      });

      $(".comment-reply-form-cancel-link").once('cancel-comment-click', function() {
        $(this).click(comment_reply_cancel);
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
