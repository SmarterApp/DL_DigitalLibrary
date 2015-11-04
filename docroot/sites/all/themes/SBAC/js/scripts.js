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
	$('#click-toggle-a').click(function(e){
	  $(this).toggleClass('list');
	  $('.view-digital-library-resources .views-row').toggleClass('list');
	  if (!$(this).hasClass('list')) {
	    $(this).text('List View');
	    window.location.hash = 'grid';
	    e.preventDefault();	    
	  }
	  else{
	    $(this).text('Grid View');
	    window.location.hash = 'list';
	    e.preventDefault();
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

