
/*
 * The version of the API that this application is compatible with.
 */
var API_VERSION = 0.9;
var PROVISIONING_WEBAPP_VERSION = '0.9.19';

/*
 * The prefix for the REST API URL. 
 */
 var GS_AP_PREFIX = '/gainspan/system';
 
 /*
  * The REST API URL for AP List.
  */
 var GS_APLIST_API = GS_AP_PREFIX+'/prov/ap_list';
 
 /*
  * The REST API URL Network Configuration.
  */
 var GS_CONF_API = GS_AP_PREFIX+'/config/network';
 
 /*
  * The REST API URL for Scan parameters.
  */
 var GS_SCANPARAMS_API = GS_AP_PREFIX+'/prov/scan_params';
 
 /*
  * The REST API URL for Web server settings.
  */
 var GS_ADMIN_API = GS_AP_PREFIX+'/config/httpd';
 
 /*
  * The REST API URL for API Version.
  */
 var GS_VERSION_API = GS_AP_PREFIX+'/api/version';
 var GS_WPS_API = GS_AP_PREFIX + '/prov/wps';
 var GS_FIRMWARE_API = GS_AP_PREFIX + '/firmware/version';
 var GS_SYSID_API = GS_AP_PREFIX + '/config/id';
 var GS_TIME_API = GS_AP_PREFIX + '/time';
 var GS_OTAFU_API = GS_AP_PREFIX + '/config/otafu';
 var GS_SSLCERTS_API = GS_AP_PREFIX+'/certs';
 var GS_TIME_OUT_MILLISECONDS = 10 * 1000;

 /*
  * App-wide Network configuration XML object.
  */
var nwConfXml = null;

/*
 * App-wide Scan parameters XML object.
 */
var scanParamsXml = null;

/*
 * App-wide Web server configuration XML object.
 */
var adminXml = null;

/*
 * App-wide WPS configuration XML object.
 */
var wpsXml = null;
var fwXml = null;
var sysIdXml = null;
var otafuXml = null;


var systemHttpApiVersion = '';


var AJAX_METHOD_GET = 'GET';
var AJAX_METHOD_POST = 'POST';

var MODE_PRO = 'modePro';
var MODE_CLIENT = 'modeClient';
var MODE_AP = 'modeLimitedAp';