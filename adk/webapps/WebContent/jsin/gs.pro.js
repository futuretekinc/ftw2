
/*
 * Collection of functions used exclusively in the PRO version of the pages.
 */




/**
 * Displays the Landing screen for the PRO version.
 */
function dispProLandingScreen(){
	setPageHeading('Device Setup');
	var divMain = document.getElementById('landing');
	clearNode(divMain);
	ajaxCallForApiVersion();
	
	/*
	if(!isOtafuCheckPerformed){
		performOtafuCheck();
	}
	*/
	
	createLink(
		divMain, 
		'lnClient', 
		'Client Settings', 
		function(){
			prefetchFirmwareInfo(
				function(){
					dispClientProvisioningScreen('cl');
				}
			);
		}, 
		'land'
	);
	createLink(
		divMain, 
		'lnLimap', 
		'Limited AP Settings', 
		function(){
			prefetchFirmwareInfo(
				function(){
					dispLimApProvisioningScreen('lim');
				}
			);
		}, 
		'land'
	);
	createLink(divMain, 'lnSwitchMode', 'Operation Mode Selection', function(){dispSwitchModeScreen();}, 'land');
	createLink(divMain, 'lnAdmin', 'Administrator Settings', function(){dispAdminSettingsScreen();}, 'land');
	/*
	if(isOtafuSupported){
		createLink(divMain, 'lnOtafu', 'OTA Firmware Update', function(){dispOtafuScreen();}, 'land');
	}
	*/
	dispFooter();
	
	hideAllBut('landing', appMode);
}

function dispFooter(){
	var ftr = document.getElementById('ftrmsg');
	hide(ftr);
	
	if(nwConfXml == null){
		var ftxhr = initializeXhr();
		ajaxCall(
				ftxhr, 
				AJAX_METHOD_GET,
				GS_CONF_API,
				null,
				function(){
					nwConfXml = parseResponse(ftxhr.responseXml, ftxhr.responseText);
					dispFooterCallback(nwConfXml, ftr);
				}
		);
	}
	else{
		dispFooterCallback(nwConfXml, ftr);
	}
}

/**
 * Callback to be called when the information to be displayed in footer is available.
 * @param nwConfXml
 * @param ftr
 */
function dispFooterCallback(nwConfXml, ftr){
	var modeSpan = document.getElementById('ftmode');
	var macSpan = document.getElementById('ftmac');
	var ipSpan = document.getElementById('ftip');
	clearNode(modeSpan);
	clearNode(macSpan);
	clearNode(ipSpan);
	
	var currentMode = getTagContent(nwConfXml, 'mode');
	var currentMacAddr = getTagContent(nwConfXml, 'mac_addr');
	/*var ipelem = nwConfXml.getElementsByTagName('ip');*/
	var ipelem = getChildrenByTagName(nwConfXml.getElementsByTagName('network')[0], 'ip');
	var currentIP = '';
	if(ipelem && ipelem.length > 0){
		currentIP = getTagContent(ipelem[0], 'ip_addr');
	}
	if(currentMode != null && currentMode != ''){
		setNodeContent(modeSpan, getDisplayText(currentMode));
	}
	setNodeContent(macSpan, currentMacAddr);
	setNodeContent(ipSpan, currentIP);
	unHide(ftr);
}



/*
 * Export the variables which would be referenced from outside the combined JS.
 * This is required for closure compiler.
 */
window['dispProLandingScreen']=dispProLandingScreen;