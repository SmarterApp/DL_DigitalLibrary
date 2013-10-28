///**
// * CSV Report.
// */
(function($) {
  // DOM ready.
    $(function() {
        if ($("div#id, div.alert-box.secondary, h2#element-invisible").text().indexOf("Warning message") == 1) {
          setTimeout(function ()  {  $(".alert-box.secondary").hide(); }, 10000);
        }
    });
})(jQuery);
