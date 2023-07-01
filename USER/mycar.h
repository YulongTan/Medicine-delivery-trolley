/*          ┌─┐      ┌─┐
#      ┌──┘ ┴ ───┘ ┴ ┐
#      │                        │
#      │       ───          │
#      │  ─┬┘      └┬─  │
#      │                        │
#      │       ─┴─          │
#      │                        │
#      └───┐         ┌─┘
#               │         │
#               │         │
#               │         │
#               │         └──────────────┐
#               │                                                       │
#               │                                                       ├─┐
#               │                                                       ┌─┘
#               │                                                       │
#                └─┐  ┐  ┌───────┬──┐  ┌┘
#                  ─┤ ─┤                        │ ─┤ ─┤
#                └──┴──┘                └──┴──┘
#                神兽保佑
#                代码无BUG!
*/
#ifndef USER_MYCAR_H_
#define USER_MYCAR_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"//GPIO
#include "driverlib/sysctl.h"//SYS
#include "driverlib/uart.h"//串口中断
#include "utils/uartstdio.h"
#include "driverlib/timer.h"//定时器
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"
#include "utils/uartstdio.h"
#include "driverlib/qei.h"
//冒烟库
#include"PID.h"
#include"GPIO.h"
#include"SYS.h"
#include"TIMER.h"
#include"QEI.h"
#include"PWM.h"
#include"UART.h"
#include"INT.h"
#endif /* USER_MYCAR_H_ */
