/*
 * SD.h
 *
 *  Created on: Aug 21, 2024
 *      Author: NinaadKotasthane
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include <stdint.h>

void SD_Card_Init(void);
void SD_Card_Unmount(void);
int list_dir (char *DataBuffer,const char *path);

#endif /* INC_SD_H_ */
