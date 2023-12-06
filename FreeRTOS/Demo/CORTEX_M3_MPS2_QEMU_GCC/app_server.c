#include "app_common.h"

TaskHandle_t server_handle;
void server_task(void *param)
{
    (void)param;
    d("");
    vTaskDelay(0);
    for (;;)
        ;
}