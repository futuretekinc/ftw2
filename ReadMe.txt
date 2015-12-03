The SDK package contains various folders.  Below is a short description of what is included in some of the folders.

ADK 		--- Includes the embedded source code for provisioning, OTAFU and Temperature and Light Sensor(TLS)
		    Hostless Applications. It also includes web page/web app sources.
		    Batch scripts are included in TLS application for creating single image and programming the 
		    GS2k module.

Documentation	--- Includes the Appication programmers guide, User guides, GEPS API documentation, Sample examples 
		    for S2W and TLS, manual for the evaluation board

EVB Schematics	--- Includes the schematic of the EVB board and User guide. 

Geps		--- Includes Geps and rom/patch libraries and header files. 

Tools		--- Includes the GS2K programming tool and the user guide for that tool. Also included are File system
		    image creator tool that can be used for creating web image etc. 

Userapps	--- Includes the source code for Serial to Wi-Fi and Firmware binary file (built based on configuration
		    selected while building package) that can be programmed into the GS2K module. It is a single image
		    that includes the WLAN, S2W and Web pages. Batch scripts are also includes for creating single image
		    and programming the GS2k module.

Userlib		--- Includes source code for network connection manager.

Wfw		--- Includes WLAN firmware image.

Hostapp		--- This folder includes two host sample source code examples, one when using SDIO and second when using
                    SPI with DMA firmware on the GS2K module.
                    SDIO - This includes the Renesas SH7269 host application if using SDIO on the Renesas SH7269 Board. In this example
                    the sample code on the SH7269 acts as a SDIO to UART bridge, so once can use a serial terminal on a PC to send AT
		    commands
		    SPI_DMA - This host app is using a GS2K EVB as a host connecting to another GS2K EVB as client
		    The GS2K EVB boards can be connected over SPI0.  See the readme document in that folder for details


Follow the steps in the SDK IAR Install and I-JET debugger document to get familiar with how to install IAR, use the debugger 
and compile and load code into the GS2K modules.