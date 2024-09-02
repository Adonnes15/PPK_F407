/*
 * imu.c
 *
 *  Created on: Jul 18, 2024
 *      Author: Admin
 */
#include "imu.h"
#include <stdio.h>

int gyro[]={1,2,3,4,5};
int acc[]={8,9,10,11,12};
int mag[]={81,54,10,1,22};
int i=0;


int imu_readings(char *imuBuffer, unsigned int bufferLength){
	if(i>=4){
		i=0;
	}
	else{
		i+=1;
	}
	sprintf(imuBuffer,"{  \"accelerometer\":  %d , \"gyroscope\":  %d , \"magnetometer\":  %d }",acc[i],gyro[i],mag[i]);
	return strlen(imuBuffer);
}

