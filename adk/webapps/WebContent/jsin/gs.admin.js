/*
 * Collection of functions which are used for the Administrator Settings Screen. 
 */

/**
 * Displays the Administrator settings screen.
 * @param idPrefix The prefix to be used for the HTML element IDs. 
 * 'cl' for the Client pages, 'lim' for the Limited AP Pages 
 */
function dispAdminSettingsScreen(idPrefix){
	setPageHeading('Administrator Settings');
	var divadm = document.getElementById('admin');
	
	/*
	 * After getting the HTML DIV allotted for the admin page, clear it first.
	 */
	clearNode(divadm);
	
	/*
	 * Then, create the form fields.
	 */
	createDiv(divadm, '', '', 'Web Server Settings', 'wizhead');
	createDiv(divadm, '', '', 'To disable web server security, please leave the following fields empty.');
	createFieldRow(divadm, 'Username: ', createTextBox('txtUserName'));
	createFieldRow(divadm, 'Password (at least 4 characters): ', createSimplePwdBox('txtNewPwd'));
	createFieldRow(divadm, 'Confirm Password: ', createSimplePwdBox('txtCnfPwd'));
	
	
	
	addBlankLine(divadm);
	var btnDiv = createDiv(divadm);
	btnDiv.appendChild(
			createButton(
				'Back', 
				function(){
					/*
					 * Based on the execution context, decide where the "Back" button should take you. 
					 */
					switch(appMode){
						case MODE_AP:
							dispLimLandingScreen('lim');
							break;
							
						case MODE_CLIENT:
							dispClientLandingScreen('cl');
							break;
							
						case MODE_PRO:
						default:
							dispProLandingScreen();
							break;
					}
					
					
				},
				'btn'
			)
		);
	
	
	btnDiv.appendChild(
			createButton(
				'Save & Apply', 
				function(){
					/*
					 * When user saves, first do validation. 
					 * Only if the input is valid, proceed to the next step
					 */
					if(validateAdminDtls()){
						saveAdminChanges(
								idPrefix,
							getContentOfId('txtUserName'),
							getContentOfId('txtNewPwd')
							
						);
					}	
				},
				'btn'
			)
		);
	
	addBlankLine(divadm);
	divadm.appendChild(createElementNode('hr'));
	
	var divSysId = createDiv(divadm);
	createDiv(divSysId, '', '', 'System Identification', 'wizhead');
	var divSysIdFields = createDiv(divSysId, 'divSysIdFields');
	
	createFieldRow(divSysIdFields, 'System Name (Please ensure this name is unique in your network): ', createTextBox('txtSysName'));
	
	addBlankLine(divSysId);
	var btnDivForSys = createDiv(divSysId);
	btnDivForSys.appendChild(
			createButton(
				'Back', 
				function(){
					/*
					 * Based on the execution context, decide where the "Back" button should take you. 
					 */
					switch(appMode){
						case MODE_AP:
							dispLimLandingScreen('lim');
							break;
							
						case MODE_CLIENT:
							dispClientLandingScreen('cl');
							break;
							
						case MODE_PRO:
						default:
							dispProLandingScreen();
							break;
					}
					
					
				},
				'btn'
			)
		);
	
	
	btnDivForSys.appendChild(
			createButton(
				'Save & Apply', 
				function(){
					if(validateSysIdDtls()){
						saveSysIdChanges(idPrefix, getContentOfId('txtSysName'));
					}
				},
				'btn'
			)
		);
	
	/*
	 * Next, make a REST call to get data for pre population
	 */
	if(adminXml == null){
		var admxhr = initializeXhr();
		ajaxCall(
				admxhr, 
				AJAX_METHOD_GET,
				GS_ADMIN_API,
				null,
				function(){
					adminXml = parseResponse(admxhr.responseXml, admxhr.responseText);
					populateAdminScreen(adminXml);
				}
		);
	}
	else{
		populateAdminScreen(adminXml);
	}
	
	if(sysIdXml == null){
		var sysxhr = initializeXhr();
		ajaxCall(
				sysxhr, 
				AJAX_METHOD_GET,
				GS_SYSID_API,
				null,
				function(){
					sysIdXml = parseResponse(sysxhr.responseXml, sysxhr.responseText);
					populateSysId(sysIdXml);
					
					
				}
		);
	}
	else{
		populateSysId(sysIdXml);
	}
	
	addBlankLine(divSysId);
	divSysId.appendChild(createElementNode('hr'));
	
	
	/*
	 * Next, make a REST call to get data for firmware versions
	 */
	if(fwXml == null){
		var fwxhr = initializeXhr();
		ajaxCall(
				fwxhr, 
				AJAX_METHOD_GET,
				GS_FIRMWARE_API,
				null,
				function(){
					fwXml = parseResponse(fwxhr.responseXml, fwxhr.responseText);
					populateSystemInfo(fwXml);
				}
		);
	}
	else{
		populateSystemInfo(fwXml);
	}
	
	hideAllBut('admin', appMode);
}

/**
 * Pre-populates the HTTPD settings.
 * @param adminXml The XML object to use for prepopulation.
 */
function populateAdminScreen(adminXml){
	var httpd = adminXml.getElementsByTagName('httpd');
	if(httpd && httpd.length > 0){
		setFieldContent(document.getElementById('txtUserName'), getTagContent(httpd[0], 'username'));
	}
}


function populateSystemInfo(fwXml){
	var divadm = document.getElementById('admin');
	var divinfo = createDiv(divadm, 'divSystemInfo');
	createDiv(divinfo, '', '', 'Firmware Information', 'wizhead');
	var version = fwXml.getElementsByTagName('version');
	if(version && version.length > 0){
		addSummaryRow(divinfo,'WLAN Version: ',getTagContent(version[0], 'wlan'));
		addSummaryRow(divinfo,'GEPS Version: ',getTagContent(version[0], 'geps'));
		addSummaryRow(divinfo,'Provisioning Web-app Version: ', PROVISIONING_WEBAPP_VERSION);
		addSummaryRow(divinfo,'Embedded Application Version: ', getTagContent(version[0], 'app'));
		addSummaryRow(divinfo,'System HTTP API Version: ', systemHttpApiVersion);
		var chipVersion = getTagContent(version[0], 'chip');

		
		if(chipVersion == '' || chipVersion == null) {
			chipVersion = 'gs1011';
		}
		
		addSummaryRow(divinfo,'Module: ', getDisplayText(chipVersion));
	}
}


function populateSysId(sysIdXml){
	var divSysIdFields = document.getElementById('divSysIdFields');
	clearNode(divSysIdFields);
	createFieldRow(divSysIdFields, 'System Name (Please ensure this name is unique in your network): ', createTextBox('txtSysName'));
	var sysid = sysIdXml.getElementsByTagName('id');
	if(sysid && sysid.length > 0){
		setFieldContent(document.getElementById('txtSysName'), getTagContent(sysid[0], 'name'));
		addSummaryRow(divSysIdFields,'UUID: ',getTagContent(sysid[0], 'uid'));
	}
}


function validateAdminDtls(){
	/*
	 * 1) If username exists, it must be at least 4 characters.
	 * 2) If password exists, it must be at least 4 characters.
	 * 3) The 2 passwords must match.
	 */
	
	var newpwd = getContentOfId('txtNewPwd');
	var cnfPwd = getContentOfId('txtCnfPwd');
	
	
	var username = getContentOfId('txtUserName');
	
	
	if(newpwd.length > 0 && newpwd.length < 4){
		handleAdminDtlsInvalid('Error: Passwords must contain at least 4 characters.');
		 return false;
	}
	
	if(username.length > 0 && username.length < 4){
		handleAdminDtlsInvalid('Error: Username must contain at least 4 characters.');
		 return false;
	}
	
	if(newpwd != cnfPwd){
		handleAdminDtlsInvalid('Error: Passwords do not match. Please try again');		
		return false;
	}
	
	return true;
}


function validateSysIdDtls(){
	/*
	 * 1)System Name must be non-empty, 
	 * 2)Shouldn't contain spaces, 
	 * 3)Should be a max of 32 characters.
	 */
	
	var sysName = getContentOfId('txtSysName');
	
	var hasWhiteSpace =  /\s/g.test(sysName);
    
	if(sysName.length == 0){
		handleSysIdInvalid('Error: System Name should not be empty');
		return false;
	}
	
	if(sysName.length > 32){
		handleSysIdInvalid('Error: System Name should not be more than 32 characters long.');
		return false;
	}
	
	if(hasWhiteSpace){
		handleSysIdInvalid('Error: System Name should not have any white spaces.');
		return false;
	}
	
	return true;
}



/**
 * Handler for invalid input. Displays the specified error message, and clears the fields.
 * @param errorMsg The error message to display.
 */
function handleAdminDtlsInvalid(errorMsg){
	var newfield = document.getElementById('txtNewPwd');
	var cnffield = document.getElementById('txtCnfPwd');
	alert(errorMsg);
	setFieldContent(newfield, '' );
	setFieldContent(cnffield, '' );
	newfield.focus();
}


function handleSysIdInvalid(errorMsg){
	var sysNameField = document.getElementById('txtSysName');
	alert(errorMsg);
	setFieldContent(sysNameField, '');
	sysNameField.focus();
}

/**
 * Saves the Web Server settings.
 * @param idPrefix The prefix to be used for the HTML element IDs. 
 * 'cl' for the Client pages, 'lim' for the Limited AP Pages 
 * @param username The username entered by the user.
 * @param pwd The password entered by the user.
 */
function saveAdminChanges(idPrefix, username, pwd){
	
	/*
	 * First, create the XML
	 */
	var postXml = createXmlDoc('httpd');
	appendXmlElement(postXml, postXml.documentElement, 'username', username);
	appendXmlElement(postXml, postXml.documentElement, 'password', pwd);
	
	/*
	 * Then POST it. After that, set the Mode to the current mode to ensure a reboot.
	 * Note that we may not have the current mode information - in which case we do a GET for the network config.
	 */
	ajaxCall(
			initializeXhr(), 
			AJAX_METHOD_POST, 
			GS_ADMIN_API, 
			postXml, 
			function() {
				/*
				 * Every time we do a POST, re-initialize the corresponding global XML to empty.
				 * This forces a GET next time to ensure that pre-populated values are up-to-date. 
				 */
				adminXml = null;
														
				if(nwConfXml == null){
					var xhr = initializeXhr();
					ajaxCall(
							xhr, 
							AJAX_METHOD_GET,
							GS_CONF_API,
							null,
							function(){
								nwConfXml = parseResponse(xhr.responseXml, xhr.responseText);
								setModeAfterAdminPost(nwConfXml);
							}
					);
				} else {
					setModeAfterAdminPost(nwConfXml);
				}	
			}
	);
}

function saveSysIdChanges(idPrefix, systemName){
	var postXml = createXmlDoc('id');
	appendXmlElement(postXml, postXml.documentElement, 'name', systemName);
	
	ajaxCall(
			initializeXhr(), 
			AJAX_METHOD_POST, 
			GS_SYSID_API, 
			postXml, 
			function() {
				/*
				 * Every time we do a POST, re-initialize the corresponding global XML to empty.
				 * This forces a GET next time to ensure that pre-populated values are up-to-date. 
				 */
				sysIdXml = null;
														
				if(nwConfXml == null){
					var xhr = initializeXhr();
					ajaxCall(
							xhr, 
							AJAX_METHOD_GET,
							GS_CONF_API,
							null,
							function(){
								nwConfXml = parseResponse(xhr.responseXml, xhr.responseText);
								setModeAfterAdminPost(nwConfXml);
							}
					);
				} else {
					setModeAfterAdminPost(nwConfXml);
				}	
			}
	);
	
}

function setModeAfterAdminPost(nwXml){
	var currentMode = getTagContent(nwXml, 'mode');
	switchMode(currentMode,'Your administrator settings are saved.');
}
