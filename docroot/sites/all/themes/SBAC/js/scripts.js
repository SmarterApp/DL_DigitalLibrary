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
	
	$('a.category-hide.filters-master').click(function() {
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
	  var key = $(this).parents().parents().attr('id');
	  var state = sessionStorage.getItem(key);
	  if (state == 'activated') {
	    $(this).addClass('activated');
	    $(this).removeClass('not-activated');
	    $(this).parents().siblings('.item-list').css({
	      'height': '300px',
	    })
	  }
	  else {
	    $(this).removeClass('activated');
	    $(this).addClass('not-activated');
	    $(this).parents().siblings('.item-list').css({
	      'height': '0',
	    })
	  }
	  
	  $(this).click(function() {	    
	    if ($(this).hasClass('activated')) {
	      sessionStorage.setItem(key, 'not-activated');
	      $(this).removeClass('activated');
	      $(this).addClass('not-activated');
	      $(this).parents().siblings('.item-list').animate({
		'height': '0',
	      })
	    }
	    else {
	      $(this).addClass('activated');
	      $(this).removeClass('not-activated');
	      sessionStorage.setItem(key, 'activated');   
	      $(this).parents().siblings('.item-list').animate({
		'height': '300px',
	      })
	    }
	  })	  
	})
	  
	  $('input.facetapi-checkbox').each(function() {
	    
	    if ($(this).is(':checked')) {
	      $(this).siblings('.item-list').css({
		'height': 'auto',
	      })
	    }
	    else {
	      $(this).siblings('.item-list').css({
		'height': '0',
	      })
	  }
	})	
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

