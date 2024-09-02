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
#ifndef __HTTP_NET_H__
#define __HTTP_NET_H__

/*the idea here is that the platform code will start listening on a port, accept connections, 
bind it to a socket and then pass on that socket along with network read and write function pointers
to http_net to process requests comming in through that socket*/

typedef struct http_net_netops_struct http_net_netops_t;

typedef int (*http_net_read_t)(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs);
typedef int (*http_net_write_t)(int socket, unsigned char *writeBuffer, int writeBufferLength, int timeoutMs);
typedef void (*http_net_disconnect_t)(int socket);

//structure holding underlying network read write functions to plugin net to http server

struct http_net_netops_struct
{
    http_net_read_t http_net_read;
    http_net_write_t http_net_write;
    http_net_disconnect_t http_net_disconnect;
};

void http_net_init_netopsStruct(http_net_netops_t *netops);
http_net_netops_t *http_net_register_netops(http_net_netops_t netops);
void http_net_deregister_netops(void);

#endif