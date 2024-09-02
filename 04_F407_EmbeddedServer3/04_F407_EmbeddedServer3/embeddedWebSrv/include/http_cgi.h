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
#ifndef __HTTP_CGI_H__
#define __HTTP_CGI_H__

#include "http_config.h"
#include "http_response.h" //for contentType

/*
callback to be registered for CGI path function along with a string. 
When a registered CGI path function is found in the page, the associated callback will be called to 
provide the dynamic replacement contents 

populate the buffer with required contents and returns actual buffer content length for success
     -1 for failure
     0 for no return content (Just a 200 OK will be sent to client)
*/

typedef int (*http_CGI_pathFunction_cb)(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);

/*The below structure holds the pointer to a static string to be replaced and 
  the corresponding replacer function that returns the replacement string. 
*/
typedef struct
{
    char *CGI_path;
    http_CGI_pathFunction_cb CGI_pathFunction;
    http_response_contenttype_t contentType;
} http_CGI_pathFunction_t;

typedef http_CGI_pathFunction_t *http_CGI_pathFunctionHandle_t;
/*function used to register a CGI pathFunction function. 
    IN : CGI path, associated callback function and contentType of function output
         contentType will be used to form response header
    OUT : 0  = Success
        : -1 = Failure
*/
http_CGI_pathFunctionHandle_t http_CGI_register_pathFunction(const char *CGIPath, http_CGI_pathFunction_cb CGIPathFunctionCb, http_response_contenttype_t contentType);

/*function to populate replacement buffer*/
int http_CGI_exec_pathFunction(char *CGIPath, char *replacerBuffer, unsigned int bufferLength);

/*function to de-register a specific replacement handle
incoming deregisterHandle will invalid NULL after this process.
*/
void http_CGI_deRegister_pathFunction(http_CGI_pathFunctionHandle_t deregisterHandle);

/*function to deregister all registrations in one go. Useful for shutdown*/
void http_CGI_deRegister_all(void);

/*debug function to print teh complete registration table*/
void http_CGI_printPathFunctionTable(void);

/*get return content type of a specified path function using its handle*/
http_response_contenttype_t http_cgi_get_contentType(http_CGI_pathFunctionHandle_t pathFunctionHandle);

//function to get pathFunction handle of a path
http_CGI_pathFunctionHandle_t http_CGI_get_pathFunctionHandle(char *CGIPath);
#endif