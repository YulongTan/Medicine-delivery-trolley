/*
 * PWM.c
 *
 *  Created on: 2023��6��30��
 *      Author: lenovo
 */
#include"PWM.h"

void ConfigurePWM(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//ʹ��PD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);//ʹ��PWMģ��1ʱ��
    //����PWM
    //����PWMʱ�ӣ�����USEPWMDIV��Ƶ����
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);//PWMʱ��80M/64
    //ʹ�����裨��ʹ�ܣ�
    //ʹ�����Ÿ���PWM����
    GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_0);
    GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_1);
    //GPIO OUT
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, 0);
    //PWM�źŷ���
    GPIOPinConfigure(GPIO_PD0_M1PWM0);//PD0->PWMģ��1�ź�0
    GPIOPinConfigure(GPIO_PD1_M1PWM1);//PD1->PWMģ��1�ź�1
    //����PWM������
    //ģ��1->������0->���¼�������ͬ��
    //ģ��1->������0->���¼�������ͬ��
    PWMGenConfigure(PWM1_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    //����PWM����
    PWMGenPeriodSet(PWM1_BASE,PWM_GEN_0,1249);
    //����PWMռ�ձȣ���ǰ����ռ�ձ�Ϊ50%����ʼPWM����Ϊ0
//    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_0,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)+1)*0.5);
//    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_1,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)+1)*0.5);
    //ʹ��PWMģ��1ͨ��0��ͨ��1���
    PWMOutputState(PWM1_BASE,PWM_OUT_0_BIT,true);
    PWMOutputState(PWM1_BASE,PWM_OUT_1_BIT,true);
    //ʹ��PWM������
    PWMGenEnable(PWM1_BASE,PWM_GEN_0);
}
void ban_pwm(void)
{
    //��ֹPWMģ��1ͨ��0��ͨ��1���
    PWMOutputState(PWM1_BASE,PWM_OUT_0_BIT,false);
    PWMOutputState(PWM1_BASE,PWM_OUT_1_BIT,false);
}
void SET_PWM(int num, float dr)
{
    switch(num)
    {
    case 1:
        PWMPulseWidthSet(PWM1_BASE,PWM_OUT_0,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)+1)*dr);
//        PWMOutputState(PWM1_BASE,PWM_OUT_0_BIT,true);
        break;
    case 2:
        PWMPulseWidthSet(PWM1_BASE,PWM_OUT_1,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)+1)*dr);
//        PWMOutputState(PWM1_BASE,PWM_OUT_1_BIT,true);
        break;
    }
}
void wheel(int num,float pwm) //PD0-PWM1 PD2-GPIO1 PD1-PWM2 PD3-GPIO1
{

    int direct;
    if(pwm>1000)
    {
        pwm=1000;
    }
    if(pwm<-1000)
    {
        pwm=-1000;
    }
    if(pwm>=0)
    {
        direct=1;//ǰ��
    }
    else
    {
        direct=2;
    }
    if(pwm!=0)
    {
        switch(num)
        {
        case 1://����
            switch(direct)
            {
            case 1:
                SET_PWM(1, pwm/1000);
                GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,0);
                break;
            case 2:
                SET_PWM(1,1+pwm/1000);
                GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,4);
                break;
            }
         case 2://����
             switch(direct)
             {
             case 1:
                 SET_PWM(2, 1-pwm/1000);
                 GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3,8);
                 break;
             case 2:
                 SET_PWM(2,-pwm/1000);
                 GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3,0);
                 break;
             }
        }
    }
    else
    {
        ban_pwm();
    }
}
