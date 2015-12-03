

/**
 * Initializes a cross-browser XHR object
 * 
 * @returns A cross-browser XHR object.
 */
function initializeXhr(){
	var xhr = false;
	try {
	  xhr = new XMLHttpRequest();
	} catch (trymicrosoft) {
	  try {
	    xhr = new ActiveXObject("Msxml2.XMLHTTP.3.0");
	  } catch (othermicrosoft) {
	    try {
	      xhr = new ActiveXObject("Microsoft.XMLHTTP");
	    } catch (failed) {
	      xhr = false;
	    }
	  }
	}

	if (!xhr)
	  alert("Error initializing XMLHttpRequest!");
	
	return xhr;
}

/*
 * Helper method to create a most suitable Microsoft XML DOMDocument
 * Used for IE
 */
function createMsXmlDoc () {
    if (typeof (ActiveXObject) != "undefined") {
        var progIDs = [
                        "Msxml2.DOMDocument.6.0", 
                        "Msxml2.DOMDocument.3.0", 
                        "MSXML2.DOMDocument", 
                        "MSXML.DOMDocument"
                      ];
        for (var i = 0; i < progIDs.length; i++) {
            try { 
                return new ActiveXObject(progIDs[i]); 
            } catch(e) {};
        }
    }
    return null;
}

/**
 * 
 * @param rootName
 *            The name of the XML root element
 * @returns A cross-browser XML document object with the specified root.
 */
function createXmlDoc (rootName) {
    if (!rootName) {
        rootName = "";
    }
    
    /*
	 * First, try creating MS DOMDocument.
	 */
    var xmlDoc = createMsXmlDoc ();
    if (xmlDoc) {
        if (rootName) {
            var rootNode = xmlDoc.createElement (rootName);
            xmlDoc.appendChild (rootNode);
        }
    }
    
    /*
	 * If unsuccessful, then it is non-IE browser. Use standard DOM API to
	 * create the document.
	 */
    else {
        if (document.implementation.createDocument) {
            xmlDoc = document.implementation.createDocument ("", rootName, null);
        }
    }
    
    return xmlDoc;
}


/*
function ajaxCall (xhr, method, url, data, callback){
	if(method != 'POST'){
		xhr.onreadystatechange = function(){
			try {
				if (xhr.readyState === 4) {
				  if (xhr.status === 200) {
					callback();
				  } else {
					alert('There was a problem with the request: xhr.status = '+xhr.status);
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
		xhr.open(method, url, true);
	}
	else {
		xhr.open(method, url, false);
		xhr.setRequestHeader("Content-Type","text/xml");
	}

	xhr.send(data);
	if(method == 'POST'){
		callback();
	}
}
*/
/**
 * Wrapper around XMLHttpRequest open and send methods
 * 
 * @param xhr -
 * 			An XHR object to be used for the AJAX call
 * @param method -
 *            the HTTP Method to use. Currently takes 'GET' and 'POST' only
 * @param url -
 *            the URL for the AJAX call
 * @param data -
 *            In case of 'POST' requests, the data to send. Can be XML
 * @param callback -
 *            Callback function to execute. In case of Async requests, it is
 *            executed on ready state change. In case of sync (POST) requests, it
 *            is executed after the POST completes.
 */
function ajaxCall (xhr, method, url, data, callback, timeout){
	var effectiveTimeOut = GS_TIME_OUT_MILLISECONDS;
	if(timeout){
		effectiveTimeOut = timeout;
	}
	var xhrTimeout = setTimeout(
			function(){
				ajaxTimedOut(xhr);
			},
			effectiveTimeOut
		);
	
	xhr.onreadystatechange = function(){
		try {
			if (xhr.readyState === 4) {
			  if (xhr.status === 200) {
				  clearTimeout(xhrTimeout);
				  
				  /*
				   * If it is a GET request, call the callback function after we receive the response.
				   * Don't do this for POST requests, since we want to handle POSTs synchronously. 
				   */
				  if(method == 'GET'){
					  callback();
				  }
			  } else {
				/*alert('There was a problem with the request: HTTP Error = '+xhr.status);*/
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
	
	var isAsync = true;
	if(method == 'POST'){
		isAsync = false;
	}
	xhr.open(method, url + '?t=' + new Date().getTime(), isAsync);


	if(method == 'POST'){
		xhr.setRequestHeader("Content-Type","text/xml");
	}

	xhr.send(data);
	
	
	/*
	 * If method is a POST, call the callback function on completion.
	 */
	if(method == 'POST'){
		callback();
	}
}

/**
 * Function called when the XHR request times out.
 */
function ajaxTimedOut(xhr){
	/*
	if(xhr && xhr.abort){
		xhr.abort();
	}
	*/
	alert('The request has timed out. Please ensure that your device is connected to the network.');
}

/**
 * Helper function to create a child XML element with text content,
 * And append it to the specified parent.
 * 
 * @param postXml The XML object.
 * @param parent The parent to which you wish to append a child.
 * @param name The name of the child XML element.
 * @param content The content of the child XML element. 
 */
function appendXmlElement(postXml, parent, name, content){
	
	var elem = postXml.createElement(name);
	elem.appendChild(postXml.createTextNode(content));
	parent.appendChild(elem);
	
}


/**
 * Helper function to parse the response of XMLHttpRequest. Ideally, the
 * responseXml property should hold the desired result. But this is not
 * cross-browser.
 * 
 * Hence, this function is used. It checks if the responseXml is valid, else
 * builds it from responseText property.
 */
function parseResponse (respXml, respTxt) {
    var xmlDoc = respXml;

    /*
	 * if responseXML is not valid, try to create the XML document from the
	 * responseText property
	 */
    if (!xmlDoc || !xmlDoc.documentElement) {
        if (window.DOMParser) {
            var parser = new DOMParser();
            try {
                xmlDoc = parser.parseFromString (respTxt, "text/xml");
            } catch (e) {
                alert ("XML parsing error");
                return null;
            };
        }
        else {
            xmlDoc = createMsXmlDoc ();
            if (!xmlDoc) {
                return null;
            }
            xmlDoc.loadXML (respTxt);

        }
    }
    return xmlDoc;
}

/**
 * Trim the string of its white spaces.
 * @param The String to trim
 * @returns {String} The trimmed string.
 */
function trim(str){
	return str.replace(/^\s\s*/, '').replace(/\s\s*$/, '');
}

/**
 * Tests whether the input is an integer
 * @param input The value to test 
 * @returns {Boolean}
 */
function isInteger(input){
	/*
	 * The second check is required since without it, 
	 * a number that ends with a decimal point returns true.
	 */
	return parseInt(input,10)== input && input.indexOf('.')<0; 
}

/*
 * Helper function for converting the XML document into a format suitable for 
 * displaying in an alert for debugging.
 * 
 * TODO: Remove this function before minification.
 */

/*
function displayXml(postXml){
	var xmlString;
	if( window.ActiveXObject ) {
		// -- Internet Explorer
		xmlString = postXml.xml;
	} else {
		// -- FireFox
		xmlString = ( new XMLSerializer() ).serializeToString( postXml );
	}
	
	alert(xmlString);
}
*/

