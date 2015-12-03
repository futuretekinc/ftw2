var MacCheck = '0';


function toggleCheckBoxById(checkBoxId) {

	if (checkBoxId == 'cbApp1') {
		if (isSelected('cbApp1')) {
			showInline(document.getElementById('App1'));
			showInline(document.getElementById('App2'));
			document.getElementById('App1').parentNode
					.appendChild(createFileInput('app1', 'FileApp1'));
			document.getElementById('App2').parentNode
					.appendChild(createFileInput('app2', 'FileApp2'));

		} else {
			hide(document.getElementById('App1'));
			hide(document.getElementById('App2'));
			removeElement('FileApp1');
			removeElement('FileApp2');
		}
	} else if (checkBoxId == 'cbWLan') {
		if (isSelected('cbWLan')) {
			showInline(document.getElementById('WLan'));
			document.getElementById('WLan').parentNode
					.appendChild(createFileInput('wlan', 'FileWlan'));

			if (MacCheck == '1') {
				showInline(document.getElementById('MacImageText'));
				document.getElementById('MacImageText').parentNode
						.appendChild(createFileInput('MacImageText',
								'FileMacImage'));
			}

		} else {
			hide(document.getElementById('WLan'));
			if (MacCheck == 1) {
				hide(document.getElementById('MacImageText'));
				removeElement('FileMacImage');
			}
			removeElement('FileWlan');
		}
	} else if (checkBoxId == 'cbWebImage') {
		if (isSelected('cbWebImage')) {
			showInline(document.getElementById('WebImage'));
			document.getElementById('WebImage').parentNode
					.appendChild(createFileInput('WebImage', 'FileWebImage'));
		} else {
			hide(document.getElementById('WebImage'));
			removeElement('FileWebImage');
		}
	}
}

function updateMacCheckBox(update) {
	var wlanDisplayString = ' WLan Binaries ';
	var wlanOrMacDisplayString = ' WLan/MAC Binaries ';

	if (update == 0) {
		setContentOfId('wlanDisplaySpan', wlanDisplayString);
		removeElement('MacImageText');
	} else {
		setContentOfId('wlanDisplaySpan', wlanOrMacDisplayString);

	}
}

function showGs2000Ui(){
	var divsToBeRemoved = ['divBackup','divApp1', 'divApp2', 'divWlan', 'divWebPageImage'];
	for (var i=0;i<divsToBeRemoved.length;i++){
		removeElement(divsToBeRemoved[i]);
		/*hide(document.getElementById(divsToBeRemoved[i]));*/
	}
	unHide(document.getElementById('divCombinedImage'));
}


function showPreGs2000Ui(){
	hide(document.getElementById('divCombinedImage'));
	var divsToBeShown = ['divApp1', 'divApp2', 'divWlan', 'divWebPageImage', 'divBackup'];
	for (var i=0;i<divsToBeShown.length;i++){
		unHide(document.getElementById(divsToBeShown[i]));
	}
}

function validatePreGs2000(otafuForm){
	/*
	 * If none of the checkboxes is selected, alert the user and fail
	 * validation.
	 */
	if (!isSelected('cbApp1') && !isSelected('cbWLan')
			&& !isSelected('cbWebImage')) {
		alert('Please Select the binaries to upload');
		return false;
	}

	/*
	 * If App binaries is checked, both App1 andApp2 files MUST be selected.
	 */
	if (isSelected('cbApp1')) {
		var app1 = otafuForm.FileApp1;
		var app2 = otafuForm.FileApp2;

		if (!app1.value || !app2.value || app1.value.length == 0
				|| app2.value.length == 0) {
			alert('Please choose both App1 and App2 binaries');
			return false;
		}
	}

	/*
	 * If WLAN is checked, then the WLAN binary file MUST be selected.
	 */
	if (isSelected('cbWLan')) {
		var wlan = otafuForm.FileWlan;
		var macimage = otafuForm.FileMacImage;

		if (!wlan.value || wlan.value.length == 0) {
			alert('Please choose WLan binary');
			return false;
		}

		if (MacCheck == '1') {
			if (!macimage.value || macimage.value.length == 0) {
				alert('Please choose Mac binary');
				return false;
			}
		}
	}

	/*
	 * If Web Image is checked, then the WEB Image binary file MUST be selected.
	 */

	if (isSelected('cbWebImage')) {
		var webimage = otafuForm.FileWebImage;

		if (!webimage.value || webimage.value.length == 0) {
			alert('Please choose Web Page Image');
			return false;
		}
	}
	
	return true;
}

function ajaxCallForNodeCheck() {
	var explicitTimeOut = 45 * 1000;
	/*
	 * if(timeout){ explicitTimeOut = timeout; }
	 */
	var apxhr = initializeXhr();
	ajaxCall(apxhr, AJAX_METHOD_GET, GS_FIRMWARE_API, null, function() {
		var respXml = parseResponse(apxhr.responseXml, apxhr.responseText);
		var version = respXml.getElementsByTagName('version');
		if (version && version.length > 0) {
			var chip = getTagContent(version[0], 'chip');
			if(chip.indexOf('gs2000') >= 0){
				gs2000 = true;
				/*showGs2000Ui();*/
			}
			else{
				showPreGs2000Ui();
				if (chip.indexOf('gs1500') >= 0 || chip.indexOf('gs1550') >= 0)  {
					MacCheck = '1';
					//				setDisabled('cbWebImage',true);
					//				setDisabled('FileWebImage',true);
					updateMacCheckBox(true);
				} else {
					MacCheck = '0';
					updateMacCheckBox(false);
				}
			}
				
		}
	}, explicitTimeOut);
}

function initialize() {
	ajaxCallForNodeCheck();

}

function setContentOfId(id, content) {
	document.getElementById(id).innerHTML = content;
}



/*
 * Export the variables/functions which would be referenced from outside the
 * combined JS. This is required for closure compiler for advanced minification.
 */
/*window['submitOtafuForm'] = submitOtafuForm;*/
window['toggleCheckBoxById'] = toggleCheckBoxById;
