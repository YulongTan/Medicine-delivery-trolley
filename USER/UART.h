/*
 * UART.h
 *
 *  Created on: 2023��6��30��
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
//ð�̿�
#include"PID.h"
//�����жϷ�����
void USART0_Handler(void);//UART0�жϺ���
void UART1_Handler_BuleTooth(void);//UART1�жϺ���
void UART5_Handler(void);//UART2�жϺ���
//���ú���
void ConfigureUART(void);//��ʼ�����ڴ�ӡ����
void ConfigureUART0(void);
void ConfigureUART_BuleTooth(void);//��������UART1
void ConfigureUART5(void);//��λ��ͨѶ
//ð�̺���
//void Data_get(char rxbuf);//�����ȡ���ַ�
#endif /* USER_UART_H_ */
