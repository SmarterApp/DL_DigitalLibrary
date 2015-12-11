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
	$('.form-item-sbac-digital-library-resources-text').append('<div id="search-x-clear"></div>');
	if ($('#edit-sbac-digital-library-resources-text').val().length) {	  
	  $('#search-x-clear').text('x');
	}
	$('#search-x-clear').click(function(){
	  location.href = window.location.pathname;
	})
	
	$('#edit-sbac-digital-library-resources-text').on('keyup', function() {
	  if ($('#edit-sbac-digital-library-resources-text').val().length) {
	    
	    $('#search-x-clear').text('x');

	  }
	  else {
	    $('#search-x-clear').empty();
	  }
	})
	
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

	  $('.expanded').each(function(){
	    $(this).addClass('plus-sign');
	    $(this).removeClass('minus-sign');
	    $(this).click(function(){
	      $(this).children('.item-list').toggleClass('item-list-size');

	      if($(this).hasClass('plus-sign')){
		$(this).addClass('minus-sign');
		$(this).removeClass('plus-sign');
		
	      }
	      else{
		$(this).addClass('plus-sign');
		$(this).removeClass('minus-sign');		
	      }
	      
	    })
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
	    }).css({
	      'overflow': 'visible'
	    });
	  }	  
	})

	
	$('#' + sessionStorage.getItem('lastClicked') + ' .facet-label a.category-hide').addClass('activated');
	$('#' + sessionStorage.getItem('lastClicked') + ' .item-list').css({
	  'height': '300px',
	});
	
	$('a.facetapi-checkbox').each(function(){
	  $(this).text().replace('/(-)/', '');
	})
	
	  $('.facetapi-checkbox').each(function(){
	    $(this).click(function(){
	      var theId = $(this).closest('.facet-block').attr('id');
	      sessionStorage.setItem('lastClicked', theId)
	    })
	  })	
	    
	$('a.category-hide').each(function() {
	  var targetList = $(this).parents().siblings().children().children().children(':checkbox:checked').length;	  
	  if (targetList > 0) {
	    $(this).addClass('selected');
	    
	  }
	  else {
	    $(this).removeClass('selected');
	  }
	  
	  $(this).click(function() {
	    $('*').not(this).removeClass('activated');
	    $('.item-list').addClass('not-activated').css({
	      'height': '0',
	    });
	    if ($(this).hasClass('activated')) {
	      $(this).removeClass('activated').addClass('not-activated');	   
	      $(this).parents().siblings('.item-list').css({
		'height': '0',
	      });
	      
	    }
	    else {

	      $(this).addClass('activated');
	      $(this).removeClass('not-activated');
	      
	      $(this).parents().siblings('.item-list').css({
		'height': '300px',
	      });
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

