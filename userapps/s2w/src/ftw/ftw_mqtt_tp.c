#include "ftw_includes.h"
#include "ftw_mqtt.h"

#define FTW_MQTT_TP_FORMAT_TOPIC_STATUS "/v/a/g/%s/status"
#define FTW_MQTT_TP_FORMAT_TOPIC_VALUE  "/v/a/g/%s/s/%08x"

FTW_RET FTW_MQTT_TP_pubishLong(FTW_MQTT_CTX_PTR pxCTX, char_ptr pCID, uint_32 ulSID, uint_32 ulValue)
{
    char    pTopic[FTW_MQTT_TOPIC_LENGTH+1];
    char    pMsg[128];
    
    sprintf(pTopic, FTW_MQTT_TP_FORMAT_TOPIC_VALUE, pCID, ulSID);
    sprintf(pMsg, "%11llu, %d", FTW_SYS_TIME_get(NULL), ulValue);
    
    return  FTW_MQTT_publish(pxCTX, 1, pTopic, pMsg);
}