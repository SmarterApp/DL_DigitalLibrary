(function($) {

Drupal.behaviors.sbac_taskit = {
  attach: function (d_context, d_settings) {
    // the trigger will fire an AJAX event to mark the task as viewed; we need to
    // update the appropriate row classes when this event fires
    $('.taskit-expand-trigger').each(function(i, el) {
      $(el).click(function(e) {
        e.preventDefault();

        var row = $(el).closest('.taskit-row');
        // mark task as viewed
        row.removeClass('taskit-new');

        // collapse/expand
        if (row.hasClass('taskit-collapsed')) {
          row.removeClass('taskit-collapsed');
        }
        else {
          row.addClass('taskit-collapsed');
        }

        return false;
      });
    });

    $('.section-notifications a').click(function(e) {
      Drupal.behaviors.sbac_taskit.mark_notifications_read();
    });
  },

  /**
   * Runs AJAX event to mark the current user's notifications as read.
   * @return {[type]} [description]
   */
  mark_notifications_read: function () {
    $('.section-notifications').once('click-notifications-section', function() {
      $.ajax({
        url: Drupal.settings.sbac_taskit.mark_read_url,
      });
    });
  }
};

})(jQuery);