/*
 * TIMER.h
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */

#ifndef USER_TIMER_H_
#define USER_TIMER_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include"QEI.h"
#include"PID.h"
void ConfigureTIME0(void);
void ConfigureTIME1(void);
void TIMER0_IRQHandler(void);//TIMER0中断函数
void AcquireVelocity_Distance(void);  //获取速度和距离
#endif /* USER_TIMER_H_ */
