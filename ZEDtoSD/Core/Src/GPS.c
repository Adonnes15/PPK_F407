/*
 * GPS.c
 *
 *  Created on: Aug 23, 2024
 *      Author: NinaadKotasthane
 */
#include "main.h"
#include "SD.h" //main.h included in this
#include "GPS.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

uint8_t MON_message[8] = { 0xB5, 0x62, 0x0A, 0x04, 0x00, 0x00, 0x0E, 0x34 };
uint8_t NMEA_enable[28] = { 0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00,
		0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x23, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF9, 0xA3 };
uint8_t ZDpoll[8] = {0xB5, 0x62, 0x01, 0x07, 0x00, 0x00, 0x08, 0x19};

UBX_NAV_POSLLH posllh;
TIMUTC time;
NAV_PVT nav;

void toggle_Log(void) {

	if (!loggingActive) {
		Log_ON();
		if (loggingActive) {
		}

	} else {

		Log_OFF();
	}

}

// Get GPS Uart data here and process
void GPS_uart(uint8_t *GPS_Buf) { //UART 1 cuz it is connected to ZED's UART 1
	if (loggingActive) {  // Check if logging is active
//		SD_Card_write(GPS_Buf);
//		  UBX_NAV_POSLLH_Parsing(&GPS_Buf[0], &posllh);
//		  UBX_NAV_TIMEUTC_Parsing(&GPS_Buf[0], &time);
		UBX_NAV_PVT_Parsing(&GPS_Buf[0], &nav);
//		  printf("iTOW:%u\ttAcc:%u\t year:%u\n",time.length,time.CLASS,time.ID);
		  printf("ID:%i\tTime of Week:%i\thours:%i\tminutes:%i\tsecs:%i\n",nav.ID,nav.iTOW,nav.hour,nav.minute,nav.sec);
	}
}

void send_msg(char *config) {
	UART_HandleTypeDef uart2 = GPS_UART_define(); //to get the uart handle initialized in main
	if (strstr(config, "NMEA")) {
		HAL_UART_Transmit(&uart2, NMEA_enable, 28, HAL_MAX_DELAY);
		printf("\r\n Starting NMEA \r\n*---------------*\r\n");

	} else if (strstr(config, "UBX")) {
		HAL_UART_Transmit(&uart2, MON_message, 8, HAL_MAX_DELAY);
		printf("\r\n Monitor \r\n*---------------*\r\n");

	} else if (strstr(config, "ZDpoll")) {
		HAL_UART_Transmit(&uart2, ZDpoll, 8, HAL_MAX_DELAY);
//		printf("\r\n ZDA Monitor \r\n*---------------*\r\n");

	}
}

void UBX_NAV_POSLLH_Parsing(unsigned char* data, UBX_NAV_POSLLH* posllh)
{
	posllh->CLASS = data[2];
	posllh->ID = data[3];
	posllh->length = data[4] | data[5]<<8;

	posllh->iTOW = data[6] | data[7]<<8 | data[8]<<16 | data[9]<<24;
	posllh->lon = data[10] | data[11]<<8 | data[12]<<16 | data[13]<<24;
	posllh->lat = data[14] | data[15]<<8 | data[16]<<16 | data[17]<<24;
	posllh->height = data[18] | data[19]<<8 | data[20]<<16 | data[21]<<24;
	posllh->hMSL = data[22] | data[23]<<8 | data[24]<<16 | data[25]<<24;
	posllh->hAcc = data[26] | data[27]<<8 | data[28]<<16 | data[29]<<24;
	posllh->vAcc = data[30] | data[31]<<8 | data[32]<<16 | data[33]<<24;

	posllh->lon_f64 = posllh->lon / 10000000.;
	posllh->lat_f64 = posllh->lat / 10000000.;
}

void UBX_NAV_TIMEUTC_Parsing(unsigned char *data, TIMUTC *time)
{
	time->CLASS = data[2];
	time->ID = data[3];
	time->length = data[4] | data[5]<<8;

	time->iTOW = data[6] | data[7]<<8 | data[8]<<16 | data[9]<<24;
	time->tAcc = data[10] | data[11]<<8 | data[12]<<16 | data[13]<<24;
	time->nano = data[14] | data[15]<<8 | data[16]<<16 | data[17]<<24;
	time->year = data[18] | data[19]<<8;
	time->month=data[20];
	time->day=data[21];
	time->hour=data[22];
	time->minute=data[23];
	time->sec=data[24];
}

void UBX_NAV_PVT_Parsing(unsigned char *data, NAV_PVT *nav)
{
	nav->CLASS = data[2];
	nav->ID = data[3];
	nav->length = data[4] | data[5]<<8;

	nav->iTOW = data[6] | data[7]<<8 | data[8]<<16 | data[9]<<24;
	nav->year = data[10] | data[11]<<8;
	nav->month=data[12];
	nav->day=data[13];
	nav->hour=data[14];
	nav->minute=data[15];
	nav->sec=data[16];
}
