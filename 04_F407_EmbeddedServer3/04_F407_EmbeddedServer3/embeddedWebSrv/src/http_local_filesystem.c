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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_local_filesystem.h"
#include "http_response.h"
#include "http_common.h"
#include "http_config.h"

static http_localfs_filesystem_file_t http_local_filesystem[HTTP_LOCAL_FILESYSTEM_NUMFILES];
static unsigned int fileIndex = 0;

//arrays created using xxd tool.
//python xxd tool:  https://gist.githubusercontent.com/rakete/c6f7795e30d5daf43bb600abc06a9ef4/raw/1d9055f342b5d9c5a284a408859545542a9f4eae/xxd.py

#ifdef HTTP_LOCALFS_INDEX
//index.html
static unsigned char index_html[] = {
    0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x62, 0x6f,
    0x64, 0x79, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x31, 0x3e,
    0x48, 0x45, 0x4c, 0x4c, 0x4f, 0x20, 0x57, 0x4f, 0x52, 0x4c, 0x44, 0x3c,
    0x2f, 0x48, 0x31, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x2f, 0x62, 0x6f, 0x64,
    0x79, 0x3e, 0x0a, 0x3c, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a};
static unsigned int index_html_len = 59;
static const char *path_index_html = "/index.html";
#endif

/*initialize filesystem . increase array size and populate details below to add it to FS
  this is like mounting the fs. to be called only once. To call again, close all open files, deinit and then init.
*/
int http_localfs_init(void)
{
    //init filesystem table to 0. Not necessary since it is a global array. implemented for future scalability
    memset(&http_local_filesystem, 0, HTTP_LOCAL_FILESYSTEM_NUMFILES * sizeof(http_localfs_filesystem_file_t));
#ifdef HTTP_LOCALFS_INDEX
    //register default index file into the local file system.
    http_localfs_registerFile(path_index_html, (char *)&index_html, index_html_len, 0);
#endif
    return HTTP_SUCCESS;
}

//file path should be static string.
int http_localfs_registerFile(const char *filePath, char *file, unsigned int fileLength, http_response_fileType_t optFileType)
{
    if (fileIndex != (HTTP_LOCAL_FILESYSTEM_NUMFILES))
    {
        http_local_filesystem[fileIndex].fileNumber = fileIndex;
        http_local_filesystem[fileIndex].filePath = filePath;
        http_local_filesystem[fileIndex].file = (char *)file;
        http_local_filesystem[fileIndex].fileLength = fileLength;
        http_local_filesystem[fileIndex].optFileType = optFileType;

        fileIndex++;
        return HTTP_SUCCESS;
    }
    else
    {
        PRINT_ERROR("fileSystem Full(%d)\r\n", fileIndex);
        return HTTP_FAILURE;
    }
}

//returns a file pointer
http_localfs_filesystem_fp_t http_localfs_fopen(const char *fileName)
{
    unsigned int i;
    for (i = 0; i < fileIndex; i++)
    {
        if (0 == strcmp(http_local_filesystem[i].filePath, fileName))
        {
            http_localfs_filesystem_fp_t fp;
            fp = (http_localfs_filesystem_fp_t)malloc(sizeof(http_localfs_filesystem_fpRoot_t));
            fp->fileNumber = i; //this can very well be pointer to that array address. but fileno is a standard convention
            fp->filePosition = 0;
            return fp;
        }
    }
    return NULL;
}

//function to close a file pointer after fops are done.
int http_localfs_fclose(http_localfs_filesystem_fp_t fp) //free the fp
{
    if (NULL == fp)
    {
        return HTTP_FAILURE;
    }

    free(fp);
    return HTTP_SUCCESS;
}

//function to unmount the local file system. all FPs should be closed before calling this to avoid memory leaks
int http_localfs_deinit(void)
{
    //but how to track and handle all fps that where malloced without much overhead?
    memset(&http_local_filesystem, 0, HTTP_LOCAL_FILESYSTEM_NUMFILES * sizeof(http_localfs_filesystem_file_t));
    fileIndex=0;
    return HTTP_SUCCESS;
}

/*regular fgetc implementation for the local file system. 
 reads the next character from stream and returns it as an unsigned char cast to an int, or EOF (-1) on end of file or error.
*/
int http_localfs_fgetc(http_localfs_filesystem_fp_t fp)
{
    //input checking
    if (NULL == fp)
    {
        return HTTP_FAILURE;
    }
    //end of file
    if ((fp->filePosition + 1) == (unsigned int)http_local_filesystem[fp->fileNumber].fileLength)
    {
        return -1; //EOF
    }
    else
    { //regular file read
        unsigned char retChar = http_local_filesystem[fp->fileNumber].file[fp->filePosition];
        fp->filePosition++;
        return (int)retChar;
    }
}

//generic feof function. returns -1 if EOF
int http_localfs_feof(http_localfs_filesystem_fp_t fp)
{
    //end of file
    if (fp->filePosition == (unsigned int)(http_local_filesystem[fp->fileNumber].fileLength - 1))
    {
        return -1; //EOF
    }
    return 0;
}

size_t http_localfs_fread(void *ptr, size_t size, size_t nmemb, http_localfs_filesystem_fp_t fp)
{
    if (NULL == ptr)
    {
        return HTTP_FAILURE;
    }
    //end of file
    if ((fp->filePosition + 1) == (unsigned int)http_local_filesystem[fp->fileNumber].fileLength)
    {
        return -1; //EOF
    }
    else
    {
        //calculate actual amount of data remaining in the file.
        unsigned int remainingLen = http_local_filesystem[fp->fileNumber].fileLength - (fp->filePosition + 1);
        //calculate requested data quantity
        unsigned int totalReadLength = (size * nmemb);

        if (remainingLen <= totalReadLength)
        { //when size is smaller than actual file size
            memcpy(ptr, (void *)&http_local_filesystem[fp->fileNumber].file[fp->filePosition], remainingLen+1);
            fp->filePosition += remainingLen;
            return (size_t)remainingLen+1;
        }
        else
        {
            memcpy(ptr, (void *)&http_local_filesystem[fp->fileNumber].file[fp->filePosition], totalReadLength);
            fp->filePosition += totalReadLength;
            return (size_t)totalReadLength;
        }
    }
    return -1;
}

//generic fileno function
int http_localfs_fileno(http_localfs_filesystem_fp_t fp)
{
    return fp->fileNumber;
}

//generic ftell function
long http_localfs_ftell(http_localfs_filesystem_fp_t fp)
{
    return (long)fp->filePosition;
}

//generic rewind function
void http_localfs_rewind(http_localfs_filesystem_fp_t fp)
{
    fp->filePosition = 0;
}

//Generic fseek function
// TODO: reusing  SEEK_SET, SEEK_CUR, and SEEK_END from stdio. need to see if this will work on embedded platforms
int http_localfs_fseek(http_localfs_filesystem_fp_t fp, long offset, int whence)
{
    if (NULL == fp)
    {
        return -1;
    }
    switch (whence)
    {
    case SEEK_SET:
    {
        if (offset >= 0 && offset <= (http_local_filesystem[fp->fileNumber].fileLength - 1))
        {
            fp->filePosition = offset;
            return 0;
        }
        else if (offset >= 0)
        {
            fp->filePosition = http_local_filesystem[fp->fileNumber].fileLength - 1;
            return 0;
        }
        else
        {
            return -1;
        }
        break;
    }
    case SEEK_CUR:
    {
        if (((fp->filePosition + offset) >= 0) && ((fp->filePosition + offset) < (unsigned int)http_local_filesystem[fp->fileNumber].fileLength))
        {
            fp->filePosition += offset;
            return 0;
        }
        else
        {
            return -1;
        }
        break;
    }
    case SEEK_END:
    {
        if (offset > 0)
        {
            return -1;
        }
        else if ((fp->filePosition + offset) >= 0)
        {
            fp->filePosition += offset;
            return 0;
        }
        else
        {
            fp->filePosition = 0;
            return 0;
        }
        break;
    }
    default:
        return -1;
        break;
    }
    return -1;
}
