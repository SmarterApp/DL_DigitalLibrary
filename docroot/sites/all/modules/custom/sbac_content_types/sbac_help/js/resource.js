jQuery(document).ready(function () {

  function initTextify() {
    jQuery('#resource-help-body')
    .textify({
      numberOfColumn: 2,
      margin: 20,
      padding: 32,
      width: "auto",
      height: "400",
      showArrows : true,
      showNavigation: true,
    });
  }

	jQuery.colorbox({
		inline:true,
		href:'#resource-help-box',
		width:'80%',
		height:'80%',
		onComplete: initTextify,
	});
});
