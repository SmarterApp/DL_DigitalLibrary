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

  $(".row.second button:submit").attr("disabled", true);
  $("input, textarea, select").live('keydown change', function(){
    $(".row.second button:submit").removeAttr("disabled");
  });

})(jQuery);
