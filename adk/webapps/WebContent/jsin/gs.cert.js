/**
 * Constructs a certificate upload form.
 * @param parent The parent container in which to create the certificate upload form.
 */
/*
function constructCertificateUploadForm(parent){
	var certForm = createForm('certpost', '/gainspan/system/wpacert', 'POST', 'multipart/form-data');
	parent.appendChild(certForm);
	
	createDiv(certForm, '', '', 'Please upload certificates in DER format only.');
	createFieldRow(certForm, 'CA Root Certificate:', createFileInput('TLS_CA'));
	createFieldRow(certForm, 'Client Certificate:', createFileInput('TLS_CLIENT'));
	createFieldRow(certForm, 'Client Key:', createFileInput('TLS_KEY'));
	
	
	createDiv(certForm).appendChild(createButton('Upload'));
	
	
}
*/

/*
function isEapTls(){
	var queryString = window.location.search.substring(1); 
	if(queryString && queryString != ''){
		var firstQueryParam = queryString.split('&')[0];
		if(firstQueryParam && firstQueryParam != ''){
			var keyvalue = firstQueryParam.split('=');
			if(keyvalue[0] == 'ssltls' && keyvalue[1] == 'true'){
				return true;
			}
		}
	}
	return false;
}
*/

/*
 * Export the variables/functions which would be referenced from outside the combined JS.
 * This is required for closure compiler for advanced minification.
 */
/*
window['constructCertificateUploadForm']=constructCertificateUploadForm;
*/
