/******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
*                         All Rights Reserved
*
* The source code contained or described herein and all documents
* related to the source code ("Material") are owned by GainSpan
* Corporation or its licensors.  Title to the Material remains
* with GainSpan Corporation or its suppliers and licensors.
*
* The Material is protected by worldwide copyright and trade secret
* laws and treaty provisions. No part of the Material may be used,
* copied, reproduced, modified, published, uploaded, posted, transmitted,
* distributed, or disclosed in any way except in accordance with the
* applicable license agreement.
*
* No license under any patent, copyright, trade secret or other
* intellectual property right is granted to or conferred upon you by
* disclosure or delivery of the Materials, either expressly, by
* implication, inducement, estoppel, except in accordance with the
* applicable license agreement.
*
* Unless otherwise agreed by GainSpan in writing, you may not remove or
* alter this notice or any other notice embedded in Materials by GainSpan
* or GainSpan's suppliers or licensors in any way.
*
* $RCSfile: gsn_includes.h,v $
*
* Description : This file contains #includes to include GainSpan modules.
*****************************************************************************/
#ifndef _GSN_INCLUDES_H_
#define _GSN_INCLUDES_H_

/*****************************************************************************
 * Standard IAR header files
 ****************************************************************************/
#include "core/cmsis/cortex_cm3.h"
#include "core_cm3.h"

/*****************************************************************************
 * Standard C Library header files
 ****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

/*****************************************************************************
 * ThreadX and NetX header files
 ****************************************************************************/
#include "rtos/tx_api.h"
#include "netx/nx_api.h"
#include "netx/netx_applications/dhcp/nxd_dhcpv6_client.h"
#include "netx/netx_bsd_layer/nxd_bsd.h"

/*****************************************************************************
 * Gsn Common Header files 
 ****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "gsn_bitfield_macros.h"

/*****************************************************************************
  * Gsn Core Services
  ****************************************************************************/
#include "core/osal/gsn_osal_threadx.h"
#include "core/reg/gsn_reg_op.h"
#include "core/osal/gsn_osal.h"
#include "core/reg/gsn_iomux.h"
#include "core/util/gsn_ring_buf.h"
#include "core/util/gsn_ring_buf.h"
#include "core/util/gsn_util.h"
#include "core/msg_handler/gsn_msg_handler.h"
#include "core/reg/gsn_reg_clkctl_op.h"
#include "core/reg/gsn_reg_clkctl_spec.h"
#include "core/sys_utils/gsn_sys_rtc_info.h"
#include "core/sys_utils/gsn_sys_reset.h"
#include "core/statistics/gsn_stats.h"
#include "core/sys_utils/gsn_assert.h"
#include "core/wif/common/gsn_wif_api.h"
#include "core/wif/common/gsn_wlan_defs.h"
#include "core/wif/common/gsn_wif_defs.h"
#include "core/wif/common/gsn_wif_sys_defs.h"
#include "core/wif/common/gsn_wif_wlan_defs.h"
#include "core/wif/common/gsn_wif_cal_defs.h"
#include "core/wif/common/gsn_wif_isotx_defs.h"
#include "core/wif/common/gsn_wif_dbg_defs.h"
#include "core/wif/common/gsn_wif_common.h"
#include "core/wif/mac_util/gsn_mac_def.h"
#include "core/wif/mac_util/gsn_mac_utils.h"
#include "core/wif/mac_util/gsn_mac_frame.h"
#include "core/hif/gsn_hi_mb.h"
#include "core/hif/gsn_hi.h"
#include "core/hif/gsn_hi_buf.h"
#include "core/wif/api/gsn_wif.h"
#include "core/sysif/gsn_sysif.h"
#include "core/isotxif/gsn_isotxif.h"
#include "core/dot154if/gsn_dot154if.h"

/*****************************************************************************
  * Gsn Drivers
  ****************************************************************************/
/* Flash If and Flash Cache*/
#include "drivers/reg/gsn_reg_flashif_spec.h"
#include "drivers/reg/gsn_reg_flashif_op.h"
#include "drivers/reg/gsn_reg_flashcache_spec.h"
#include "drivers/reg/gsn_reg_flashcache_op.h"
#include "drivers/flash_if/gsn_flash_if.h"
#include "drivers/flash_cache/gsn_flash_cache.h"

/*SPI*/
#include "drivers/reg/gsn_reg_spi_op.h"
#include "drivers/reg/gsn_reg_spi_spec.h"
#include "drivers/spi_fs/buffer.h"
#include "drivers/spi/gsn_spi.h"
#include "drivers/spi/gsn_spi_poll.h"
/*SPI_FS*/

#include "drivers/spi_fs/gsn_spiFs.h"

/*UART*/
#include "drivers/reg/gsn_reg_uart_spec.h"
#include "drivers/reg/gsn_reg_uart_op.h"
#include "drivers/uart/gsn_uart.h"

/*GPIO*/
#include "drivers/reg/gsn_reg_gpio_spec.h"
#include "drivers/reg/gsn_reg_gpio_op.h"
#include "drivers/gpio/gsn_gpio.h"

/*SAR ADC */
#include "drivers/reg/gsn_reg_aadc_spec.h"
#include "drivers/reg/gsn_reg_aadc_op.h"
//#include "drivers\aadc\gsn_aadc.h"

/*SDADC */
#include "drivers/reg/gsn_reg_sdadcdac_spec.h"
#include "drivers/reg/gsn_reg_sdadcdac_op.h"
#include "drivers/sdadc/gsn_sdadc.h"

/* Mail Box*/
#include "drivers/reg/gsn_reg_mb_spec.h"
#include "drivers/reg/gsn_reg_mb_op.h"
#include "drivers/mb/gsn_mb.h"

#include "drivers/rtc/gsn_rtc.h"
/*SDIO*/
#include "drivers/reg/gsn_reg_sdio_op.h"
#include "drivers/reg/gsn_reg_sdio_spec.h"
#include "drivers/sdio/gsn_sdio.h"
#include "drivers/otp/gsn_otp.h"

/* PWM */

#include "drivers/reg/gsn_reg_pwm_op.h"
#include "drivers/reg/gsn_reg_pwm_spec.h"
#include "drivers/pwm/gsn_pwm.h"

/* I2C */
#include "drivers/reg/gsn_reg_i2c_spec.h"
#include "drivers/reg/gsn_reg_i2c_op.h"
#include "drivers/i2c/gsn_i2c.h"


/*SAR ADC NEW */

#include "drivers/adc/gsn_adc.h"

/*****************************************************************************
  * Gsn Modules
  ****************************************************************************/
#include "modules/dbg/gsn_dbg.h"
#include "modules/sys_qual/gsn_sys_qual.h"
#include "modules/nw/gsn_nw_defines.h"
#include "modules/soft_timer/gsn_soft_timer.h"
#include "modules/otp_mm/gsn_otp_mm.h"
#include "modules/otp_mm/gsn_otp_mm_grps.h"
#include "modules/wdd/gsn_wdd_security.h"
#include "security/wpa_if/gsn_wpaif.h"
#include "modules/wdd/gsn_wdd.h"
#include "modules/sys_ctl/gsn_sys_ctl.h"
#include "modules/isotx/gsn_isotx.h"
#include "modules/nw/netx/gsn_nw.h"
#include "modules/nw/netx/gsn_nwif.h"
#include "modules/taskSleep/gsn_task_sleep.h"
#include "modules/dynamic_mem_mgmt/dynamic_mem_mgmt.h"
#include "modules/sntp/gsn_sntp.h"
#include "modules/dns_srvr/gsn_dns_server.h"
#include "modules/dhcp_srvr/gsn_dhcp_srvr.h"
#include "modules/tod/gsn_tod.h"
#include "modules/mdns_sd/gsn_mdns.h"
#include "modules/excp_hdlr/gsn_excp_hdlr.h"
#include "modules/pwr_mgmt/gsn_pwr_mgmt.h"
#include "modules/emu/gsn_emu.h"
#include "modules/wlrpan_driver/gsn_wlrpan_driver.h"
#include "modules/mesh_mgmt/rpl/gsn_rpl.h"
#include "modules/mesh_mgmt/mle/gsn_mle.h"
#include "modules/mesh_mgmt/zigbee_ip/gsn_6lowpan_driver.h"
#include "modules/mesh_mgmt/zigbee_ip/gsn_zigbee_ip.h"
#include "modules/ext_fs/gsn_ext_flash_driver.h"
#include "modules/ext_fs/gsn_ext_flash_fs.h"
#endif /* _GSN_INCLUDES_H_ */
