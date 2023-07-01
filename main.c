/**           ����
 *����LED      PF1��PF2��(PF3)    ������
 *GPIOOUT     PD2��PD3
 *UART0       PA0��PA1          �жϺ���USART0_Handler��ʹ���Դ��Ĵ����ض��塤printf
 *UART1       PB0\PB1           ����
 *UART5       PE4 PE5   RT      ����λ��ͨѶ
 *TIMER0                        �ж�ʱ��1ms(ϵͳʱ��80Mhz,Ԥ��Ƶ200����װ��ֵ4000�����¼���)
 *TIMER1                        �ж�ʱ��10ms(ϵͳʱ��80Mhz,Ԥ��Ƶ200����װ��ֵ40000�����¼���)
 *PWM1-0-1    PD0��PD1          ��������Ƶ��1K,PWM1������0�ֿ���·��Ԥ��ƵΪ64�����¼�����װ��ֵ1250
 *
 *QEI0        PD6(A)��PD7(B)          PD6->PHA0,PD7->PHB0        2��31�η� AB���źŲ�����
 *QEI1        PC5(A)\PC6(B)           A B���źŽ���
 */
#include"mycar.h"
//ð�̺���
void move(float setpwm);//ֱ��
void move_line(float setpwm);//Ѳ��
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
//	    AcquireVelocity_Distance();//��ȡС�����ٶ�
	    wheel(1,800);
	    wheel(2,800);
//	    v1pid=initPID(10.5,1,0.01,v1pid);
//	    v2pid=initPID(11,1,0,v2pid);
	    UARTprintf("%u,%u\n",(uint32_t)gest.v1,(uint32_t)gest.v2);
//	    UARTprintf("%d,%d\n",(uint32_t)QEIPositionGet(QEI0_BASE),(uint32_t)QEIPositionGet(QEI1_BASE));
	}

}
//

//ð�̺���
void move(float setpwm)//ֱ��
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

/*��ʱn��
 * SysCtlDelay(SysCtlClockGet()*n/3);
 *����ע��/ȥע����� ctrl+/
 * �������Ctrl+shif+"+" Ctrl+"-"
 * ����LED PF1 PF2 PF3 �ֱ��Ӧ������
 * UARTprintf();
 * uint32_t pos=QEIPositionGet(QEI0_BASE);
 *M1PWM0->PD0  M1PWM1->PD1
 *M1PWM4->PF0  M1PWM5->PF1  M1PWM6->PF2  M1PWM7->PF3
 */
