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
#include <string.h>
#include <stdlib.h>
#include "http_cgi.h"
#include "http_config.h"
#include "http_common.h"

/*defining this as array for the following reasons
1) lookup speed is better than linked list
2) configuration is static and fixed at compile time. This can be adjusted in http_config.h 

return actual buffer content length on success. -1 on failure
*/
http_CGI_pathFunction_t CGI_path[HTTP_MAX_CGI_SIZE]; //hoping compiler to do its job and init to 0

int http_CGI_exec_pathFunction(char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
    int i;
    for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
    {
        if (NULL != CGI_path[i].CGI_path)
        {
            if (0 == strcmp(CGIPath, CGI_path[i].CGI_path))
            {
                return CGI_path[i].CGI_pathFunction(CGIPath, replacerBuffer, bufferLength);
            }
        }
    }
    return -1;
}

http_CGI_pathFunctionHandle_t http_CGI_register_pathFunction(const char *CGIPath, http_CGI_pathFunction_cb CGIPathFunctionCb, http_response_contenttype_t contentType)
{
    //find a uninitialized array element
    if ((NULL == CGIPath) || (NULL == CGIPathFunctionCb) )
    {
        PRINT_ERROR("ERROR: http_CGI_register_pathFunction - NULL CGIPath or CB (%p)\r\n", (void *)CGIPath);
        return 0;
    }
    else
    {
        int i = 0;
        for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
        { //find an empty slot and fill in the registration
            if (NULL == CGI_path[i].CGI_path)
            {
                //allocate memory and copy string to it.
                CGI_path[i].CGI_path = (char *)malloc((size_t)strlen(CGIPath) + 1);
                strncpy(CGI_path[i].CGI_path, CGIPath, strlen(CGIPath));
                CGI_path[i].CGI_path[strlen(CGIPath)] = 0;

                CGI_path[i].CGI_pathFunction = CGIPathFunctionCb;
                CGI_path[i].contentType = contentType;
                return &CGI_path[i];
            }
        }
        PRINT_ERROR("ERROR: http_CGI_register_pathFunction - no more slots to register(%d)\r\n", i);
        return NULL;
    }
    return NULL; //Just a safety net.
}

void http_CGI_deRegister_pathFunction(http_CGI_pathFunctionHandle_t deregisterHandle)
{
    //free the strings?
    //make contents in array 0
    free(deregisterHandle->CGI_path);
    deregisterHandle->CGI_path = NULL;
    deregisterHandle->CGI_pathFunction = NULL;
    deregisterHandle = NULL;
}

//deregister all registrations in one-go. Useful to implement a shutdown function
void http_CGI_deRegister_all(void)
{
    int i = 0;
    for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
    { //find an empty slot and fill in the registration
        if (0 != CGI_path[i].CGI_path)
        {
            //free the string memory from heap
            free(CGI_path[i].CGI_path);
            CGI_path[i].CGI_path = NULL;
            CGI_path[i].CGI_pathFunction = NULL;
        }
    }
}

//function to get contentType form a pathFunction handle
http_response_contenttype_t http_cgi_get_contentType(http_CGI_pathFunctionHandle_t pathFunctionHandle)
{
    if (NULL != pathFunctionHandle)
    {
        return pathFunctionHandle->contentType;
    }
    return 0; //no content type registered
}

//function to get pathFunction handle of a path
http_CGI_pathFunctionHandle_t http_CGI_get_pathFunctionHandle(char *CGIPath)
{
    int i;
    for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
    {
        if (NULL != CGI_path[i].CGI_path)
        {
            if (0 == strcmp(CGIPath, CGI_path[i].CGI_path))
            {
                return &CGI_path[i];
            }
        }
    }
    return NULL;
}

//temporarily commented off to fix pedantic errors. Not major since this is this is a test function. ISSUE #2
#ifdef HTTP_REPLACER_TABLE_DEBUG_PRINTF
//test function to print complete registration table. to be used only for debugging
void http_CGI_printPathFunctionTable(void)
{
    int i;
    printf("FUNCTION\t\tPATH\r\n");
    for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
    {
        printf("%p\t\t", (void *)CGI_path[i].CGI_pathFunction);
        printf("%s\r\n", CGI_path[i].CGI_path);
    }
    printf("==============================================================\r\n");
}
#endif