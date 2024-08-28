/*
 * GPS.h
 *
 *  Created on: Aug 23, 2024
 *      Author: NinaadKotasthane
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include <stdint.h>

typedef struct UBX_NAV_POSLLH {
	unsigned char CLASS;
	unsigned char ID;
	unsigned short length;

	unsigned int iTOW;
	signed int lon;
	signed int lat;
	signed int height;
	signed int hMSL;
	unsigned int hAcc;
	unsigned int vAcc;

	double lon_f64;
	double lat_f64;
} UBX_NAV_POSLLH;

typedef struct TIMUTC{
	unsigned char CLASS;
	unsigned char ID;
	unsigned short length;
	unsigned int iTOW;
	unsigned int tAcc;
	signed int nano;
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int sec;

}TIMUTC;

typedef struct NAV_PVT{
	unsigned char CLASS;
	unsigned char ID;
	unsigned short length;
	unsigned int iTOW;
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int sec;

}NAV_PVT;

extern NAV_PVT nav;
extern UBX_NAV_POSLLH posllh;
extern TIMUTC time;

void UBX_NAV_POSLLH_Parsing(unsigned char *data, UBX_NAV_POSLLH *posllh);
void UBX_NAV_TIMEUTC_Parsing(unsigned char *data, TIMUTC *time);
void UBX_NAV_PVT_Parsing(unsigned char *data, NAV_PVT *nav);
void GPS_uart(uint8_t *GPS_Buf);
void toggle_Log(void);
void send_msg(char *config);

#endif /* INC_GPS_H_ */
