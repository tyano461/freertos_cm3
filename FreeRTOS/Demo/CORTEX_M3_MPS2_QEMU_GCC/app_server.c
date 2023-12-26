#include "app_common.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "task.h"
#include "app_common.h"
#include "app_queue.h"

#define SERVER_PORT 7151
#define RX_BUF_SIZE 1000

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

/* functions */
static void server_receive_main(void);

/* variables */
TaskHandle_t server_handle;
char rx_buf[RX_BUF_SIZE];

/* funtions */
void server_task(void *param)
{
    (void)param;
    d("");

    server_receive_main();
    vTaskDelay(0);
    for (;;)
        ;
}

static void server_receive_main(void)
{
    struct freertos_sockaddr xClient, xBindAddress;
    Socket_t xListeningSocket, xConnectedSocket;
    socklen_t xSize = sizeof(xClient);
    static const TickType_t xReceiveTimeOut = portMAX_DELAY;
    const BaseType_t xBacklog = 20;
    BaseType_t result;
    int ret;
    queue_t *queue;

    xListeningSocket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP);
    d("sock:%ld", (int32_t)xListeningSocket);

    configASSERT(xListeningSocket != FREERTOS_INVALID_SOCKET);

    FreeRTOS_setsockopt(xListeningSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO,
                        &xReceiveTimeOut,
                        sizeof(xReceiveTimeOut));

    memset((void *)&xBindAddress, 0, sizeof(xBindAddress));
    xBindAddress.sin_port = (uint16_t)SERVER_PORT;
    xBindAddress.sin_port = FreeRTOS_htons(xBindAddress.sin_port);

    result = FreeRTOS_bind(xListeningSocket, &xBindAddress, sizeof(xBindAddress));
    ERRRET(result < 0, "bind failed.%ld", result);

    result = FreeRTOS_listen(xListeningSocket, xBacklog);
    ERRRET(result < 0, "listen failed.%ld", result);

    d("wait connection");

    for (;;)
    {
        xConnectedSocket = FreeRTOS_accept(xListeningSocket, &xClient, &xSize);
        d("accept");
        configASSERT(xConnectedSocket != FREERTOS_INVALID_SOCKET);

        ret = FreeRTOS_recv(xListeningSocket, rx_buf, RX_BUF_SIZE, 0);
        if (ret < 0)
            continue;
        if (ret == 0)
        {
            d("close");
        }
        else
        {
            ret = FreeRTOS_send(xListeningSocket, rx_buf, ret, 0);
            if (ret < 0)
            {
                d("response send failed.");
                continue;
            }

            queue = pvPortMalloc(ret + sizeof(queue_t));
            if (!queue)
            {
                d("malloc failed.");
                continue;
            }

            queue->len = ret;
            memcpy(queue->data, rx_buf, ret);
            enqueue(queue);
        }
    }
error_return:
    return;
}
#pragma GCC diagnostic pop