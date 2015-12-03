/*Lets patch each API with and withot error checking flavours*/

/* This function doesnot have error checking flavour*/
#ifndef NX_FPT_H
#define NX_FPT_H

#include "netx/nx_api.h"
#include "netx/netx_applications/dhcp/nxd_dhcp_client.h"
#include "netx/netx_applications/dns/nxd_dns.h"
#ifndef RPL_SIM
#include "netx/netx_bsd_layer/nxd_bsd.h"
#else
#include "netx/netx_bsd_layer/nxd_bsd.h"
#endif
#ifndef _RPST_
#define _RPST_
#endif

typedef VOID  (* _nx_system_initialize_FP_T)(VOID);
extern _RPST_ _nx_system_initialize_FP_T _nx_system_initialize_FP;

typedef	UINT  (* _nxe_packet_pool_create_FP_T)(NX_PACKET_POOL *pool_ptr, CHAR *name_ptr, ULONG payload_size,
								  VOID *pool_start, ULONG pool_size, UINT pool_control_block_size);
extern _RPST_ _nxe_packet_pool_create_FP_T _nxe_packet_pool_create_FP;

typedef UINT  (* _nx_packet_pool_create_FP_T)(NX_PACKET_POOL *pool_ptr, CHAR *name_ptr, ULONG payload_size,
                             VOID *pool_start, ULONG pool_size);
extern _RPST_ _nx_packet_pool_create_FP_T _nx_packet_pool_create_FP;

typedef UINT  (* _nxe_packet_allocate_FP_T)(NX_PACKET_POOL *pool_ptr,  NX_PACKET **packet_ptr,
                           ULONG packet_type, ULONG wait_option);
extern _RPST_ _nxe_packet_allocate_FP_T _nxe_packet_allocate_FP;

typedef UINT  (* _nx_packet_allocate_FP_T)(NX_PACKET_POOL *pool_ptr,  NX_PACKET **packet_ptr,
                          ULONG packet_type, ULONG wait_option);
extern _RPST_ _nx_packet_allocate_FP_T _nx_packet_allocate_FP;

typedef UINT  (* _nxe_ip_create_FP_T)(NX_IP *ip_ptr, CHAR *name, ULONG ip_address, ULONG network_mask,
                     NX_PACKET_POOL *default_pool, VOID (*ip_link_driver)(struct NX_IP_DRIVER_STRUCT *),
                     VOID *memory_ptr, ULONG memory_size, UINT priority, UINT ip_control_block_size);
extern _RPST_ _nxe_ip_create_FP_T _nxe_ip_create_FP;

typedef UINT  (* _nx_ip_create_FP_T)(NX_IP *ip_ptr, CHAR *name, ULONG ip_address, ULONG network_mask,
                    NX_PACKET_POOL *default_pool, VOID (*ip_link_driver)(struct NX_IP_DRIVER_STRUCT *),
                    VOID *memory_ptr, ULONG memory_size, UINT priority);
extern _RPST_ _nx_ip_create_FP_T _nx_ip_create_FP;

typedef UINT  (* _nxe_arp_enable_FP_T)(NX_IP *ip_ptr, VOID *arp_cache_memory, ULONG arp_cache_size);
extern _RPST_ _nxe_arp_enable_FP_T _nxe_arp_enable_FP;

typedef UINT  (* _nx_arp_enable_FP_T)(NX_IP *ip_ptr, VOID *arp_cache_memory, ULONG arp_cache_size);
extern _RPST_ _nx_arp_enable_FP_T _nx_arp_enable_FP;

typedef UINT  (* _nxe_udp_enable_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nxe_udp_enable_FP_T _nxe_udp_enable_FP;

typedef UINT  (* _nx_udp_enable_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nx_udp_enable_FP_T _nx_udp_enable_FP;


typedef UINT  (* _nxe_tcp_enable_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nxe_tcp_enable_FP_T _nxe_tcp_enable_FP;

typedef UINT  (* _nx_tcp_enable_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nx_tcp_enable_FP_T _nx_tcp_enable_FP;


typedef UINT  (* _nxe_dhcp_create_FP_T)(NX_DHCP *dhcp_ptr, NX_IP *ip_ptr, CHAR *name_ptr);
extern _RPST_ _nxe_dhcp_create_FP_T _nxe_dhcp_create_FP;

typedef UINT  (* _nx_dhcp_create_FP_T)(NX_DHCP *dhcp_ptr, NX_IP *ip_ptr, CHAR *name_ptr);
extern _RPST_ _nx_dhcp_create_FP_T _nx_dhcp_create_FP;

typedef UINT  (* _nxe_dns_create_FP_T)(NX_DNS *dns_ptr, NX_IP *ip_ptr, UCHAR *domain_name);
extern _RPST_ _nxe_dns_create_FP_T _nxe_dns_create_FP;

typedef UINT  (* _nx_dns_create_FP_T)(NX_DNS *dns_ptr, NX_IP *ip_ptr, UCHAR *domain_name);
extern _RPST_ _nx_dns_create_FP_T _nx_dns_create_FP;


typedef UINT  (* _nxe_ip_delete_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nxe_ip_delete_FP_T _nxe_ip_delete_FP;

typedef UINT  (* _nx_ip_delete_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nx_ip_delete_FP_T _nx_ip_delete_FP;

typedef UINT  (* _nxe_dhcp_delete_FP_T)(NX_DHCP *dhcp_ptr);
extern _RPST_ _nxe_dhcp_delete_FP_T _nxe_dhcp_delete_FP;

typedef UINT  (* _nx_dhcp_delete_FP_T)(NX_DHCP *dhcp_ptr);
extern _RPST_ _nx_dhcp_delete_FP_T _nx_dhcp_delete_FP;

typedef UINT  (* _nxe_dns_delete_FP_T)(NX_DNS *dns_ptr);
extern _RPST_ _nxe_dns_delete_FP_T _nxe_dns_delete_FP;

typedef UINT  (* _nx_dns_delete_FP_T)(NX_DNS *dns_ptr);
extern _RPST_ _nx_dns_delete_FP_T _nx_dns_delete_FP;

typedef UINT  (* _nxe_ip_address_set_FP_T)(NX_IP *ip_ptr, ULONG ip_address, ULONG network_mask);
extern _RPST_ _nxe_ip_address_set_FP_T _nxe_ip_address_set_FP;

typedef UINT  (* _nx_ip_address_set_FP_T)(NX_IP *ip_ptr, ULONG ip_address, ULONG network_mask);
extern _RPST_ _nx_ip_address_set_FP_T _nx_ip_address_set_FP;

typedef UINT  (* _nxe_ip_gateway_address_set_FP_T)(NX_IP *ip_ptr, ULONG ip_address);
extern _RPST_ _nxe_ip_gateway_address_set_FP_T _nxe_ip_gateway_address_set_FP;

typedef UINT  (* _nx_ip_gateway_address_set_FP_T)(NX_IP *ip_ptr, ULONG ip_address);
extern _RPST_ _nx_ip_gateway_address_set_FP_T _nx_ip_gateway_address_set_FP;

typedef UINT  (* _nxe_dns_server_add_FP_T)(NX_DNS *dns_ptr, ULONG server_address);
extern _RPST_ _nxe_dns_server_add_FP_T _nxe_dns_server_add_FP;

typedef UINT  (* _nx_dns_server_add_FP_T)(NX_DNS *dns_ptr, ULONG server_address);
extern _RPST_ _nx_dns_server_add_FP_T _nx_dns_server_add_FP;

typedef UINT  (* _nxe_dhcp_stop_FP_T)(NX_DHCP *dhcp_ptr);
extern _RPST_ _nxe_dhcp_stop_FP_T _nxe_dhcp_stop_FP;

typedef UINT  (* _nx_dhcp_stop_FP_T)(NX_DHCP *dhcp_ptr);
extern _RPST_ _nx_dhcp_stop_FP_T _nx_dhcp_stop_FP;

typedef UINT  (* _nxe_ip_driver_direct_command_FP_T)(NX_IP *ip_ptr, UINT command, ULONG *return_value_ptr);
extern _RPST_ _nxe_ip_driver_direct_command_FP_T _nxe_ip_driver_direct_command_FP;

typedef UINT  (* _nx_ip_driver_direct_command_FP_T)(NX_IP *ip_ptr, UINT command, ULONG *return_value_ptr);
extern _RPST_ _nx_ip_driver_direct_command_FP_T _nx_ip_driver_direct_command_FP;


typedef UINT  (* _nxe_dhcp_state_change_notify_FP_T)(NX_DHCP *dhcp_ptr, 
                            VOID (*dhcp_state_change_notify)(NX_DHCP *dhcp_ptr, UCHAR new_state, void *notifyCtx),
                            									void *notifyCtx);
extern _RPST_ _nxe_dhcp_state_change_notify_FP_T _nxe_dhcp_state_change_notify_FP;

typedef UINT  (* _nx_dhcp_state_change_notify_FP_T)(NX_DHCP *dhcp_ptr, VOID (*dhcp_state_change_notify)(NX_DHCP *dhcp_ptr, UCHAR new_state, void * notifyCtx), 
											void * notifyCtx);
extern _RPST_   _nx_dhcp_state_change_notify_FP_T _nx_dhcp_state_change_notify_FP;

typedef UINT  (* _nxe_dhcp_start_FP_T)(NX_DHCP *dhcp_ptr);
extern _RPST_   _nxe_dhcp_start_FP_T _nxe_dhcp_start_FP;

typedef UINT  (* _nx_dhcp_start_FP_T)(NX_DHCP *dhcp_ptr);
extern _RPST_   _nx_dhcp_start_FP_T _nx_dhcp_start_FP;

typedef UINT  (* _nxe_ip_status_check_FP_T)(NX_IP *ip_ptr, ULONG needed_status, ULONG *actual_status, ULONG wait_option);
extern _RPST_   _nxe_ip_status_check_FP_T _nxe_ip_status_check_FP;

typedef UINT  (* _nx_ip_status_check_FP_T)(NX_IP *ip_ptr, ULONG needed_status, ULONG *actual_status, ULONG wait_option);
extern _RPST_   _nx_ip_status_check_FP_T _nx_ip_status_check_FP;

typedef UINT  (* _nxe_ip_address_get_FP_T)(NX_IP *ip_ptr, ULONG *ip_address, ULONG *network_mask);
extern _RPST_   _nxe_ip_address_get_FP_T _nxe_ip_address_get_FP;

typedef UINT  (* _nx_ip_address_get_FP_T)(NX_IP *ip_ptr, ULONG *ip_address, ULONG *network_mask);
extern _RPST_   _nx_ip_address_get_FP_T _nx_ip_address_get_FP;

typedef UINT  (* _nxe_dhcp_user_option_retrieve_FP_T)(NX_DHCP *dhcp_ptr, UINT option_request, UCHAR *destination_ptr, UINT *destination_size);
extern _RPST_   _nxe_dhcp_user_option_retrieve_FP_T _nxe_dhcp_user_option_retrieve_FP;

typedef UINT  (* _nx_dhcp_user_option_retrieve_FP_T)(NX_DHCP *dhcp_ptr, UINT option_request, UCHAR *destination_ptr, UINT *destination_size);
extern _RPST_   _nx_dhcp_user_option_retrieve_FP_T _nx_dhcp_user_option_retrieve_FP;


typedef UINT  (* _nxe_packet_data_append_FP_T)(NX_PACKET *packet_ptr, VOID *data_start, ULONG data_size,
                              NX_PACKET_POOL *pool_ptr, ULONG wait_option);
extern _RPST_   _nxe_packet_data_append_FP_T _nxe_packet_data_append_FP;

typedef UINT  (* _nx_packet_data_append_FP_T)(NX_PACKET *packet_ptr, VOID *data_start, ULONG data_size,
                              NX_PACKET_POOL *pool_ptr, ULONG wait_option);
extern _RPST_   _nx_packet_data_append_FP_T _nx_packet_data_append_FP;


typedef VOID  (* _nx_ip_packet_receive_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_   _nx_ip_packet_receive_FP_T _nx_ip_packet_receive_FP;

typedef VOID  (* _nx_arp_packet_deferred_receive_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_   _nx_arp_packet_deferred_receive_FP_T _nx_arp_packet_deferred_receive_FP;

typedef VOID  (* _nx_rarp_packet_deferred_receive_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_   _nx_rarp_packet_deferred_receive_FP_T _nx_rarp_packet_deferred_receive_FP;

typedef UINT  (* _nxe_packet_length_get_FP_T)(NX_PACKET *packet_ptr, ULONG *length);
extern _RPST_   _nxe_packet_length_get_FP_T _nxe_packet_length_get_FP;

typedef UINT  (* _nx_packet_length_get_FP_T)(NX_PACKET *packet_ptr, ULONG *length);
extern _RPST_   _nx_packet_length_get_FP_T _nx_packet_length_get_FP;

typedef UINT  (* _nxe_packet_transmit_release_FP_T)(NX_PACKET **packet_ptr_ptr);
extern _RPST_   _nxe_packet_transmit_release_FP_T _nxe_packet_transmit_release_FP;

typedef UINT  (* _nx_packet_transmit_release_FP_T)(NX_PACKET *packet_ptr);
extern _RPST_   _nx_packet_transmit_release_FP_T _nx_packet_transmit_release_FP;

typedef UINT  (* _nxe_packet_data_retrieve_FP_T)(NX_PACKET *packet_ptr, VOID *buffer_start, ULONG *bytes_copied);
extern _RPST_   _nxe_packet_data_retrieve_FP_T _nxe_packet_data_retrieve_FP;

typedef UINT  (* _nx_packet_data_retrieve_FP_T)(NX_PACKET *packet_ptr, VOID *buffer_start, ULONG *bytes_copied);
extern _RPST_   _nx_packet_data_retrieve_FP_T _nx_packet_data_retrieve_FP;

typedef VOID  (*_nx_ip_thread_entry_FP_T)(ULONG ip_ptr_value);
extern _RPST_ _nx_ip_thread_entry_FP_T _nx_ip_thread_entry_FP;

typedef	VOID  (*_nx_ipv4_packet_receive_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_ _nx_ipv4_packet_receive_FP_T _nx_ipv4_packet_receive_FP;

typedef	UINT (*_nx_ip_dispatch_process_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr, UINT protocol);
extern _RPST_ _nx_ip_dispatch_process_FP_T _nx_ip_dispatch_process_FP;

typedef	VOID  ( *_nx_udp_packet_receive_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_ _nx_udp_packet_receive_FP_T _nx_udp_packet_receive_FP;

typedef VOID  (* _nx_tcp_packet_process_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_ _nx_tcp_packet_process_FP_T _nx_tcp_packet_process_FP;

typedef	VOID  (* _nx_tcp_fast_periodic_processing_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nx_tcp_fast_periodic_processing_FP_T _nx_tcp_fast_periodic_processing_FP;

typedef UINT  (* _nx_tcp_socket_create_FP_T)(NX_IP *ip_ptr, NX_TCP_SOCKET *socket_ptr, CHAR *name, 
                ULONG type_of_service, ULONG fragment, UINT time_to_live, ULONG window_size,
                VOID (*tcp_urgent_data_callback)(NX_TCP_SOCKET *socket_ptr),
                VOID (*tcp_disconnect_callback)(NX_TCP_SOCKET *socket_ptr));
extern _RPST_ _nx_tcp_socket_create_FP_T _nx_tcp_socket_create_FP;

typedef UINT  (* _nx_tcp_socket_send_internal_FP_T)(NX_TCP_SOCKET *socket_ptr, NX_PACKET *packet_ptr, ULONG wait_option);
extern _RPST_ _nx_tcp_socket_send_internal_FP_T _nx_tcp_socket_send_internal_FP;

typedef VOID  ( *_nx_tcp_socket_state_transmit_check_FP_T)(NX_TCP_SOCKET *socket_ptr);
extern _RPST_ _nx_tcp_socket_state_transmit_check_FP_T _nx_tcp_socket_state_transmit_check_FP;

typedef int (* nx_bsd_send_internal_FP_T)(INT sockID, const CHAR *msg, INT msgLength, 
									NXD_ADDRESS *dst_address, USHORT dst_port, UINT local_interface_index);
extern _RPST_ nx_bsd_send_internal_FP_T nx_bsd_send_internal_FP;

typedef VOID  (* nx_bsd_tcp_receive_notify_FP_T)(NX_TCP_SOCKET *socket_ptr);
extern _RPST_ nx_bsd_tcp_receive_notify_FP_T nx_bsd_tcp_receive_notify_FP;

typedef VOID  ( *nx_bsd_tcp_establish_notify_FP_T)(NX_TCP_SOCKET *socket_ptr);
extern _RPST_ nx_bsd_tcp_establish_notify_FP_T nx_bsd_tcp_establish_notify_FP;

typedef VOID  ( *nx_bsd_tcp_socket_disconnect_notify_FP_T)(NX_TCP_SOCKET *socket_ptr);

extern _RPST_ nx_bsd_tcp_socket_disconnect_notify_FP_T nx_bsd_tcp_socket_disconnect_notify_FP;

typedef VOID  ( *nx_bsd_udp_receive_notify_FP_T)(NX_UDP_SOCKET *socket_ptr);

extern _RPST_ nx_bsd_udp_receive_notify_FP_T nx_bsd_udp_receive_notify_FP;

typedef UINT ( *nx_bsd_socket_set_inherited_settings_FP_T)(UINT master_sock_id, UINT secondary_sock_id);

extern _RPST_ nx_bsd_socket_set_inherited_settings_FP_T nx_bsd_socket_set_inherited_settings_FP;

typedef int ( *nx_bsd_tcp_create_listen_socket_FP_T)(int master_sockid, int backlog);

extern _RPST_ nx_bsd_tcp_create_listen_socket_FP_T nx_bsd_tcp_create_listen_socket_FP;

typedef VOID  ( *_nx_dhcp_thread_entry_FP_T)(ULONG dhcp_instance);

extern _RPST_ _nx_dhcp_thread_entry_FP_T _nx_dhcp_thread_entry_FP;

typedef UINT  ( *_nx_dhcp_send_request_internal_FP_T)(NX_DHCP *dhcp_ptr, UINT dhcp_message_type);

extern _RPST_ _nx_dhcp_send_request_internal_FP_T _nx_dhcp_send_request_internal_FP;

typedef VOID  ( *_nx_dhcp_process_FP_T)(NX_DHCP *dhcp_ptr);

extern _RPST_ _nx_dhcp_process_FP_T _nx_dhcp_process_FP;

typedef UINT (*_nx_ipv6_process_hop_by_hop_option_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_ _nx_ipv6_process_hop_by_hop_option_FP_T _nx_ipv6_process_hop_by_hop_option_FP;

typedef UINT (*_nxd_ipv6_interface_find_FP_T)(NX_IP *ip_ptr, NXD_ADDRESS *dest_address, NXD_IPV6_ADDRESS **ipv6_addr);
extern _RPST_ _nxd_ipv6_interface_find_FP_T _nxd_ipv6_interface_find_FP;

typedef VOID (*_nx_ipv6_packet_send_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr,
                          ULONG protocol, ULONG payload_size, int hop_limit);
extern _RPST_ _nx_ipv6_packet_send_FP_T _nx_ipv6_packet_send_FP;

typedef VOID  (*_nx_icmpv6_packet_process_FP_T)(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern _RPST_ _nx_icmpv6_packet_process_FP_T _nx_icmpv6_packet_process_FP;

typedef UINT  (*_nxd_ipv6_address_set_FP_T)(NX_IP *ip_ptr, UINT interface_index, NXD_ADDRESS *ip_address, ULONG prefix_length, UINT *address_index);
extern _RPST_ _nxd_ipv6_address_set_FP_T _nxd_ipv6_address_set_FP;

typedef UINT  (*_nxd_ipv6_enable_FP_T)(NX_IP *ip_ptr);
extern _RPST_ _nxd_ipv6_enable_FP_T _nxd_ipv6_enable_FP;

typedef int (*CHECK_IPV6_SOLICITED_NODE_MCAST_ADDRESS_FP_T)(ULONG *dest_ip, ULONG* myip);
extern _RPST_ CHECK_IPV6_SOLICITED_NODE_MCAST_ADDRESS_FP_T CHECK_IPV6_SOLICITED_NODE_MCAST_ADDRESS_FP;

typedef VOID (*nx_bsd_timeout_process_FP_T)(void);
extern _RPST_ nx_bsd_timeout_process_FP_T nx_bsd_timeout_process_FP;

typedef INT  (*getpeername_FP_T)(INT sockID, struct sockaddr *remoteAddress, INT *addressLength);
extern _RPST_ getpeername_FP_T getpeername_FP;

typedef INT  (*getsockname_FP_T)(INT sockID, struct sockaddr *localAddress, INT *addressLength);
extern _RPST_ getsockname_FP_T getsockname_FP;

typedef INT  (*recvfrom_FP_T)(INT sockID, CHAR *buffer, INT buffersize, INT flags,struct sockaddr *fromAddr, INT *fromAddrLen);
extern _RPST_ recvfrom_FP_T recvfrom_FP;

typedef INT  (*recv_FP_T)(INT sockID, VOID *rcvBuffer, INT bufferLength, INT flags);
extern _RPST_ recv_FP_T recv_FP;

typedef INT  (*sendto_FP_T)(INT sockID, CHAR *msg, INT msgLength, INT flags, struct sockaddr *destAddr, INT destAddrLen);
extern _RPST_ sendto_FP_T sendto_FP;

typedef INT  (*send_FP_T)(INT sockID, const CHAR *msg, INT msgLength, INT flags);
extern _RPST_ send_FP_T send_FP;

typedef INT  (*accept_FP_T)(INT sockID, struct sockaddr *ClientAddress, INT *addressLength);
extern _RPST_ accept_FP_T accept_FP;

typedef INT  (*listen_FP_T)(INT sockID, INT backlog);
extern _RPST_ listen_FP_T listen_FP;

typedef INT  (*ioctl_FP_T)(INT sockID, INT command, INT *result);
extern _RPST_ ioctl_FP_T ioctl_FP;

typedef CHAR* (*inet_ntoa_FP_T)(struct in_addr address_to_convert);
extern _RPST_ inet_ntoa_FP_T inet_ntoa_FP;

typedef UINT (*bsd_number_convert_FP_T)(UINT number, CHAR *string);
extern _RPST_ bsd_number_convert_FP_T bsd_number_convert_FP;

typedef INT  (*inet_aton_FP_T)(const CHAR *cp_arg, struct in_addr *addr);
extern _RPST_ inet_aton_FP_T inet_aton_FP;

typedef in_addr_t (*inet_addr_FP_T)(const CHAR *buffer);
extern _RPST_ inet_addr_FP_T inet_addr_FP;

typedef INT  (*bind_FP_T)(INT sockID, struct sockaddr *localAddress, INT addressLength);
extern _RPST_ bind_FP_T bind_FP;

typedef INT  (*connect_FP_T)(INT sockID, struct sockaddr *remoteAddress, INT addressLength);
extern _RPST_ connect_FP_T connect_FP;

typedef VOID (*nx_bsd_socket_tcp_disconnect_handler_FP_T)(NX_TCP_SOCKET *socket_ptr);
extern _RPST_ nx_bsd_socket_tcp_disconnect_handler_FP_T nx_bsd_socket_tcp_disconnect_handler_FP;

typedef INT  (*select_FP_T)(INT nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
extern _RPST_ select_FP_T select_FP;

typedef INT  (*soc_close_FP_T)( INT sockID);
extern _RPST_ soc_close_FP_T soc_close_FP;

typedef INT  (*socket_FP_T)(INT protocolFamily, INT type, INT protocol);
extern _RPST_ socket_FP_T socket_FP;


typedef INT  (*getsockopt_FP_T)(INT sockID, INT option_level, INT option_name, void *option_value, INT *option_length);
extern _RPST_ getsockopt_FP_T getsockopt_FP;

typedef INT  (*fcntl_FP_T)(INT sock_ID, UINT flag_type, UINT f_options);
extern _RPST_ fcntl_FP_T fcntl_FP;

typedef VOID (*nx_bsd_socket_tcp_disconnect_extended_handler_FP_T)(NX_TCP_SOCKET *socket_ptr);
extern _RPST_ nx_bsd_socket_tcp_disconnect_extended_handler_FP_T nx_bsd_socket_tcp_disconnect_extended_handler_FP;

typedef UINT (*nx_bsd_set_socket_disconnect_complete_notify_FP_T)(VOID (*user_bsd_disconnect_complete_cb)(NX_TCP_SOCKET *socket_ptr));
extern _RPST_ nx_bsd_set_socket_disconnect_complete_notify_FP_T nx_bsd_set_socket_disconnect_complete_notify_FP;

typedef UINT (*nx_bsd_set_socket_establish_notify_FP_T)(VOID (*user_establish_cb)(NX_TCP_SOCKET *socket_ptr));
extern _RPST_ nx_bsd_set_socket_establish_notify_FP_T nx_bsd_set_socket_establish_notify_FP;

typedef INT  (*setsockopt_FP_T)(INT sockID, INT option_level, INT option_name, const void *option_value, INT option_length);
extern _RPST_ setsockopt_FP_T setsockopt_FP;

typedef INT  (*soc_close_extended_FP_T)( INT sockID);
extern _RPST_ soc_close_extended_FP_T soc_close_extended_FP;

typedef VOID (*FD_SET_FP_T)(INT fd, fd_set *fdset);
extern _RPST_ FD_SET_FP_T FD_SET_FP;

typedef VOID (*FD_CLR_FP_T)(INT fd, fd_set *fdset);
extern _RPST_ FD_CLR_FP_T FD_CLR_FP;

typedef INT  (*FD_ISSET_FP_T)(INT fd, fd_set *fdset);
extern _RPST_ FD_ISSET_FP_T FD_ISSET_FP;

typedef VOID (*FD_ZERO_FP_T)(fd_set *fdset);
extern _RPST_ FD_ZERO_FP_T FD_ZERO_FP;

typedef VOID (*set_errno_FP_T)(INT tx_errno);
extern _RPST_ set_errno_FP_T set_errno_FP;

typedef INT (*nx_bsd_callback_register_FP_T)(INT socket_id, void (*user_callback)(INT socket_id,NX_BSD_CB_EVENT_TYPE_T event, UINT port), 
									INT flags);
extern _RPST_ nx_bsd_callback_register_FP_T nx_bsd_callback_register_FP;


typedef INT (*nx_bsd_callback_FP_T)( INT socket_id, void (*app_callback)(void *socket_struct,NX_BSD_CB_EVENT_TYPE_T event, UINT port), INT flag );
extern _RPST_ nx_bsd_callback_FP_T nx_bsd_callback_FP;

typedef UINT (*nx_bsd_socket_inherit_user_callback_FP_T)(UINT sockID, UINT new_secondary_sockID);
extern _RPST_ nx_bsd_socket_inherit_user_callback_FP_T nx_bsd_socket_inherit_user_callback_FP;

typedef VOID (*bsd_callback_resolve_FP_T)(void *socket_struct, NX_BSD_CB_EVENT_TYPE_T event, UINT port);
extern _RPST_ bsd_callback_resolve_FP_T bsd_callback_resolve_FP;

typedef VOID (*nx_bsd_thread_entry_FP_T)(ULONG info);
extern _RPST_ nx_bsd_thread_entry_FP_T nx_bsd_thread_entry_FP;

typedef int (*_nxd_get_errno_FP_T)(void);
extern _RPST_ _nxd_get_errno_FP_T _nxd_get_errno_FP;

typedef VOID (*nx_bsd_set_error_code_FP_T)(NX_BSD_SOCKET *bsd_socket_ptr, UINT status_code);
extern _RPST_ nx_bsd_set_error_code_FP_T nx_bsd_set_error_code_FP;

typedef VOID ( *nx_bsd_udp_packet_received_FP_T)(int sockID, NX_PACKET *packet_ptr);

extern _RPST_  nx_bsd_udp_packet_received_FP_T nx_bsd_udp_packet_received_FP;

typedef	UINT  (*nx_bsd_tcp_syn_received_notify_FP_T)(NX_TCP_SOCKET *socket_ptr, NX_PACKET *packet_ptr);

extern _RPST_ nx_bsd_tcp_syn_received_notify_FP_T nx_bsd_tcp_syn_received_notify_FP;

typedef void (*nx_bsd_tcp_pending_connection_FP_T)(UINT local_port, NX_TCP_SOCKET *socket_ptr);
extern _RPST_ nx_bsd_tcp_pending_connection_FP_T nx_bsd_tcp_pending_connection_FP;

typedef int   (*nx_bsd_find_interface_by_source_addr_FP_T)(UINT addr_family, ULONG* ip_addr);
extern _RPST_ nx_bsd_find_interface_by_source_addr_FP_T nx_bsd_find_interface_by_source_addr_FP;

typedef VOID  (* _nxd_bsd_ipv4_packet_send_FP_T)(NX_PACKET *packet_ptr);
extern _RPST_ _nxd_bsd_ipv4_packet_send_FP_T _nxd_bsd_ipv4_packet_send_FP;

typedef VOID (* _nxd_bsd_ipv6_packet_send_FP_T)(NX_PACKET *packet_ptr);

extern _RPST_ _nxd_bsd_ipv6_packet_send_FP_T _nxd_bsd_ipv6_packet_send_FP;

typedef NX_PACKET * (*nx_bsd_packet_ptr_get_FP_T)(INT sockID);

extern _RPST_ nx_bsd_packet_ptr_get_FP_T nx_bsd_packet_ptr_get_FP;

typedef VOID (* nx_bsd_tcp_window_update_notify_FP_T)(NX_TCP_SOCKET *socket_ptr);

extern _RPST_ nx_bsd_tcp_window_update_notify_FP_T nx_bsd_tcp_window_update_notify_FP;

typedef VOID ( *nx_bsd_tcp_socket_queue_depth_notify_FP_T)(NX_TCP_SOCKET *socket_ptr);

extern _RPST_ nx_bsd_tcp_socket_queue_depth_notify_FP_T nx_bsd_tcp_socket_queue_depth_notify_FP;

typedef VOID  (* nx_bsd_tcp_socket_error_notify_FP_T)(NX_TCP_SOCKET *socket_ptr);

extern _RPST_ nx_bsd_tcp_socket_error_notify_FP_T nx_bsd_tcp_socket_error_notify_FP;

typedef	VOID ( *nx_bsd_user_cb_invoke_FP_T)( INT bsd_socket_index, NX_BSD_CB_EVENT_TYPE_T  event, UINT port);

extern _RPST_ nx_bsd_user_cb_invoke_FP_T nx_bsd_user_cb_invoke_FP;

typedef VOID (* nx_bsd_user_cb_resolve_FP_T)(void *socket_struct, NX_BSD_CB_EVENT_TYPE_T event, UINT port);

extern _RPST_ nx_bsd_user_cb_resolve_FP_T nx_bsd_user_cb_resolve_FP;

typedef INT (* nx_bsd_callback_register_param_FP_T)(INT socket_id, void *cb_param, void (*user_callback)(INT socket_id,NX_BSD_CB_EVENT_TYPE_T event, void *cb_param), INT flags);

extern _RPST_ nx_bsd_callback_register_param_FP_T nx_bsd_callback_register_param_FP;

typedef INT (* nx_bsd_callback_register_param2_FP_T)(INT socket_id, void *cb_param1, void *cb_param2, 
												void (*user_callback)(INT socket_id,NX_BSD_CB_EVENT_TYPE_T event, void *cb_param1, void *cb_param2), 
												INT flags);

extern _RPST_ nx_bsd_callback_register_param2_FP_T nx_bsd_callback_register_param2_FP;

typedef VOID (* nx_bsd_select_wakeup_FP_T)(UINT sock_id, UINT fd_sets);

extern _RPST_ nx_bsd_select_wakeup_FP_T nx_bsd_select_wakeup_FP;

typedef NX_TCP_SOCKET * (* nx_bsd_socket_ptr_get_FP_T)(INT sockID);

extern _RPST_ nx_bsd_socket_ptr_get_FP_T nx_bsd_socket_ptr_get_FP;

typedef UINT (*_nx_dhcp_reinitialize_FP_T)(NX_DHCP *dhcp_ptr,UINT clearIpAddr);

extern _RPST_  _nx_dhcp_reinitialize_FP_T _nx_dhcp_reinitialize_FP;

typedef UINT  ( *_nx_dhcp_force_renew_FP_T)(NX_DHCP *dhcp_ptr);

extern _RPST_ _nx_dhcp_force_renew_FP_T _nx_dhcp_force_renew_FP;

typedef UINT  (* _nx_dhcp_decline_FP_T)(NX_DHCP *dhcp_ptr);
extern _RPST_ _nx_dhcp_decline_FP_T _nx_dhcp_decline_FP;

typedef UINT  ( *_nx_dhcp_release_FP_T)(NX_DHCP *dhcp_ptr);

extern _RPST_ _nx_dhcp_release_FP_T _nx_dhcp_release_FP;

typedef UINT  (* _nx_dhcp_conf_set_FP_T)(NX_DHCP *dhcp_ptr, NX_DHCP_CONF_OPTION_T option, VOID *val, UINT len);

extern _RPST_ _nx_dhcp_conf_set_FP_T _nx_dhcp_conf_set_FP;


typedef UINT  (*_nxe_tcp_socket_mss_peer_get_FP_T)(NX_TCP_SOCKET *socket_ptr, ULONG *peer_mss);

extern _RPST_ _nxe_tcp_socket_mss_peer_get_FP_T _nxe_tcp_socket_mss_peer_get_FP;

typedef UINT  ( *_nx_tcp_socket_mss_peer_get_FP_T)(NX_TCP_SOCKET *socket_ptr, ULONG *peer_mss);

extern _RPST_ _nx_tcp_socket_mss_peer_get_FP_T _nx_tcp_socket_mss_peer_get_FP;

typedef UINT  (* _nx_tcp_socket_send_FP_T)(NX_TCP_SOCKET *socket_ptr, NX_PACKET *packet_ptr, ULONG wait_option);

extern _RPST_ _nx_tcp_socket_send_FP_T _nx_tcp_socket_send_FP;

typedef UINT  ( *_nx_packet_release_FP_T)(NX_PACKET *packet_ptr);

extern _RPST_ _nx_packet_release_FP_T _nx_packet_release_FP;

typedef	UINT  ( * _nx_tcp_socket_receive_FP_T)(NX_TCP_SOCKET *socket_ptr, NX_PACKET **packet_ptr, ULONG wait_option);

extern _RPST_ _nx_tcp_socket_receive_FP_T _nx_tcp_socket_receive_FP;
#endif
