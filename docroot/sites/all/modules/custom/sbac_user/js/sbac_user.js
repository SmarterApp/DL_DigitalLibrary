(function ($) {
  
  Drupal.behaviors.sbac_user = {
    attach: function (context, settings) {
      $("#legal-login #edit-save").attr('disabled', 'disabled');
      $('#legal-login #edit-legal-accept').click( function() {
        var legalCheckbox = $(this);
        if (legalCheckbox.is(':checked')) {
            $('#legal-login #edit-save').removeAttr('disabled');
        } else {
            $("#legal-login #edit-save").attr('disabled', 'disabled');
        }
      });
    }
  };

  // set the default vertical tab on user profile form
  $("form#user-profile-form #edit-submit").click(function() {
    if($('#edit-group_expertise[style*="display: block;"]').length) {
      $("#vertical-tabs-default").val("edit-group_expertise");
    } 
    if($('#edit-group_privacy[style*="display: block;"]').length) {
      $("#vertical-tabs-default").val("edit-group_privacy");
    }
  });

  // user field privacy, cannot modify these fields
  $("#edit-field-privacy-und-field-first-name").prop('disabled', true);
  $("#edit-field-privacy-und-field-position").prop('disabled', true);
  $("#edit-field-privacy-und-field-state").prop('disabled', true);
  $("#edit-field-privacy-und-field-grade-level-s-").prop('disabled', true);
  $("#edit-field-privacy-und-field-subject-s-").prop('disabled', true);
  $("#edit-field-privacy-und-field-special-populations").prop('disabled', true);

  var placeholder = ($('#edit-picture').has('div.form-item-picture-delete').length) ? 'Change Picture' : 'Add Picture';
  $('.row #edit-picture-upload').after('<input id="upload-cover" value="'+ placeholder +'" type="text">');
  $(".row #edit-picture-upload").change( function(){
    if($(this).val() == ""){
      var fname = $("#upload-cover").val();
       $(this).val(fname);
    }
  });
  
  $('.row #edit-picture-upload').mouseover(function(){
    $('.row #upload-cover').addClass('hovered');
  });
  
  $('.row #edit-picture-upload').mouseleave(function(){
    $('.row #upload-cover').removeClass('hovered');
  });
  
  // has to append email field description here as the problem lies deep inside the theme element function
  $('#user-profile-form #edit-account .form-item-mail div.description').insertAfter('#user-profile-form #edit-account .form-item-mail label');

  $(".row.second button:submit:not(#sbac-favorites-submit)").attr("disabled", true);
  $("input, textarea, select").live('keydown change', function(){
    $(".row.second button:submit").removeAttr("disabled");
  });

})(jQuery);
