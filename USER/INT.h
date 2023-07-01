/*
 * INT.h
 *
 *  Created on: 2023Äê7ÔÂ1ÈÕ
 *      Author: lenovo
 */

#ifndef USER_INT_H_
#define USER_INT_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
void ConfigureINT(void);
void key_handler(void);
void SW1_handler(void);
void SW2_handler(void);
#endif /* USER_INT_H_ */
