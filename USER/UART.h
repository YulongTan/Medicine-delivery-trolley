/*
 * UART.h
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */

#ifndef USER_UART_H_
#define USER_UART_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
//冒烟库
#include"PID.h"
//串口中断服务函数
void USART0_Handler(void);//UART0中断函数
void UART1_Handler_BuleTooth(void);//UART1中断函数
void UART5_Handler(void);//UART2中断函数
//配置函数
void ConfigureUART(void);//初始化串口打印函数
void ConfigureUART0(void);
void ConfigureUART_BuleTooth(void);//配置蓝牙UART1
void ConfigureUART5(void);//上位机通讯
//冒烟函数
//void Data_get(char rxbuf);//处理获取的字符
#endif /* USER_UART_H_ */
