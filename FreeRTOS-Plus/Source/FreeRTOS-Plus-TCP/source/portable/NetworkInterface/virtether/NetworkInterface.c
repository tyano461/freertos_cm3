/*
 * FreeRTOS+TCP V3.1.0
 * Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/*****************************************************************************
 * Note: This file is Not! to be used as is. The purpose of this file is to provide
 * a template for writing a network interface. Each network interface will have to provide
 * concrete implementations of the functions in this file.
 *
 * See the following URL for an explanation of this file and its functions:
 * https://freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/Embedded_Ethernet_Porting.html
 *
 *****************************************************************************/

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "list.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"

#include "dlog.h"

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
 * driver will filter incoming packets and only pass the stack those packets it
 * considers need processing. */
#if (ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0)
#define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer) eProcessBuffer
#else
#define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer) eConsiderFrameForProcessing((pucEthernetBuffer))
#endif

BaseType_t xNetworkInterfaceInitialise(void)
{
    /* FIX ME. */
    d("");
    return pdTRUE;
}

BaseType_t xNetworkInterfaceOutput(NetworkBufferDescriptor_t *const pxNetworkBuffer,
                                   BaseType_t xReleaseAfterSend)
{
    if (pxNetworkBuffer)
    {
        d("eb:%p ip:%lu bp:%u p:%u"
          " ct:%p ow:%p n:%p p:%p iv:%lu len:%u aft:%ld",
          pxNetworkBuffer->pucEthernetBuffer, pxNetworkBuffer->ulIPAddress, pxNetworkBuffer->usBoundPort, pxNetworkBuffer->usPort, pxNetworkBuffer->xBufferListItem.pvContainer, pxNetworkBuffer->xBufferListItem.pvOwner, pxNetworkBuffer->xBufferListItem.pxNext, pxNetworkBuffer->xBufferListItem.pxPrevious, pxNetworkBuffer->xBufferListItem.xItemValue, pxNetworkBuffer->xDataLength, xReleaseAfterSend);
    }
    else
    {
        d("");
    }
    return pdTRUE;
}

void vNetworkInterfaceAllocateRAMToBuffers(NetworkBufferDescriptor_t pxNetworkBuffers[ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS])
{
    (void)pxNetworkBuffers;
    /* FIX ME. */
    d("");
}

BaseType_t xGetPhyLinkStatus(void)
{
    /* FIX ME. */
    d("");
    return pdFALSE;
}

BaseType_t xApplicationGetRandomNumber(uint32_t *pulNumber)
{
    d("");
    return *pulNumber + 1;
}
uint32_t ulApplicationGetNextSequenceNumber(uint32_t ulSourceAddress,
                                            uint16_t usSourcePort,
                                            uint32_t ulDestinationAddress,
                                            uint16_t usDestinationPort)
{
    (void)ulSourceAddress;
    (void)usSourcePort;
    (void)ulDestinationAddress;
    (void)usDestinationPort;
    uint32_t pulNumber = 0;

    d("");
    xApplicationGetRandomNumber(&pulNumber);
    return pulNumber;
}
