/*
 * QEI.c
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */
#include"QEI.h"
void ConfigureQEI0(void)
{
    //使能QEI与GPIOD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //解锁PD7引脚
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
    //复用GPIO
    GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_6);
    GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PD6_PHA0);//PD6->编码器A相输入
    GPIOPinConfigure(GPIO_PD7_PHB0);//PD7->编码器B相输入
    //配置引脚模式-----------------------
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_6,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_7,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    //----------------------
    //配置QEI0模块，A、B两相信号边沿均产生计数，不开启索引脉冲复位，正交相位模式，A、B两相信号不交换，最大计数值为0xffffffff
    QEIConfigure(QEI0_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP,0xffffffff);
    //禁用QEI0的所有中断
    QEIIntDisable(QEI0_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);
//    //配置速度捕获
//    QEIVelocityConfigure(QEI0_BASE,QEI_VELDIV_4,SysCtlClockGet()/100);//设置定时器节拍数为
//    //使能速度获取
//    QEIVelocityEnable(QEI0_BASE);
    //使能QEI0
    QEIEnable(QEI0_BASE);
    //设置QEI0模块当前位置计数器值为2^31
    QEIPositionSet(QEI0_BASE,0x80000000);
}
void ConfigureQEI1(void)
{
    //使能QEI1与GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //复用GPIO
    GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_5);
    GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_6);
    GPIOPinConfigure(GPIO_PC5_PHA1);//PC5->编码器A相输入
    GPIOPinConfigure(GPIO_PC6_PHB1);//PC6->编码器B相输入
    //配置引脚模式----------------
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_5,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    //-------------------------
    //配置QEI1模块，A、B两相信号边沿均产生计数，不开启索引脉冲复位，正交相位模式，A、B两相信号交换，最大计数值为0xffffffff
    QEIConfigure(QEI1_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_SWAP,0xffffffff);
    //禁用QEI1的所有中断
    QEIIntDisable(QEI1_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);
//    //配置速度捕获
//    QEIVelocityConfigure(QEI1_BASE,QEI_VELDIV_4,SysCtlClockGet()/100);//设置定时器节拍数为
//    //使能速度获取
//    QEIVelocityEnable(QEI1_BASE);
    //使能QEI1
    QEIEnable(QEI1_BASE);
    //设置QEI1模块当前位置计数器值为2^31
    QEIPositionSet(QEI1_BASE,0x80000000);
}
void AcquireVelocity_Distance(void)
{
//    unsigned long speed1,speed2;
//    speed1=QEIVelocityGet(QEI0_BASE);//返回的值是在指定的时间周期内检测到的脉冲数，QEI输入时钟频率为主频的1/4（即40MHz）
//    speed2=QEIVelocityGet(QEI1_BASE);//
//    if(QEIDirectionGet(QEI0_BASE)==1)//
//    {
//        gest.v1=speed1*13.291;
//    }
//    else if(QEIDirectionGet(QEI0_BASE)==-1)
//    {
//        gest.v1=0-speed1*13.291;
//    }
//    if(QEIDirectionGet(QEI1_BASE)==1)
//    {
//        gest.v2=speed2*13.291;
//    }
//    else if(QEIDirectionGet(QEI1_BASE)==-1)
//    {
//        gest.v2=0-speed2*13.291;
//    }
//    gest.v1=QEIVelocityGet(QEI0_BASE);
}

