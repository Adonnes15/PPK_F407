/*
 * SD.c
 *
 *  Created on: Aug 21, 2024
 *      Author: NinaadKotasthane
 */
#include "SD.h"
#include "fatfs.h"
#include <stdio.h>
#include <string.h>
#include "main.h"

FATFS FatFs;
FIL Fil;
FRESULT FR_Status;
FATFS *FS_Ptr;
UINT RWC, WWC; // Read/Write Word Counter
DWORD FreeClusters;
uint32_t TotalSize, FreeSpace;
char RW_Buffer[200];

void SD_Card_Init(void)
{
    FR_Status = f_mount(&FatFs, SDPath, 1);
    if (FR_Status != FR_OK)
    {
      printf("Error! While Mounting SD Card, Error Code: (%i)\r\n", FR_Status);
    }
    else{
    printf("SD Card Mounted Successfully! \r\n\n");
    f_getfree("", &FreeClusters, &FS_Ptr);
	TotalSize = (uint32_t)((FS_Ptr->n_fatent - 2) * FS_Ptr->csize * 0.5);
	FreeSpace = (uint32_t)(FreeClusters * FS_Ptr->csize * 0.5);
	printf("Total SD Card Size: %lu Bytes\r\n", TotalSize);
	printf("Free SD Card Space: %lu Bytes\r\n\n", FreeSpace);
    }
}

void SD_Card_Unmount(void)
{
	  FR_Status = f_mount(NULL, "", 0);
	  if (FR_Status != FR_OK)
	  {
	      printf("\r\nError! While Un-mounting SD Card, Error Code: (%i)\r\n", FR_Status);

	  } else{
	      printf("\r\nSD Card Un-mounted Successfully! \r\n");

	  }
}

int list_dir (char *DataBuffer,const char *path)
{
    FRESULT res;
    DIR dir;
    FILINFO fno;
    int nfile, ndir;
    char TxBuffer[1000] = {0}; // Initialize TxBuffer with null terminators to handle string concatenation.

    res = f_opendir(&dir, path);  /* Open the directory */
    if (res == FR_OK) {
        nfile = ndir = 0;
        for (;;) {
            res = f_readdir(&dir, &fno);  /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Error or end of dir */

            char entry[500];  // Buffer to hold the current entry (either directory or file)

            if (fno.fattrib & AM_DIR) {  /* Directory */
                sprintf(entry, "   <DIR>   %s\n", fno.fname);
                ndir++;
            } else {  /* File */
                sprintf(entry, "%s\n",fno.fname);
                nfile++;
            }

            // Ensure there is enough space in TxBuffer before concatenation
            if (strlen(TxBuffer) + strlen(entry) < sizeof(TxBuffer)) {
                strcat(TxBuffer, entry);
            } else {
                printf("Buffer overflow risk: TxBuffer size exceeded.\n");
                break;
            }
        }
        f_closedir(&dir);
        sprintf(DataBuffer,TxBuffer);
        printf("List in directory:\n%s", TxBuffer);
        printf("%d dirs, %d files.\n", ndir, nfile);
    } else {
        printf("Failed to open \"%s\". (%u)\n", path, res);
    }
    return strlen(DataBuffer);
}
