/*
 * INT.c
 *
 *  Created on: 2023年7月1日
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
    uint32_t status;//获取中断标志位
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);       //使能外设
    //配置PF1、PF2、PF3引脚为输出模式
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;//确认
    //配置PF4引脚为输入，推挽模式，内部上拉
    GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    //配置PF4引脚为外部中断引脚，下降沿触发
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
    //配置中断服务函数入口
    GPIOIntRegister(GPIO_PORTF_BASE, key_handler);
    //使能GPIOF中断
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0);
    //使能中断控制器的GPIOF中断
    IntEnable(INT_GPIOF);
    //使能处理器中断
    IntMasterEnable();
    //清除中断标志
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
    //配置中断优先级
    IntPrioritySet(INT_GPIOF, 0xE0);
}



