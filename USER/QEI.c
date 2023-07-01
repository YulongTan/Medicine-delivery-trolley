/*
 * QEI.c
 *
 *  Created on: 2023��6��30��
 *      Author: lenovo
 */
#include"QEI.h"
void ConfigureQEI0(void)
{
    //ʹ��QEI��GPIOD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //����PD7����
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
    //����GPIO
    GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_6);
    GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PD6_PHA0);//PD6->������A������
    GPIOPinConfigure(GPIO_PD7_PHB0);//PD7->������B������
    //��������ģʽ-----------------------
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_6,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_7,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    //----------------------
    //����QEI0ģ�飬A��B�����źű��ؾ������������������������帴λ��������λģʽ��A��B�����źŲ�������������ֵΪ0xffffffff
    QEIConfigure(QEI0_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP,0xffffffff);
    //����QEI0�������ж�
    QEIIntDisable(QEI0_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);
//    //�����ٶȲ���
//    QEIVelocityConfigure(QEI0_BASE,QEI_VELDIV_4,SysCtlClockGet()/100);//���ö�ʱ��������Ϊ
//    //ʹ���ٶȻ�ȡ
//    QEIVelocityEnable(QEI0_BASE);
    //ʹ��QEI0
    QEIEnable(QEI0_BASE);
    //����QEI0ģ�鵱ǰλ�ü�����ֵΪ2^31
    QEIPositionSet(QEI0_BASE,0x80000000);
}
void ConfigureQEI1(void)
{
    //ʹ��QEI1��GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //����GPIO
    GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_5);
    GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_6);
    GPIOPinConfigure(GPIO_PC5_PHA1);//PC5->������A������
    GPIOPinConfigure(GPIO_PC6_PHB1);//PC6->������B������
    //��������ģʽ----------------
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_5,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD);
    //-------------------------
    //����QEI1ģ�飬A��B�����źű��ؾ������������������������帴λ��������λģʽ��A��B�����źŽ�����������ֵΪ0xffffffff
    QEIConfigure(QEI1_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_SWAP,0xffffffff);
    //����QEI1�������ж�
    QEIIntDisable(QEI1_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);
//    //�����ٶȲ���
//    QEIVelocityConfigure(QEI1_BASE,QEI_VELDIV_4,SysCtlClockGet()/100);//���ö�ʱ��������Ϊ
//    //ʹ���ٶȻ�ȡ
//    QEIVelocityEnable(QEI1_BASE);
    //ʹ��QEI1
    QEIEnable(QEI1_BASE);
    //����QEI1ģ�鵱ǰλ�ü�����ֵΪ2^31
    QEIPositionSet(QEI1_BASE,0x80000000);
}
void AcquireVelocity_Distance(void)
{
//    unsigned long speed1,speed2;
//    speed1=QEIVelocityGet(QEI0_BASE);//���ص�ֵ����ָ����ʱ�������ڼ�⵽����������QEI����ʱ��Ƶ��Ϊ��Ƶ��1/4����40MHz��
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

