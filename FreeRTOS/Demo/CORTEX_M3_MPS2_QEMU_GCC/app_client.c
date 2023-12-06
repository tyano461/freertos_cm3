#include "app_common.h"
#include "FreeRTOS_Sockets.h"

/* functions */
static void vCreateTCPClientSocket(void);

TaskHandle_t client_handle;
void client_task(void *param)
{
    (void)param;
    d("");
    vCreateTCPClientSocket();
    for (;;)
        ;
}

static void vCreateTCPClientSocket(void)
{
    Socket_t xClientSocket;
    socklen_t xSize = sizeof(struct freertos_sockaddr);
    static const TickType_t xTimeOut = pdMS_TO_TICKS(2000);

    xClientSocket = FreeRTOS_socket(FREERTOS_AF_INET,
                                    FREERTOS_SOCK_STREAM,
                                    FREERTOS_IPPROTO_TCP);
    d("sock:%ld", (int32_t)xClientSocket);
    configASSERT(xClientSocket != FREERTOS_INVALID_SOCKET);

    FreeRTOS_setsockopt(xClientSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO, &xTimeOut,
                        sizeof(xTimeOut));

    FreeRTOS_setsockopt(xClientSocket,
                        0,
                        FREERTOS_SO_SNDTIMEO,
                        &xTimeOut,
                        sizeof(xTimeOut));
    d("sockopt");

    FreeRTOS_bind(xClientSocket, NULL, xSize);
    d("bind");
}