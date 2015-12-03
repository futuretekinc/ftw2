#ifndef _FSTATICW_FPT_H_

#define _FSTATICW_FPT_H_

#if ( !FS_CAPI_USED )
typedef int (* fg_staticisblkfree_FP_T) ( const FS_VOLUMEINFO * vi, long sector );
typedef int (* fg_staticisblkused_FP_T) ( const FS_VOLUMEINFO * vi, long sector );
typedef int (* fg_staticwear_FP_T) ( FS_MULTI * fm, int drvnum );
typedef int (* fsm_staticwear_FP_T) ( int drvnum );
#endif /* (!FS_CAPI_USED) */

extern _RPST_ fg_staticisblkfree_FP_T fg_staticisblkfree_FP;
extern _RPST_ fg_staticisblkused_FP_T fg_staticisblkused_FP;
extern _RPST_ fg_staticwear_FP_T fg_staticwear_FP;
extern _RPST_ fsm_staticwear_FP_T fsm_staticwear_FP;

#endif
