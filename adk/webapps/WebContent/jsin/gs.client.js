/*
 * Collection of functions which are used for the Client Configuration Screen.
 */

var isWpsCheckPerformed = false;
var isWpsSupported = false;
var isTimeConfigCheckPerformed = false;
var isTimeConfigSupported = false;



/**
 * Displays the Landing Screen for Client mode.
 * @param idPrefix The prefix to be used for the HTML element IDs. 
 * 'cl' for the Client pages, 'lim' for the Limited AP Pages 
 */
function dispClientLandingScreen(idPrefix){
	var divMain = document.getElementById(idPrefix+'land');
	clearNode(divMain);
	setPageHeading('Client Settings');
	ajaxCallForApiVersion();
	createLink(
			divMain, 
			'', 
			'Wireless and Network Configuration', 
			/*
			 * TODO: Convert this 3-level deeply nested functions into the lighter JS syntax
			 */
			function(){
				prefetchFirmwareInfo(
					function(){
						prefetchNetworkConfig(
							function(){
								dispClientProvisioningScreen(idPrefix);
							}
						);
					}
				);
			}, 
			'land'
		);
	createLink(divMain, '', 'Administrator Settings', function(){dispAdminSettingsScreen(idPrefix);}, 'land');
	
	hideAllBut(idPrefix+'land', appMode);
}

/*
 * Checks if the node supports WPS provisioning
 * This is done by attempting a GET on /gainspan/system/prov/wps
 * 
 * If the node does not support WPS, this REST API returns HTTP status code 404.
 */
function ajaxCallForWpsCheck(xhr, method, url){
	
	xhr.onreadystatechange = function(){
		try {
			if (xhr.readyState === 4) {
				/*alert('XHR status = '+xhr.status);*/
			  if (xhr.status === 200) {
				   isWpsSupported = true;
				   isWpsCheckPerformed = true;
			  } else if(xhr.status === 404) {
				   isWpsSupported = false;
				   isWpsCheckPerformed = true;
			  }
			}
		  }
		  catch( e ) {
			  if(e.message){
				  alert('Caught Exception: ' + e.message);
			  }
			  else if(e.description){
				  alert('Caught Exception: ' + e.description);
			  }
		  }
	};
	
	var isAsync = false;
	xhr.open(method, url, isAsync);

	xhr.send(null);
}

/**
 * Check if the node supports WPS.
 */
function performWpsCheck(){
	var wpsxhr = initializeXhr();
	ajaxCallForWpsCheck(wpsxhr, AJAX_METHOD_GET, GS_WPS_API);
}

/*
 * Checks if the node supports Time configuration
 * This is done by attempting a GET on /gainspan/system/time
 * 
 * If the node does not support time configuration, this REST API returns HTTP status code 404.
 */
function ajaxCallForTimeConfigCheck(xhr, method, url){
	
	xhr.onreadystatechange = function(){
		try {
			if (xhr.readyState === 4) {
				/*alert('XHR status = '+xhr.status);*/
			  if (xhr.status === 200) {
				  isTimeConfigSupported = true;
				  isTimeConfigCheckPerformed = true;
			  } else if(xhr.status === 404) {
				  isTimeConfigSupported = false;
				  isTimeConfigCheckPerformed = true;
			  }
			}
		  }
		  catch( e ) {
			  if(e.message){
				  alert('Caught Exception: ' + e.message);
			  }
			  else if(e.description){
				  alert('Caught Exception: ' + e.description);
			  }
		  }
	};
	
	var isAsync = false;
	xhr.open(method, url, isAsync);

	xhr.send(null);
}

/**
 * Check if the node supports setting its time to UTC time.
 */
function performTimeConfigCheck(){
	var timeXhr = initializeXhr();
	ajaxCallForTimeConfigCheck(timeXhr, AJAX_METHOD_GET, GS_TIME_API);
}

/**
 * Displays the actual options for Client Provisioning.
 * @param idPrefix
 */
function dispClientProvisioningScreen(idPrefix){
	var divProv = document.getElementById(idPrefix+'prov');
	clearNode(divProv);
	setPageHeading('Client Settings');
	
	if(!isWpsCheckPerformed){
		performWpsCheck();
	}

	if(!isTimeConfigCheckPerformed){
		performTimeConfigCheck();
	}
	
	createDiv(divProv, '', 'center', 'Please select one of the following methods to connect your device to the wireless network.', 'bold');
	
	var ol = createElementNode('ul');
	var listDiv = createDiv(divProv);
	listDiv.appendChild(ol);
	
	
	if(isWpsSupported){
				
		createListItem(ol, '', 'mainopts', createLink(ol, 'wpspush', 'WPS Push Button', function(){dispWpsPushMethod(idPrefix);}));
		createListItem(ol, '', 'mainopts', createLink(ol, 'wpspin', 'WPS PIN', function(){dispWpsPinMethod(idPrefix);}));
		
	}
	
	createListItem(ol, '', 'mainopts',createLink(ol, 'nwscan', 'Select an Existing Network', function(){dispScanScreen(); preApListCall();}));
	createListItem(ol, '', 'mainopts',createLink(ol, 'nwmanual', 'Manual Configuration to Join a Network', function(){dispStaConfigScreen(true);}));
	
	/*divProv.appendChild(createElementNode('p'));*/
	addBlankLine(divProv);
	var btnDiv = createDiv(divProv, '', 'center');
	btnDiv.appendChild(
			createButton(
				'Back',
				function(){
					if(appMode == MODE_CLIENT){
						dispClientLandingScreen(idPrefix);
					} else if (appMode == MODE_PRO){
						dispProLandingScreen();
					}
					
				}
				/*,'centerbtn'*/
			)
		);
	
	/*
	createLink(
			divProv, 
			'', 
			'Home', 
			function(){
				if(appMode == MODE_CLIENT){
					dispClientLandingScreen(idPrefix);
				} else if (appMode == MODE_PRO){
					dispProLandingScreen();
				}
				
			}, 
			'land'
		);
	*/
	
	hideAllBut(idPrefix+'prov', appMode);
}

/**
 * Displays the WPS Push method provisioning screen.
 * @param idPrefix
 */
function dispWpsPushMethod(idPrefix){
	
	var divSum = document.getElementById(idPrefix+'summary');
	clearNode(divSum);
	
	createDiv(divSum, '', '', 'WPS Push Button', 'wizhead');
	
	/*
	var msg1 = 'After selecting "Proceed" below, press the WPS button on your AP within 2 minutes.';
	var msg2='This will cause the device to initiate WPS provisioning process and you will be disconnected from the device.';
	*/
	
	var ol = createElementNode('ol');
	createDiv(divSum).appendChild(ol);
	
	createListItem(ol, '', '', 'Locate the WPS button on your AP');
	createListItem(ol, '', '', 'Click on the "Push" button below');
	createListItem(ol, '', '', 'Press the WPS button on your AP within 2 minutes');
	
	/*
	createDiv(divSum, '', 'wpssum', msg1);
	createDiv(divSum, '', 'wpssum', msg2);
	*/
	
	/*divSum.appendChild(createElementNode('p'));*/
	addBlankLine(divSum);
	divSum.appendChild(
			createButton(
			'Cancel', 
			function() {
				dispClientProvisioningScreen(idPrefix);
			},
			'btn'
		)
	);
	
	divSum.appendChild(
			createButton(
				'Push', 
				function() {
					wpsXml = createXmlDoc('wps');
					appendXmlElement(wpsXml, wpsXml.documentElement, 'enabled', 'true');
					appendXmlElement(wpsXml, wpsXml.documentElement, 'mode', 'pbc');
					ajaxCall(
						initializeXhr(),
						AJAX_METHOD_POST,
						GS_WPS_API,
						wpsXml,
						function(){
							dispWpsStatus(idPrefix);
						}
							
					);
				},
				'btn'
			)
		);
	hideAllBut(idPrefix+'summary', appMode);
}

/**
 * Displays the WPS PIN method provisioning screen.
 * @param idPrefix
 */
function dispWpsPinMethod(idPrefix){
	var divSum = document.getElementById(idPrefix+'summary');
	clearNode(divSum);
	
	var msg1 = 'Please enter the WPS PIN for your AP.';
	var msg2 = 'This will cause the device to initiate WPS provisioning process and you will be disconnected from the device.';

	createDiv(divSum, '', 'wpssum', msg1);
	createDiv(divSum, '', 'wpssum', msg2);
	/*divSum.appendChild(createElementNode('p'));*/
	addBlankLine(divSum);
	
	createFieldRow(divSum, 'WPS PIN: ', createTextBox('txtWpsPin'));
	
	var version = getChipVersion();
	if(version && version.indexOf("1011") >= 0){
		/*
		 * For GS1011, we also display a checkbox that determines whether the PIN being used is a Default PIN
		 */
		
		createCheckBox(
				divSum,
				'',
				'cbDefaultPin',
				false,
				function(){
					 
					if(isSelected('cbDefaultPin')){
						unHide(ssidRow);
					} else {
						hide(ssidRow);
					}
				},
				'Default PIN'
			);
		createFieldRow(divSum, 'SSID: ', createTextBox('txtWpsSsid'));
		var ssidRow = document.getElementById('txtWpsSsid').parentNode;
		hide(ssidRow);
	}
	
	/*divSum.appendChild(createElementNode('p'));*/
	addBlankLine(divSum);
	
	divSum.appendChild(
			createButton(
			'Cancel', 
			function() {
				dispClientProvisioningScreen(idPrefix);
			},
			'btn'
		)
	);
	
	divSum.appendChild(
			createButton(
				'Proceed', 
				function() {
					var wpsPin = getContentOfId('txtWpsPin');
					if(!validateWpsPin(wpsPin)){
						return false;
					}
					wpsXml = createXmlDoc('wps');
					appendXmlElement(wpsXml, wpsXml.documentElement, 'enabled', 'true');
					var cbDefaultPin = document.getElementById('cbDefaultPin');
					var modeValue = 'pin';
					if(cbDefaultPin && isSelected('cbDefaultPin')){
						modeValue = 'def-pin-'+ getContentOfId('txtWpsSsid');
					}
					appendXmlElement(wpsXml, wpsXml.documentElement, 'mode', modeValue);
					appendXmlElement(wpsXml, wpsXml.documentElement, 'pin', wpsPin);
					
					/*
					 * TODO: Do validation on SSID. It must be max 32 characters
					 */
					ajaxCall(
						initializeXhr(),
						AJAX_METHOD_POST,
						GS_WPS_API,
						wpsXml,
						function(){
							dispWpsStatus(idPrefix);
						}
							
					);
				},
				'btn'
			)
		);
	hideAllBut(idPrefix+'summary', appMode);
}


function preApListCall(){
	doChipVersionCheck();
}

function doChipVersionCheck(){
	if(fwXml == null){
		var fwxhr = initializeXhr();
		ajaxCall(
				fwxhr, 
				AJAX_METHOD_GET,
				GS_FIRMWARE_API,
				null,
				function(){
					fwXml = parseResponse(fwxhr.responseXml, fwxhr.responseText);
					doModeCheck();
				}
		);
	}
	else{
		doModeCheck();
	}
}


function doModeCheck(){
	if (nwConfXml == null) {
		var nwxhr = initializeXhr();
		ajaxCall(
				nwxhr, 
				AJAX_METHOD_GET, 
				GS_CONF_API, 
				null, 
				function() {
					nwConfXml = parseResponse(nwxhr.responseXml, nwxhr.responseText);
					ajaxCallForApList();
				}
			);
	} else {
		ajaxCallForApList();
	}
}
/*
 * Helper method which makes the Ajax call to fetch the AP list.
 */
function ajaxCallForApList() {
	var explicitTimeOut = 45 * 1000;
	/*
	if(timeout){
		explicitTimeOut = timeout;
	}
	*/
	var apxhr = initializeXhr();
	ajaxCall(
			apxhr, 
			AJAX_METHOD_GET, 
			GS_APLIST_API, 
			null, 
			function() {
				var respXml = parseResponse(apxhr.responseXml, apxhr.responseText);
				dispApList('cl', respXml);
				
				/*
				var btnRefresh = document.getElementById('btnApRefresh');
				btnRefresh.disabled = false;
				btnRefresh.value = "Refresh";
				
				setDisabled('btnBack', false);
				setDisabled('cbscanparams', false);
				*/
			},
			explicitTimeOut
		);
}

/*
 * Helper method which performs the AJAX call for Scan parameters; 
 * and then pre-populates the scan options fields. 
 */
function ajaxCallForScanParams() {
	if (scanParamsXml == null) {
		var spxhr = initializeXhr();
		ajaxCall(spxhr, 
				AJAX_METHOD_GET, 
				GS_SCANPARAMS_API, 
				null,
				function() {
					scanParamsXml = parseResponse(spxhr.responseXml,
							spxhr.responseText);
					populateScanParams(scanParamsXml);
				}
		);
	} else {
		populateScanParams(scanParamsXml);
	}

}

/**
 * Populates the Scan Parameters fields
 * @param spXml The Scan Parameters XML.
 */
function populateScanParams(spXml) {
	var sp = spXml.getElementsByTagName('scan_params');
	if (sp && sp.length > 0) {
		
		setFieldContent(document.getElementById('parmChannel'), getTagContent(
				sp[0], 'channel'));
		setFieldContent(document.getElementById('parmTime'), getTagContent(
				sp[0], 'scan_time'));
		setFieldContent(document.getElementById('parmDelay'), getTagContent(
				sp[0], 'scan_delay'));
	}
}
/*
 * Helper method to make an AJAX post with the scan parameters.
 */
function ajaxPostScanParams(channel, scan_time, scan_delay) {
	var postXml = createXmlDoc('scan_params');
	appendXmlElement(postXml, postXml.documentElement, 'channel', channel);
	appendXmlElement(postXml, postXml.documentElement, 'scan_time', scan_time);
	appendXmlElement(postXml, postXml.documentElement, 'scan_delay', scan_delay);

	ajaxCall(
			initializeXhr(), 
			AJAX_METHOD_POST, 
			GS_SCANPARAMS_API, 
			postXml, 
			function() {
				/*
				 * Every time we do a POST, re-initialize the corresponding global XML to empty.
				 * This forces a GET next time to ensure that pre-populated values are up-to-date. 
				 */
				scanParamsXml = null;
			}
		);
}

/**
 * Simply displays a "scanning ..." message to the user, 
 * while the AP scan is going on.
 */
function dispScanScreen() {

	document.getElementById('scan').innerHTML = '<div class="bold center">Scanning for networks ...<br /> This may take upto 45 seconds <br /></div>';
	hideAllBut('scan', appMode);
	/*ajaxCallForApList();*/
}

function dispScanOption(parent) {
	var scan = createDiv(parent, 'scanDiv');
	createCheckBox(
			createDiv(scan, 'divScanCb'), 
			'', 
			'cbscanparams', 
			false,
			function() {
				toggleScanParams(scan);
			}, 
			'Configure Scan Parameters'
		);
}

/**
 * Displays the screen to configure scan parameters
 */
function dispScanParamsScreen(root, parent) {

	var chan = createDropDown('parmChannel');
	
	var regDomain = getTagContent(nwConfXml, 'reg_domain');
	var maxChannels = getMaxChannelsForDomain(regDomain);
	
	for ( var c = 0; c <= maxChannels; c++) {
		var csel = false;
		if (c == 0) {
			csel = true;
		}
		addDropDownItem(chan, c, c, getDisplayText(c, 'scan-params-screen'), csel);
	}

	createFieldRow(parent, 'Channel: ', chan);
	createFieldRow(parent, 'Scan Time (ms): ', createTextBox('parmTime'));
	createFieldRow(parent, 'Scan Delay (ms): ', createTextBox('parmDelay'));
	root.appendChild(parent);

	ajaxCallForScanParams();
}


/**
 * Appends an AP result to the AP List.
 * @param tbody The table body object.
 * @param idx The index of the result
 * @param ssid The SSID 
 * @param security The security mode
 * @param channel The channel that the AP is operating on/
 * @param rssi The signal strength of the AP
 * @param pwd The password (not displayed)
 * @param wepauth The WEP Auth mode.
 */
function appendAp(tbody, idx, ssid, security, channel, rssi, pwd, wepauth, eapType, eapUsername, eapPwd, band) {
	var aRow = createElementNode('tr');
	setClass(aRow, 'row');

	createColumn(aRow, false, idx);
	createColumn(aRow, false, ssid);
	createColumn(aRow, false, '-'+rssi);
	createColumn(aRow, false, getDisplayText(security));
	createColumn(aRow, false, channel);

	var selectBtn = createButton('Select', function() {
		
		dispStaConfigScreen(false, ssid, channel, security, wepauth, pwd, eapType, eapUsername, eapPwd, band);
	}, 'btn');

	var connectCol = createElementNode('td');
	connectCol.appendChild(selectBtn);
	setClass(connectCol, 'col');

	aRow.appendChild(connectCol);

	tbody.appendChild(aRow);

}

/**
 * Displays the header for the AP List.
 * @param tbody
 */
function dispApListHeader(tbody) {
	var header = createElementNode('tr');
	setClass(header, 'row');

	createColumn(header, true, 'Number');
	createColumn(header, true, 'SSID');
	createColumn(header, true, 'Signal Strength (dBm)');
	createColumn(header, true, 'Security Mode');
	createColumn(header, true, 'Channel');

	tbody.appendChild(header);

}

/**
 * Displays an appropriate message if no AP is found.
 */
function dispNoApsMsg() {
	var divNoAp = document.getElementById('noap');
	var noapmsg = 'No Access Points were found. Please Refresh. ';
	if(appMode == MODE_PRO){
		noapmsg = noapmsg + 'You can configure scan parameters By choosing the "Configure Scan Parameters" option below.';
	}
	if (divNoAp == null) {
		divNoAp = createDiv(
				document.getElementById('list'),
				'noap',
				'',
				noapmsg);
	}
	unHide(divNoAp);

}

/**
 * Displays the AP List
 * @param idPrefix
 * @param aplistXml The AP List XML fetched using the AJAX call.
 */
function dispApList(idPrefix, aplistXml) {
	var divApList = document.getElementById('list');
	clearNode(divApList);
	createDiv(divApList, '', '',
			'Select from the following existing networks', 'wizhead');
	var apList = aplistXml.getElementsByTagName('ap');

	if (apList && apList.length > 0) {

		var tbody = createTblBody(divApList, '', 'tbl');
		dispApListHeader(tbody);
		var validApCount = 0;
		for ( var i = 0; i < apList.length; i++) {
			var anAp = apList[i];
			/*
			 * We need to hide APs with blank SSIDs
			 */
			var anSsid = getTagContent(anAp, 'ssid');
			
			if(anSsid && anSsid != ''){
				validApCount ++;
				appendAp(
						tbody, 
						getTagContent(anAp, 'index'), 
						anSsid, 
						getTagContent(anAp, 'security'), 
						getTagContent(anAp, 'channel'), 
						getTagContent(anAp, 'rssi'),
						getTagContent(anAp, 'password'), 
						getTagContent(anAp,	'wepauth'),
						getTagContent(anAp,	'eap_type'),
						getTagContent(anAp,	'eap_username'),
						getTagContent(anAp,	'eap_password'),
						getTagContent(anAp, 'band')
					);
			}
			
		}
		if(validApCount == 0){
			dispNoApsMsg();
		}
	} else {
		dispNoApsMsg();
	}

	addBlankLine(divApList);
	addBlankLine(divApList);
	divApList.appendChild(
		createButton(
			'Back', 
			function() {				
				dispClientProvisioningScreen(idPrefix);
			}, 
			'btn',
			'btnBack'
		)
	);

	divApList.appendChild(
			createButton(
				'Refresh', 
				function() {
					/*
					this.disabled = true;
					this.value = 'Scanning ...';
					setDisabled('btnBack', true);
					setDisabled('cbscanparams', true);
					*/
					dispScanScreen();
					var chan = document.getElementById('parmChannel');
					if(appMode == MODE_PRO){
						/*var timeout = GS_TIME_OUT_MILLISECONDS;*/
						if (isSelected('cbscanparams')) {
							ajaxPostScanParams(chan.options[chan.selectedIndex].value,
									getContentOfId('parmTime'), getContentOfId('parmDelay'));
							/*timeout = parseInt(getContentOfId('parmTime')) * 14 + 3500;*/
						}
						/*ajaxCallForApList(timeout);*/
					} /* else {
						ajaxCallForApList();
					}*/
					ajaxCallForApList();
				}, 
				'btn',
				'btnApRefresh'
			)
		);

	if(appMode == MODE_PRO){
		dispScanOption(divApList);
	}
	
	adaptScanOptions();

	hideAllBut('list', appMode);
}


function adaptScanOptions(){
	
	var chip = getChipVersion();
	
	var currentMode = getTagContent(nwConfXml, 'mode');
	
	/*
	 * Scan Parameters to be disabled in following cases:
	 * 1. GS 1550 (in any mode)
	 * 2. GS 1500 in Limited AP Mode
	 * 
	 */
	chip = chip.toUpperCase();
	var scanParamsDisabled = (
			(chip.indexOf('GS1500') != -1 && currentMode == 'limited-ap')
			|| chip.indexOf('GS1550') != -1
			
		);
	if(appMode == MODE_PRO){
		setDisabled ('cbscanparams', scanParamsDisabled);
	}
	
	/*
	 * Refresh button to be disabled in following cases:
	 * 1. GS 1550 in Limited AP mode
	 * 2. GS 1500 in Limited AP mode
	 * 
	 */
	var refreshDisabled = (
			(chip.indexOf('GS1500') != -1 || chip.indexOf('GS1550') != -1)
			&& currentMode == 'limited-ap'
		);
	setDisabled ('btnApRefresh', refreshDisabled);
	
	
}

function toggleScanParams(parent) {
	var paramsDiv = document.getElementById('scanparams');
	if (!paramsDiv) {
		paramsDiv = createDiv(parent, 'scanparams');
		hide(paramsDiv);
	}
	if (isSelected('cbscanparams')) {
		if (paramsDiv.style.display == 'none') {
			dispScanParamsScreen(parent, paramsDiv);
			unHide(paramsDiv);
		}
	} else {
		clearNode(paramsDiv);
		hide(paramsDiv);
	}
}

/*
 * Displays the details about the AP which the user selected from the scan results list.
 */
function dispSelectedConfig(ssid, security, channel, wepauth, pwd, ro) {
	setFieldROVal('wlSsid', ssid, ro);
	setFieldROVal('wlChannel', channel, ro);

	var ddSec = document.getElementById('idSecType');
	ddSec.disabled = ro;
	if (security == 'none') {
		ddSec.selectedIndex = 0;
	} else if (security == 'wep') {
		ddSec.selectedIndex = 1;
	} else if (security.indexOf('wpa') !== -1) {
		ddSec.selectedIndex = 2;
	}

	ddSec.onchange();
	if (security == 'wep') {

		var wauth = document.getElementById('wepAuthMode');
		if (wepauth == 'open') {
			wauth.selectedIndex = 0;
		} else if (wepauth == 'shared') {
			wauth.selectedIndex = 1;
		}

		if (pwd && pwd != '') {
			var splits = pwd.split(':');
			var wepidx = document.getElementById('wepid');
			wepidx.selectedIndex = splits[0] - 1;
			setFieldContent(document.getElementById('wepkey'), splits[1]);
		}
	}

	hideAllBut('client', appMode);

}

/*
 * Displays the Configuration parameters for a client to be provisioned to an AP.
 */
function dispStaConfigScreen(isManual, ssid, channel, security, wepauth, cred, eapType, eapUsername, eapPwd, band) {
	var cDiv = document.getElementById('client');
	/*clearNode(cDiv);*/
	if(! cDiv.hasChildNodes()){
		dispDirectConfig(cDiv, 'cl');
	}	
	if (isManual) {
		ajaxCallForNwConfig('cl', 'basic');
	} else {
		setSelectedConfig('cl', cDiv, ssid, channel, security, wepauth, cred, eapType, eapUsername, eapPwd, band);
	}
 
	hideAllBut('client', appMode);
	
}

/**
 * Displays the basic parameters for client provisioning.
 * @param parent
 * @param idPrefix
 */
function dispDirectConfig(parent, idPrefix) {
	var heading = 'Configure Wireless and Network Settings';
	var msg = 'These settings govern the functioning of the device when it is operating in Client mode.';
	createDiv(parent, '', '', heading , 'wizhead');
	if(appMode == MODE_PRO){
		createDiv(parent, '', '', msg, 'note');
	}
	var wldiv = createDiv(parent, idPrefix + 'wlDiv');
	var fieldsDiv = createDiv(wldiv, idPrefix + 'fieldsDiv');

	createFieldRow(fieldsDiv, 'SSID: ', createTextBox(idPrefix + 'wlSsid', 32));
	
	var chan = createDropDown(idPrefix + 'wlChannel');
	if(isBandConfigSupported() == true){
		var ddBand = createDropDown(idPrefix + 'band');
		addDropDownItem(ddBand, 0, '2.4GHz', '2.4GHz', true);
		addDropDownItem(ddBand, 1, '5GHz', '5GHz', false);
		createFieldRow(fieldsDiv, 'Band: ', ddBand);
		ddBand.onchange = function(){
			clearNode(chan);
			var channelsList = getChannelsForBand(ddBand.options[ddBand.selectedIndex].value, getRegDomain(), 'client');
			
			for(var c = 0; c < channelsList.length; c++){
				addDropDownItem(chan, c, channelsList[c], getDisplayText(channelsList[c]), c==0?true:false);
			}
		};
	} else {
		for ( var c = 0; c <= getMaxChannelsForDomain(getRegDomain()); c++) {
			addDropDownItem(chan, c, c, getDisplayText(c), c==0?true:false);
		}
	}
	
	
	createFieldRow(fieldsDiv, 'Channel: ', chan);
	var dd = createDropDown(idPrefix + 'idSecType');

	addDropDownItem(dd, 0, 'none', getDisplayText('none', idPrefix), true);
	addDropDownItem(dd, 1, 'wep', getDisplayText('wep', idPrefix), false);
	addDropDownItem(dd, 2, 'wpa-personal', getDisplayText('wpa-personal',
			idPrefix), false);
	addDropDownItem(dd, 3, 'wpa-enterprise', getDisplayText('wpa-enterprise',
			idPrefix), false);

	dd.onchange = function() {
		dispSecurityFields(fieldsDiv, dd.options[dd.selectedIndex].value,
				idPrefix);
	};
	createFieldRow(fieldsDiv, 'Security: ', dd);

	/*if(appMode != MODE_PRO){*/
		wldiv.appendChild(createElementNode('hr'));
	/*}*/
	dispClientAdvancedConfig('cl', parent);
	
	var btnDiv = createDiv(parent, idPrefix + 'btn');
	var nextBtn = createButton(
			'Next', 
			function(){
				/*
				 * On Click function first performs validations; then proceeds to next screen.
				 */
				if(!validateSsid(getContentOfId(idPrefix + 'wlSsid'))){
					alert('Error: SSID is invalid. It must not be empty, and must be a maximum of 32 characters in length.');
					return false;
				}
				var sectype = dd.options[dd.selectedIndex].value;
				if(sectype == 'wep'){
					/*
					 * If WEP, then validate WEP key
					 */
					if(!validateWepKey(getContentOfId(idPrefix+'wepkey'), false)){
						alert('Error: WEP Key is invalid. It must consist of 5 or 13 ASCII characters, or it must be a 10-digit or a 26-digit hexadecimal value');
						return false;
					}
				} else if (sectype == 'wpa-personal'){
					/*
					 * If WPA-Personal, then validate WPA passphrase.
					 */
					if(!validateWpaPassphrasesMatch(getContentOfId(idPrefix+'secpp'), getContentOfId(idPrefix+'secppconf'))
									||
						!validateWpaPassphraseLength(getContentOfId(idPrefix+'secpp'))		
					){
						var passphraseField = document.getElementById(idPrefix+'secpp');
						var passphraseConfirmField = document.getElementById(idPrefix+'secppconf');
						
						setFieldContent(passphraseField, '');
						setFieldContent(passphraseConfirmField, '');
						
						passphraseField.focus();
						return false;
					}
				} else if (sectype == 'wpa-enterprise'){
					
					if(!validateEapEntry(idPrefix+'eappwd') || !validateEapEntry(idPrefix+'eapusername')){
						return false;
					}
					if(!validateWpaPassphrasesMatch(getContentOfId(idPrefix+'eappwd'), getContentOfId(idPrefix+'cnfeappwd'))){
						var passphraseField = document.getElementById(idPrefix+'eappwd');
						var passphraseConfirmField = document.getElementById(idPrefix+'cnfeappwd');
						
						setFieldContent(passphraseField, '');
						setFieldContent(passphraseConfirmField, '');
						
						passphraseField.focus();
						return false;
					}
				}
				if(isSelected(idPrefix+'cbadvanced') && isSelected(idPrefix+'rstatic')){
					/*
					 * If static IP has been selected, validate IP addresses.
					 */
					var rowIds = [ 'txtIp', 'txtSn', 'txtGw', 'txtDns'];
					if(! validateIpConsolidated(idPrefix, rowIds)){
						return false;
					}
				}
				dispStaSummaryScreen(idPrefix);
			},
			'btn'
		);
	
	var backBtn = createButton(
			'Back', 
			function() {
				dispClientProvisioningScreen(idPrefix);
			},
			'btn'
		);
	btnDiv.appendChild(backBtn);
	btnDiv.appendChild(nextBtn);
}

/**
 * Displays the advanced configuration for client provisioning.
 * @param idPrefix
 * @param parent
 */
function dispClientAdvancedConfig(idPrefix, parent) {
	
	/*var aDiv = createDiv(parent, idPrefix+'advanced');*/
	var aDiv = document.getElementById(idPrefix+'advanced');
	if(aDiv == null){
		aDiv = createDiv(parent, idPrefix+'advanced');
		createCheckBox(
				createDiv(aDiv, 'divAdvancedCb'), 
				'', 
				idPrefix+'cbadvanced', 
				false,
				function() {
					toggleAdvancedClientConf(idPrefix, aDiv);
				}, 
				'Advanced Options',
				'bold'
			);
	}
	
}

function toggleAdvancedClientConf(idPrefix, parent){
	
	var ipDiv = document.getElementById(idPrefix+'ipDiv');
	if(ipDiv == null){
		ipDiv = createDiv(parent, idPrefix+'ipDiv');
		var divConf = constructApConf(
				ipDiv,
				idPrefix, 
				function(){
					
					hideStaticConfig(idPrefix);
				},
				function(){
					
					dispStaticConfig(ipDiv, idPrefix);
				}
			);
		var divIpHdr = document.getElementById(idPrefix+ 'iptitle');
		clearNode(divIpHdr);
		
		createDiv(divIpHdr, '', '',
		'Select a method to obtain or set the IP address.', 'note');
		
		unHide(divIpHdr);
		var ipBtnsDiv = document.getElementById(idPrefix+'ipbtns');
		if(ipBtnsDiv != null){
			clearNode(ipBtnsDiv);
		}
		else{
			ipBtnsDiv = createDiv(divConf, idPrefix+'ipbtns'); 
		}
	}
	
	if(isSelected(idPrefix+'cbadvanced')){
		ajaxCallForNwConfig(idPrefix, 'advanced');
		unHide(ipDiv);
	} else{
		hide(ipDiv);
	}
	
	
}

function setSelectedConfig(idPrefix, parent, ssid, channel, security, wepauth, cred, eapType, eapUsername, eapPwd, band) {
	setFieldContent(document.getElementById(idPrefix + 'wlSsid'), ssid);
	var ddChannel = document.getElementById(idPrefix + 'wlChannel');
	var channelInt = parseInt(channel);
	/*ddChannel.selectedIndex = channelInt*/;
	
	
	if(isBandConfigSupported() == true){
		var ddBand = document.getElementById(idPrefix + 'band');
		
		/*
		 * If band info is available, we have arrived from Scan Results page.
		 * 
		 */
		if(band.indexOf('2.4GHz')!=-1){
			ddBand.selectedIndex = 0;
		} else {
			ddBand.selectedIndex = 1;
		}
	
		ddBand.onchange();
	}
	
	ddChannel.value = channel;

	var ddSec = document.getElementById(idPrefix + 'idSecType');
	ddSec.disabled = false;
	
	var securityUpper = security.toUpperCase(); 
	if (securityUpper == 'NONE') {
		ddSec.selectedIndex = 0;
	} else if (securityUpper.indexOf('WEP') !== -1) {
		ddSec.selectedIndex = 1;
	} else if (securityUpper == 'WPA-PERSONAL') {
		ddSec.selectedIndex = 2;
	} else if (securityUpper == 'WPA-ENTERPRISE') {
		ddSec.selectedIndex = 3;
	}
	ddSec.onchange();

	if (securityUpper.indexOf('WEP') !== -1) {
		var wauth = document.getElementById(idPrefix + 'wepAuthMode');
		
		if (wepauth == 'open') {
			wauth.selectedIndex = 0;
		} else if (wepauth == 'shared') {
			wauth.selectedIndex = 1;
		}
		
		var splits = cred.split(':');
		var wepidx = document.getElementById(idPrefix + 'wepid');
		wepidx.selectedIndex = splits[0] - 1;
		setFieldContent(document.getElementById(idPrefix + 'wepkey'), splits[1]);
	} else if (securityUpper == 'WPA-ENTERPRISE'){
		var eapdd = document.getElementById(idPrefix+'eaptype');
		switch(eapType){
			case 'eap-fast-gtc': 
				eapdd.selectedIndex = 0;
				break;
			case 'eap-fast-mschap': 
				eapdd.selectedIndex = 1;
				break;
			case 'eap-ttls': 
				eapdd.selectedIndex = 2;
				break;
			case 'eap-peap0': 
				eapdd.selectedIndex = 3;
				break;
			case 'eap-peap1': 
				eapdd.selectedIndex = 4;
				break;
			case 'eap-tls': 
				eapdd.selectedIndex = 5;
				break;
		}
		
		setFieldContent(document.getElementById(idPrefix+'eapusername'), eapUsername);
			
	}
}

/**
 * Displays the summary screen for client configuration.
 * @param idPrefix
 */
function dispStaSummaryScreen(idPrefix){
	var ssid = getContentOfId(idPrefix+'wlSsid');
	var pwd = ''; 
	var channel = getContentOfId(idPrefix+'wlChannel');
	var wepauth = '';
	
	/*
	 * DHCP is the default. User can choose static under advanced settings.
	 */
	var ip_type = 'dhcp';
	var ipadr = '';
	var snmask = '';
	var gw='';
	var dns='';
	var divSum = document.getElementById(idPrefix + 'summary');
	
	clearNode(divSum);
	hideAllBut(idPrefix + 'summary', appMode);
	createDiv(divSum, '', '','Wireless Configuration Summary','wizhead');
	/*createDiv(divSum,'','','Here is a summary of the configuration.');*/
	
	/*
	if(appMode != MODE_PRO){
		summarymsg = ' When you click on "Save and Apply", the settings will be applied and you will lose connectivity to the device.';
		createDiv(divSum,'','',summarymsg);	
	}
	*/
		
	addSummaryRow(divSum,'SSID: ',ssid);
	addSummaryRow(divSum,'Channel: ',getDisplayText(channel));
	var security = getContentOfId(idPrefix+'idSecType');
	var securityUpper = security.toUpperCase();
	addSummaryRow(divSum,'Security: ',getDisplayText(security, idPrefix));
	var setTime = false;
	if(securityUpper == 'WPA-PERSONAL'){
		pwd = getContentOfId(idPrefix + 'secpp');
		/*addSummaryRow(divSum, 'Passphrase: ', pwd);*/
	} else if (securityUpper == 'WPA-ENTERPRISE'){
		var eapType = getContentOfId(idPrefix + 'eaptype');
		var eapUsername = getContentOfId(idPrefix+'eapusername');
		var eapPwd = getContentOfId(idPrefix+'eappwd');
		addSummaryRow(divSum, 'EAP Type:', getDisplayText(eapType));
		addSummaryRow(divSum, 'EAP Username:', eapUsername);
		if(isTimeConfigSupported){
			setTime = isSelected('cbtime');
			addSummaryRow(divSum, 'Set Time: ', setTime==true?'Yes':'No');
		}
		
	}
	else if(securityUpper.indexOf('WEP') != -1){
		pwd = getContentOfId(idPrefix+'wepid')
				+':'
				+ normalizeWepKey(getContentOfId(idPrefix+'wepkey'));
		wepauth = getContentOfId(idPrefix +'wepAuthMode');
		addSummaryRow(divSum, 'WEP Auth Mode: ', getDisplayText(wepauth));
		addSummaryRow(divSum, 'WEP Key Index: ', getContentOfId(idPrefix+'wepid'));
		/*addSummaryRow(divSum, 'WEP Key: ', getContentOfId(idPrefix+'wepkey'));*/
		
	}
	
	
	if(isSelected(idPrefix+'cbadvanced') && isSelected(idPrefix+'rstatic')){
		ip_type = 'static';
		ipadr = getConcatIP(idPrefix+'txtIp');
		snmask = getConcatIP(idPrefix+'txtSn');
		gw = getConcatIP(idPrefix+'txtGw');
		dns = getConcatIP(idPrefix+'txtDns');
		
		addSummaryRow(divSum, 'IP Address: ', ipadr);
		addSummaryRow(divSum, 'Subnet Mask: ', snmask);
		addSummaryRow(divSum, 'Gateway: ', gw);
		addSummaryRow(divSum, 'DNS Server: ', dns);
	}
	 
	
	
	
	/*divSum.appendChild(createElementNode('p'));*/
	addBlankLine(divSum);
	if(appMode != MODE_PRO){
		summarymsg = 'Click on "Save and Apply" to confirm your settings, and then re-connect using the new wireless settings.';
		createDiv(divSum,'','',summarymsg, 'note');	
	}
	
	
	
	divSum.appendChild(
			createButton(
			'Back', 
			function() {
				dispStaConfigScreen(true);
			},
			'btn'
		)
	);
	
	var btnText = 'Save';
	if(appMode != MODE_PRO){
		btnText = 'Save And Apply';
	}
	
	divSum.appendChild(
			createButton(
				btnText, 
				function() {
					/*
					 * FIXME: Convert the long list of args here into a single object which we then pass.
					 */
					dispClientConnect(idPrefix, ssid, pwd, security, channel, wepauth, ip_type, ipadr, snmask, gw, dns, eapType, eapUsername, eapPwd, setTime );
				},
				'btn'
			)
		);
	
}

/**
 * Displays a "connecting" page to the user while the connection parameters are
 * being posted to the server
 */
function dispClientConnect(idPrefix, ssid, enteredPass, security, channel, wepauth, ip_type, ipadr, snmask, gw, dns, eapType, eapUsername, eapPwd, setTime ) {
	/*
	 * FIXME: Instead of accepting this long list of args, accept an object whose properties we can then extract. 
	 */
	var divConnect = document.getElementById(idPrefix +'connect');

	divConnect.innerHTML = '<div class="center bold">Connecting ... </div>';
	hideAllBut(idPrefix +'connect', appMode);

	var postXml = createXmlDoc('network');

	
	if(appMode != MODE_PRO){
		var mode = postXml.createElement('mode');
		mode.appendChild(postXml.createTextNode('client'));
		postXml.documentElement.appendChild(mode);
	}
	
	var client = postXml.createElement('client');
	postXml.documentElement.appendChild(client);

	var wireless = postXml.createElement('wireless');
	client.appendChild(wireless);

		
	
	appendXmlElement(postXml, wireless, 'ssid', ssid);
	appendXmlElement(postXml, wireless, 'password', enteredPass);
	appendXmlElement(postXml, wireless, 'channel', channel);
	appendXmlElement(postXml, wireless, 'security', security);
	appendXmlElement(postXml, wireless, 'wepauth', wepauth);
	
	if(security.toUpperCase() == 'WPA-ENTERPRISE'){
		appendXmlElement(postXml, wireless, 'eap_type', eapType);
		appendXmlElement(postXml, wireless, 'eap_username', eapUsername);
		appendXmlElement(postXml, wireless, 'eap_password', eapPwd);
	}
	
	var ipelem = postXml.createElement('ip');
	client.appendChild(ipelem);
	appendXmlElement(postXml, ipelem, 'ip_type', ip_type);
	if(isSelected(idPrefix+'cbadvanced') && ip_type == 'static'){	
		appendXmlElement(postXml, ipelem, 'ip_addr', ipadr);
		appendXmlElement(postXml, ipelem, 'subnetmask', snmask);
		appendXmlElement(postXml, ipelem, 'gateway', gw);
		appendXmlElement(postXml, ipelem, 'dns_addr', dns);
	} 
	if(isTimeConfigSupported && setTime == true){
		postTime(
				idPrefix, 
				function(){
					postNetworkConfig(idPrefix,postXml, ssid);
				}
			);
	} else {
		postNetworkConfig(idPrefix,postXml, ssid);
	}
	
}

function postNetworkConfig(idPrefix,postXml, ssid){
	ajaxCall(
			initializeXhr(), 
			AJAX_METHOD_POST, 
			GS_CONF_API, 
			postXml, 
			function() {
				/*
				 * Every time we do a POST, re-initialize the corresponding global XML to empty.
				 * This forces a GET next time to ensure that pre-populated values are up-to-date. 
				 */
				nwConfXml = null;
				var heading = 'Wireless Settings';
				dispStatus(idPrefix, ssid, heading);
				
			}
		);
}
	
function postTime(idPrefix, callback){
	var timeXml = "<time>"+new Date().getTime()+"</time>";
	ajaxCall(
			initializeXhr(), 
			AJAX_METHOD_POST, 
			GS_TIME_API, 
			timeXml, 
			function() {
				callback();
			}
		);
}
/**
 * Displays the status of connection to the specified AP
 * 
 * @param ssid
 *            the SSID of the AP to which the device will now attempt to
 *            connect.
 */
function dispStatus(idPrefix, ssid, heading) {

	var divStatus = document.getElementById('status');
	clearNode(divStatus);
	
	var msgPrefix = 'The configuration settings have been ';
	var msgSuffix = ' for the AP: '+ssid;
	
	var msg = '';
	if(appMode == MODE_PRO){
		msg = msgPrefix + 'saved'+msgSuffix+'. Click on "Apply Settings" to confirm your settings, and then re-connect using the new wireless settings.';
	} else {
		/*msg = msgPrefix + 'applied'+msgSuffix;*/
		msg = 'Wireless settings have been applied to connect your device to the network: '+ssid;
	}
	
	var head = createDiv(divStatus, '','', heading, 'wizhead');
	var d1 = createDiv(divStatus, '', '', msg, 'finalmsg');
	/*var d2 = createDiv(divStatus, '', '', msg);*/
	
	var btnDiv = createDiv(divStatus);
	
	
	if(appMode == MODE_PRO){
		btnDiv.appendChild(
			createButton(
				'Apply Settings', 
				function(){
					var msg = 'Wireless settings have been applied to connect your device to the network: '+ssid;
					switchMode('client',msg);
				},
				'btn'
			)
		);
		
		btnDiv.appendChild(
			createButton(
				'Home', 
				function(){
					dispProLandingScreen();
				},
				'btn'
			)
		);
	}
	
	
	hideAllBut('status', appMode);

}


/**
 * Hide the static IP config screen. Called if the user selects DHCP
 */
function hideStaticConfig(idPrefix) {
	var divStatic = document.getElementById(idPrefix+'apstatic');
	hide(divStatic);
}


function constructApConf(parent, idPrefix, dhcpfn, statfn){
	
	clearNode(parent);
	hide(createDiv(parent, idPrefix+'iptitle'));
	
	var rdiv = createDiv(parent, '', 'radio' );
	var fs = createElementNode('fieldset');
	rdiv.appendChild(fs);
	var d1 = createDiv(fs);
	var d2 = createDiv(fs);
	
	createRadio(d1, 'ipset', 'dhcp', idPrefix+'rdhcp', true, dhcpfn, getDisplayText('dhcp'));
	createRadio(d2, 'ipset', 'static', idPrefix+'rstatic', false, statfn,getDisplayText('static'));
	
	hide(createDiv(parent, idPrefix+'apstatic'));
	return parent;
	
}


/**
 * Display the static IP configuration screen.
 */
function dispStaticConfig(parent, idPrefix) {
	var divStatic = document.getElementById(idPrefix+'apstatic');
	if(divStatic == null){
		divStatic = createDiv(parent, idPrefix+'apstatic');
	}
	if (!divStatic.hasChildNodes()) {
		constructIPConfig(divStatic, idPrefix);
	}
	unHide(divStatic);
	populateStaticIpSettings(nwConfXml, idPrefix)
	//ajaxCallForNwConfig(idPrefix, 'advanced');
	
}

function dispWpsStatus(idPrefix){
	var divStatus = document.getElementById('status');
	clearNode(divStatus);
	
	var head = createDiv(divStatus, '','', 'Initiating WPS Provisioning', 'wizhead');
	var d1 = createDiv(divStatus, '', '', 'Wireless settings are being applied to connect your device to the network.', 'finalmsg');
	/*var d2 = createDiv(divStatus, '', '', msg);*/
	
	hideAllBut('status', appMode);
	if(appMode != MODE_PRO){
		hideFooter();
	}
}

function validateEapEntry(id){
	var field = document.getElementById(id);
	var entry = getContentOfId(id);
	
	if(!entry || entry.length < 1){
		alert('This field must not be empty');
		setFieldContent(field, '');
		field.focus();
		return false;
	}
	
	return true;
}

/*
 * Export the variables/functions which would be referenced from outside the combined JS.
 * This is required for closure compiler for advanced minification.
 */
window['dispClientLandingScreen']=dispClientLandingScreen;
