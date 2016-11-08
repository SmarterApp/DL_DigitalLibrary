(function ($) {
	$(document).ready(function() {
		var domstr = "<style>" + 
			"#edit-submit-authorized-domains{ top:-192px; left:430px;  position:relative;}" + 
			"#views-exposed-form-authorized-domains-page{width:400px;}" + 
			"</style>" + 
			"<div id='help-topic-links'  style='top:-183px; left:230px;  position:relative;'>" + 
			"<a href='/admin/sbac-authorized-domains/list/authorized-domains-export.csv' class='help-topic-link help-topic-link1' title='Download a list of all authorized domains'>Download</a></div>" + 
			"<div id='help-topic-links'  style='top:-183px;  left:320px; position:relative;'>" + 
			"<a href='javascript:void(0)' onclick='subform()' class='help-topic-link help-topic-link1'>Reset</a></div>";
        $("#views-exposed-form-authorized-domains-page").append(domstr);
    });
})(jQuery);