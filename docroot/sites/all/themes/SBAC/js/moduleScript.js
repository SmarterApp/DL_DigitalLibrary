!function(e,t){typeof module!="undefined"&&module.exports?module.exports.browser=t():typeof define=="function"?define(t):this[e]=t()}("bowser",function(){function n(n){var r=/(msie|trident)/i.test(n),i=/chrome|crios/i.test(n),s=/phantom/i.test(n),o=/iphone/i.test(n),u=/ipad/i.test(n),a=/ipod/i.test(n),f=/touchpad/i.test(n),l=/silk/i.test(n),c=/safari/i.test(n)&&!i&&!s&&!l,h=/android/i.test(n),p=/opera/i.test(n)||/opr/i.test(n),d=/firefox/i.test(n),m=/gecko\//i.test(n),g=/seamonkey\//i.test(n),y=/version\/(\d+(\.\d+)?)/i,b=/firefox[ \/](\d+(\.\d+)?)/i,w=/mobile/i.test(n),E={};return p?((t=n.match(y))&&t.length>1?t=t[1]:(t=n.match(/opr\/(\d+(\.\d+)?)/i))&&t.length>1?t=t[1]:(t=n.match(/opera[ \/](\d+(\.\d+)?)/i))&&t.length>1?t=t[1]:t=0,E={name:"Opera",opera:e,version:t}):r?E={name:"Internet Explorer",msie:e,version:n.match(/(msie |rv:)(\d+(\.\d+)?)/i)[2]}:i?E={name:"Chrome",webkit:e,chrome:e,version:n.match(/(?:chrome|crios)\/(\d+(\.\d+)?)/i)[1],ipad:u,iphone:o,ios:!!n.match(/crios/i),mobile:w}:s?E={name:"PhantomJS",webkit:e,phantom:e,version:n.match(/phantomjs\/(\d+(\.\d+)?)/i)[1]}:f?E={name:"TouchPad",webkit:e,touchpad:e,version:n.match(/touchpad\/(\d+(\.\d+)?)/i)[1]}:l?E={name:"Amazon Silk",webkit:e,android:e,mobile:e,version:n.match(/silk\/(\d+(\.\d+)?)/i)[1]}:o||u||a?(E={name:o?"iPhone":u?"iPad":"iPod",webkit:e,mobile:o,ios:e,iphone:o,ipad:u,ipod:a},y.test(n)&&(E.version=n.match(y)[1])):h?E={name:"Android",webkit:e,android:e,mobile:e,version:(n.match(y)||n.match(b))[1]}:c?E={name:"Safari",webkit:e,safari:e,version:(t=n.match(y))?t[1]:0}:m?(E={name:"Gecko",gecko:e,mozilla:e,version:(t=n.match(b))&&t?t[1]:0},d&&(E.name="Firefox",E.firefox=e)):g&&(E={name:"SeaMonkey",seamonkey:e,version:n.match(/seamonkey\/(\d+(\.\d+)?)/i)[1]}),E.msie&&E.version>=9||E.chrome&&E.version>=20||E.firefox&&E.version>=10||E.safari&&E.version>=5||E.opera&&E.version>=10?E.a=e:E.msie&&E.version<9||E.chrome&&E.version<20||E.firefox&&E.version<10||E.safari&&E.version<5||E.opera&&E.version<10?E.c=e:E.x=e,E}var e=!0,t,r=n(typeof navigator!="undefined"?navigator.userAgent:"");return r._detect=n,r})

var divLoaded = false;

jQuery( document ).ready(function( $ ) {
	var iframeOffset = jQuery('#contentIframe').offset();
	jQuery('#contentIframe').width(jQuery('#resource-element-wrapper').width());
	var iframeWidth = jQuery('#contentIframe').width();
	var iframeHeight = jQuery('#contentIframe').height();
	jQuery('<div/>', {
    id: 'clickDiv',
	style: '-ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";filter: alpha(opacity=0);-moz-opacity: 0.0;-khtml-opacity: 0.0;opacity: 0.0;background:#000;width:' +  iframeWidth +'px;height:' + iframeHeight + 'px;position:absolute;cursor:pointer;top:' + iframeOffset.top + 'px;left:' + iframeOffset.left + 'px;',
    click: function() {
		runModule();
    } }).appendTo('body');
	var loadURL = window.location.protocol + jQuery('#contentIframe').attr('src').replace('CoverPage.html','frameScale.html');    
        jQuery('<a/>', {
          id: 'lauchModuleLink',
          alt: 'Launch Accessible Module',
          style: 'position: absolute; left: -999em; width: 1em; overflow: hidden;',
          href: loadURL,
          target: '_blank' }).appendTo('body');
	divLoaded = true;
});

jQuery( window ).resize(function() {
	if(divLoaded)
	{
		var iframeOffset = jQuery('#contentIframe').offset();
		var iframeWidth = jQuery('#contentIframe').width();
		var iframeHeight = jQuery('#contentIframe').height();
		jQuery('#clickDiv').css({width:iframeWidth,height:iframeHeight,top:iframeOffset.top,left:iframeOffset.left});
	}
});

function runModule() {
		if(bowser.name.indexOf("Internet Explorer") >= 0 && Number(bowser.version) < 9)
		{
			alert("It appears you are using a version of Internet Explorer earlier than 9.0.\n\nIn order to access this module, please revisit while using a current web browser such as: Internet Explorer 9.0+, Safari 5+, Google Chrome.");
			return;
		}
		if(bowser.name.toLowerCase().indexOf("iphone") >= 0)
		{
			confirm("It appears you are using an iPhone to attempt to access this module.\n\nIn order to access this module, please revisit while using a desktop computer.");
			return;
		}
		if(bowser.name.toLowerCase().indexOf("ipad") >= 0)
		{
			if(!confirm("It appears you are using an iPad. While you can access this module from an iPad, due to browser limitations you may experience challenges which degrade visuals presentation and user interactivity.\n\nFor an optimal user experience, please consider revisiting from a desktop computer while using Internet Exporer 9.0+, Safari 5+ or Google Chrome."))
				return;
		}		
		if(bowser.name.indexOf("Firefox") >= 0)
		{
			if(!confirm("It appears you are using Mozilla Firefox. While you can access this module using Firefox, due to browser limitations you may experience challenges which degrade visuals presentation and user interactivity.\n\nFor an optimal user experience, please consider revisiting while using Internet Exporer 9.0+, Safari 5+ or Google Chrome."))
                          return;
		}
		var pQuery = window.jQuery;
		var moduleWidth=1600,
		moduleHeight=900,
		availableWindowHeight = Math.round(pQuery( window.window ).height()*.9),
		availableWindowWidth = Math.round(pQuery(  window.window ).width()*.9);
		var heightRatio = ((availableWindowHeight/moduleHeight) >= 1) ? 1 : (availableWindowHeight/moduleHeight);
		var widthRatio = ((availableWindowWidth/moduleWidth) >= 1) ? 1 : (availableWindowWidth/moduleWidth);
		var resizeRatio = (heightRatio <= widthRatio) ? heightRatio : widthRatio;
		window.firstLoad = true;
		var loadURL = window.location.protocol + jQuery('#contentIframe').attr('src').replace('CoverPage.html','frameScale.html');
		pQuery.fancybox.open({
			padding:0,
			href:loadURL,
			type:'iframe',
			width: Math.round(moduleWidth*resizeRatio),
			height: Math.round(moduleHeight*resizeRatio),
			autoSize: false,
			beforeShow: function(){ jQuery("body").css({'overflow-y':'hidden'}); },
			afterClose: function(){ jQuery("body").css({'overflow-y':'visible'}); },			
			scrolling: false,
			beforeClose: function() { return confirm('Your answers will not be saved when you close this module.\n\nAre you sure you want to close the module?'); },
			onUpdate: function() { 
					if (!window.firstLoad)
					{
						var moduleWidth=1600,
						moduleHeight=900,
						availableWindowHeight = Math.round(pQuery( window.window ).height()*.9),
						availableWindowWidth = Math.round(pQuery(  window.window ).width()*.9);
						var heightRatio = ((availableWindowHeight/moduleHeight) >= 1) ? 1 : (availableWindowHeight/moduleHeight);
						var widthRatio = ((availableWindowWidth/moduleWidth) >= 1) ? 1 : (availableWindowWidth/moduleWidth);
						var resizeRatio = (heightRatio <= widthRatio) ? heightRatio : widthRatio;
						pQuery('.fancybox-wrap').css('height', moduleHeight*resizeRatio).css('width',moduleWidth*resizeRatio);
						pQuery('.fancybox-skin').css('height', moduleHeight*resizeRatio).css('width',moduleWidth*resizeRatio);
						pQuery('.fancybox-outer').css('height', moduleHeight*resizeRatio).css('width',moduleWidth*resizeRatio);																									
						pQuery('.fancybox-inner').css('height', moduleHeight*resizeRatio).css('width',moduleWidth*resizeRatio);
						pQuery('.fancybox-iframe').css('height', moduleHeight*resizeRatio).css('width',moduleWidth*resizeRatio);
						pQuery.fancybox.reposition();
					}
					else
					{
						window.firstLoad = false;
					}
			},
			scrolling: 'no',
			iframe: {
				scrolling: 'no',
				preload: true	
			}
		});
}