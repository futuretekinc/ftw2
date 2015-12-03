Introduction
------------
This application helps demonstrate the following features
* HTTP RESTful TLS
* Zeroconf and Discovery
* HTTP RESTful API's for Provisioning
* OTA Firmware Update

Application Lifecycle
* The application starts by default in Limited AP mode. In this mode a user can
  connect to the device and configure it. 
* Once provisioned, the application can function in either AP or Client mode. In
  both modes the application makes services available via DNS-SD and allows
  interaction with clients via its HTTP API. 
* OTAFU is also available in both modes.

Installation and Interaction with Application
---------------------------------------------
* Install gs2000_app binary.
* Install super block, control block, wlan binary, and web pages on module flash.
* Connect to the embedded application using the SSID configured in source code
* If you have "Bonjour" plug-in for IE or DNS-SD add-on for Firefox, you 
  will be able to discover the provisoning and TLS services automatically.
  Clicking on the services will take you to the web application.
* You can also use the iOS and Android apps to interact with the embedded
  application. Please refer to the README of the respective apps for more
  information.

IMPORTANT
---------
* The default build will generate an image with MAC address 00:1d:c9:aa:bb:cc
  and SSID TLS_GS2K_aabbcc. This MUST be modified to the appropriate values
  in order for the the system to work correctly. If not, the behavior is 
  undefined.

Building the TLS Server Application
-----------------------------------
* This can be built in IAR. The top-level project is 
  afw\adk\tls\build\tls.eww. The output files are gs2000_app.bin.
* NOTE: Building the above project using FLASH_FETCH compile time flag
  and selecting "app_flashFetch.icf" under linker options in tls workspace
  generates binary app.bin which runs from flash. 
  For generating gs2000_app.bin, "app_image_builder.exe" tool should be used.
  
Build Options
-------------
Some useful build options that can be modified in the project file are:
Feature(Flag): Description
* ADK_IOT_GATEWAY_ENABLE : To enable/disable connecting to IOT gateway server i.e POST TLS
  readings to the IOT Gateway Server.
  This is DISABLED by default.To ENABLE, add ADK_IOT_GATEWAY_ENABLE flag 
  in "prefetch" workspace and "tls" workspace. Also the app_iot_gateway_updater.c
  should be pulled into prefetch for compilation.
* ADK_IOT_COAP : To enable/disable posting of TLS readings to IOT server using COAP.
  This is DISABLED by default. Hence HTTP is used for communication.
  To ENABLE, add ADK_IOT_COAP flag in "prefetch" workspace and "tls" workspace.
* ADK_CLOUD_ENABLE : To enable/disable connecting to EXOSITE cloud server i.e POST TLS
  readings to the CLOUD.This is DISABLED by default.To ENABLE, add ADK_CLOUD_ENABLE flag 
  in "prefetch" workspace and "tls" workspace. 
* Group Provisioning (ADK_PROV_GROUP_SECURE): To enable/disable 
  group provisioning functionality.
  This is DISABLED by default. To ENABLE, add ADK_PROV_GROUP_SECURE flag 
  in "prefetch" workspace and "tls" workspace
* Filesystem upload (ADK_FS_UPLOAD_ENABLE): To enable/disable 
  filesystem upload functionality.
  This is ENABLED by default. To DISABLE, remove ADK_FS_UPLOAD_ENABLE flag 
  in "prefetch" workspace
* WPS Support (ADK_PROV_WPS_ENABLE): To enable/disable WPS support.
  This is ENABLED by default. To disable, remove ADK_PROV_WPS_ENABLE flag from "prefetch" workspace
* Provisioning(ADK_PROV_ENABLE): To enable/disable Provisioning. 
  This is ENABLED by default. To disable, remove ADK_PROV_ENABLE flag 
  from "prefetch" workspace
* OTAFU (ADK_OTAFU_ENABLE): To enable/disable OTAFU. 
  This is ENABLED by default. To disable, remove ADK_OTAFU_ENABLE flag 
  from "prefetch" workspace and "tls" workspace
 
 Other build options can be found in the project files of "prefetch"
 and "tls" workspace.

Parameters/Behavior that can be modified in source code
------------------------------------------------------------
* App_default_config.h contains the default definitions of MAC address, SSID.
* Connection management behavior can be controlled by modifying defaults in 
  App_default_config.h and by modifying the sources in src/sm/App_sm.c and 
  src/ncm/app_ncm.c

HTTP API and Data Format
------------------------
* Resource: Temperature, Light, Battery and RSSI values
  URI: http://<ip>/gainspan/profile/tls
  Methods: GET
* Resource: Gainspan system services
  URI: http://<ip>/gainspan/system/<services>  (services like config)
  Methods: GET, POST (POST is overloaded to serve as PUT)
* Data format is XML by default
* The TLS resource can also send data in JSON if the appropriate compile time
  option is set. The Web and Mobile applicaitons are capable of handling both 
  formats. The compiler option is APP_API_JSON and is set in app_http_api.c
  