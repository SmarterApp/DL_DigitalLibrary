(function ($) {
  Drupal.behaviors.sbac_custom = {
    attach: function (context, settings) {
      $('.disabled').click(function(e) {
          e.preventDefault();
          //do other stuff when a click happens
      });
      
      $('.ccss-term-delete').click(function(){
        var nid = $(this).attr('nid');
        var update_form = function(data) {
          $('tr#term-' + nid).hide();
        }

        $.ajax({
          type: "POST",
          url: "/ajax-alignment-crud",
          success: update_form,
          data:'op=delete&nid=' + nid
        });
        return false;
      });

      $('.sbac-custom-term-remove').click(function () {
        var parentTerm = $(this);
        var parentId = $(this).attr("tid");
        var update_data = function(data) {
          var obj = jQuery.parseJSON(data);
          if ((obj.publication == 'SBAC-ELA-v1' && obj.depth <= 3)
              || (obj.publication == 'SBAC-MA-v1' && obj.depth <= 5)
              || (obj.publication == '0')){
            $('.alignment-form').hide();
            $('.alignment-buttons').show();
          }

          $('.alignment-filter').html(obj.html);
          var attr = parentTerm.parent('li').attr('id');
          $("#" + attr + " ~ li").remove();
          parentTerm.parent('li').remove();

          //reattached the behaviors
          Drupal.attachBehaviors('.sbac-custom-term-remove');
          $('.disabled').click(function(e) {
              e.preventDefault();
              //do other stuff when a click happens
          });
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

          if ((obj.publication == 'SBAC-ELA-v1' && obj.depth > 3)
              || (obj.publication == 'SBAC-MA-v1' && obj.depth > 5)){
            $('.alignment-form').show();
            $('.alignment-buttons').hide();
            $('.alignment-filter').html('');

            var update_form = function(data) {
              var obj = jQuery.parseJSON(data);
              $('.alignment-form').html(obj.html);
              $('p[id^=description-]').more({length:200, moreText: 'read more', lessText: 'read less'});

              $('#ccss-cancel').click(function() {
                $('#modalBackdrop').hide();
                $('#modalContent').hide();
              });
            }

            var refNode = $('input#ref_node').val();

            $.ajax({
              type: "POST",
              url: "/ajax-alignment-form",
              success: update_form,
              data:'tid=' + parentId + '&ref_node=' + refNode
            });
          }
          else {
            $('.alignment-form').hide();
            $('.alignment-buttons').show();
            $('.alignment-filter').html(obj.html);
            
            $('.disabled').click(function(e) {
                e.preventDefault();
                //do other stuff when a click happens
            });
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
