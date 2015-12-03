/*
 * Collection of app-specific functions which are common to all the versions of the pages. 
 */

/*
 * Array of the top-level DIVs used in the PRO version of the page.
 */
var proDivArray = [ 'limland','limprov', 'admin', 'client',
	     			'status', 'limconnect', 'limsummary', 
	     			'clprov', 'clland', 'landing', 'scan', 
	     			'list', 'clconnect', 'clsummary', 'mode', 'otafu' ];
/*
 * Array of the top-level DIVs used in the Client version of the page.
 */
var clientDivArray = [ 'clland','clprov', 'admin', 'scan', 'list',
   		 			'status', 'client', 'clconnect', 'clsummary' ];

/*
 * Array of the top-level DIVs used in the Limited AP version of the page.
 */
var limapDivArray = [ 'limland','limprov', 'admin', 
  		 			'status', 'limconnect', 'limsummary' ]; 

/**
 * Function that pre-fetches the Firmware Info. 
 * Used by Client and Limited AP pages to ensure Fimrware info is 
 * available before proceeding  
 * 
 * @param callback The callback to execute once firmware info is available
 */
function prefetchFirmwareInfo(callback){
	if(fwXml == null){
		var fwxhr = initializeXhr();
		ajaxCall(
				fwxhr, 
				AJAX_METHOD_GET,
				GS_FIRMWARE_API,
				null,
				function(){
					fwXml = parseResponse(fwxhr.responseXml, fwxhr.responseText);
					callback();
				}
		);
	}
	else{
		callback();
	}
}

function prefetchNetworkConfig(callback){
	if (nwConfXml == null) {
		var nwxhr = initializeXhr();
		ajaxCall(
				nwxhr, 
				AJAX_METHOD_GET, 
				GS_CONF_API, 
				null, 
				function() {
					nwConfXml = parseResponse(nwxhr.responseXml, nwxhr.responseText);
					callback();
				}
			);
	} else {
		callback();
	}
}

/**
 * Checks the API version in use on the node.
 * If it is different from that assumed by this app, displays a warning.
 */

function ajaxCallForApiVersion() {
	if(systemHttpApiVersion == ''){
		var verxhr = initializeXhr();
		ajaxCall(
				verxhr,
				AJAX_METHOD_GET,
				GS_VERSION_API,
				null,
				function() {
					var respXml = parseResponse(verxhr.responseXml,
							verxhr.responseText);
					systemHttpApiVersion = respXml.getElementsByTagName('version')[0].firstChild.nodeValue;
					
					/*
					if (parseFloat(version) > API_VERSION) {
						alert('There is a mismatch between the version of the API provided by the server ('
								+ version
								+ '), and that assumed by this app. Some features may not work properly.');
					}*/
				});
	}
}




/*
 * Helper method which makes the Ajax call to fetch the Network config.
 * whichScreen can be one of
 * 1) 'basic' To populate the basic config fields
 * 2) 'advanced' To populate the advanced fields
 */
function ajaxCallForNwConfig(idPrefix, whichScreen) {
	if (nwConfXml == null) {
		var nwxhr = initializeXhr();
		ajaxCall(
				nwxhr, 
				AJAX_METHOD_GET, 
				GS_CONF_API, 
				null, 
				function() {
					nwConfXml = parseResponse(nwxhr.responseXml, nwxhr.responseText);
					if (whichScreen == 'basic') {
						populateBasicSettings(nwConfXml, idPrefix);
					} else if (whichScreen == 'advanced'){
						populateAdvancedSettings(nwConfXml, idPrefix);
					}
				}
			);
	} else {
		if (whichScreen == 'basic') {
			populateBasicSettings(nwConfXml, idPrefix);
		} else if (whichScreen == 'advanced'){
			populateAdvancedSettings(nwConfXml, idPrefix);
		}
	}
}


/**
 * Gets the display text corresponding to the input xml value
 * @param xmlVal
 */
function getDisplayText(xmlVal, context){
	var returnVal= '';
	switch (xmlVal) {
	
	case 'prov-ap':
		returnVal = 'Provisioning AP';
		break;
	
	case 'limited-ap':
		returnVal = 'Limited AP';
		break;
	
	case 'client':
		returnVal = 'Client';
		break;
	
	case 'ad-hoc':
		returnVal = 'Ad-Hoc/IBSS';
		break;
	
	case 'dhcp':
		returnVal = 'Acquire IP Address automatically (DHCP)';
		break;
	
	case 'infra':
		returnVal = 'Infrastructure Client';
		break;
	
	case 'static':
		returnVal = 'Static IP Address Configuration';
		break;
	
	case 'open':
		returnVal = 'Open';
		break;
		
	case 'shared':
		returnVal = 'Shared';
		break;
	
	case 'none':
		switch (context){
		
		case 'cl':
			returnVal='No Security';
			break;
		
		case 'lim':
			returnVal='Open';
			break;
		
		default:
			returnVal='No Security';
			break;
		}
		break;
	
	case 'wpa-personal':
		switch (context){
		
		case 'cl':
			returnVal='WPA/WPA2 Personal';
			break;
		
		case 'lim':
			returnVal='WPA2 Personal (AES+TKIP)';
			break;
		
		default:
			returnVal='WPA/WPA2 Personal';
			break;
		}
		break;
	
	case 'wpa-enterprise' :
		returnVal='WPA/WPA2 Enterprise';
		break;
	
	case 'eap-fast':
		returnVal = 'EAP-FAST';
		break;
		
	case 'eap-fast-gtc':
		returnVal = 'EAP-FAST-GTC';
		break;
		
	case 'eap-fast-mschap':
		returnVal = 'EAP-FAST-MSCHAP';
		break;
		
	case 'eap-ttls':
		returnVal = 'EAP-TTLS';
		break;
		
	case 'eap-peap':
		returnVal = 'EAP-PEAP v0/1';
		break;
	
	case 'eap-peap0':
		returnVal = 'EAP-PEAP0';
		break;
	
	case 'eap-peap1':
		returnVal = 'EAP-PEAP1';
		break;
		
	case 'eap-tls':
		returnVal = 'EAP-TLS';
		break;
		
	case 'wep':
		switch (context){
		
		case 'cl':
			returnVal='WEP';
			break;
		
		case 'lim':
			returnVal='WEP-40 (Open)';
			break;
		
		default:
			returnVal='WEP';
			break;
		}
		break;
	
	case 0:
	case '0':
		switch(context){
		case 'client-screen': 
			returnVal = 'Any';
			break;
		case 'scan-params-screen':
			returnVal = 'All';
			break;
		default:
			returnVal = 'Any';
			break;
		}
		break;
	
	case 'gs1011':
		returnVal = 'GS1011';
		break;
		
	case 'gs1011m':
		returnVal = 'GS1011M';
		break;
		
	case 'gs1500':
		returnVal = 'GS1500';
		break;
		
	case 'gs1500m':
		returnVal = 'GS1500M';
		break;
	
	case 'gs1550':
		returnVal = 'GS1550';
		break;
	
	case 'gs2000':
		returnVal = 'GS2000';
		break;
	
	case 'gs2000m':
		returnVal = 'GS2000M';
		break;
		
	default:
		returnVal = xmlVal;
		break;
	}
	return returnVal;
}

/**
 * Validates the entered SSID
 * @param enteredSsid
 * @returns {Boolean}
 */
function validateSsid(enteredSsid){
	return enteredSsid.length > 0 && enteredSsid.length <= 32; 
}

/**
 * Validates the WEP Key
 * @param wepkey The WEP key.
 * @param force40bit Whether to force 40-bit. If false, allows both 40 bit and 104 bit.
 * @returns {Boolean} True if the validation succeeds, false otherwise.
 */
function validateWepKey(wepkey, force40bit){
	
	
	/*
	 * RegEx to match 40 bit or 104 bit hexadecimal
	 */
	var wepkey40bitHexRE = "^[A-Fa-f0-9]{10}$"; 
	var wepkey104bitHexRE = "^[A-Fa-f0-9]{26}$";
	
	/*
	 * RegEx to match only printable ASCII characters (5 char or 13 char)
	 * http://www.catonmat.net/blog/my-favorite-regex/
	 */
	var wepKey5CharAscii = "^[ -~]{5}$";
	var wepKey13CharAscii = "^[ -~]{13}$";
	if(wepkey.match(wepkey40bitHexRE) || wepkey.match(wepKey5CharAscii)){
		return true;
	}else{
		if(!force40bit && wepkey.match(wepkey104bitHexRE) || wepkey.match(wepKey13CharAscii)){
			return true;
		}
	}
	
	return false;
}

/*
 * Helper function to set IP Address into a octet-separated IP field.
 */
function setIpAddress(fieldPrefix, ipadr){
	var octets = ipadr.split('.');
	for(var i=0;i<4;i++){
		setFieldContent(document.getElementById(fieldPrefix+'-'+i), octets[i]);
	}
}

/**
 * Validates the IP octet
 */
function validateIPOctet(value, min, max) {
	/*return (!isNaN(value) && value >= min && value <= max);*/
	var octetRE = '^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])$';
	return value.match(octetRE);
}

/*
 * Helper function to create an IP Address input row.
 */
function createIPAdrRow(parent, rowPrefix, label){
	var aDiv = createDiv(parent, rowPrefix, 'iprow', label, 'lbl');
	for (var box=0;box<4;box++){
		aDiv.appendChild(
				createTextBox(
						rowPrefix+'-'+box,
						3,
						'octet',
						function() {
							var entered = getContentOfId(this.id);
							/*if (!validateIPOctet(parseInt(entered, 10), 0, 255))*/ 
							if (!validateIPOctet(entered)){
								alert('The address you entered is invalid. Each octet must be between 0 and 255, inclusive. Please enter a valid IP address.');
								setContentOfId(this.id, '');
								this.focus();
							}
							;
						}
				)
		);
		if (box < 3) {
			appendDot(aDiv);
		}
	}
	createBr(aDiv, 'clr');
}

/*
 * Helper function to create the various fields required for static IP address input.
 */
function constructIPConfig(parent, idPrefix) {
	var rowIds = [ 'txtIp', 'txtSn', 'txtGw', 'txtDns'];
	var labels = ['IP Address: ', 'Subnet Mask: ', 'Gateway: ', 'DNS Server: '];
	for ( var i = 0; i < rowIds.length; i++) {
		createIPAdrRow(parent, idPrefix+rowIds[i], labels[i]);
	}
}

/*
 * Helper function to extract individual octets of an IP and concatenate them into an IP address.
 */
function getConcatIP(rowId) {
	var returnVal = '';
	for ( var i = 0; i < 4; i++) {
		returnVal += getContentOfId(rowId +'-' + i);
		if (i < 3) {
			returnVal += '.';
		}
	}
	return returnVal;

}

/**
 * Helper function to create a field row.
 * @param parent The parent node
 * @param label The label for the field.
 * @param field The actual field
 * @param justBefore If the row has to be inserted just before an existing element, then this parameter specifies that existing element. 
 * @returns
 */
 
function createFieldRow(parent, label, field, justBefore, style){
	var aDiv = createDiv(parent);
	createLabel(aDiv, field.id, label, 'lbl');
	if(style && style != ''){
		setClass(field, style);
	} else {
		setClass(field, 'fld');
	}
	aDiv.appendChild(field);
	if(justBefore && justBefore != ''){
		aDiv = parent.removeChild(aDiv);
		parent.insertBefore(aDiv, justBefore.parentNode);
	}
	createBr(aDiv, 'clr');
	return aDiv;
}

function setFieldROVal(id, val, readonly) {
	var field = document.getElementById(id);
	setReadOnly(field, readonly);
	setFieldContent(field, val);
}

/*
 * Helper method to get entered password.
 */
function getEnteredPass(idPrefix, index) {
	if (index == 0) {
		return '';
	} else if (index == 1) {
		var wepid = document.getElementById(idPrefix+'wepid');
		var sel = wepid.options[wepid.selectedIndex].value;
		return sel + ':' + getContentOfId(idPrefix+'wepkey');
	} else if (index == 2) {
		return getContentOfId(idPrefix+'secpp');
	}
}

/**
 * Adds a summary row
 * @param parent The parent node
 * @param label The summary label
 * @param value The summary value.
 */
function addSummaryRow(parent, label, value){
	var aDiv = createDiv(parent);
	var lblSpan = createSpan(label, '', 'sumlbl');
	aDiv.appendChild(lblSpan);
	
	var lblVal = createSpan(value, '', 'sumval');
	aDiv.appendChild(lblVal);
	
	createBr(aDiv, 'clr');
}


/**
 * Pre populates the basic settings.
 * @param nwXml The network config XML object.
 * @param idPrefix The prefix. 'cl' for Client configuration; 'lim' for Limited AP.
 */
function populateBasicSettings(nwXml, idPrefix){
	var confXml;
	if(idPrefix == 'cl'){
		confXml = nwXml.getElementsByTagName('client'); 
	}
	else if(idPrefix == 'lim'){
		confXml = nwXml.getElementsByTagName('ap');
	}
	var regDomain = getTagContent(nwXml, 'reg_domain');
	var maxChannels = getMaxChannelsForDomain(regDomain);
	
	/*adjustChannelDropDown(document.getElementById(idPrefix+'wlChannel'), maxChannels);*/
	
	if(confXml && confXml.length > 0){
		var wifi = confXml[0].getElementsByTagName('wireless');
		if(wifi && wifi.length > 0){
			setFieldContent(document.getElementById(idPrefix+'wlSsid'), getTagContent(wifi[0], 'ssid'));
			var channelInt = parseInt(getTagContent(wifi[0], 'channel'));
			
			if(isBandConfigSupported() == true){
				var ddBand = document.getElementById(idPrefix + 'band');
								
				/*
				 * If band info is not available - we are in Manual Config page.
				 * Here, set the band based on the channel 
				 */
				if(channelInt <= 14){
					ddBand.selectedIndex = 0;
				} else {
					ddBand.selectedIndex = 1;
				}
								
				ddBand.onchange();
			}
			
			setFieldContent(document.getElementById(idPrefix+'wlChannel'), channelInt);
			
			var ddSec = document.getElementById(idPrefix+'idSecType');
			ddSec.disabled = false;
			var security = getTagContent(wifi[0], 'security');
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
				/* Wep Auth Mode is only valid in client page. In Limited AP page, it is invalid */
				if(idPrefix == 'cl'){
					var wauth = document.getElementById(idPrefix +'wepAuthMode');
					var wepauth = getTagContent(wifi[0], 'wepauth');
					if(wepauth == 'open'){
						wauth.selectedIndex = 0;
					}
					else if(wepauth == 'shared'){
						wauth.selectedIndex= 1;
					}
				}
				
				var wepcred = getTagContent(wifi[0], 'password');
				var splits = wepcred.split(':');
				var wepidx = document.getElementById(idPrefix+'wepid');
				wepidx.selectedIndex = splits[0] - 1;
				/*setFieldContent(document.getElementById(idPrefix+'wepkey'), splits[1]);*/
			}
			
			else if (securityUpper == 'WPA-ENTERPRISE'){
				var eapdd = document.getElementById(idPrefix+'eaptype');
				var eapType = getTagContent(wifi[0], 'eap_type');
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
				
				setFieldContent(document.getElementById(idPrefix+'eapusername'), getTagContent(wifi[0], 'eap_username'));
					
			}
		}
		
		var ip = confXml[0].getElementsByTagName('ip');
		if(ip && ip.length > 0){
			if(idPrefix == 'cl'){
				var ipType = getTagContent(ip[0], 'ip_type');
				if(ipType == 'static'){
					var cbadvanced = document.getElementById(idPrefix+'cbadvanced');
					if(cbadvanced){
						cbadvanced.click();
					}
				}
			}
		}
	}
}

function populateStaticIpSettings(nwXml, idPrefix){
	var confXml = nwXml.getElementsByTagName('client'); 
	if(confXml && confXml.length >0){
		var ip = confXml[0].getElementsByTagName('ip');
		if(ip && ip.length > 0){
			setIpAddress(idPrefix+'txtIp', getTagContent(ip[0], 'ip_addr'));
			setIpAddress(idPrefix+'txtSn', getTagContent(ip[0], 'subnetmask'));
			setIpAddress(idPrefix+'txtGw', getTagContent(ip[0], 'gateway'));
			setIpAddress(idPrefix+'txtDns', getTagContent(ip[0], 'dns_addr'));
		}
	}
}

/**
 * Pre populates the advanced settings.
 * @param nwXml The network config XML object.
 * @param idPrefix
 */
function populateAdvancedSettings(nwXml, idPrefix){
	var confXml;
	if(idPrefix == 'cl'){
		confXml = nwXml.getElementsByTagName('client'); 
	}
	else if(idPrefix == 'lim'){
		confXml = nwXml.getElementsByTagName('ap');
	}
	
	if(confXml && confXml.length >0){
		var ip = confXml[0].getElementsByTagName('ip');
		if(ip && ip.length > 0){
			setIpAddress(idPrefix+'txtIp', getTagContent(ip[0], 'ip_addr'));
			setIpAddress(idPrefix+'txtSn', getTagContent(ip[0], 'subnetmask'));
			setIpAddress(idPrefix+'txtGw', getTagContent(ip[0], 'gateway'));
			if(idPrefix == 'cl'){
				var ipType = getTagContent(ip[0], 'ip_type');
				/*
				 * TODO:
				 * 
				 * Currently having flow-related issues with prepopulating the 
				 * DHCP/Static radio button.
				 * 
				 * The issue is - even if we prepopulate, as soon as the user clicks on it,
				 * ajaxCallForNwConfig is called, and it re-prepopulates!
				 * 
				 * Commenting this until we fix the issue.
				 */
				if(ipType == 'static'){
					populateRadio(idPrefix+'rstatic');
				} else {
					populateRadio(idPrefix+'rdhcp');
				}
				setIpAddress(idPrefix+'txtDns', getTagContent(ip[0], 'dns_addr'));
			}
			else if(idPrefix == 'lim'){
				
				/*
				 * If idPrefix is 'lim', then we are in Limited AP configuration.
				 * We need to display beacon interval in addition to already displayed values
				 */
				var wifi = confXml[0].getElementsByTagName('wireless');
				if(wifi && wifi.length > 0 && appMode == MODE_PRO){
					var bi = getTagContent(wifi[0], 'beacon_interval');
					if(bi){
						bi = parseInt(bi);
						if(bi < 100){
							bi = 100;
						} else if (bi > 1600){
							bi = 1600;
						}
					}
					setFieldContent(document.getElementById(idPrefix+'beaconint'), bi);
				}
				var divLimDhcp = document.getElementById('divlimDhcp');
				if(getTagContent(ip[0], 'dhcp_server_enable') == 'true'){
					document.getElementById('cbdhcp').checked = true;
					unHide(divLimDhcp);
				}
				else{
					document.getElementById('cbdhcp').checked = false;
					hide(divLimDhcp);
				}
				setIpAddress(idPrefix+'txtDhcp', getTagContent(ip[0], 'dhcp_start_addr'));
				setFieldContent(document.getElementById(idPrefix+'txtNumDhcp'), getTagContent(ip[0], 'dhcp_num_addrs'));
				/*document.getElementById('cbdhcp').onclick();*/
				
				var divLimDns = document.getElementById('divlimDns');
				if(getTagContent(ip[0], 'dns_server_enable') == 'true'){
					document.getElementById('cbdns').checked = true;
					unHide(divLimDns);
				}
				else{
					document.getElementById('cbdns').checked = false;
					hide(divLimDns);
				}
				setFieldContent(document.getElementById(idPrefix+'txtDomainName'), getTagContent(ip[0], 'dns_domain'));
				/*document.getElementById('cbdns').onclick();*/
			}
		}
	}
}

/**
 * Displays the security fields depending on the security type chosen.
 * @param parent The parent node
 * @param option The security type
 * @param idPrefix 
 */
function dispSecurityFields(parent, option, idPrefix) {
	var divSec = document.getElementById(idPrefix + 'SecFields');
	if (divSec == null) {
		divSec = createDiv(parent, idPrefix + 'SecFields');
	} else {
		clearNode(divSec);
	}

	if (option == 'wep') {
		if (idPrefix == 'cl') {
			var wam = createDropDown(idPrefix + 'wepAuthMode');
			addDropDownItem(wam, 0, 'open', getDisplayText('open'), true);
			addDropDownItem(wam, 1, 'shared', getDisplayText('shared'), false);
			createFieldRow(divSec, 'WEP Auth Mode: ', wam);
		}

		var ddwep = createDropDown(idPrefix + 'wepid');

		for ( var i = 1; i <= 4; i++) {
			var selected = false;
			if (i == 1) {
				selected = true;
			}
			addDropDownItem(ddwep, i - 1, i, i, selected);
		}
		createFieldRow(divSec, 'WEP Key Index: ', ddwep);
		createFieldRow(divSec, 'WEP Key: ', createTextBox(idPrefix + 'wepkey'));
	} else if (option == 'wpa-personal') {
		createFieldRow(divSec, 'Passphrase: ', createSimplePwdBox(idPrefix	+ 'secpp'));
		createFieldRow(divSec, 'Confirm Passphrase: ', createSimplePwdBox(idPrefix	+ 'secppconf'));
	} else if (option == 'wpa-enterprise'){
		var ddenterprise = createDropDown(idPrefix+'eaptype');
		addDropDownItem(ddenterprise, 0, 'eap-fast-gtc', getDisplayText('eap-fast-gtc'), true);
		addDropDownItem(ddenterprise, 1, 'eap-fast-mschap', getDisplayText('eap-fast-mschap'), true);
		addDropDownItem(ddenterprise, 2, 'eap-ttls', getDisplayText('eap-ttls'), false);
		addDropDownItem(ddenterprise, 3, 'eap-peap0', getDisplayText('eap-peap0'), false);
		addDropDownItem(ddenterprise, 4, 'eap-peap1', getDisplayText('eap-peap1'), false);
		addDropDownItem(ddenterprise, 5, 'eap-tls', getDisplayText('eap-tls'), false);
		
		
		createFieldRow(divSec, 'EAP Type: ', ddenterprise);
		
		createFieldRow(divSec, 'EAP Username: ', createTextBox(idPrefix+'eapusername'));
		createFieldRow(divSec, 'EAP Password: ', createSimplePwdBox(idPrefix+'eappwd'));
		createFieldRow(divSec, 'Confirm EAP Password: ', createSimplePwdBox(idPrefix+'cnfeappwd'));
		
		addBlankLine(divSec);
		divSec.appendChild(createElementNode('hr'));
		
		
		createDiv(divSec, '', '', 'Certificate Configuration', 'wizhead');
		
		var uploadCertBtn = createButton
							('Upload Certificates', 
								function(){
									var certPage = '/eapcerts.html';
									/*
									var eapType = ddenterprise.options[ddenterprise.selectedIndex].value;
									if(eapType == 'eap-tls'){
										certPage+='?ssltls=true';
									}
									*/
									var newWindow = window.open(certPage, 'name', 'height=700,width=800');
								}, 
								'btn'
							);
		divSec.appendChild(uploadCertBtn);
		
		if(isTimeConfigSupported){
			addBlankLine(divSec);
			divSec.appendChild(createElementNode('hr'));
			
			
			createDiv(divSec, '', '', 'Time Settings', 'wizhead');
			createCheckBox(
					divSec, 
					'', 
					'cbtime', 
					false,
					function() {
						/*
						 * Do Nothing.
						 * 
						 * The value of this checkbox will be used in later
						 * screens to determine whether to include the time in 
						 * the POST or not.
						 */					
					}, 
					'Set node time to current UTC time'
				);
		}
		
		
		
	}
}

/**
 * Validates the WPA Passphrase length.
 * @param passphrase
 * @returns {Boolean}
 */
function validateWpaPassphraseLength(passphrase){
	/*var passphrase8charRE = ".{8,}";*/
	if(passphrase.length < 8 || passphrase.length > 63){
		alert('Error: Passphrase must be between 8 and 63 characters long.');
		return false;
	}
	return true;
}

/**
 * Validates whether the passphrase and the confirm passphrase fields match.
 * @param passphrase
 * @param confpassphrase
 * @returns {Boolean}
 */
function validateWpaPassphrasesMatch(passphrase, confpassphrase){
	if(passphrase != confpassphrase){
		alert('Error: PassPhrases do not match.');
		return false;
	}
	return true;
}

/**
 * Hides all top-level DIVs except the one specified. 
 * This is how we achieve "navigation" from one "screen" to other.
 * @param elemId The ID of the DIV to remain visible.
 * @param mode The version of the App running.
 */
function hideAllBut(elemId, mode){
	var divArray;
	if(mode == MODE_PRO){
		divArray = proDivArray;
	}
	else if (mode == MODE_CLIENT){
		divArray = clientDivArray;
	}
	else if (mode == MODE_AP){
		divArray = limapDivArray;
	}

 	for ( var i = 0; i < divArray.length; i++) {
 		if (divArray[i] != elemId) {
 			hide(document.getElementById(divArray[i]));
 		}
 	}

 	document.getElementById(elemId).style.display = 'block';
}

/**
 * Validates the WPS PIN.
 * @param enteredPin
 */
function validateWpsPin(enteredPin){
	var wpsPinRE = "^[0-9]{8,8}$";
	if(! enteredPin.match(wpsPinRE)){
		alert('WPS PIN must be an 8 digit number. Please try again');
		return false;
	}
	return true;
}

/**
 * Validates the Beacon interval value. It must be between 100 and 1600.
 * @param enteredBi The Beacon Interval value input by the user.
 * @returns {Boolean}
 */
function validateBeaconInterval(enteredBi){
	/*
	 * TODO: Consider taking the lower and upper bounds as parameters rather than hardcoding here.
	 */
	if(!enteredBi || enteredBi == ''|| !isInteger(enteredBi)){
		return false;
	}
	var intBi = parseInt(enteredBi, 10);
	if(intBi < 100 || intBi > 1600){
		return false;
	}
	return true;
}

/**
 * Validates the "Number of DHCP addresses" input.
 * @param numAddrs Number of DHCP addresses value input by user.
 * @returns {Boolean}
 */
function validateDhcp(numAddrs, maxDhcpAddresses){
	/*
	 * TODO: Consider taking the lower and upper bounds as parameters rather than hardcoding here.
	 */
	if(!numAddrs || numAddrs == ''|| !isInteger(numAddrs)){
		return false;
	}
	var intAddrs = parseInt(numAddrs, 10);
	if(intAddrs < 1 || intAddrs > maxDhcpAddresses){
		return false;
	}
	return true;
}

/**
 * Validates the Domain Name input.
 * @param domainName The domain name entered by the use.
 * @returns {Boolean}
 */
function validateDomainName(domainName){
	/*
	 * Domain name must not be empty.
	 */
	
	if(!domainName || domainName.length < 1 || domainName == ''){
		return false;
	}
	
	return true;
}

/**
 * Performs a consolidated validation of IP addresses.
 * @param idPrefix The ID prefix
 * @param rowIds The array of IP Address Row IDS which need to be validated.
 * @returns {Boolean}
 */
function validateIpConsolidated(idPrefix, rowIds){
	for(var i=0;i<rowIds.length;i++){
		for(var j=0;j<=3;j++){
			var anId = idPrefix+rowIds[i]+'-'+j;
			var aBox = document.getElementById(anId);
			var anOctet = parseInt(getContentOfId(anId));
			
			/*if(!validateIPOctet(anOctet, 0, 255))*/
			if (!validateIPOctet(getContentOfId(anId))){
				alert('The address you entered is invalid. Each octet must be between 0 and 255, inclusive. Please enter a valid IP address.');
				aBox.focus();
				return false;
			}
		}
	}
	return true;
}

/**
 * Hides the footer.
 */
function hideFooter(){
	hide(document.getElementById('footer'));
}

/**
 * Sets the page heading.
 * @param heading
 */
function setPageHeading(heading){
	document.getElementById("pghead").innerHTML = '<h1 class="pghead">'+heading+'</h1>';
}

/**
 * Gets the maximum number of channels for the specified regulatory domain.
 * @param regDomain The regulatory domain.
 * @returns {Number} The maximum number of channels.
 */
function getMaxChannelsForDomain(regDomain){
	var regDomainUpper = regDomain.toUpperCase(); 
	if(regDomainUpper === 'FCC'){
		return 11;
	} else if(regDomainUpper === 'ETSI'){
		return 13;
	} else if(regDomainUpper === 'TELEC'){
		return 14;
	} else if(regDomainUpper === 'UNKNOWN'){
		return 14;
	} else {
		return 14;
	}
}

/**
 * Adjusts the maximum channels on an existing Channel drop-down 
 * @param drop The existing Channel drop-down.
 * @param maxChannels
 */
function adjustChannelDropDown(drop, maxChannels){
	
	var currentSize = drop.options.length;
	var currentMax = parseInt(drop.options[currentSize - 1].value);
	
	if(maxChannels > currentMax){
		for(var i = currentMax + 1; i<=maxChannels; i++){
			var actualIndex = i - (currentMax - currentSize + 1);
			addDropDownItem(drop, actualIndex, i, getDisplayText(i), false);
		}
	} else if (currentMax > maxChannels){
		for (var i=currentMax; i>maxChannels; i--){
			var actualIndex = i - (currentMax - currentSize + 1);
			drop.remove(actualIndex);
		}
	}
}

/**
 * "Selects" a radio button - used for prepopulation.
 * @param id The ID of the radio button to select.
 */
function populateRadio(id){
	
	var radioButton = document.getElementById(id);
	if(radioButton){
		//radioButton.checked = true;
		radioButton.click();
	}
}

function getChipVersion(){
	/*
	 * TODO:
	 * 
	 * Optimization - Do this one time on startup
	 * since chip version does not change during execution time.
	 */
	var version = fwXml.getElementsByTagName('version');
	if(version && version.length > 0){
		return getTagContent(version[0], 'chip');
	} else {
		return 'gs1011';
	}
}

function isBandConfigSupported(){
	var version = getChipVersion();
	return version && version.indexOf("1550") >=0;
}

function getRegDomain(){
	return getTagContent(nwConfXml, 'reg_domain');
}


function getMode(){
	return getTagContent(nwConfXml, 'mode');
}

function getChannelsForBand(band, regDomain, screen){
	/*alert('band, regDomain, mode: '+band+regDomain+mode);*/
	var regDomainUpper = regDomain.toUpperCase();		
	if(band.indexOf("5GHz") !== -1){	
		
		var commonUpperLimit = 48;
		if(screen == "client"){
			commonUpperLimit = 64;
		}
		var common = new Array();
		if(screen == "client"){
			common.push(0);
		}
		for(var i=36;i<=commonUpperLimit;i=i+4){
			common.push(i); 
		}
	
		var etsi = new Array();
		if(screen == "client"){		
			for(var j=100;j<=140;j=j+4){
				etsi.push(j);		
			}
		}
	
		var fcc = new Array();
		for(k=149;k<=165;k=k+4){
			fcc.push(k);
		}
	
		if(regDomainUpper === 'FCC'){
			return common.concat(fcc);
		} else if(regDomainUpper === 'ETSI'){
			return common.concat(etsi);
		} else if(regDomainUpper === 'TELEC'){
			return common;
		} else if(regDomainUpper === 'UNKNOWN'){
			return common;
		} else {
			return common;
		}
	} else if(band.indexOf("2.4GHz") !== -1){
		var maxChannels = getMaxChannelsForDomain(regDomain);
		var anArray = new Array();
		var start = (screen == 'client')?0:1;
		for(var i=start;i<=maxChannels;i++){
			anArray.push(i);
			
		}
		return anArray;
	}
}

/*
 * http://stackoverflow.com/q/3745666/570930
 */
/*function hexToAscii(hexInput) {
    var hex = hexInput.toString();//force conversion
    var str = '';
    for (var i = 0; i < hex.length; i += 2)
        str += String.fromCharCode(parseInt(hex.substr(i, 2), 16));
    return str;                
}*/

function asciiToHex(str) {
  var arr = [];
  for (var i = 0, l = str.length; i < l; i ++) {
    var hex = Number(str.charCodeAt(i)).toString(16);
    arr.push(hex);
  }
  return arr.join('');
}

/**
 * Normalizes the WEP Key. 
 * If the key is in ASCII form, convert it to Hex form. 
 * If it is already in Hex form, return as-is
 * 
 * This function does not perform regex validation. It is assumed that such validation has already been performed before calling this function.
 * @param wepKey The Key to normalize.
 */
function normalizeWepKey(wepKey){
	if(wepKey.length == 5 || wepKey.length == 13){
		return asciiToHex(wepKey);
	} else {
		return wepKey;
	}
}