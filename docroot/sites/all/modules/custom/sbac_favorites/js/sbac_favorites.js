(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.sbac_favorites = {
    attach: function (context, settings) {
      // on click, save as favorite.
      $('.sbac-favorites-link').click( function () {
        var the_favorite_link = $(this);
        var id = the_favorite_link.attr('id');
        var uid = the_favorite_link.attr('uid');
        var is_favorite = 0;
        if (the_favorite_link.hasClass('sbac-favorites-link-yes')) {
          is_favorite = 1;
        }
        submit_favorite(the_favorite_link, id, uid, is_favorite);
        return false;
      });

      // display hover text.
      $('.sbac-favorites-link').hover( function () {
        $(this).next().show();
      });

      // hide hover text.
      $('.sbac-favorites-link').mouseleave( function () {
        $(this).next().hide();
      });
    }
  };

  /**
   * Submits the request to drupal.
   *
   * @param the_favorite_link
   * @param id
   * @param uid
   * @param is_favorite
   */
  submit_favorite = function (the_favorite_link, id, uid, is_favorite) {
    var ajax_request = $.ajax({
      type: 'POST',
      url: "/sbac-favorites-click",
      data: {'id':id, 'uid':uid, 'is_favorite':is_favorite},
      success: function(data) {
        ajax_request = null;
        if (is_favorite == 0) {
          the_favorite_link.removeClass('sbac-favorites-link-no').addClass('sbac-favorites-link-yes'); // update class
          the_favorite_link.next().html('Added to Favorites'); // update text
          the_favorite_link.html('Unfavorite');
          var old_count = $('.sbac-favorites-menu span').html(); // update menu counter
          old_count++;
          $('.sbac-favorites-menu span').html(old_count);
          $('.sbac-favorites-menu-tooltip').show(0).delay(3000).hide(0); // show / hide the tooltip
        }
        else {
          the_favorite_link.removeClass('sbac-favorites-link-yes');
          the_favorite_link.addClass('sbac-favorites-link-no');
          the_favorite_link.next().html('Add to Favorites');
          the_favorite_link.html('Add to Favorites');
          var old_count = $('.sbac-favorites-menu span').html();
          old_count--;
          $('.sbac-favorites-menu span').html(old_count);
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
        delete_favorite(the_favorite_link, id, uid);
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
  delete_favorite = function (the_favorite_link, id, uid) {
    var ajax_delete_request = $.ajax({
      type: 'POST',
      url: the_favorite_link.attr('href'),
      data: {'id':id, 'uid':uid},
      success: function(data, textStatus, jqXHR) {
        var response = jQuery.parseJSON(data);
        ajax_delete_request = null;
        the_favorite_link.closest('tr').remove();
        if (response.total > 0) {
          $('.sbac-favorites-menu span').html(response.total);
        }
        else {
          $('.sbac-favorites-menu span').html(0);
          $('.favorites-helpful-info').remove();
          $('#favorites-table').empty().append(response.no_results);
        }
      },
      error: function(data) {

      }
    });
  };

})(jQuery);
