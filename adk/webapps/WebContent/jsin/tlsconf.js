;
/*var gsTlsConfApi = '/gainspan/profile/tls/config.xml';*/
var GS_TLSCONF_API = '/gainspan/profile/tls/config';
var tlsConfigXml = null;


/*
 * Displays the TLS configuration screen.
 */
function dispTlsScreen(){
	var tlsscreen = document.getElementById('tlsscreen');
	clearNode(tlsscreen);
	//hideAllBut('tlsscreen');
	
	createIPAdrRow(tlsscreen, 'ipDataServer', 'Data Server IP Address: ');
	createFieldRow(tlsscreen, 'Data Period (seconds): ', createTextBox('txtDataPeriod'));
	
	var typeDrop = createDropDown('ddType');
	addDropDownItem(typeDrop, 0, 'udp', 'UDP', true);
	addDropDownItem(typeDrop, 1, 'tcp', 'TCP', false);
	addDropDownItem(typeDrop, 2, 'http', 'Http', false);
	addDropDownItem(typeDrop, 3, 'https', 'Https', false);
	addDropDownItem(typeDrop, 4, 'http formatted', 'Formatted Http', false);
	addDropDownItem(typeDrop, 5, 'https formatted', 'Formatted Https', false);
	
	createFieldRow(tlsscreen, 'Data Type: ', typeDrop);
	createFieldRow(tlsscreen, 'Data Port: ', createTextBox('txtDataPort'));
	createIPAdrRow(tlsscreen, 'ipSnmpServer', 'SNMP Server IP Address: ');
	createIPAdrRow(tlsscreen, 'ipSntpServer', 'SNTP Server IP Address: ');
	
	var btnDiv = createDiv(tlsscreen, 'divSaveBtn');
	btnDiv.appendChild(
			createButton(
					'Save', 
					function(){
						var confirmString = 'The following settings will be applied. Are you sure you want to proceed?\n\n';
						var dataServerIP = getConcatIP('ipDataServer');
						var snmpServerIP = getConcatIP('ipSnmpServer');
						var sntpServerIP = getConcatIP('ipSntpServer');
						var dataPort = getContentOfId('txtDataPort');
						var dataPeriod = getContentOfId('txtDataPeriod');
						var typeDrop = document.getElementById('ddType');
						var dataType = typeDrop.options[typeDrop.selectedIndex].value;
						
						confirmString += ('Data Server IP: '+dataServerIP+'\n');
						confirmString += ('Data Period: '+dataPeriod+'\n');
						confirmString += ('Data Port: '+dataPort+'\n');
						confirmString += ('Data Type: '+dataType+'\n');
						confirmString += ('SNMP Server IP: '+snmpServerIP+'\n');
						confirmString += ('SNTP Server IP: '+sntpServerIP+'\n');
						
						if(confirm(confirmString)){
							var postXml = constructTlsConfigXml(dataServerIP, dataPeriod, dataPort, dataType, snmpServerIP, sntpServerIP );
							postTlsConfig(postXml);
						}
					}, 
					'btn'
				)
		);
	
	ajaxCallForTlsConfig();
	
}

/*
 * Constructs the XML for the TLS configuration.
 */
/*
function constructTlsConfigXml(){
	var typeDrop = document.getElementById('ddType');
	var dataType = typeDrop.options[typeDrop.selectedIndex].value;
	var postXml = createXmlDoc('tls_params');
	appendXmlElement(postXml, postXml.documentElement, 'data_server_ip', getConcatIP('ipDataServer'));
	appendXmlElement(postXml, postXml.documentElement, 'snmp_server_ip', getConcatIP('ipSnmpServer'));
	appendXmlElement(postXml, postXml.documentElement, 'sntp_server_ip', getConcatIP('ipSntpServer'));
	appendXmlElement(postXml, postXml.documentElement, 'data_port', getContentOfId('txtDataPort'));
	appendXmlElement(postXml, postXml.documentElement, 'data_period', getContentOfId('txtDataPeriod'));
	appendXmlElement(postXml, postXml.documentElement, 'data_type', dataType);
	
	return postXml;
}
*/

function constructTlsConfigXml(dataServerIP, dataPeriod, dataPort, dataType, snmpServerIP, sntpServerIP){
	var postXml = createXmlDoc('tls_params');
	appendXmlElement(postXml, postXml.documentElement, 'data_server_ip', dataServerIP);
	appendXmlElement(postXml, postXml.documentElement, 'snmp_server_ip', snmpServerIP);
	appendXmlElement(postXml, postXml.documentElement, 'sntp_server_ip', sntpServerIP);
	appendXmlElement(postXml, postXml.documentElement, 'data_port', dataPort);
	appendXmlElement(postXml, postXml.documentElement, 'data_period', dataPeriod);
	appendXmlElement(postXml, postXml.documentElement, 'data_type', dataType);
	
	return postXml;
}

/*
 * POSTs the TLS configuration XML.
 */
function postTlsConfig(postXml){
	
	
	ajaxCall(
			initializeXhr(), 
			'POST', 
			GS_TLSCONF_API, 
			postXml, 
			function() {
				/*
				 * Every time we do a POST, re-initialize the corresponding global XML to empty.
				 * This forces a GET next time to ensure that pre-populated values are up-to-date. 
				 */
				tlsConfigXml = null;
				backToHomePage();
			}
	);
}

function backToHomePage(){
	window.location = 'index.html';
}

/*
 * Pre-populates the TLS configuration screen fields.
 */
function populateTlsConfig(tlsConfigXml){
	var tlsConfRoot = tlsConfigXml.getElementsByTagName('tls_params');
	if(tlsConfRoot && tlsConfRoot.length > 0){
		setIpAddress('ipDataServer', getTagContent(tlsConfRoot[0], 'data_server_ip'));
		setFieldContent(document.getElementById('txtDataPeriod'), getTagContent(tlsConfRoot[0], 'data_period'));
		setFieldContent(document.getElementById('txtDataPort'), getTagContent(tlsConfRoot[0], 'data_port'));
		setIpAddress('ipSnmpServer', getTagContent(tlsConfRoot[0], 'snmp_server_ip'));
		setIpAddress('ipSntpServer', getTagContent(tlsConfRoot[0], 'sntp_server_ip'));
		var dataType = getTagContent(tlsConfRoot[0], 'data_type');
		var dropType = document.getElementById('ddType');
		dropType.selectedIndex = getIndexFor(dataType);
		
	}
}


function getIndexFor(dataType){
	switch (dataType) {
	case 'udp':
		return 0;
		break;

	case 'tcp':
		return 1;
		break;
		
	case 'http':
		return 2;
		break;
		
	case 'https':
		return 3;
		break;
		
	case 'http formatted':
		return 4;
		break;
		
	case 'https formatted':
		return 5;
		break;
		
	default:
		return 0;
	}
}

/*
 * GETs the TLS configuration XML. Used for pre-populating the fields.
 */
function ajaxCallForTlsConfig(){
	if(tlsConfigXml == null){
		var tlsxhr = initializeXhr();
		ajaxCall(
				tlsxhr, 
				'GET',
				GS_TLSCONF_API,
				null,
				function(){
					tlsConfigXml = parseResponse(tlsxhr.responseXml, tlsxhr.responseText);
					populateTlsConfig(tlsConfigXml);
				}
		);
	}
	else{
		populateTlsConfig(tlsConfigXml);
	}
	
}