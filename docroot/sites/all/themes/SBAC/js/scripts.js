(function ($) {
  Drupal.behaviors = Drupal.behaviors || {};

  Drupal.behaviors.helpTextify = {
    attach: function (context, settings) {
//      function initTextify(){
//        $('#current-help-topic article .body').textify({
//          numberOfColumn: 2,
//          margin: 20,
//          padding: 32,
//          width: "auto",
//          height: "400",
//          showArrows : true,
//          showNavigation: true
//        });
//      }
    }
  };

  Drupal.behaviors.accountDropdown = {
    attach: function (context, settings) {
      $(document).click(function() {
        if (!$(this).hasClass('open')) {
          var selectedDiv = $('.open');
          selectedDiv.hide();
          selectedDiv.removeClass('open');
        }
      });
    }
  };

  Drupal.behaviors.helpTextify = {
    attach: function (context, settings) {
      $(function() {
        $('#edit-pass').attr('autocomplete', 'off');
      });
    }
  };

  Drupal.behaviors.toggleGrid = {
    attach: function (context, settings) {
      $(document).ready(function(){
	if (sessionStorage['gridview'] == 'list'){
	  $('.view-digital-library-resources .views-row, #click-toggle-a').addClass('list');
	}
	$('#click-toggle-a').click(function(e){
	  $(this).toggleClass('list');
	  $('.view-digital-library-resources .views-row').toggleClass('list');
	  if (!$(this).hasClass('list')) {
	    sessionStorage['gridview'] = 'grid';
	    $(this).text('List View');	    
	  }
	  else{
	    $(this).text('Grid View');
	    sessionStorage['gridview'] = 'list';
	  }
	});
      })
    }
  };

  Drupal.behaviors.toggleFilters = {
    attach: function (context, settings) {
      $(document).ready(function(){
	$('a.category-hide').click(function() {

	});
      })
    }
  };
  
})(jQuery);

