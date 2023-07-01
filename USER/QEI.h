/*
 * QEI.h
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */

#ifndef USER_QEI_H_
#define USER_QEI_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "utils/uartstdio.h"
#include"PID.h"
void ConfigureQEI0(void);
void ConfigureQEI1(void);
void AcquireVelocity_Distance(void);//处理获取的速度
#endif /* USER_QEI_H_ */
