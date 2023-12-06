#include "app_common.h"

TaskHandle_t client_handle;
void client_task(void *param)
{
    (void)param;
    d("");
    for (;;)
        ;
}