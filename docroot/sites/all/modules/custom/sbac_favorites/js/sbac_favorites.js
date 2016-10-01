(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_favorites = {
    attach: function (context, settings) {
      // Show collection list
      var timeoutId;
      $('.sbac-favorites-link').click(function(){
        return false;
      });
      $('.sbac-favorites-link, .sbac-favorites-collections').mouseover(function(){
        clearInterval(timeoutId);
        $('.sbac-favorites-collections').fadeIn(100);
        return false;
      }).mouseleave(function(){
        timeoutId = setTimeout(function() {
          $('.sbac-favorites-collections').fadeOut(400);
        }, 3000);
        return false;
      });

      $('.sbac-favorites-collections').on('click', '.sbac-favorites-collection', function(e){
        var target = $(e.target);
        var resource = target.closest('.sbac-favorites-collections');

        var id = resource.data('nid');
        var uid = resource.data('uid');
        var type = resource.data('type');
        var cid = target.data('cid');

        var is_favorite = 0;
        if (target.hasClass('sbac-favorite-yes')) {
          is_favorite = 1;
        }

        submit_favorite(target, resource, id, uid, type, cid, is_favorite);

        return false;
      });

      $('.sbac-favorites-collection-create').click(function(){
        return false;
      });
    }
  };

  /**
   * Submits the request to drupal.
   *
   * @param the_favorite_link
   * @param resource
   * @param id
   * @param uid
   * @param type
   * @param cid
   * @param is_favorite
   */
  submit_favorite = function (the_favorite_link, resource, id, uid, type, cid, is_favorite) {
    var ajax_request = $.ajax({
      type: 'POST',
      url: "/sbac-favorites-click",
      data: {'id':id, 'uid':uid, 'type':type, 'cid':cid, 'is_favorite':is_favorite},
      success: function(data) {
        ajax_request = null;
        if (is_favorite == 0) {
          the_favorite_link.removeClass('sbac-favorite-no').addClass('sbac-favorite-yes'); // update class
          resource.siblings('.sbac-favorites-link').removeClass('sbac-favorites-link-no').addClass('sbac-favorites-link-yes');
        }
        else {
          the_favorite_link.removeClass('sbac-favorite-yes').addClass('sbac-favorite-no');
          if (0 == resource.children('.sbac-favorite-yes').length) {
              resource.siblings('.sbac-favorites-link').removeClass('sbac-favorites-link-yes').addClass('sbac-favorites-link-no');
          }
        }
      },
      error: function(data) {

      }
    });
  };

  Drupal.behaviors.sbac_favorites_delete = {
    attach: function (context, settings) {
      // on click, save as favorite.
      $('.sbac-favorites-delete-favorite').click( function () {
        var the_favorite_link = $(this);
        var id = the_favorite_link.attr('id');
        var uid = the_favorite_link.attr('uid');
        var type = the_favorite_link.attr('type');
        delete_favorite(the_favorite_link, id, uid, type);
        return false;
      });
    }
  };

  /**
   * Submits the request to drupal.
   *
   * @param the_favorite_link
   * @param id
   * @param uid
   */
  delete_favorite = function (the_favorite_link, id, uid, type) {
    var ajax_delete_request = $.ajax({
      type: 'POST',
      url: the_favorite_link.attr('href'),
      data: {'id':id, 'uid':uid, 'type':type},
      success: function(data, textStatus, jqXHR) {
        var response = jQuery.parseJSON(data);
        ajax_delete_request = null;
        the_favorite_link.closest('tr').remove();
        if (response.total > 0) {
          $('.sbac-favorites-menu span').html(response.total);
        }
        else {
          $('.sbac-favorites-menu span').html(response.total);
          $('#favorites-table').empty().append(response.no_results);
          Drupal.attachBehaviors();
        }
      },
      error: function(data) {

      }
    });
  };

})(jQuery);
