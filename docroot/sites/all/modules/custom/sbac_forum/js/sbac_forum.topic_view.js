(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_forum_js_topic_node_view_page = {
    attach: function (context, settings) {


      $('.bac-forum-topic-node-view-controls').mouseenter(function() {
        $('.sbac-forum-topic-node-view-controls-popup').show('fast');
      });

      $('.sbac-forum-topic-node-view-controls-wrapper').mouseleave(function() {
        $('.sbac-forum-topic-node-view-controls-popup').hide('fast');
      });


    }
  };



})(jQuery);
