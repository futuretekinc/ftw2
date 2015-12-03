SDIO HostAPP Setup:

1. Install the resesas setup to the PC(Renesas Starter Kit for sh7269)

2. UnZip the sw package(sh7269_sdio_host_sample.zip) to D:\\Sw-test\sh7269_sdio_host_sample

3. Go to D:\\sh7269_sdio_host_sample and open the project sh7269_sdio_host_sample.hws, it opens, the same in
    the renesas IDE-High performance Embedded Workshop.

4. compile the project and download to the sh7269 connected to the PC via debugger.

5. Connect the sh7269 serial port to the PC via usb cable and it is detected on the PC as a serial port.
   Open a serial terminal program with baud 115200 at this port.

6. Now run the program on the sh7269 via debugger and the serial terminal displays the initial message as:

    SH7269 SDIO HOST Sample Program. Ver.1.00.00
    Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.


    Waiting for SD Card Insertion...

7. switch on the GS2000 loaded with sdio s2w binaries.
8. Connect the Gs2000 SDIO lines to sh7269 sdio via a sdio card connector.then the serial terminal shows the message as:

   SD-cd-int
   [SD] card inserted!
   [SD] card mount OK


    Serial2WiFi APP
SDIO>

9. Now the host app is ready and it will acts as a bridge between the uart(serial terminal) and sdio.the serial terminal 
   will accept all std s2w commands and it returns the response.

Note:
the host app is bridge application and it acts as bridge between the uart and sdio...

some serial captures are given below:
-----------------------------


SDIO>
at+nstat=?
at+nstat=?
MAC=00:1d:c9:00:00:00
WSTATE=NOT CONNECTED    MODE=NONE
BSSID=00:00:00:00:00:00   SSID="" CHANNEL=NONE   SECURITY=NONE
RSSI=0
IP addr=0.0.0.0   SubNet=0.0.0.0  Gateway=0.0.0.0
DNS1=0.0.0.0       DNS2=0.0.0.0
Rx Count=0     Tx Count=0

OK

SDIO>
at+ws
at+ws
       BSSID              SSID                     Channel  Type  RSSI Security

 00:23:69:a4:07:93, gs2000_t50                      , 01,  INFRA , -63 , WPA2-PE                             RSONAL
 68:7f:74:52:6f:d4, GainSpan2                       , 01,  INFRA , -75 , WPA2-PE                             RSONAL
 00:23:69:a4:10:c9, GSDemo_B                        , 01,  INFRA , -62 , WPA2-PE                             RSONAL
 00:22:75:56:18:d2, KAI                             , 01,  INFRA , -80 , WPA2-PE                             RSONAL
 00:1d:c9:03:07:07, GSDemo_AP123                    , 06,  INFRA , -52 , NONE
 58:6d:8f:78:78:d8, batman                          , 06,  INFRA , -59 , NONE
 00:25:9c:18:4e:bf, kruthikAP                       , 09,  INFRA , -77 , NONE
 00:25:9c:18:5c:36, gs2k                            , 11,  INFRA , -36 , NONE
 bc:f6:85:43:6a:48, ipv6-test                       , 11,  INFRA , -50 , NONE
 98:fc:11:94:4a:d4, GainSpan                        , 11,  INFRA , -40 , WPA2-PE                             RSONAL
No.Of AP Found:10

OK

SDIO>
SDIO>
at+ndhcp=1
at+ndhcp=1
OK

SDIO>
at+wa=gs2k
at+wa=gs2k
    IP              SubNet         Gateway
 192.168.1.101   255.255.255.0   192.168.1.1

OK

SDIO>
at+nstcp=1234
at+nstcp=1234
CONNECT 0

OK

SDIO>

CONNECT 0 1 192.168.1.100 4535




