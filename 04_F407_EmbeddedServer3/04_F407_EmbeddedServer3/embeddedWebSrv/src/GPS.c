/*
 * GPS.c
 *
 *  Created on: Jul 18, 2024
 *      Author: Admin
 */

#include "stm32f4xx_discovery_407.h"

int toggle_LED(char *replacerBuffer, unsigned int bufferLength){

		//if (0 == strcmp(CGIPath, serverTestCGIPath)){
		if ((bufferLength <= 0) || NULL == replacerBuffer)
		return -1;
		char pStatus=0;

				BSP_LED_Toggle(LED1);
				if (true == HAL_GPIO_ReadPin(LED1_GPIO_PORT, LED1_PIN)) {
					BSP_LED_On(LED1);
					BSP_LED_On(LED2);
					BSP_LED_On(LED3);
					BSP_LED_Off(LED4);
					pStatus = 1;
				} else if (false == HAL_GPIO_ReadPin(LED1_GPIO_PORT, LED1_PIN)) {
					BSP_LED_Off(LED1);
					BSP_LED_Off(LED2);
					BSP_LED_Off(LED3);
					BSP_LED_On(LED4);
					pStatus = 0;
				}
				sprintf(replacerBuffer,"{  \"LEDstatus\":  %d }",pStatus);
				return strlen(replacerBuffer);
}
