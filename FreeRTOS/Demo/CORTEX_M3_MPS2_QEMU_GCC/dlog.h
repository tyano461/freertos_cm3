#ifndef __APP_DLOG_H__
#define __APP_DLOG_H__

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define d(s, ...)                                                                                                                                                   \
    do                                                                                                                                                              \
    {                                                                                                                                                               \
        TaskHandle_t me = xTaskGetCurrentTaskHandle();                                                                                                              \
        printf("[%04x] %s(%d) %s " s " fr:%p \n", (uint16_t)((uint32_t)me & 0xffff), __FILENAME__, __LINE__, __func__, ##__VA_ARGS__, __builtin_return_address(0)); \
    } while (0)

char *b2s(const void *data, int maxlen);
#endif