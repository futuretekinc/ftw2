/*
 * Collection of functions which are used for the Limited AP Settings Screen. 
 */


/**
 * Displays the Landing Screen for Limited AP mode. 
 */
function dispLimLandingScreen(idPrefix){
	/*First, locate the DIV in which we will display the Landing Screen for Limited AP.*/
	var divMain = document.getElementById(idPrefix+'land');
	setPageHeading('Limited AP Settings');
	ajaxCallForApiVersion();
	
	
	/*Clear the contents of this DIV, if any*/
	clearNode(divMain);
		
	/*
	 * Create the Links for appropriate options.
	 */
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
								dispLimApProvisioningScreen(idPrefix);
							}
						);
					}
				);
			}, 
			'land');
	createLink(divMain, '', 'Administrator Settings', function(){dispAdminSettingsScreen(idPrefix);}, 'land');
	
	/*
	 * Hide all other DIVs
	 */
	hideAllBut(idPrefix+'land', appMode);
}

/**
 * Displays the Limited AP Configuration Screen.
 */
function dispLimApProvisioningScreen(idPrefix){
	
	/*First, locate the DIV in which we will display the Limited AP Configuration.*/
	var divProv = document.getElementById(idPrefix+'prov');
	
	/*clearNode(divProv);*/
	
	
	
	/* 
	 * In PRO version, display Heading as "Limited AP settings". 
	 * In home-owner version, we already know we are doing Limited AP configuration. So,
	 * display the Wizard heading as the page heading and remove the wizard heading.
	 */
	
	var heading = 'Configure Wireless and Network Settings';
	var pageHeading = heading;
	if(appMode == MODE_PRO){
		pageHeading = 'Limited AP Settings';
	} 
	setPageHeading(pageHeading);
	
	/*If the DIV is not empty, then create the contents dynamically*/
	if(! divProv.hasChildNodes()){
	
		if(appMode == MODE_PRO){
			createDiv(divProv, '', '', heading , 'wizhead');
		}
		
		/*
		if(appMode == MODE_PRO){
			var msg = 'These settings govern the functioning of the device when it is operating as a Limited AP.';
			createDiv(divProv, '', '', msg, 'bold');
		}
		*/
		var wldiv = createDiv(divProv, idPrefix + 'wlDiv');
		var fieldsDiv = createDiv(wldiv, idPrefix + 'fieldsDiv');

		createFieldRow(fieldsDiv, 'SSID: ', createTextBox(idPrefix + 'wlSsid', 32));
		
		var ssidElement = document.getElementById(idPrefix + 'wlSsid');
		var targetLocation = ssidElement.parentNode.lastChild;
		var uniqueSpan = createSpan ('Please ensure that this SSID (network name) is unique in your wireless environment.', '', 'note');
		
		targetLocation.parentNode.insertBefore(uniqueSpan, targetLocation);
		
		
		var chan = createDropDown(idPrefix + 'wlChannel');
	
		/*
		 * In Limited AP mode, user MUST select a channel on which the AP will operate.
		 * 'All' or 'Any' options should not exist.
		 */
			
		if(isBandConfigSupported() == true){
			var ddBand = createDropDown(idPrefix + 'band');
			addDropDownItem(ddBand, 0, '2.4GHz', '2.4GHz', true);
			addDropDownItem(ddBand, 1, '5GHz', '5GHz', false);
			createFieldRow(fieldsDiv, 'Band: ', ddBand);
			ddBand.onchange = function(){
				clearNode(chan);
				var channelsList = getChannelsForBand(ddBand.options[ddBand.selectedIndex].value, getRegDomain(), 'limited-ap');
				
				for(var c = 0; c < channelsList.length; c++){
					addDropDownItem(chan, c, channelsList[c], getDisplayText(channelsList[c]), c==0?true:false);
				}
			};
		} else {
			for ( var c = 1; c <= getMaxChannelsForDomain(getRegDomain()); c++) {
				addDropDownItem(chan, c-1, c, getDisplayText(c), c==1?true:false);
			}
		}
		
		createFieldRow(fieldsDiv, 'Channel: ', chan);
		var dd = createDropDown(idPrefix + 'idSecType');
	
		addDropDownItem(dd, 0, 'none', getDisplayText('none', idPrefix), true);
		addDropDownItem(dd, 1, 'wep', getDisplayText('wep', idPrefix), false);
		addDropDownItem(dd, 2, 'wpa-personal', getDisplayText('wpa-personal',
				idPrefix), false);
	
		dd.onchange = function() {
			dispSecurityFields(fieldsDiv, dd.options[dd.selectedIndex].value,
					idPrefix);
		};
		createFieldRow(fieldsDiv, 'Security: ', dd);
			
		/*if(appMode != MODE_PRO){*/
			divProv.appendChild(createElementNode('hr'));
		/*}*/
		
		dispLimAdvancedConfig('lim', divProv);
		
		var btnDiv = createDiv(divProv, idPrefix + 'btn');
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
						if(!validateWepKey(getContentOfId(idPrefix+'wepkey'), true)){
							alert('Error: WEP Key must be a 10 digit value using numbers 0-9 and/or characters A-F; or a 5 character ASCII string.');
							var wepkeyField = document.getElementById(idPrefix+'wepkey');
							setFieldContent(wepkeyField, '');
							wepkeyField.focus();
							return false;
						}
					} else if (sectype.indexOf('wpa') != -1 ){
						/*
						 * If WPA, then validate WPA passphrase.
						 */
						if(!validateWpaPassphrasesMatch(getContentOfId(idPrefix+'secpp'), getContentOfId(idPrefix+'secppconf'))
												||
							!validateWpaPassphraseLength(getContentOfId(idPrefix+'secpp'))){
							
							var passphraseField = document.getElementById(idPrefix+'secpp');
							var passphraseConfirmField = document.getElementById(idPrefix+'secppconf');
							
							setFieldContent(passphraseField, '');
							setFieldContent(passphraseConfirmField, '');
							
							passphraseField.focus();
							return false;
						}
					}
					if (isSelected(idPrefix+'cbadvanced')){
						/*
						 * If advanced mode, then validate Beacon interval, number of DHCP addresses, and the IP addresses.
						 */
						if(appMode == MODE_PRO && !validateBeaconInterval(getContentOfId(idPrefix+'beaconint'))){
							alert('Error: Beacon Interval must be between 100 and 1600 ms');
							var bi = document.getElementById(idPrefix+'beaconint');
							setFieldContent(bi, '');
							bi.focus();
							return false;
						}
						
						var chip = getChipVersion();
						var maxDhcpAddr = 32;
						if(chip && chip.indexOf('gs2000') >= 0){
							maxDhcpAddr = 64;
						}
						
						if(isSelected('cbdhcp') && !validateDhcp(getContentOfId(idPrefix+'txtNumDhcp'), maxDhcpAddr)){
							alert('Error: Number of DHCP addresses must be between 1 and '+maxDhcpAddr);
							var numDhcp = document.getElementById(idPrefix+'txtNumDhcp');
							setFieldContent(numDhcp, '');
							numDhcp.focus();
							return false;
						}
						
						if(isSelected('cbdns') && !validateDomainName(getContentOfId(idPrefix+'txtDomainName'))){
							alert('Error: Domain name must not be empty');
							var domainName = document.getElementById(idPrefix+'txtDomainName');
							domainName.focus();
							return false;
						}
						
						var rowIds = [ 'txtIp', 'txtSn', 'txtGw'];
						if(isSelected('cbdhcp')){
							rowIds.push('txtDhcp');
						}
						
						if(! validateIpConsolidated(idPrefix, rowIds)){
							return false;
						}
					}
					dispLimApSummaryScreen(idPrefix);
				},
				'btn'
			);
		var backBtn = createButton(
				'Back', 
				function() {
					if(appMode == MODE_AP){
						dispLimLandingScreen(idPrefix);
					}
					else if (appMode == MODE_PRO){
						dispProLandingScreen();
					}
				},
				'btn'
			);
		
		addBlankLine(btnDiv);
		
		btnDiv.appendChild(backBtn);
		btnDiv.appendChild(nextBtn);
		ajaxCallForNwConfig(idPrefix, 'basic');
	}
	hideAllBut(idPrefix+'prov', appMode);
	
	
}

/**
 * Displays the advanced configuration for Limited AP.
 * @param idPrefix The prefix to be used for the HTML element IDs. 
 * 'cl' for the Client pages, 'lim' for the Limited AP Pages 
 * @param parent The parent node.
 */
function dispLimAdvancedConfig(idPrefix, parent) {
	
	var aDiv = document.getElementById(idPrefix+'advanced');
	if(aDiv == null){
		aDiv = createDiv(parent, idPrefix+'advanced');
		createCheckBox(
				createDiv(aDiv, 'divAdvancedCb'), 
				'', 
				idPrefix+'cbadvanced', 
				false,
				function() {
					toggleAdvancedLimApConf(idPrefix, aDiv);
				}, 
				'Advanced Options',
				'bold'
			);
	}
	
}

/**
 * Toggles the Advanced Limited AP configuration.
 * @param idPrefix The prefix to be used for the HTML element IDs. 
 * 'cl' for the Client pages, 'lim' for the Limited AP Pages 
 * @param parent The parent node.
 */
function toggleAdvancedLimApConf(idPrefix, parent){
	
	var ipDiv = document.getElementById(idPrefix+'ipDiv');
	if(ipDiv == null){
		ipDiv = createDiv(parent, idPrefix+'ipDiv');
		
		
		/*
		var divIpHdr = document.getElementById(idPrefix+ 'iptitle');
		clearNode(divIpHdr);
		createDiv(divIpHdr, '', '',
		'Users can change network parameters to obtain or set the IP address of this device');
		unHide(divIpHdr);
		*/
		if(appMode == MODE_PRO){
			createFieldRow(ipDiv, 'Beacon Interval (Range: 100 to 1600 ms): ', createTextBox(idPrefix+'beaconint'));
		}
		
		constructLimIPConfig(ipDiv, idPrefix);
		
		var ipBtnsDiv = document.getElementById(idPrefix+'ipbtns');
		if(ipBtnsDiv != null){
			clearNode(ipBtnsDiv);
		}
		else{
			ipBtnsDiv = createDiv(ipDiv, idPrefix+'ipbtns'); 
		}
		
		ajaxCallForNwConfig(idPrefix, 'advanced');
	}
	
	
	if(isSelected(idPrefix+'cbadvanced')){
		unHide(ipDiv);
	} else{
		hide(ipDiv);
	}
}

/**
 * Constructs the IP-related fields for Advanced Limited AP configuration
 * @param parent The parent node.
 * @param idPrefix The prefix to be used for the HTML element IDs. 
 * 'cl' for the Client pages, 'lim' for the Limited AP Pages
 */
function constructLimIPConfig(parent, idPrefix){
	
	createDiv(parent, '', '', 'Network Address Settings:', '');
	var rowIds = [ 'txtIp', 'txtSn', 'txtGw'];
	var labels = ['IP Address: ', 'Subnet Mask: ', 'Gateway: '];
	for ( var i = 0; i < rowIds.length; i++) {
		createIPAdrRow(parent, idPrefix+rowIds[i], labels[i]);
	}
	
	createCheckBox(createDiv(parent), 'cbdhcp', 'cbdhcp', true, function(){toggleDhcpSettings(parent);}, 'Enable DHCP Server');
	var divDhcp = createDiv(parent, 'divlimDhcp');
	dispDhcpSettings(divDhcp);
	
	createCheckBox(createDiv(parent), 'cbdns', 'cbdns', true, function(){toggleDnsSettings(divDns);}, 'Enable DNS Server');
	var divDns = createDiv(parent, 'divlimDns');
	dispDnsSettings(divDns);
}

/**
 * Toggles the DHCP settings for advanced Limited AP. 
 * Called whenever user clicks the Enabled DHCP checkbox.
 * @param parent The parent node.
 */
function toggleDhcpSettings(parent){
	var divDhcp = document.getElementById('divlimDhcp'); 
	if(divDhcp == null){
		divDhcp = createDiv(parent, 'divlimDhcp');
	}
	if(isSelected('cbdhcp')){
		if(!divDhcp.hasChildNodes()){
			dispDhcpSettings(divDhcp);
		}
		unHide(divDhcp);
	}
	else{
		/*clearNode(divDhcp);*/
		hide(divDhcp);
	}
}

/**
 * Displays the DHCP settings for advanced Limited AP config.
 * @param parent The parent node.
 */
function dispDhcpSettings(parent){
	createIPAdrRow(parent, 'limtxtDhcp', 'Starting Address: ');
	createFieldRow(parent, 'Number of Addresses: ', createTextBox('limtxtNumDhcp'));
}

/**
 * Toggles the DNS settings for advanced Limited AP. 
 * Called whenever user clicks the Enabled DNS checkbox.
 * @param parent The parent node.
 */
function toggleDnsSettings(parent){
	var divDns = document.getElementById('divlimDns'); 
	if(divDns == null){
		divDns = createDiv(parent, 'divlimDns');
	}
	if(!divDns.hasChildNodes()){
		dispDnsSettings(divDns);
	}
	if(isSelected('cbdns')){	
		unHide(divDns);		
	} else{
		/*clearNode(divDns);*/
		hide(divDns);
	}
}

/**
 * Displays the DNS settings for advanced Limited AP config.
 * @param parent The parent node.
 */
function dispDnsSettings(parent){
	createFieldRow(parent, 'Domain Name', createTextBox('limtxtDomainName'));
}

/**
 * Displays the Limited AP summary screen.
 * @param idPrefix
 */
function dispLimApSummaryScreen(idPrefix){
	var ssid = getContentOfId(idPrefix+'wlSsid');
	var pwd = ''; 
	var channel = getContentOfId(idPrefix+'wlChannel');
	var wepauth = 'open';
	
	
	var ipadr = '';
	var snmask = '';
	var gw='';
	
	var dhcp = 'true';
	var dns = 'true';
	var dhcpstart = '';
	var dhcpnum = '';
	var domain = '';
	var beaconinterval = '';
	
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
	addSummaryRow(divSum,'Security: ',getDisplayText(security, idPrefix));
	if(security.toUpperCase().indexOf('WPA') != -1){
		pwd = getContentOfId(idPrefix + 'secpp');
		/*addSummaryRow(divSum, 'Passphrase: ', pwd);*/
	}
	else if(security.toUpperCase().indexOf('WEP') != -1){
		pwd = getContentOfId(idPrefix+'wepid')
				+':'
				+ normalizeWepKey(getContentOfId(idPrefix+'wepkey'));
		/*
		 * In Limted AP mode, wepauth is always Open
		 */
		/*
		wepauth = getContentOfId(idPrefix +'wepAuthMode');
		addSummaryRow(divSum, 'WEP Auth Mode: ', getDisplayText(wepauth));
		*/
		addSummaryRow(divSum, 'WEP Key Index: ', getContentOfId(idPrefix+'wepid'));
		/*addSummaryRow(divSum, 'WEP Key: ', getContentOfId(idPrefix+'wepkey'));*/
		
	}
	
	
	if(isSelected(idPrefix+'cbadvanced')){
		if(appMode == MODE_PRO){
			beaconinterval = getContentOfId(idPrefix+'beaconint');
			addSummaryRow(divSum, 'Beacon Interval: ', beaconinterval);
		}
		
		
		ipadr = getConcatIP(idPrefix+'txtIp');
		snmask = getConcatIP(idPrefix+'txtSn');
		gw = getConcatIP(idPrefix+'txtGw');
		
		addSummaryRow(divSum, 'IP Address: ', ipadr);
		addSummaryRow(divSum, 'Subnet Mask: ', snmask);
		addSummaryRow(divSum, 'Gateway: ', gw);
		
		if(isSelected('cbdhcp')){
			dhcp = 'true';
			dhcpstart = getConcatIP('limtxtDhcp');
			dhcpnum = getContentOfId('limtxtNumDhcp');
			addSummaryRow(divSum,'DHCP Start Address: ', dhcpstart);
			addSummaryRow(divSum,'Number of DHCP addresses: ', dhcpnum);
		}
		else{
			dhcp = 'false';
			addSummaryRow(divSum,'DHCP Server: ', 'Disabled');
		}
	
		if(isSelected('cbdns')){
			dns = 'true';
			domain = getContentOfId('limtxtDomainName');
			addSummaryRow(divSum, 'Domain Name: ', domain);
		}
		else{
			dns = 'false';
			addSummaryRow(divSum, 'DNS Server: ', 'Disabled');
		}
	}
	
	addBlankLine(divSum);
	var btnText = 'Save';
	if(appMode != MODE_PRO){
		btnText = 'Save And Apply';
		var saveAndApplyMsg = 'Click on "Save and Apply" to confirm your settings, and then re-connect to the device using the new settings.';
		createDiv(divSum,'','',saveAndApplyMsg);
	}
	
	divSum.appendChild(
			createButton(
			'Back', 
			function() {
				dispLimApProvisioningScreen(idPrefix);
			},
			'btn'
		)
	);
	
	
	divSum.appendChild(
			createButton(
				btnText, 
				function() {
					dispLimConnect(idPrefix, ssid, pwd, security, channel, wepauth, beaconinterval, ipadr, snmask, gw, dhcp, dhcpstart, dhcpnum, dns, domain );
				},
				'btn'
			)
		);
	
}





/**
 * Displays a "connecting" page to the user while the connection parameters are
 * being posted to the server
 */
function dispLimConnect(idPrefix, ssid, pwd, security, channel, wepauth, beaconinterval, ipadr, snmask, gw, dhcp, dhcpstart, dhcpnum, dns, domain ) {
	var divConnect = document.getElementById(idPrefix +'connect');

	divConnect.innerHTML = '<div class="center bold">Connecting ... </div>';
	hideAllBut(idPrefix +'connect', appMode);

	var postXml = createXmlDoc('network');

	if(appMode != MODE_PRO){
		var mode = postXml.createElement('mode');
		mode.appendChild(postXml.createTextNode('limited-ap'));
		postXml.documentElement.appendChild(mode);
	}
	
	
	
	var client = postXml.createElement('ap');
	postXml.documentElement.appendChild(client);

	var wireless = postXml.createElement('wireless');
	client.appendChild(wireless);

		
	
	appendXmlElement(postXml, wireless, 'ssid', ssid);
	appendXmlElement(postXml, wireless, 'password', pwd);
	appendXmlElement(postXml, wireless, 'channel', channel);
	appendXmlElement(postXml, wireless, 'security', security);
	appendXmlElement(postXml, wireless, 'wepauth', wepauth);
	
	if(isSelected(idPrefix+'cbadvanced')){
		if(appMode == MODE_PRO){
			appendXmlElement(postXml, wireless, 'beacon_interval', parseInt(beaconinterval, 10));
		}
		
		var ipelem = postXml.createElement('ip');
		client.appendChild(ipelem);
		
	
		
		appendXmlElement(postXml, ipelem, 'ip_addr', ipadr);
		appendXmlElement(postXml, ipelem, 'subnetmask', snmask);
		appendXmlElement(postXml, ipelem, 'gateway', gw);
	 
		appendXmlElement(postXml, ipelem, 'dhcp_server_enable', dhcp);
		appendXmlElement(postXml, ipelem, 'dns_server_enable', dns);
		
		if(dhcp === 'true'){
			appendXmlElement(postXml, ipelem, 'dhcp_start_addr', dhcpstart);
			appendXmlElement(postXml, ipelem, 'dhcp_num_addrs', parseInt(dhcpnum,10));
		}
		if(dns === 'true'){
			appendXmlElement(postXml, ipelem, 'dns_domain', domain);
		}
	}
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
				var heading = 'Wireless Configuration Summary';
				dispLimStatus(idPrefix, ssid, heading);
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
function dispLimStatus(idPrefix, ssid, heading) {

	var divStatus = document.getElementById('status');
	clearNode(divStatus);
	
	var msgPrefix = 'The configuration settings have been ';
	var msgSuffix = 'Click on "Apply Settings" to confirm your settings, and then re-connect to the device using the new settings.';
	
	var msg = '';
	if(appMode == MODE_PRO){
		msg = msgPrefix + 'saved. '+msgSuffix;
	} else {
		msg = 'Your device setup is now complete. You are now logged out. Please re-connect to the device using your new wireless settings.';
	}
	var head = createDiv(divStatus, '','', heading, 'wizhead');
	var d1 = createDiv(divStatus, '', '', msg, 'finalmsg');
	/*var d2 = createDiv(divStatus, '', '', msg);*/
	
	var btnDiv = createDiv(divStatus);
	
	
	if(appMode == MODE_PRO){
		addBlankLine(btnDiv);
		btnDiv.appendChild(
		createButton(
				'Apply Settings', 
				function(){
					/*var msg = 'The settings have been saved and applied. The configuration is now complete. You may close this page.';*/
					var msg = 'Your device setup is now complete. You are now logged out. Please re-connect to the device using your new wireless settings.';
					switchMode('limited-ap',msg);
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

/*
 * Export the variables which would be referenced from outside the combined JS.
 * This is required for closure compiler.
 */
window['dispLimLandingScreen']=dispLimLandingScreen;