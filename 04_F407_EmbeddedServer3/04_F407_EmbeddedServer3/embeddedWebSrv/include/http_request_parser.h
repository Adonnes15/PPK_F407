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
#ifndef __HTTP_REQUEST_PARSER_H__
#define __HTTP_REQUEST_PARSER_H__

#include "http_config.h"

//HTTP method enums
typedef enum {
    NONE = -1,
    GET = 1,
    POST,
    HEAD,
    PUT,
    DELETE,
    OPTIONS,
    CONNECT,
    TRACE,
    PATCH
} httpRequest_method_t; //enum to map HTTP request methods

//file type indicator
typedef enum {
    httpFileClass_none = 0,
    httpFileClass_SSI,
    httpFileClass_CGI,
	httpFileClass_Custom,
	httpFileClass_Download
} httpRequest_fileClass_t; //enum to identify regular, SSI or CGI file types.

//parsed HTTP request
typedef struct
{
    httpRequest_fileClass_t fileClass;            //contains the file type
    httpRequest_method_t method;             // contains teh requested method
    char httpFilePath[HTTP_MAX_PATH_LENGTH]; //contains file path
} http_request_t;                            //struct to hold results of parsing a HTTP request. Later header can be added here.

/*
parse and identify a request
*/
int parseRquest_identifyRequest(unsigned char *requestBuffer, http_request_t *httpRequest);

#endif
