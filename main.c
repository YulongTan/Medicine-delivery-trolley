/**           引脚
 *板载LED      PF1、PF2、(PF3)    红蓝绿
 *GPIOOUT     PD2、PD3
 *UART0       PA0和PA1          中断函数USART0_Handler，使用自带的串口重定义·printf
 *UART1       PB0\PB1           蓝牙
 *UART5       PE4 PE5   RT      与上位机通讯
 *TIMER0                        中断时间1ms(系统时钟80Mhz,预分频200，重装载值4000，向下计数)
 *TIMER1                        中断时间10ms(系统时钟80Mhz,预分频200，重装载值40000，向下计数)
 *PWM1-0-1    PD0、PD1          设置驱动频率1K,PWM1发生器0分开两路，预分频为64，向下计数，装载值1250
 *
 *QEI0        PD6(A)、PD7(B)          PD6->PHA0,PD7->PHB0        2的31次方 AB相信号不交换
 *QEI1        PC5(A)\PC6(B)           A B相信号交换
 */
#include"mycar.h"
//冒烟函数
void move(float setpwm);//直行
void move_line(float setpwm);//巡线
int main(void)
{

    ConfigureSYS();
    ConfigureTIME0();
    ConfigureTIME1();
    ConfigureGPIO();
    ConfigurePWM();
    ConfigureUART_BuleTooth();
    ConfigureUART5();
    //ConfigureUART0();
    ConfigureUART();
    ConfigureQEI0();
    ConfigureQEI1();
    ConfigureINT();
	while(1)
	{
//	    AcquireVelocity_Distance();//获取小车的速度
	    wheel(1,800);
	    wheel(2,800);
//	    v1pid=initPID(10.5,1,0.01,v1pid);
//	    v2pid=initPID(11,1,0,v2pid);
	    UARTprintf("%u,%u\n",(uint32_t)gest.v1,(uint32_t)gest.v2);
//	    UARTprintf("%d,%d\n",(uint32_t)QEIPositionGet(QEI0_BASE),(uint32_t)QEIPositionGet(QEI1_BASE));
	}

}
//

//冒烟函数
void move(float setpwm)//直行
{
//    tgest.v1=setpwm+pwm;
//    tgest.v2=setpwm-pwm;
    tgest.v1=setpwm;
    tgest.v2=setpwm;
    v1pid=initPID(0,0,0,v1pid);
    v2pid=initPID(0,0,0,v2pid);
    float pwm1=PID(&v1pid,tgest.v1-gest.v1,1000,-1000);
    float pwm2=PID(&v2pid,tgest.v2-gest.v2,1000,-1000);
    wheel(1,pwm1);
    wheel(0,pwm2);
}
void move_line(float setpwm)
{
    tgest.angx=0;
    float pwm=PID(&angxpid,tgest.angx-gest.angx,250,-250);
    tgest.v1=setpwm+pwm;
    tgest.v2=setpwm-pwm;
    v1pid=initPID(0,0,0,v1pid);
    v2pid=initPID(0,0,0,v2pid);
    float pwm1=PID(&v1pid,tgest.v1-gest.v1,1000,-1000);
    float pwm2=PID(&v2pid,tgest.v2-gest.v2,1000,-1000);
    wheel(1,pwm1);
    wheel(0,pwm2);
}

/*延时n秒
 * SysCtlDelay(SysCtlClockGet()*n/3);
 *快速注解/去注解操作 ctrl+/
 * 字体调节Ctrl+shif+"+" Ctrl+"-"
 * 板载LED PF1 PF2 PF3 分别对应红蓝绿
 * UARTprintf();
 * uint32_t pos=QEIPositionGet(QEI0_BASE);
 *M1PWM0->PD0  M1PWM1->PD1
 *M1PWM4->PF0  M1PWM5->PF1  M1PWM6->PF2  M1PWM7->PF3
 */
