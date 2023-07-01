/*
 * PWM.h
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */

#ifndef USER_PWM_H_
#define USER_PWM_H_
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
void ConfigurePWM(void);
void SET_PWM(int num,float dr);//dr 0~1为占空比
void wheel(int num, float pwm);//1是左轮 2是右轮   pwm -1000~1000
void ban_pwm(void);//禁止pwm输出
#endif /* USER_PWM_H_ */
