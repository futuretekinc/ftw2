How to measure the throughput using SPI-DMA
-------------------------------------------

On Host(GS2011 D1) Side:
---------------------------

1. Download the host app binary to GS2011-D1 board.
2. Use superblock which is available in the same folder.
3. Open a terra-term and connect to the host GS2011-uart0 with baud 9600
4. Power cycle the host .

On node(GS2011) side.
---------------------
1. Load the SPI-DMA binary
2. Connect its SPI0 lines to the host SPI0.
 	j19 (GS2011) or J16 (GS2100M) HOST      j19(I0 OF GS2000 SLAVE EVB)

    	PIN5 SPIO DOUT  .........               PIN8(SPIO DIN)
    	PIN8 SPIO DIN   .........               PIN5(SPIO DOUT) 
    	PIN7 SPI0 CLK   .........               PIN7(SPI0 CLK) 
    	PIN9 SPI0 CS0   .........               PIN9(SPI0 CS0)
    	GPIO37(SDIO_DAT1_INT) .....             GPIO37(SDIO_DAT1_INT)
    	MODULE_GND        .........             MODULE_GND


3. Power cycle the GS2011 with SPI-DMA.


Now Serial2WiFi message comes on the host terra-term and it accepts all AT commands;

To measure the throughput:
-------------------------

1. Set the mac address
   AT+NMAC=00:1d:c9:01:55:55
2. make dhcp enable
   AT+NDHCP=1
3. Connect to an AP
   AT+WA=<ssid>
4. make radio in active mode
   AT+WRXACTIVE=1
5. switch off echo
   ATE0

For UDP:
-------
On the Remote PC side (Uses Hercules Serial terminal SW which can be downloaded from http://www.hw-group.com/products/hercules/index_en.html):
----------------------
1. start the hercules as udp with remote ip as the node ip and ports as the local and remote port given with the AT commands to create the udp connection on GS2011 side.
2. This PC should be connected to the same AP(better to coonect via wire for better throughput)

On the GS2011 side:
-------------------

1. start a udp client
   AT+NCUDP=<remote pc ip>,<remote port>,<local port> 
2. enable throughput 
   AT+THROUGHPUT=<enable>,<pkt size>,<pkt numbers in 6 char format>
   AT+THROUGHPUT=1,1024,009999
   ESC<Z><cid><1024><data of 1024 bytes>
   --> it internally sends out 9999 packets to the udp server and 
       calculate the time and speed and prints the throughput in kbps


For TCP:
-------
On the Remote PC side:
----------------------
1. start the hercules as tcp server with port given with the AT commands to create the tcp connection on GS2011 side.
2. This PC should be connected to the same AP(better to coonect via wire for better throughput)

On the GS2011 side:
-------------------

1. start a TCP client
   AT+NCTCP=<remote pc ip>,<remote port>
2. enable throughput 
   AT+THROUGHPUT=<enable>,<pkt size>,<pkt numbers in 6 char format>
   AT+THROUGHPUT=1,1024,009999
   ESC<Z><cid><1024><data of 1024 bytes>
   --> it internally sends out 9999 packets to the udp server and 
       calculate the time and speed and prints the throughput in kbps


note:
   The packet size cannot be changed now and it is fixed as 1024
   the data send with ESC <Z> should be exactly matching with the length field(1024)
   one can change the pkt numbers using the AT+THROUGHPUT command without closing the existing udp/tcp connection.

Limitaion:
   The througput command has limited to only TX from GS2011.it never excepts any incomming data(wifi-to -GS2011)
