typedef GSN_STATUS
(* GsnDhcpSrvr_Start_FP_T)(GSN_DHCP_SRVR_T *dhcpSrvr, GSN_DHCP_SRVR_CFG_T *dhcpSrvrCfg);
 extern  _RPST_ GsnDhcpSrvr_Start_FP_T GsnDhcpSrvr_Start_FP;

typedef GSN_STATUS
(* GsnDhcpSrvr_Stop_FP_T)(GSN_DHCP_SRVR_T *dhcpSrvr);
extern  _RPST_ GsnDhcpSrvr_Stop_FP_T GsnDhcpSrvr_Stop_FP;

typedef GSN_STATUS
(* GsnDhcpSrvr_ClientDelete_FP_T)(GSN_DHCP_SRVR_T *pDhcpSrvr,GSN_MAC_ADDR_T* macAddr);
extern  _RPST_ GsnDhcpSrvr_ClientDelete_FP_T GsnDhcpSrvr_ClientDelete_FP;

typedef UINT8
(* GsnDhcpSrvr_ClientQuery_FP_T)(GSN_DHCP_SRVR_T *pDhcpSrvr, GSN_DHCP_SRVR_CLIENT_T* clients, UINT8 buffCount);
extern  _RPST_ GsnDhcpSrvr_ClientQuery_FP_T GsnDhcpSrvr_ClientQuery_FP;