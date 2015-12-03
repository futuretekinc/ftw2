#if OAL_MUTEX_SUPPORTED
typedef int (* oal_mutex_create_FP_T) ( oal_mutex_t * p_mutex );
typedef int (* oal_mutex_delete_FP_T) ( oal_mutex_t * p_mutex );
typedef int (* oal_mutex_get_FP_T) ( oal_mutex_t * p_mutex );
typedef int (* oal_mutex_put_FP_T) ( oal_mutex_t * p_mutex );

extern _RPST_ oal_mutex_create_FP_T oal_mutex_create_FP;
extern _RPST_ oal_mutex_delete_FP_T oal_mutex_delete_FP;
extern _RPST_ oal_mutex_get_FP_T oal_mutex_get_FP;
extern _RPST_ oal_mutex_get_FP_T oal_mutex_put_FP;

#endif

