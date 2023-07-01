/*
 * TIMER.c
 *
 *  Created on: 2023��6��30��
 *      Author: lenovo
 */

#include"TIMER.h"
void TIMER1_IRQHandler()   //100
{
    //��ȡ�ж�״̬
    uint32_t status=TimerIntStatus(TIMER1_BASE, true);
    //����жϱ�־λ
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
    //����
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
    //��ȡ�ж�״̬
    uint32_t status=TimerIntStatus(TIMER0_BASE, true);//���κ���ж�״̬
    //����жϱ�־λ
    TimerIntClear(TIMER0_BASE,status);
//    ���Ƴ���
//    if(led)
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);
//    else
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0);
//    led=!led;
}
void ConfigureTIME0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//ʹ��TIMER0
    //���ö�ʱ������Timer0��ֲ�����TIMERAΪ�������¼���ģʽ
    TimerClockSourceSet(TIMER0_BASE,TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC);
    //����Ԥ��Ƶֵ,TIMER0��16/32-bits��ʱ�������ֳ�������ʱ��ʱԤ��Ƶ�������ã���ʱԤ��ƵΪ8λ
    TimerPrescaleSet(TIMER0_BASE, TIMER_A,199);
    //����װ��ֵ��TIMERA����16λ����
    TimerLoadSet(TIMER0_BASE, TIMER_A,3999);
    //ע���жϷ�����
    TimerIntRegister(TIMER0_BASE,TIMER_A, TIMER0_IRQHandler);
    //������ʱ��A��ʱ�ж�
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    //�����ж����ȼ�
    IntPrioritySet(INT_TIMER0A,  1);//����λ��Ч��Խ�����ȼ�Խ�ߣ�0xE0-0x00 0-14
    //ʹ���ж�
    IntEnable(INT_TIMER0A);
    IntMasterEnable();
    //ʹ�ܶ�ʱ��
    TimerEnable( TIMER0_BASE, TIMER_A);
}
void ConfigureTIME1(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);//ʹ��TIMER0
    //���ö�ʱ������Timer0��ֲ�����TIMERAΪ�������¼���ģʽ
    TimerClockSourceSet(TIMER1_BASE,TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER1_BASE,TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC);
    //����Ԥ��Ƶֵ,TIMER0��16/32-bits��ʱ�������ֳ�������ʱ��ʱԤ��Ƶ�������ã���ʱԤ��ƵΪ8λ
    TimerPrescaleSet(TIMER1_BASE, TIMER_A,199);
    //����װ��ֵ��TIMERA����16λ����
    TimerLoadSet(TIMER1_BASE, TIMER_A,39999);
    //ע���жϷ�����
    TimerIntRegister(TIMER1_BASE,TIMER_A, TIMER1_IRQHandler);
    //������ʱ��A��ʱ�ж�
    TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
    //�����ж����ȼ�
    IntPrioritySet(INT_TIMER1A,  0);//����λ��Ч��Խ�����ȼ�Խ�ߣ�0xE0-0x00 0-14
    //ʹ���ж�
    IntEnable(INT_TIMER1A);
    IntMasterEnable();
    //ʹ�ܶ�ʱ��
    TimerEnable( TIMER1_BASE, TIMER_A);
}

