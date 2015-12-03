/*
 *Collection of functions for the operation mode configuration. 
 */
function dispSwitchModeScreen(){
	var modeDiv = document.getElementById('mode');
	clearNode(modeDiv);
	
	/*
	var hDiv = createDiv(modeDiv, '', '', 'Use this screen to switch the mode of operation. You will lose connectivity to the device when the mode is set.', 'bold');
	var ul = createElementNode('ul');
	createDiv(modeDiv).appendChild(ul);
	
	createListItem(ul, '', '', 'Choose "Client" to start the device in client mode');
	createListItem(ul, '', '', 'Choose "Limited AP" to start the device as a Limited AP');
	
	
	var aDiv = createDiv(modeDiv);
	
	var mdrop = createDropDown('modedrop');

	
	addDropDownItem(mdrop, 0, 'client', getDisplayText('client'), true);
	addDropDownItem(mdrop, 1, 'limited-ap', getDisplayText('limited-ap'), false);

	
	createFieldRow(aDiv, 'Mode: ', mdrop);
	*/
	
	createDiv(modeDiv, '', '', 'Select the mode of operation', 'wizhead');
	var rdiv = createDiv(modeDiv, '', 'radio' );
	var fs = createElementNode('fieldset');
	rdiv.appendChild(fs);
	var d1 = createDiv(fs);
	var d2 = createDiv(fs);
	
	createRadio(d1, 'modeset', 'modeclient', 'divmodeclient', true, '', getDisplayText('client'));
	createRadio(d2, 'modeset', 'modelimap', 'divmodelimap', false, '',getDisplayText('limited-ap'));
	addBlankLine(modeDiv);
	
	var btnDiv = createDiv(modeDiv, 'divmodebtn');
	btnDiv.appendChild(
			createButton(
					'Back', 
					function(){
						dispProLandingScreen();
					}, 
					'btn'
				)
			);
		
	btnDiv.appendChild(
			createButton(
				'Set Mode', 
				function(){
					/*var targetMode = mdrop.options[mdrop.selectedIndex].value;*/
					var targetMode = '';
					if(isSelected('divmodeclient')){
						targetMode = 'client';
					} else {
						targetMode = 'limited-ap';
					}
					switchMode(targetMode, 'Your device is now in '+ getDisplayText(targetMode) +' mode. You are now logged out. Please re-connect to the device using your new wireless settings. ');
				}, 
				'btn'
			)
		);
	
	populateModeSelection();
	
	hideAllBut('mode', appMode);
	
	
	/*
	 * The following commented code was used to display the current mode in the mode selection screen.
	 * However, this is redundant since we already display the current mode in the footer.
	 * 
	 *  Hence, commenting it out. This piece of code is a target for deletion in future passes. 
	 */
	/*
	if(nwConfXml == null){
		var modexhr = initializeXhr();
		ajaxCall(
				modexhr, 
				AJAX_METHOD_GET,
				GS_CONF_API,
				null,
				function(){
					nwConfXml = parseResponse(modexhr.responseXml, modexhr.responseText);
					var currentMode = nwConfXml.getElementsByTagName('mode');
					if(currentMode && currentMode.length > 0){
						var aSpan = createSpan(getDisplayText(currentMode[0].firstChild.nodeValue), '', 'gsspan');
						hDiv.appendChild(aSpan);
					}
				}
		);
	}
	else{
		var currentMode = nwConfXml.getElementsByTagName('mode');
		if(currentMode && currentMode.length > 0){
			var aSpan = createSpan(getDisplayText(currentMode[0].firstChild.nodeValue), '', 'gsspan');
			hDiv.appendChild(aSpan);
		}
	}
	*/
	
}

/**
 * Set the mode of operation
 * @param targetMode The mode to set
 * @param msg The message to display on completion.
 */
function switchMode(targetMode, msg){
	var modeXml = createXmlDoc('network');

	var mode = modeXml.createElement('mode');
	mode.appendChild(modeXml.createTextNode(targetMode));
	modeXml.documentElement.appendChild(mode);
	
	
	ajaxCall(
			initializeXhr(), 
			AJAX_METHOD_POST, 
			GS_CONF_API, 
			modeXml, 
			function() {
				/*
				 * Every time we do a POST, re-initialize the corresponding global XML to empty.
				 * This forces a GET next time to ensure that pre-populated values are up-to-date. 
				 */
				nwConfXml = null;
				var stat = document.getElementById('status');
				clearNode(stat);

				var hDiv = createDiv(stat, '', '', msg, 'finalmsg');
				/*stat.appendChild(createButton('Home',function(){dispProLandingScreen();},'btn'));*/
				hideAllBut('status', appMode);
				if(appMode == MODE_PRO){
					hideFooter();
				}
			}
	);

}

function populateModeSelection(){
	if(nwConfXml == null){
		var modexhr = initializeXhr();
		ajaxCall(
				modexhr, 
				AJAX_METHOD_GET,
				GS_CONF_API,
				null,
				function(){
					nwConfXml = parseResponse(modexhr.responseXml, modexhr.responseText);
					doPrepopulation(nwConfXml);
				}
		);
	}
	else{
		doPrepopulation(nwConfXml);
	}
}

function doPrepopulation(nwXml){
	var currentMode = getTagContent(nwXml, 'mode');
	if(currentMode == 'client'){
		populateRadio('divmodeclient');
	} else if (currentMode == 'limited-ap'){
		populateRadio('divmodelimap');
	}
}

function selectRadio(id){
	var moderadio = document.getElementById(id);
	if(moderadio){
		moderadio.checked = true;
	}
}