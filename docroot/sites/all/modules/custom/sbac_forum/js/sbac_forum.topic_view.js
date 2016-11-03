(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_forum_js_topic_node_view_page = {
    attach: function (context, settings) {


      $('.sbac-forum-topic-node-view-controls').mouseenter(function () {
        $('.sbac-forum-topic-node-view-controls-popup').show('fast');
      });

      $('.sbac-forum-topic-node-view-controls-wrapper').mouseleave(function () {
        $('.sbac-forum-topic-node-view-controls-popup').hide('fast');
      });

      if ($('body').hasClass('page-comment-reply')) {
        $('.topic-node-controls').hide();
        $('.topic-node-comments-counter').hide();
      }

      var direct_comment_open = function (e) {
        //remove all already open comment forms
        $(".topic-node-comment-region-right-reply-form").each(function () {
          $(this).hide('fast');
          $(this).remove(".comment-form");
          $(this).prev().show('fast');
        });

        var href = $(this).attr('href');
        var formCont = $('.topic-node-reply-direct-wrapper');
        // Hide the control button.
        $(this).parents('[class~=topic-node-controls]').hide('slow', function () {
          // Load the page callback contents (form). Re-attach all behaviours
          formCont.load(href, function () {
            Drupal.behaviors.sbac_forum_js_topic_node_view_page.expand(formCont);
            Drupal.attachBehaviors(formCont, Drupal.settings);
          });
        });
        return false;
      };

      var comment_open = function (e) {
        //remove all already open comment forms
        $(".topic-node-comment-region-right-reply-form").each(function () {
          $(this).hide('fast');
          $(this).remove(".comment-form");
          $(this).prev("[class~=topic-node-comment-region-right-bottom]").show('fast');
        });
        $(".topic-node-reply-direct-wrapper").hide('slow');
        $(".topic-node-reply-direct-wrapper").html('');
        $(".topic-node-controls a").each(function () {
          $(this).show('fast');
        });
        var directLinkSelector = '.sbac-forum-topic-node-direct-comment-link';
        $(directLinkSelector).parents('[class~=topic-node-controls]').slideDown('fast');

        var title = $(this).attr('title');
        var href = $(this).attr('href');
        var formLinksCont = $(this).parents("[class~=topic-node-comment-region-right-bottom]");
        var formCont = $(this).parents("[class~=topic-node-comment-region-right-bottom]").next();

        formLinksCont.hide('slow'); // Hide links.

        // Load the page callback contents (form). Re-attach all behaviours
        formCont.load(href, function () {
          Drupal.behaviors.sbac_forum_js_topic_node_view_page.expand(formCont);
          Drupal.attachBehaviors(formCont, Drupal.settings);
        });


        return false;
      };

      var comment_reply_cancel = function (e) {
        var linkContSelector = '.' + $(this).attr('comment-form-sec');
        var activeFormCont = $(this).parents("[class~=topic-node-comment-region-right-bottm-comment]");
        activeFormCont.slideUp('1000', function () {
          activeFormCont.html('');
          $(linkContSelector).show('fast');
        });
        return false;
      };

      var comment_reply_direct_cancel = function (e) {
        var directLinkSelector = '.sbac-forum-topic-node-direct-comment-link';
        var activeDirectFormCont = $('.topic-node-reply-direct-wrapper');
        activeDirectFormCont.slideUp('5000', function () {
          activeDirectFormCont.html('');
          $(directLinkSelector).parents('[class~=topic-node-controls]').slideDown('fast');
        });
        return false;
      }

      $('.sbac-forum-topic-node-direct-comment-link').once('direct-comment-click', function () {
        $(this).click(direct_comment_open);
      });

      $(".comment-reply, .comment-add a").once('comment-click', function () {
        $(this).click(comment_open);
      });

      $(".comment-reply-form-cancel-link").once('cancel-comment-click', function () {
        if ($('body').hasClass('page-comment-reply')) {
          // Means do not attach the javascript click hanlder to do client side functions. Its not ajax loaded anymore.
        }
        else {
          $(this).click(comment_reply_cancel);
        }
      });

      $(".comment-direct-reply-form-cancel-link").once('cancel-comment-direct-click', function () {
        if ($('body').hasClass('page-comment-reply')) {
          // Means do not attach the javascript click hanlder to do client side functions. Its not ajax loaded anymore.
        }
        else {
          $(this).click(comment_reply_direct_cancel);
        }
      });

      // Ensure it doesnt go to the next page to validate.
      $('.comment-form button#edit-submit').once('submit-validation-shortcircuit', function () {
        $(this).attr('disabled', 'disabled');
        $('.comment-form .field-name-comment-body .form-textarea').keypress(function () {
          $('.comment-form button#edit-submit').removeAttr('disabled');
        });
        $('.comment-form .field-name-comment-body .form-textarea').blur(function () {
          if (!$(this).val()) {
            $('.comment-form button#edit-submit').attr('disabled', 'disabled');
          }
          ;
        });
      });

    }, // End attach
    expand: function (formCont) {
      formCont.show('slow');
      formCont.animate({
        'min-height': ['220px', "swing"],
      });
    } // End expand.
  };

  Drupal.behaviors.sbac_forum_recommend = {
    attach: function (context, settings) {
      // on click, recommend post.
      $('.sbac-recommend-link').click(function (e) {
        e.preventDefault();
        var recommend_link = $(this);
        var cid = recommend_link.attr('cid');
        submit_recommendation(cid);
      });
    }
  };

  submit_recommendation = function (cid) {
    var ajax_request = $.ajax({
      type: 'POST',
      url: "/sbac-forum/recommend",
      data: {'cid': cid},
      success: function (data) {
        var response = $.parseJSON(data);
        $('#sbac-recommend-' + cid).remove();
        $('#recommend-info-' + cid).html(response.recommendations + ' recommended');
      }
    });
  }
})(jQuery);
