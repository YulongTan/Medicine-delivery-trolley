/*
 * TIMER.c
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */

#include"TIMER.h"
void TIMER1_IRQHandler()   //100
{
    //获取中断状态
    uint32_t status=TimerIntStatus(TIMER1_BASE, true);
    //清除中断标志位
    TimerIntClear(TIMER1_BASE,status);
    static float cth1[3],cth2[3];
    cth1[1]=QEIPositionGet(QEI0_BASE);
    cth1[2]=cth1[1]-cth1[0];
    cth1[0]=cth1[1];
    if(QEIDirectionGet(QEI0_BASE))
    {
        gest.v1=cth1[2]*13.2913535344f;
        gest.x1=(QEIPositionGet(QEI0_BASE)-0x80000000)*0.1329135353;
    }
    else
    {
        gest.v1=-cth1[2]*13.2913535344f;
        gest.x1=(QEIPositionGet(QEI0_BASE)-0x80000000)*0.1329135353;
    }
    //右轮
    cth2[1]=QEIPositionGet(QEI1_BASE);
    cth2[2]=cth2[1]-cth2[0];
    cth2[0]=cth2[1];
    if(QEIDirectionGet(QEI1_BASE))
    {
        gest.v2=cth2[2]*13.2913535344f;
        gest.x2=(QEIPositionGet(QEI1_BASE)-0x80000000)*0.1329135353;
    }
    else
    {
        gest.v2=-cth2[2]*13.2913535344f;
        gest.x2=(QEIPositionGet(QEI1_BASE)-0x80000000)*0.1329135353;
    }
//
//    float tmp=QEIPositionGet(QEI1_BASE);
//    static float catch1[3];
//    static int cnt1, cnt2;
//    catch1[1]=QEIPositionGet(QEI0_BASE);
//    catch1[2]=catch1[1]-catch1[0];
//    if(catch1[2]>=13)
//    {
//        if(QEIDirectionGet(QEI0_BASE))
//        {
//            gest.x1+=1.7278759595f;
//            gest.v1=1727.8759594744/cnt1;
//            catch1[0]=catch1[1];
//            cnt1=0;
//        }
//        else
//        {
//            gest.x1-=1.7278759595f;
//            gest.v1=-1727.8759594744/cnt1;
//            catch1[0]=catch1[1];
//            cnt1=0;
//        }
//    }
//    else
//    {
//        cnt1++;
//    }
//

//    static float catch2[3];
//    catch2[1]=tmp;
//    catch2[2]=catch2[1]-catch2[0];
//    if(catch2[2]==13)
//    {
//        if(QEIDirectionGet(QEI1_BASE))
//        {
//            gest.x2+=1.7278759595f;
//            gest.v2=1727.8759594744/catch2[2];
//            catch2[0]=catch2[1];
//            cnt2=0;
//        }
//        else
//        {
//            gest.x2-=1.7278759595f;
//            gest.v2=-1727.8759594744/catch2[2];
//        }
//    }
//    else
//    {
//        cnt2++;
//    }
//    static float catch1[3],catch2[3];
//    static int time1,time2;
//    catch1[1]=QEIPositionGet(QEI0_BASE);
//    catch1[2]=catch1[1]-catch1[0];
//    catch1[0]=catch1[1];
//    if(QEIDirectionGet(QEI0_BASE))
//    {
//        if(catch[2]==130)
//        //gest.x1+=0.52f;
//        gest.v1=catch1[2]*132.9;
//    }
//    else
//    {
//        //gest.x1-=0.52f;
//        gest.v1=-catch1[2]*132.9;
//    }
//    catch2[1]=QEIPositionGet(QEI1_BASE);
//    catch2[2]=catch2[1]-catch1[0];
//    catch2[0]=catch2[1];
//    if(QEIDirectionGet(QEI1_BASE))
//    {
//        //gest.x2+=0.52f;
//        gest.v2=catch2[2]*132.9;
//    }
//    else
//    {
//        //gest.x2-=0.52f;
//        gest.v2=-catch2[2]*132.9;
//    }
}
void TIMER0_IRQHandler()//1ms
{
    //获取中断状态
    uint32_t status=TimerIntStatus(TIMER0_BASE, true);//屏蔽后的中断状态
    //清除中断标志位
    TimerIntClear(TIMER0_BASE,status);
//    闪灯程序
//    if(led)
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);
//    else
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0);
//    led=!led;
}
void ConfigureTIME0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//使能TIMER0
    //配置定时器，将Timer0拆分并配置TIMERA为连续向下计数模式
    TimerClockSourceSet(TIMER0_BASE,TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC);
    //设置预分频值,TIMER0是16/32-bits定时器，当分成两个定时器时预分频才起作用，此时预分频为8位
    TimerPrescaleSet(TIMER0_BASE, TIMER_A,199);
    //设置装载值，TIMERA是以16位工作
    TimerLoadSet(TIMER0_BASE, TIMER_A,3999);
    //注册中断服务函数
    TimerIntRegister(TIMER0_BASE,TIMER_A, TIMER0_IRQHandler);
    //开启定时器A超时中断
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    //设置中断优先级
    IntPrioritySet(INT_TIMER0A,  1);//高四位有效，越低优先级越高，0xE0-0x00 0-14
    //使能中断
    IntEnable(INT_TIMER0A);
    IntMasterEnable();
    //使能定时器
    TimerEnable( TIMER0_BASE, TIMER_A);
}
void ConfigureTIME1(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);//使能TIMER0
    //配置定时器，将Timer0拆分并配置TIMERA为连续向下计数模式
    TimerClockSourceSet(TIMER1_BASE,TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER1_BASE,TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC);
    //设置预分频值,TIMER0是16/32-bits定时器，当分成两个定时器时预分频才起作用，此时预分频为8位
    TimerPrescaleSet(TIMER1_BASE, TIMER_A,199);
    //设置装载值，TIMERA是以16位工作
    TimerLoadSet(TIMER1_BASE, TIMER_A,39999);
    //注册中断服务函数
    TimerIntRegister(TIMER1_BASE,TIMER_A, TIMER1_IRQHandler);
    //开启定时器A超时中断
    TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
    //设置中断优先级
    IntPrioritySet(INT_TIMER1A,  0);//高四位有效，越低优先级越高，0xE0-0x00 0-14
    //使能中断
    IntEnable(INT_TIMER1A);
    IntMasterEnable();
    //使能定时器
    TimerEnable( TIMER1_BASE, TIMER_A);
}

