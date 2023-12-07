#ifndef FREERTOS_IP_CONFIG_H
#define FREERTOS_IP_CONFIG_H

#define ipconfigBYTE_ORDER  pdFREERTOS_LITTLE_ENDIAN
#define ipconfigUSE_IPv4    1
#define ipconfigUSE_TCP     1
#define ipconfigIPv4_BACKWARD_COMPATIBLE 1
#define ipconfigUSE_DHCP_HOOK 0

#define ipconfigUSE_DHCP 0
#define ipconfigUSE_NETWORK_EVENT_HOOK 1
#endif
