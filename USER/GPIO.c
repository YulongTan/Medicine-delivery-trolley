/*
 * GPIO.c
 *
 *  Created on: 2023��5��25��
 *      Author: lenovo
 */
#include"GPIO.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
void ConfigureGPIO(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//ʹ��PF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//ʹ��PD
}



