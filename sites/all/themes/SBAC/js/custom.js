(function ($) {
  Drupal.behaviors.sbac_custom = {
    attach: function (context, settings) {
      //$('#edit-field-education-alignment').hide();

      $('.sbac-custom-term-remove').click(function () {
        var parentTerm = $(this);
        var parentId = $(this).attr("tid");
        var update_data = function(data) {
          var obj = jQuery.parseJSON(data);
          if (obj.depth < 3) {
            $('#edit-field-education-alignment').hide();
          }
          
          $('.alignment-filter').html(obj.html);  
          var attr = parentTerm.parent('li').attr('id');
          $("#" + attr + " ~ li").remove();
          parentTerm.parent('li').remove();
          
          //reattached the behaviors
          Drupal.attachBehaviors('.sbac-custom-term');
        }
        
        $.ajax({
          type: "POST",
          url: "/ajax-terms",
          success: update_data,
          data:'parent=' + parentId + '&remove=true',
        });
        
        return false;
      });
      
      $('.sbac-custom-term').click( function () {
        var parentId = $(this).attr("tid");
        
        var update_data = function(data) {
          var obj = jQuery.parseJSON(data);
          $('ul.sbac-breadcrumb').append('<li id="term-' + obj.parent.tid + '"><a href="#" tid="' + obj.parent.tid + '"class="sbac-custom-term-remove"><span class="b-label">' + obj.parent.name + '&nbsp;&nbsp;&nbsp;|&nbsp; x</span><span class="arrow"><span></span></span></a></li>')
          if (obj.depth >= 3) {
            $('.alignment-filter').html('');
            
            $('#edit-field-education-alignment').show();
            $('.form-type-checkbox').hide();
            var length = obj.tids_count,
                element = null;
                
            for (var i = 0; i < length; i++) {
              var id = obj.tids[i].tid;
              $('.form-item-field-education-alignment-und-' + id).show();   
            }   
            
          }else {
            $('.alignment-filter').html(obj.html);  
          }
          
          //reattached the behaviors
          Drupal.attachBehaviors('.sbac-custom-term');
        }
        
        $.ajax({
          type: "POST",
          url: "/ajax-terms",
          success: update_data,
          data:'parent=' + parentId ,
        });
        
        var update_breadcrumb = function(data) {
          var obj = jQuery.parseJSON(data);
          $('.alignment-breadcrumb').html(obj.html);
          
          Drupal.attachBehaviors('.sbac-custom-term-remove');
        }
        
        $.ajax({
          type: "POST",
          url: "/ajax-alignment-breadcrumbs",
          success: update_breadcrumb,
          data:'tid=' + parentId ,
        });
        
        return false;
      });
      
      $('.feedback').click(function() {
        $('.block-sbac-central-feedback-box').show();
        return false;
      });
      $('body').click(function() {
        $('.block-sbac-central-feedback-box').hide();
      });
      
    }
  };
})(jQuery);