Introduction
------------
The cloud connect module provides the common functionality required to conenct
Gainspan embedded applications to the cloud. 
Currently connectivity to Exosite cloud is supported.
The ADK's supported for cloud connectivity are:
 * TLS
 * Smartplug
 
API's
-----
The basic set of API's are defined in gsn_cloud_api.h. These include API's for
* Initialization - Gsn_CloudApiInit()
* Activating of device on cloud - Gsn_CloudActivateDevice()
* POSTing of data on to cloud - Gsn_cloudPostUdpates()

Applications initialize the cloud connectity library for use by providing
information about the ADK type (TLS, Smartplug) as well as a callback function
that can be used to extract application specific information such as CIK, UUID
and application data that has to be POSTED.

The cloud connect module is also aware of application specific data (TLS, 
Smartplug) and can format them appropriately before dispatching to the cloud.
So, the cloud connect library is actually aware of the applications that it
supports and has a tight coupling to them.

The cloud connect library also exposes a second level of API's that can be 
useful for applications that expect the library to handle the regular dispatch
of data to the cloud. These API's are
* Start cloud updates - Gsn_CloudUpdaterStart()
* Stop cloud upates -  Gsn_CloudUpdaterStop()
When Gsn_CloudUpdaterStart() is called, the library creates a thread which sends
updates to clouds on a regular basis. Before sending updates, the callback
function regsitered by the application is used to fetch application data and
then POST it to the cloud. 