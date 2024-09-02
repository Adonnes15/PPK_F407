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
/*
   Function to parse incoming request buffer and identify the request method,
   and path. 

   At this initial stage , query strings and headers will not be handled since
   the initial version is targeting just GET requests. 
*/

#include "http_request_parser.h"
#include "helperFunctions.h"
#include "http_config.h"
#include "http_common.h"
#include <string.h>
#include <stdio.h>

//list of file types supporting SSI
unsigned int httpFileType_SSIList_size = 4;
const char *const httpFileType_SSIList[] = {"shtml", "shtm", "ssi", "xml"};
//list of file types supporting CGI
unsigned int httpFileType_CGIList_size = 3;
const char *const httpFileType_CGIList[] = {"cgi", "sh", "exe"};

//list of custom file types
unsigned int httpFileType_customList_size = 3;
const char *const httpFileType_customList[] = {"wact", "sheesh", "armitage"};

unsigned int httpFileType_DownloadList_size = 2;
const char *const httpFileType_DownloadList[] = {"shool", "download"};

static httpRequest_method_t parseRequest_mapMethodToEnum(char *method)
{
    /*since most requesters send method in caps, toUpper is not applied */
    if (0 == strcmp(method, "GET"))
        return GET;
    else if (0 == strcmp(method, "POST"))
        return POST;
    else if (0 == strcmp(method, "PUT"))
        return PUT;
    else if (0 == strcmp(method, "HEAD"))
        return HEAD;
    else if (0 == strcmp(method, "DELETE"))
        return DELETE;
    else if (0 == strcmp(method, "OPTIONS"))
        return OPTIONS;
    else if (0 == strcmp(method, "CONNECT"))
        return CONNECT;
    else if (0 == strcmp(method, "TRACE"))
        return TRACE;
    else if (0 == strcmp(method, "PATCH"))
        return PATCH;
    else
        return NONE;
}

//identify whether the requested file is CGI/SSI or just for regular contents.
static httpRequest_fileClass_t parseRequest_identifyFileClass(char *path)
{
    char *fileType = strrchr(path, '.'); //can hit some real corner case where there is no extension and thre is a . in path
    if (0 == fileType)
    {
        return httpFileClass_none;
    }
    else
    {
        fileType += 1; //to remove the .
    }

    unsigned int i = 0;
    for (i = 0; i < httpFileType_SSIList_size; i++)
    {
        if (0 == strcmp(httpFileType_SSIList[i], fileType))
            return httpFileClass_SSI;
    }

    for (i = 0; i < httpFileType_CGIList_size; i++)
    {
        if (0 == strcmp(httpFileType_CGIList[i], fileType))
            return httpFileClass_CGI;
    }

    for (i = 0; i < httpFileType_customList_size; i++)
     {
            if (0 == strcmp(httpFileType_customList[i], fileType))
                return httpFileClass_Custom;
     }
    for (i = 0; i < httpFileType_DownloadList_size; i++)
     {
            if (0 == strcmp(httpFileType_DownloadList[i], fileType))
                return httpFileClass_Download;
     }

    return httpFileClass_none;
}
int parseRquest_identifyRequest(unsigned char *requestBuffer, http_request_t *httpRequest)
{
    /*TODO: suppot Query parsing*/
	printf("Request Buffer : %s",requestBuffer);
    const char *startOfPath = strchr((char*)requestBuffer, ' ') + 1;
    const char *endOfPath;

    //AK
//    const char *startOfQuery;
//    const char *endOfQuery;
    //

//    if (strstr((char*)requestBuffer, "?"))
//    { //if there is a query string, path ends at the start of query
//        endOfPath = strchr(startOfPath, '?');
//
////        //AK
////        startOfQuery = endOfPath + 1; //to not include the '?'
////        if (strstr((char*)requestBuffer, "HTTP/1."))
////        {
////        	endOfQuery = strchr(startOfQuery, ' '); //if there is a HTTP version mentioned, Query ends there
////        }
////        else
////        {
////                endOfQuery = strchr(startOfQuery, '\n'); //if none of the above, Query ends at newline
////        }
////        //
//    }
    if (strstr((char*)requestBuffer, "HTTP/1."))
    { //if there is a HTTP version mentioned, path ends there
        endOfPath = strchr(startOfPath, ' ');
        //startOfQuery = -1; //AK query dosen't exist
    }
    else
    {
        endOfPath = strchr(startOfPath, '\n'); //if none of the above, path ends at newline
        //startOfQuery = -1; //AK query dosen't exist
    }
    //getting enough memory
    //TODO: will this work in embedded?
    char *methordToken = strtok((char*)requestBuffer, " ");
    char method[strlen(methordToken) + 1];
    char path[endOfPath - startOfPath];

//    // AK making query
//    if (startOfQuery != -1){  //If query exits
//    char query[endOfPath-startOfQuery];
//    strncpy(query, startOfQuery, endOfQuery - startOfQuery);
//    }
//    //

    //copying internally
    strncpy(method, methordToken, strlen(methordToken));
    strncpy(path, startOfPath, endOfPath - startOfPath);

	
    //null termination
	method[sizeof(method)-1] = 0; //-1 to delete trailing space
    path[sizeof(path)] = 0; 
	//parse and copy method for returning.
    httpRequest->method = parseRequest_mapMethodToEnum(method);

    //decode URL and copy path for returning.
    char decodedURL[sizeof(path)];
    url_decode(path, decodedURL);
    
	if(0==strcmp(decodedURL,"/")){ //redirect / to configured ROOT page.
		strncpy(httpRequest->httpFilePath, HTTP_SERVER_ROOT_PAGE, HTTP_MAX_PATH_LENGTH);
	}
	else{
		strncpy(httpRequest->httpFilePath, decodedURL, HTTP_MAX_PATH_LENGTH);
	}

    //decode file type and add copy it for returning
    httpRequest->fileClass = parseRequest_identifyFileClass(path);

    //return success
    return HTTP_SUCCESS;
}
