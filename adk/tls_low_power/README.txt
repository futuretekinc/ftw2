Introduction
------------
This application helps demonstrate the following features
* Ultra Low Power by Loading Code on Demand
* Doing Deep Sleep or Standby whenever possible
* Network Data Communication - Push to server using UDP / COAP to IOT gateway

Application Lifecycle
* The TLS low power app starts in client mode, i.e connects to an access point called GainSpanDemo
* The app wakes up every X sec (X= 5).
* Loads the basic APP code required for power on and stabilization
* Powers on the sensors and starts a timer (100ms) for stabilization to complete
* Goes to DeepSleep
* At the timeout, does the sensor reading (as of now this reading is discarded)
* Every Y (Y=2) wakeup, it loads the network stack and other required app code
* Releases Reset to WLAN allowing WLAN to run and fetch the code and gives Boot Indication to the WLAN
* Does a sensor reading and sends the data to the server
* Goes to standby

IMPORTANT
---------
* The default build will generate an image with MAC address 00:1d:c9:aa:bb:cc
  and SSID TLS_GS2K_aabbcc. This MUST be modified to the appropriate values
  in order for the the system to work correctly. If not, the behavior is 
  undefined.

Building the TLS Server Application
-----------------------------------
* This can be built in IAR. The top-level project is 
  afw\adk\tls-low-power\build\tls.eww. The output files are app.bin and app.map
* NOTE: The TLS Low Power application can be run only in flash fetch mode
  For generating gs2000_app.bin, "image_builder_postFetch.exe" tool should be used.
  
Build Options
-------------
Some useful build options that can be modified in the project file are:
Feature(Flag): Description
* ADK_IOT_GATEWAY_ENABLE : To enable/disable connecting to IOT gateway server i.e POST TLS
  readings to the IOT Gateway Server.
  This is DISABLED by default.To ENABLE, add ADK_IOT_GATEWAY_ENABLE flag 
  in "postfetch" workspace and "tls" workspace.
* ADK_IOT_COAP : To enable/disable posting of TLS readings to IOT server using COAP.
  This is ENABLED by default. If DISABLED ,HTTP is used for communication.
  To DISABLE, add ADK_IOT_COAP flag in "postfetch" workspace and "tls" workspace.
 * ULTRA_LOW_POWER : To enable/disable going into ultra low power mode (260nA mode).
  This is DISABLED by default.To ENABLE, add ADK_IOT_GATEWAY_ENABLE flag 
  in "postfetch" workspace, "prefetch" and "tls" workspace.
  
 Other build options can be found in the project files of "postfetch"
 and "tls" workspace.

Parameters/Behavior that can be modified in source code
------------------------------------------------------------
* App_default_config.h contains the default definitions of MAC address, SSID.
* Connection management behavior can be controlled by modifying defaults in 
  App_default_config.h and by modifying the sources in src/sm/App_sm.c and 
  src/ncm/app_ncm.c
  