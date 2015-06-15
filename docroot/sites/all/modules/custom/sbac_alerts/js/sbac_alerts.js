(function ($) {
  Drupal.behaviors.sbac_alerts = {
    attach: function (context, settings) {
      var alert_settings = Drupal.settings.sbac_alert_settings;
      if(alert_settings){
        if(getCookie('user-token') != alert_settings.token){
          setCookie('user-token', '');
            setCookie('display-notifications', '');
        }        
        if(getCookie('display-notifications') != 'hidden'){
            $("#lp-notifications-wrapper").show();
        }
        $("#close-notifications").click(function () {
          setCookie('user-token', alert_settings.token);
          setCookie('display-notifications', 'hidden');
          $("#lp-notifications-wrapper").fadeOut("slow");
          $('#close-notifications').removeClass('show-x');	    
        });
        // Toggle "Show More" / "Show Less".
        $(".views-field-title.views-accordion-header").click(function (){
          var id = "#" + $(this).attr('id');
          // Set timeout to allow views accordian to first change aria-selected.
          setTimeout(function(){
            var selected = $(id).attr('aria-selected');
            if(selected == 'true'){
              $( id + " span.more" ).replaceWith( '<span class="less">Show Less</span>' );
            }
            if(selected == 'false'){
              $( id + " span.less" ).replaceWith( '<span class="more">Show More</span>' );
            }
          }, 1);
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
