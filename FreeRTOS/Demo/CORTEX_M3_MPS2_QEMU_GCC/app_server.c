#include "app_common.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static void vCreateTCPServerSocket(void);

TaskHandle_t server_handle;
void server_task(void *param)
{
    (void)param;
    d("");

    vCreateTCPServerSocket();
    vTaskDelay(0);
    for (;;)
        ;
}

static void vCreateTCPServerSocket(void)
{
    struct freertos_sockaddr xClient, xBindAddress;
    Socket_t xListeningSocket, xConnectedSocket;
    socklen_t xSize = sizeof(xClient);
    static const TickType_t xReceiveTimeOut = portMAX_DELAY;
    const BaseType_t xBacklog = 20;

    xListeningSocket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP);
    d("sock:%ld", (int32_t)xListeningSocket);

    configASSERT(xListeningSocket != FREERTOS_INVALID_SOCKET);

    FreeRTOS_setsockopt(xListeningSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO,
                        &xReceiveTimeOut,
                        sizeof(xReceiveTimeOut));

    memset((void *)&xBindAddress, 0, sizeof(xBindAddress));
    xBindAddress.sin_port = (uint16_t)10000;
    xBindAddress.sin_port = FreeRTOS_htons(xBindAddress.sin_port);

    FreeRTOS_bind(xListeningSocket, &xBindAddress, sizeof(xBindAddress));
    d("bind");

    FreeRTOS_listen(xListeningSocket, xBacklog);
    d("listen");

    for (;;)
    {
        xConnectedSocket = FreeRTOS_accept(xListeningSocket, &xClient, &xSize);
        d("accept");
        configASSERT(xConnectedSocket != FREERTOS_INVALID_SOCKET);
    }
}
#pragma GCC diagnostic pop