(function ($) {
  Drupal.behaviors.sbac_alerts = {
    attach: function (context, settings) {
      var alert_settings = Drupal.settings.sbac_alert_settings;
      if(alert_settings){
        if(getCookie('user-token') != alert_settings.token){
          setCookie('user-token', '');
            setCookie('display-notifications', '');
	    $('#close-notifications').addClass('show-x');
        }        
        if(getCookie('display-notifications') != 'hidden'){
            $("#lp-notifications-wrapper").show();
	    $('#close-notifications').addClass('show-x');
        }
        $("#close-notifications").click(function () {
          setCookie('user-token', alert_settings.token);
          setCookie('display-notifications', 'hidden');
            $("#lp-notifications-wrapper").fadeOut("slow");
	    $('#close-notifications').removeClass('show-x');	    
        });
      }
    }
  };

  // Set and expire cookie after 1 week
  function setCookie(key, value) {
    var expires = new Date();
    expires.setTime(expires.getTime() + 7*24*60*60*1000);
    document.cookie = key + '=' + value + ';expires=' + expires.toUTCString();
  }

  // Get cookie for testing
  function getCookie(key) {
    var keyValue = document.cookie.match('(^|;) ?' + key + '=([^;]*)(;|$)');
    return keyValue ? keyValue[2] : null;
  }
  // Helper function to give a list of cookies
  function listCookies() {
    var theCookies = document.cookie.split(';');
    var aString = '';
    for (var i = 1; i <= theCookies.length; i++) {
      aString += i + ' ' + theCookies[i - 1] + "\n";
    }
    return aString;
  }
  console.log(listCookies());
})(jQuery);
