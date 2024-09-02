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
#ifndef __HTTP_CONFIG_H__
#define __HTTP_CONFIG_H__

//#define DEBUG_ERROR 0 //this will be passed as build environment variable

//Max length of path supported by the system including string termination
#define HTTP_MAX_PATH_LENGTH 100

//Max length of method string including termination
#define HTTP_MAX_METHOD_LENGTH 8

//Max number of SSI strings supported
#define HTTP_MAX_SSI_COUNT 5
//max length of an SSI string in html
#define HTTP_MAX_SSI_LENGTH 15
//max length of a SSI replacement string 
#define HTTP_MAX_SSI_REPLACE_LENGTH 150

//maximum occurance of an SSI string per read buffer
#define HTTP_MAX_PER_SSI_COUNT 10
//Max number of CGIs supported
#define HTTP_MAX_CGI_SIZE 5

//populate a default index for local FS
//#define HTTP_LOCALFS_INDEX

//server buffer sizes. All these are created locally per request. 
#define HTTP_SERVER_READ_BUFFER_SIZE (unsigned int)1024 //buffer used to read incoming request from network
#define HTTP_SERVER_HEADER_BUFFER_SIZE (unsigned int)256 //buffer used to form and later send response through socket. this can be lesser
#define HTTP_SERVER_FREAD_BUFFER_SIZE (unsigned int)1024 //buffer used to send contents. chunked vs regular send will be based on this vs filesize
#define HTTP_SERVER_CGI_BUFFER_SIZE (unsigned int)256 //buffer used to hold response from CGI.

//root page to remap when requested path is "/"
#define HTTP_SERVER_ROOT_PAGE	"/index.html"

//server read timeout
#define HTTP_SERVER_TIMOUT_MS 100

#endif
