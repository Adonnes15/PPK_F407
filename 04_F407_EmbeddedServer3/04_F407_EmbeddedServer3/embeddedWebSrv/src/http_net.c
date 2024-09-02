/* Copyright (c) 2011-2018 Atmel Corporation. All rights reserved.
*
* \asf_license_start
*
* \page License
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
*    Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \asf_license_stop
*
*/
#include "http_net.h"
#include "http_common.h"
#include <stdio.h>
#include <string.h>

/*currently supporting only one network at a time - should this go into http_server.c?
    potentially many can be registersd and corresponding address can be returned.
*/
static http_net_netops_t http_net_netops;

/*init a plain fops structure*/
void http_net_init_netopsStruct(http_net_netops_t *netops)
{
    if (NULL != netops)
    {
        memset(netops, 0, sizeof(http_net_netops_t));
    }
}
/*function to register fops to http server*/
http_net_netops_t *http_net_register_netops(http_net_netops_t netops)
{
    memcpy((void *)&http_net_netops, (void *)&netops, sizeof(http_net_netops_t));
    return &http_net_netops;
}

/*function to deregister fops from http server*/
void http_net_deregister_netops(void)
{
    memset(&http_net_netops, 0, sizeof(http_net_netops_t));
}
