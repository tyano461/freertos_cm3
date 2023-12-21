#include "app_common.h"
#include <stdio.h>
#include "FreeRTOS_IP.h"
#include "dlog.h"

/* The MAC address array is not declared const as the MAC address will
normally be read from an EEPROM and not hard coded (in real deployed
applications).*/
static uint8_t ucMACAddress[6] = {0xaa, 0x00, 0x02, 0xaa, 0xbb, 0xcc};

/* Define the network addressing.  These parameters will be used if either
ipconfigUDE_DHCP is 0 or if ipconfigUSE_DHCP is 1 but DHCP auto configuration
failed. */
static const uint8_t ucIPAddress[4] = {192, 168, 100, 2};
static const uint8_t ucNetMask[4] = {255, 255, 255, 0};
static const uint8_t ucGatewayAddress[4] = {192, 168, 100, 1};

/* The following is the address of an OpenDNS server. */
static const uint8_t ucDNSServerAddress[4] = {192, 168, 100, 1};

void main_tcp(void)
{
    d("Build: %s, %s(%s)", __TIME__, __DATE__, GITVER);
    FreeRTOS_IPInit(ucIPAddress,
                    ucNetMask,
                    ucGatewayAddress,
                    ucDNSServerAddress,
                    ucMACAddress);

    xTaskCreate(server_task, "server_task", 500, NULL, SERVER_PRIORITY, &server_handle);
    xTaskCreate(client_task, "client_task", 500, NULL, CLIENT_PRIORITY, &client_handle);
    vTaskStartScheduler();
    printf("task not work\n");
}

void vApplicationIPNetworkEventHook(eIPCallbackEvent_t eNetworkEvent)
{
    static BaseType_t xTasksAlreadyCreated = pdFALSE;

    /* Both eNetworkUp and eNetworkDown events can be processed here. */
    if (eNetworkEvent == eNetworkUp)
    {
        /* Create the tasks that use the TCP/IP stack if they have not already
        been created. */
        if (xTasksAlreadyCreated == pdFALSE)
        {
            /*
             * For convenience, tasks that use FreeRTOS-Plus-TCP can be created here
             * to ensure they are not created before the network is usable.
             */

            xTasksAlreadyCreated = pdTRUE;
        }
    }
}
