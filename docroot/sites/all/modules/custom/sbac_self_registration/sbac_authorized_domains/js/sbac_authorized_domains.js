(function ($) {
	function getDomainDistrictList(stateId, district_und) {
		$("#edit-field-district-und").empty();
		$("#edit-field-district-und").append("<option value='_none'>- Select a value -</option>");
		$.ajax({
			type: "POST",
			dataType: "json",
			url: "/admin/sbac/authorized-domains/get_districts_json",
			data: {
				stateId: stateId
			},
			success: function(json) {
				fillDomainDistrictData(json);

				if(district_und > 0) {
					$("#edit-field-district-und").val(district_und);
				}
			},
			error: function() {

			}
		});
	}

	function fillDomainDistrictData(json) {
		data = json.data;
		if (data != undefined && data.length > 0) {
			for (var i=0; i<data.length; i++) {
				$("#edit-field-district-und").append("<option value='" + data[i].tid + "'>" + data[i].name + "</option>");
			}
		}
	}

	$(document).ready(function (){
		if($("#edit-field-domain-state-und").val() != "_none") {
			getDomainDistrictList($("#edit-field-domain-state-und").val(), $("#edit-field-district-und").val());
		}
		
		$("#edit-field-domain-state-und").trigger("liszt:updated"); 

		$("#edit-field-domain-state-und").chosen().change(function(){
			getDomainDistrictList($("#edit-field-domain-state-und").val(), 0);
		});
	});
})(jQuery);
