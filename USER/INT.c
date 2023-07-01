/*
 * INT.c
 *
 *  Created on: 2023��7��1��
 *      Author: lenovo
 */
#include"INT.h"
void SW1_handler(void)
{

}
void SW2_handler(void)
{

}
void key_handler()
{
    static int Led=1;
    uint32_t status;//��ȡ�жϱ�־λ
    status=GPIOIntStatus(GPIO_PORTF_BASE, true);
    GPIOIntClear(GPIO_PORTF_BASE, status);
    if(status==GPIO_PIN_0 || status==GPIO_PIN_4)
    {

        if(Led<8)
            Led=Led*2;
        else
            Led=2;
    }
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, Led);
    if(status==GPIO_PIN_0)
    {
        SW1_handler();
    }
    if(status==GPIO_PIN_4)
    {
        SW2_handler();
    }
}
void ConfigureINT()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);       //ʹ������
    //����PF1��PF2��PF3����Ϊ���ģʽ
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;//ȷ��
    //����PF4����Ϊ���룬����ģʽ���ڲ�����
    GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    //����PF4����Ϊ�ⲿ�ж����ţ��½��ش���
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
    //�����жϷ��������
    GPIOIntRegister(GPIO_PORTF_BASE, key_handler);
    //ʹ��GPIOF�ж�
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0);
    //ʹ���жϿ�������GPIOF�ж�
    IntEnable(INT_GPIOF);
    //ʹ�ܴ������ж�
    IntMasterEnable();
    //����жϱ�־
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
    //�����ж����ȼ�
    IntPrioritySet(INT_GPIOF, 0xE0);
}



