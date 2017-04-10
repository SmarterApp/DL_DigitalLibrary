(function ($) {
	/**
	 *Display of Download and Reset buttons and adjust Filter button position in authorized domain page
	 */
	$(document).ready(function() {
		var domstr = "<div class='help-topic-links download-wrapper'>" + 
			"<a href='/admin/sbac-authorized-domains/list/authorized-domains-export.csv' class='help-topic-link help-topic-link1' title='Download a list of all authorized domains'>Download</a></div>" + 
			"<div class='help-topic-links reset-wrapper'>" + 
			"<a href='javascript:void(0)' onclick='subform()' class='help-topic-link help-topic-link1'>Reset</a></div>";
        $("#views-exposed-form-authorized-domains-page").append(domstr);
    });
})(jQuery);
