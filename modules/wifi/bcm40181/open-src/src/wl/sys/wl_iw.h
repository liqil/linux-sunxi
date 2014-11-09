/*
 * Linux Wireless Extensions support
 *
 * Copyright (C) 1999-2011, Broadcom Corporation
 * 
 *         Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 * 
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 * 
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 *
 * $Id: wl_iw.h,v 1.15.80.6 2010/12/23 01:13:23 Exp $
 */

#ifndef _wl_iw_h_
#define _wl_iw_h_

#include <linux/wireless.h>

#include <typedefs.h>
#include <proto/ethernet.h>
#include <wlioctl.h>

#include <linux/semaphore.h>       //add by barbara 2011.5.12

#define WL_SCAN_PARAMS_SSID_MAX 	10
#define GET_SSID			"SSID="
#define GET_CHANNEL			"CH="
#define GET_NPROBE 			"NPROBE="
#define GET_ACTIVE_ASSOC_DWELL  	"ACTIVE="
#define GET_PASSIVE_ASSOC_DWELL  	"PASSIVE="
#define GET_HOME_DWELL  		"HOME="
#define GET_SCAN_TYPE			"TYPE="

/* Lin - Has Android changed these strings ? */
#define BAND_GET_CMD				"GETBAND"
#define BAND_SET_CMD				"SETBAND"
#define DTIM_SKIP_GET_CMD			"DTIMSKIPGET"
#define DTIM_SKIP_SET_CMD			"DTIMSKIPSET"
#define SETSUSPEND_CMD				"SETSUSPENDOPT"
#define PNOSSIDCLR_SET_CMD			"PNOSSIDCLR"
/* Lin - Is the extra space needed? */
#define PNOSETUP_SET_CMD			"PNOSETUP " /* TLV command has extra end space */
#define PNOENABLE_SET_CMD			"PNOFORCE"
#define PNODEBUG_SET_CMD			"PNODEBUG"

#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"

/* Structure to keep global parameters */
typedef struct wl_iw_extra_params {
	int 	target_channel; /* target channel */
} wl_iw_extra_params_t;

#define SOFTAP 1
/* ============================================== */
/* Defines from wlc_pub.h */
#define	WL_IW_RSSI_MINVAL		-200	/* Low value, e.g. for forcing roam */
#define	WL_IW_RSSI_NO_SIGNAL	-91	/* NDIS RSSI link quality cutoffs */
#define	WL_IW_RSSI_VERY_LOW	-80	/* Very low quality cutoffs */
#define	WL_IW_RSSI_LOW		-70	/* Low quality cutoffs */
#define	WL_IW_RSSI_GOOD		-68	/* Good quality cutoffs */
#define	WL_IW_RSSI_VERY_GOOD	-58	/* Very good quality cutoffs */
#define	WL_IW_RSSI_EXCELLENT	-57	/* Excellent quality cutoffs */
#define	WL_IW_RSSI_INVALID	 0	/* invalid RSSI value */
#define MAX_WX_STRING 80
#define isprint(c) bcm_isprint(c)
#define WL_IW_SET_ACTIVE_SCAN	(SIOCIWFIRSTPRIV+1)
#define WL_IW_GET_RSSI			(SIOCIWFIRSTPRIV+3)
#define WL_IW_SET_PASSIVE_SCAN	(SIOCIWFIRSTPRIV+5)
#define WL_IW_GET_LINK_SPEED	(SIOCIWFIRSTPRIV+7)
#define WL_IW_GET_CURR_MACADDR	(SIOCIWFIRSTPRIV+9)
#define WL_IW_SET_STOP				(SIOCIWFIRSTPRIV+11)
#define WL_IW_SET_START			(SIOCIWFIRSTPRIV+13)

/* IWPRIV IOCTLS for SOFTAP */
#define WL_SET_AP_CFG           (SIOCIWFIRSTPRIV+15)
#define WL_AP_STA_LIST          (SIOCIWFIRSTPRIV+17)
#define WL_AP_MAC_FLTR	        (SIOCIWFIRSTPRIV+19)
#define WL_AP_BSS_START         (SIOCIWFIRSTPRIV+21)
#define AP_LPB_CMD              (SIOCIWFIRSTPRIV+23)
#define WL_AP_STOP              (SIOCIWFIRSTPRIV+25)
#define WL_FW_RELOAD            (SIOCIWFIRSTPRIV+27)
#define WL_COMBO_SCAN            (SIOCIWFIRSTPRIV+29)
#define WL_AP_SPARE3            (SIOCIWFIRSTPRIV+31)
#define 		G_SCAN_RESULTS 8*1024
#define 		WE_ADD_EVENT_FIX	0x80
#define          G_WLAN_SET_ON	0
#define          G_WLAN_SET_OFF	1

typedef struct wl_iw {
	char nickname[IW_ESSID_MAX_SIZE];

	struct iw_statistics wstats;

	int spy_num;
	int wpaversion;			/* wpaversion setting */
	int pcipher;			/* pairwise cipher setting */
	int gcipher;			/* group cipher setting  */
	int privacy_invoked; 		/* IW_AUTH_PRIVACY_INVOKED setting */

	struct ether_addr spy_addr[IW_MAX_SPY];
	struct iw_quality spy_qual[IW_MAX_SPY];
	void  *wlinfo;
	dhd_pub_t * pub;
} wl_iw_t;

int	 wl_control_wl_start(struct net_device *dev);
#define WLC_IW_SS_CACHE_MAXLEN				512
#define WLC_IW_SS_CACHE_CTRL_FIELD_MAXLEN	32
#define WLC_IW_BSS_INFO_MAXLEN 				\
	(WLC_IW_SS_CACHE_MAXLEN - WLC_IW_SS_CACHE_CTRL_FIELD_MAXLEN)

typedef struct wl_iw_ss_cache {
	uint32 buflen;
	uint32 version;
	uint32 count;
	wl_bss_info_t bss_info[1];
	char dummy[WLC_IW_BSS_INFO_MAXLEN - sizeof(wl_bss_info_t)];
	int dirty;
	struct wl_iw_ss_cache *next;
} wl_iw_ss_cache_t;

typedef struct wl_iw_ss_cache_ctrl {
	wl_iw_ss_cache_t *m_cache_head;	/* specific scan cache head */
	int m_link_down;		/* link down indicator flag */
	int m_timer_expired;		/* specifc scan cache timer expiration flag */
	char m_active_bssid[ETHER_ADDR_LEN];	/* bssid of currently associated AP */
	uint m_prev_scan_mode;	/* current scan type flag, specific or broadcast */
	uint m_cons_br_scan_cnt;	/* consecutive broadcast scan counter */
	struct timer_list *m_timer;	/* specific scan cache timer */
} wl_iw_ss_cache_ctrl_t;

typedef enum broadcast_first_scan {
	BROADCAST_SCAN_FIRST_IDLE = 0,
	BROADCAST_SCAN_FIRST_STARTED,
	BROADCAST_SCAN_FIRST_RESULT_READY,
	BROADCAST_SCAN_FIRST_RESULT_CONSUMED
} broadcast_first_scan_t;
#ifdef SOFTAP
#define SSID_LEN	33
#define SEC_LEN		16
#define KEY_LEN		65
#define PROFILE_OFFSET	32
struct ap_profile {
	uint8	ssid[SSID_LEN];
	uint8	sec[SEC_LEN];
	uint8	key[KEY_LEN];
	uint32	channel; /* 0 for auto */
	uint32	preamble;
	uint32	max_scb;	/* maxmium number of station */
};


#define MACLIST_MODE_DISABLED	0
#define MACLIST_MODE_ENABLED	1
#define MACLIST_MODE_ALLOW		2
struct mflist {
	uint count;
	struct ether_addr ea[16];
};
struct mac_list_set {
	uint32	mode;
	struct mflist white_list;
	struct mflist black_list;
};
#endif   /* #ifdef SOFTAP */

#if WIRELESS_EXT > 12
#include <net/iw_handler.h>
extern const struct iw_handler_def wl_iw_handler_def;
#endif /* WIRELESS_EXT > 12 */

extern int wl_iw_ioctl(struct net_device *dev, struct ifreq *rq, int cmd);
extern void wl_iw_event(struct net_device *dev, wl_event_msg_t *e, void* data);
extern int wl_iw_get_wireless_stats(struct net_device *dev, struct iw_statistics *wstats);
int wl_iw_attach(struct net_device *dev, void * dhdp);
void wl_iw_detach(void);

extern int net_os_wake_lock(struct net_device *dev);
extern int net_os_wake_unlock(struct net_device *dev);
extern int net_os_wake_lock_timeout(struct net_device *dev);
extern int net_os_wake_lock_timeout_enable(struct net_device *dev);
extern int net_os_set_suspend_disable(struct net_device *dev, int val);
extern int net_os_set_suspend(struct net_device *dev, int val);
extern int net_os_set_dtim_skip(struct net_device *dev, int val);
extern int net_os_set_packet_filter(struct net_device *dev, int val);
extern int net_os_send_hang_message(struct net_device *dev);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 27)
#define IWE_STREAM_ADD_EVENT(info, stream, ends, iwe, extra) \
	iwe_stream_add_event(info, stream, ends, iwe, extra)
#define IWE_STREAM_ADD_VALUE(info, event, value, ends, iwe, event_len) \
	iwe_stream_add_value(info, event, value, ends, iwe, event_len)
#define IWE_STREAM_ADD_POINT(info, stream, ends, iwe, extra) \
	iwe_stream_add_point(info, stream, ends, iwe, extra)
#else
#define IWE_STREAM_ADD_EVENT(info, stream, ends, iwe, extra) \
	iwe_stream_add_event(stream, ends, iwe, extra)
#define IWE_STREAM_ADD_VALUE(info, event, value, ends, iwe, event_len) \
	iwe_stream_add_value(event, value, ends, iwe, event_len)
#define IWE_STREAM_ADD_POINT(info, stream, ends, iwe, extra) \
	iwe_stream_add_point(stream, ends, iwe, extra)
#endif

extern int dhd_pno_enable(dhd_pub_t *dhd, int pfn_enabled);
extern int dhd_pno_clean(dhd_pub_t *dhd);
extern int dhd_pno_set(dhd_pub_t *dhd, wlc_ssid_t* ssids_local, int nssid, uchar  scan_fr);
extern int dhd_pno_get_status(dhd_pub_t *dhd);
extern int dhd_dev_pno_reset(struct net_device *dev);
extern int dhd_dev_pno_set(struct net_device *dev, wlc_ssid_t* ssids_local,
	int nssid, uchar  scan_fr);
extern int dhd_dev_pno_enable(struct net_device *dev,  int pfn_enabled);
extern int dhd_dev_get_pno_status(struct net_device *dev);

#define PNO_TLV_PREFIX			'S'
#define PNO_TLV_VERSION			1
#define PNO_TLV_SUBVERSION 		0
#define PNO_TLV_RESERVED		0
#define PNO_TLV_TYPE_SSID_IE		'S'
#define PNO_TLV_TYPE_TIME		'T'
#define  PNO_EVENT_UP			"PNO_EVENT"

typedef struct cmd_tlv {
	char prefix;
	char version;
	char subver;
	char reserved;
} cmd_tlv_t;




typedef struct cscan_tlv {
	char prefix;
	char version;
	char subver;
	char reserved;
} cscan_tlv_t;

#define CSCAN_COMMAND				"CSCAN "
#define CSCAN_TLV_PREFIX 			'S'
#define CSCAN_TLV_VERSION			1
#define CSCAN_TLV_SUBVERSION			0
#define CSCAN_TLV_TYPE_SSID_IE          'S'
#define CSCAN_TLV_TYPE_CHANNEL_IE   'C'
#define CSCAN_TLV_TYPE_NPROBE_IE     'N'
#define CSCAN_TLV_TYPE_ACTIVE_IE      'A'
#define CSCAN_TLV_TYPE_PASSIVE_IE    'P'
#define CSCAN_TLV_TYPE_HOME_IE         'H'
#define CSCAN_TLV_TYPE_STYPE_IE        'T'

extern int wl_iw_parse_channel_list_tlv(char** list_str, uint16* channel_list,
                                        int channel_num, int *bytes_left);

extern int wl_iw_parse_data_tlv(char** list_str, void  *dst, int dst_size,
                                const char token, int input_size, int *bytes_left);

extern int wl_iw_parse_ssid_list_tlv(char** list_str, wlc_ssid_t* ssid,
                                     int max, int *bytes_left);

extern int wl_iw_parse_ssid_list(char** list_str, wlc_ssid_t* ssid, int idx, int max);

extern int wl_iw_parse_channel_list(char** list_str, uint16* channel_list, int channel_num);


#define NETDEV_PRIV(dev)	(*(wl_iw_t **)netdev_priv(dev))

#endif /* _wl_iw_h_ */
