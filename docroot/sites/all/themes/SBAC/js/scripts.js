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
      $(document).ready(function() {
	$('#faux-click-sbac').click(function(){
	  if (window.location.href.indexOf('distinguished') > -1) {	    
	    location.href = '/digital-library-resources';
	  }
	  else{
	    location.href = '/digital-library-resources/distinguished';
	  }
	  
	})
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

	$('.collapsed, .expanded').each(function(){
	  if($(this).children('.facetapi-checkbox').hasClass('facetapi-inactive')){
	    $(this).removeClass('minus-sign');
	    $(this).addClass('plus-sign');	    	    
	  }
	  else{
	    $(this).removeClass('plus-sign');
	    $(this).addClass('minus-sign');
	  }
	})
	
	$('a.category-hide.filters-master').hover(function() {
	  if ($('.filters .inner-wrap').hasClass('not-activated-filters')) {	    
	    $('.filters .inner-wrap').removeClass('not-activated-filters');
	    $('.filters .inner-wrap').addClass('activated-filters');
	    $('.filters .inner-wrap').animate({
	      'height': '45px'
	    });
	  }
	  else {
	    $('.filters .inner-wrap').removeClass('activated-filters');
	    $('.filters .inner-wrap').addClass('not-activated-filters');
	    $('.filters .inner-wrap').animate({
	      'height': '100%'
	    });
	  }	  
	})

	$('a.facetapi-checkbox').each(function(){
	  $(this).text().replace('/(-)/', '');
	})
	
	
	$('a.category-hide').each(function() {
	  var targetList = $(this).parents().siblings().children().children().children(':checkbox:checked').length;	  
	  if (targetList > 0) {
	    $(this).addClass('selected');
	    
	  }
	  else {
	    $(this).removeClass('selected');
	  }
	  
	  $(this).parents().parents().hover(function() {	    
	    if ($(this).children().children().hasClass('activated')) {
	      $(this).children().children().removeClass('activated');
	      $(this).children().children().addClass('not-activated');	   
		$(this).children().children().parents().siblings('.item-list').stop().animate({
		  'height': '0',
		}, 'fast');
	      
	    }
	    else {
	      $(this).children().children().addClass('activated');
	      $(this).children().children().removeClass('not-activated');	     
		$(this).children().children().parents().siblings('.item-list').stop().animate({
		  'height': '300px',
		}, 'fast');
	    }
	  })	  
	})
	
      });
      
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

