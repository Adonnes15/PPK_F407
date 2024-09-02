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
#ifndef __HTTP_SSI_REPLACER_H__
#define __HTTP_SSI_REPLACER_H__

#include "http_config.h"

/*
callback to be registered for SSI replacement along with a string. 
When a registered SSI string is found in the page, the associated callback will be called to 
provide the dynamic replacement contents 

populate the buffer with required contents and return 0 for success;
*/

typedef int (*http_SSI_replacer_cb)(const char *SSIString, char *replacerBuffer, unsigned int bufferLength);

/*The below structure holds the pointer to a static string to be replaced and 
  the corresponding replacer function that returns the replacement string. 
*/
typedef struct
{
    char *SSI_String;
    http_SSI_replacer_cb SSI_stringReplacer;
} http_SSI_replacer_t;

typedef http_SSI_replacer_t *http_SSI_replacerHandle_t;

extern http_SSI_replacer_t http_SSI_replacer[];

/*function used to register a SSI string replacer function. 
    IN : "static" string to be replaced and associated callback function
    OUT : 0  = Success
        : -1 = Failure
*/
http_SSI_replacerHandle_t http_SSI_register_replacer(const char *SSIString, http_SSI_replacer_cb SSIReplacerCb);

/*function to populate replacement buffer*/
int http_SSI_get_replacer_string(char *SSIString, char *replacerBuffer, unsigned int bufferLength);

/*function to de-register a specific replacement handle
incoming deregisterHandle will invalid NULL after this process.
*/
void http_SSI_deRegister_replacer(http_SSI_replacerHandle_t deregisterHandle);

/*function to deregister all registrations in one go. Useful for shutdown*/
void http_SSI_deRegister_all(void);

/*debug function to print teh complete registration table*/
void http_SSI_printReplacerTable(void);

#endif