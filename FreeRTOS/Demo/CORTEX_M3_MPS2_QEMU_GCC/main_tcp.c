#include "app_common.h"
#include <stdio.h>

void main_tcp(void) {
    xTaskCreate(server_task, "server_task", 500, NULL, SERVER_PRIORITY, &server_handle);
    xTaskCreate(client_task, "client_task", 500, NULL, CLIENT_PRIORITY, &client_handle);
    vTaskStartScheduler();
    printf("task not work\n");
}