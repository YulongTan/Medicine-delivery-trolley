/*
 * PWM.h
 *
 *  Created on: 2023��6��30��
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
void SET_PWM(int num,float dr);//dr 0~1Ϊռ�ձ�
void wheel(int num, float pwm);//1������ 2������   pwm -1000~1000
void ban_pwm(void);//��ֹpwm���
#endif /* USER_PWM_H_ */
