#ifndef _FTW_CONFIG_H_
#define _FTW_CONFIG_H_

#include "ftw_includes.h"
#include "ftw_net.h"
#include "ftw_mqtt.h"

typedef struct  FTW_CONFIG_STRUCT
{
    FTW_NET_CONFIG  xNet;
    FTW_MQTT_CONFIG xMQTT;
}   FTW_CONFIG, _PTR_ FTW_CONFIG_PTR;

FTW_RET FTW_CONFIG_init(char_ptr pFileName);
FTW_RET FTW_CONFIG_loadDefault(void);

FTW_RET FTW_CONFIG_load(char_ptr pFileName);
FTW_RET FTW_CONFIG_save(char_ptr pFileName);

FTW_NET_CONFIG_PTR  FTW_CONFIG_getNet(void);
FTW_MQTT_CONFIG_PTR FTW_CONFIG_getMQTT(void);

#endif
