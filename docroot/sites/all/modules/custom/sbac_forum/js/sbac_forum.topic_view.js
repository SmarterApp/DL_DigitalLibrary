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
        var formCont = $(this).parents("[class~=topic-node-comment-region-right-bottom]").next();

        // Load the page callback contents (form). Re-attach all behaviours
        formCont.load(href,function(){
          Drupal.behaviors.sbac_forum_js_topic_node_view_page.expand(formCont);
          Drupal.attachBehaviors(formCont, Drupal.settings);
        });

        return false;
      };

      $(".comment-reply a, .comment-add a").once('comment-click', function() {
        $(this).click(comment_open);
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
