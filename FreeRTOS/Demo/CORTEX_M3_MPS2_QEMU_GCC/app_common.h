#ifndef __APP_COMMON_H__
#define __APP_COMMON_H__

#include "FreeRTOS.h"
#include "task.h"
#include "dlog.h"

#define SERVER_PRIORITY (tskIDLE_PRIORITY + 2)
#define CLIENT_PRIORITY (tskIDLE_PRIORITY + 2)

extern TaskHandle_t server_handle;
extern TaskHandle_t client_handle;

void main_tcp(void);
void create_server_task(void);
void create_client_task(void);
void server_task(void *param);
void client_task(void *param);
#endif