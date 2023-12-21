#include "app_common.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

/* definitions */
#define BUF_SIZE 10
/* functions */
void vTCPSend(char *pcBufferToTransmit, const size_t xTotalLengthToSend);

/* vaiables */
static const char *msg = "aiueo";
static uint8_t buf[BUF_SIZE];
TaskHandle_t client_handle;

static inline int snlen(const char *s, int maxlen)
{
    int i = 0;
    while (i < maxlen && *s++)
        i++;
    return i;
}

/* functions */
void client_task(void *param)
{
    (void)param;
    size_t len;
    d("");

    len = snlen(msg, BUF_SIZE - 1);
    memcpy(buf, msg, len + 1);
    // vTCPSend((char *)buf, len);
    for (;;)
        vTaskDelay(100);
}

void vTCPSend(char *pcBufferToTransmit, const size_t xTotalLengthToSend)
{
    Socket_t xSocket;
    struct freertos_sockaddr xRemoteAddress;
    BaseType_t xAlreadyTransmitted = 0, xBytesSent = 0;
    size_t xLenToSend;

    d("IN");
    xRemoteAddress.sin_port = FreeRTOS_htons(10000);
    xRemoteAddress.sin_addr = FreeRTOS_inet_addr_quick(192, 168, 100, 1);

    /* Create a socket. */
    xSocket = FreeRTOS_socket(FREERTOS_AF_INET4,
                              FREERTOS_SOCK_STREAM,
                              FREERTOS_IPPROTO_TCP);
    configASSERT(xSocket != FREERTOS_INVALID_SOCKET);

    d("socket");
    if (FreeRTOS_connect(xSocket, &xRemoteAddress, sizeof(xRemoteAddress)) == 0)
    {
        d("connected");
        while ((size_t)xAlreadyTransmitted < xTotalLengthToSend)
        {
            xLenToSend = xTotalLengthToSend - xAlreadyTransmitted;
            xBytesSent = FreeRTOS_send(/* The socket being sent to. */
                                       xSocket,
                                       /* The data being sent. */
                                       &(pcBufferToTransmit[xAlreadyTransmitted]),
                                       /* The remaining length of data to send. */
                                       xLenToSend,
                                       /* ulFlags. */
                                       0);

            if (xBytesSent >= 0)
            {
                /* Data was sent successfully. */
                xAlreadyTransmitted += xBytesSent;
            }
            else
            {
                /* Error - break out of the loop for graceful socket close. */
                break;
            }
        }
    }
    else
    {
        d("not connected");
    }

    /* Initiate graceful shutdown. */
    FreeRTOS_shutdown(xSocket, FREERTOS_SHUT_RDWR);

    /* Wait for the socket to disconnect gracefully (indicated by FreeRTOS_recv()
       returning a -pdFREERTOS_ERRNO_EINVAL error) before closing the socket. */
    while (FreeRTOS_recv(xSocket, pcBufferToTransmit, xTotalLengthToSend, 0) >= 0)
    {
        /* Wait for shutdown to complete.  If a receive block time is used then
           this delay will not be necessary as FreeRTOS_recv() will place the RTOS task
           into the Blocked state anyway. */
        vTaskDelay(pdTICKS_TO_MS(250));

        /* Note - real applications should implement a timeout here, not just
        loop forever. */
    }

    /* The socket has shut down and is safe to close. */
    FreeRTOS_closesocket(xSocket);
    d("OUT");
}
