/*
 * imu.h
 *
 *  Created on: Jul 18, 2024
 *      Author: Admin
 */

#ifndef IMU_H_
#define IMU_H_

extern int gyro[];
extern int acc[];
extern int mag[];
extern int i;

int imu_readings(char *imuBuffer, unsigned int bufferLength);

#endif /* IMU_H_ */
