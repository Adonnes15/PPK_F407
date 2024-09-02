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
#ifndef __HTTP_FILE_H__
#define __HTTP_FILE_H__
#include <stdio.h>

/*
Uses standard terminology and signature as standard c file operations
expects same behaviour as standard C file operations
some quick references: 
    EOF = -1
    whence = SEEK_SET,SEEK_CUR or SEEK_END from stdio.h
file pointer (fp) is cast to void* to support different FS implementations
*/

typedef int (*http_file_fclose_t)(void *fp);
typedef int (*http_file_fgetc_t)(void *fp);
typedef int (*http_file_feof_t)(void *fp);
typedef void* (*http_file_fopen_t)(const char *filename); //returns file pointer (fp)
typedef int (*http_file_fseek_t)(void *fp, long offset, int whence);
typedef size_t (*http_file_fread_t)(void *ptr, size_t size, size_t nmemb, void *fp);

typedef struct
{
    http_file_fopen_t fopen;
    http_file_fclose_t fclose;
    http_file_fread_t fread;
    http_file_fgetc_t fgetc;
    http_file_fseek_t fseek;
    http_file_feof_t eof;
} http_file_fops_t; //type to register underlying file system fops to the HTTP server.

//global variable used to access fops by http server
extern http_file_fops_t http_file_fops;

//deregister all fops and make the structure NULL
void http_file_deregister_fops(void);

//register fops to teh http server
int http_file_register_fops(http_file_fops_t fops);

//make a new fops structure contents all NULL
void http_file_init_fopsStruct(http_file_fops_t *fops);

#endif