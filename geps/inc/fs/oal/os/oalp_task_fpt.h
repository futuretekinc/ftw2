#ifndef _OALP_TASK_FPT_H_
#define _OALP_TASK_FPT_H_

#if OAL_TASK_SUPPORTED
typedef int (* oal_task_create_FP_T) ( oal_task_t * p_task, const oal_task_dsc_t * task_dsc, oal_task_id_t * task_id );
typedef int (* oal_task_delete_FP_T) ( oal_task_t * p_task );
typedef void (* oal_task_yield_FP_T) ( void );
typedef oal_task_id_t (* oal_task_get_id_FP_T) ( void );
typedef void (* oal_task_sleep_FP_T) ( uint32_t ms );

extern _RPST_ oal_task_create_FP_T oal_task_create_FP;
extern _RPST_ oal_task_delete_FP_T  oal_task_delete_FP;
extern _RPST_ oal_task_yield_FP_T oal_task_yield_FP;
extern _RPST_ oal_task_get_id_FP_T oal_task_get_id_FP;
extern _RPST_ oal_task_sleep_FP_T oal_task_sleep_FP;

#endif
#endif

