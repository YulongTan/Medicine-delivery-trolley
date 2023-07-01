/*
 * PWM.c
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */
#include"PWM.h"

void ConfigurePWM(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//使能PD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);//使能PWM模块1时钟
    //配置PWM
    //配置PWM时钟（设置USEPWMDIV分频器）
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);//PWM时钟80M/64
    //使能外设（已使能）
    //使能引脚复用PWM功能
    GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_0);
    GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_1);
    //GPIO OUT
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, 0);
    //PWM信号分配
    GPIOPinConfigure(GPIO_PD0_M1PWM0);//PD0->PWM模块1信号0
    GPIOPinConfigure(GPIO_PD1_M1PWM1);//PD1->PWM模块1信号1
    //配置PWM发生器
    //模块1->发生器0->向下计数，不同步
    //模块1->发生器0->向下计数，不同步
    PWMGenConfigure(PWM1_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    //配置PWM周期
    PWMGenPeriodSet(PWM1_BASE,PWM_GEN_0,1249);
    //配置PWM占空比（当前设置占空比为50%）初始PWM设置为0
//    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_0,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)+1)*0.5);
//    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_1,(PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)+1)*0.5);
    //使能PWM模块1通道0和通道1输出
    PWMOutputState(PWM1_BASE,PWM_OUT_0_BIT,true);
    PWMOutputState(PWM1_BASE,PWM_OUT_1_BIT,true);
    //使能PWM发生器
    PWMGenEnable(PWM1_BASE,PWM_GEN_0);
}
void ban_pwm(void)
{
    //禁止PWM模块1通道0和通道1输出
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
        direct=1;//前进
    }
    else
    {
        direct=2;
    }
    if(pwm!=0)
    {
        switch(num)
        {
        case 1://左轮
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
         case 2://右轮
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
