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
int list_dir (const char *path);
void read_files(char* fileName);

extern uint8_t loggingActive;

void Log_ON();
void Log_OFF();
void SD_Card_write(uint8_t *data);

#endif /* INC_SD_H_ */
