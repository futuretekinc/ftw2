#if OAL_EVENT_SUPPORTED
typedef int (* oal_event_create_FP_T) ( oal_event_t * p_event );
typedef int (* oal_event_delete_FP_T) ( oal_event_t * p_event );
typedef int (* oal_event_get_FP_T) ( oal_event_t * p_event, oal_event_flags_t wflags, oal_event_flags_t * sflags, oal_event_timeout_t timeout );
typedef int (* oal_event_set_FP_T) ( oal_event_t * p_event, oal_event_flags_t flags, oal_task_id_t task_id );
typedef int (* oal_event_set_int_FP_T) ( oal_event_t * p_event, oal_event_flags_t flags,  oal_task_id_t task_id );
#endif

extern _RPST_ oal_event_create_FP_T oal_event_create_FP;
extern _RPST_ oal_event_delete_FP_T oal_event_delete_FP;
extern _RPST_ oal_event_get_FP_T oal_event_get_FP;
extern _RPST_ oal_event_set_FP_T oal_event_set_FP;
extern _RPST_ oal_event_set_int_FP_T oal_event_set_int_FP;

