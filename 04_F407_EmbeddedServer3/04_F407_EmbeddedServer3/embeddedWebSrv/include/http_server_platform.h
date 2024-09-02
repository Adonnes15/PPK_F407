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
#ifndef __HTTP_SERVER_PLATFORM_H__
#define __HTTP_SERVER_PLATFORM_H__

#include "helperFunctions.h"
#include "http_request_parser.h"
#include "http_common.h"
#include "http_config.h"
#include "http_SSI_replacer.h"
#include "http_cgi.h"
#include "http_response.h"
#include "http_local_filesystem.h"
#include "http_file.h"
#include "http_net.h"
#include "http_server.h"
#include "HTTP_file_list.h"
#include <string.h>
#include "socket/include/socket.h"
#include "common/include/nm_common.h"
#include "driver/include/m2m_wifi.h"

extern http_net_netops_t *httpNetops;

int http_server_WINC15x0_init(void);
int http_server_WINC15x0_net_read(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs);
int http_server_WINC15x0_net_write(int socket, unsigned char *writeBuffer, int writeBufferLength, int timeoutMs);
void http_server_WINC15x0_net_disconnect(int socket);

void tcpServerSocketEventHandler(SOCKET sock, uint8_t u8Msg, void *pvMsg);

#endif
