(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  /**
   * Some general JS behavior gets attached to the resource form.
   *
   * @type {{attach: Function}}
   */
  Drupal.behaviors.sbac_forum_forum_form = {
    attach: function (context, settings) {

      var elem = 'input#edit-field-forum-access-states-und-0';
      if ($( elem ).prop( "checked" )) {
        $('p.forum-state-warning-message').show();
      } else {
        $('p.forum-state-warning-message').hide();
      };


      // animate the warning message for state access restriction
      $('.field-name-field-forum-access-states input.form-radio').change(function() {
        if ($( '#edit-field-forum-access-states-und-0' ).prop( "checked" )) {
          $('p.forum-state-warning-message').slideDown('fast');
        } else {
          $('p.forum-state-warning-message').slideUp('fast');
        };
      });


      var elem2 = 'input#edit-field-forum-access-user-roles-und-0';
      if ($( elem2 ).prop( "checked" )) {
        $('p.forum-role-warning-message').show();
      } else {
        $('p.forum-role-warning-message').hide();
      };


      // When a file is selected, dialog box closes, show the upload button
      $('.field-name-field-forum-access-user-roles input.form-radio').change(function() {
        if ($( '#edit-field-forum-access-user-roles-und-0' ).prop( "checked" )) {
          $('p.forum-role-warning-message').slideDown('fast');
        } else {
          $('p.forum-role-warning-message').slideUp('fast');
        };
      });
    }
  };

})(jQuery);
