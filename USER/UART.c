/*
 * UART.c
 *
 *  Created on: 2023��6��30��
 *      Author: lenovo
 */
#include"UART.h"
void UART1_Handler_BuleTooth(void)
{
    int32_t rxbuf;
    //��ȡ�ж�״̬
    uint32_t status=UARTIntStatus(UART1_BASE,true);
    //����жϱ�־λ
    UARTIntClear(UART1_BASE, status);
    //���FIFO���Ƿ����ַ������У���ȡ����
    while(UARTCharsAvail(UART1_BASE))
    {
      rxbuf=UARTCharGetNonBlocking(UART1_BASE);//��������
      UARTCharPutNonBlocking(UART1_BASE, rxbuf);//����ȡ�����ַ��ٷ��ͳ�ȥ
    }
}
void UART5_Handler(void)//��λ��ͨ��
{
    int32_t rxbuf;
    //��ȡ�ж�״̬
    uint32_t status=UARTIntStatus(UART5_BASE,true);
    //����жϱ�־λ
    UARTIntClear(UART5_BASE, status);
    //���FIFO���Ƿ����ַ������У���ȡ����
    while(UARTCharsAvail(UART5_BASE))
    {
      rxbuf=UARTCharGetNonBlocking(UART5_BASE);//��������
      static char a[20];
      static int cnt=0;
      if(rxbuf=='\n')
      {
          a[cnt]='\0';
          gest.angx=atof(a);
          cnt=0;
          a[0]='\0';
      }
      else
      {
          a[cnt]=rxbuf;
          cnt++;
      }
//      UARTCharPutNonBlocking(UART5_BASE, rxbuf);//����ȡ�����ַ��ٷ��ͳ�ȥ

    }
}
void USART0_Handler(void)
{
    int32_t rxbuf;
    //��ȡ�ж�״̬
    uint32_t status=UARTIntStatus(UART0_BASE,true);
    //����жϱ�־λ
    UARTIntClear(UART0_BASE, status);
    //���FIFO���Ƿ����ַ������У���ȡ����
    while(UARTCharsAvail(UART0_BASE))
    {
      rxbuf=UARTCharGetNonBlocking(UART0_BASE);
      UARTCharPutNonBlocking(UART0_BASE, rxbuf);//����ȡ�����ַ��ٷ��ͳ�ȥ
    }
}
void ConfigureUART5(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);//ʹ��PE
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);//ʹ��UART5
    GPIOPinConfigure(GPIO_PE4_U5RX);//RX=GPIO_PIN_4
    GPIOPinConfigure(GPIO_PE5_U5TX);//TX=PIO_PIN_5
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTClockSourceSet(UART5_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk( UART5_BASE, SysCtlClockGet(),115200,UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //ʹ��FIFO������FIFO���
    UARTFIFOEnable(UART5_BASE);
    UARTFIFOLevelSet(UART5_BASE, UART_FIFO_RX1_8,UART_FIFO_TX1_8);
    //���ô����ж�
    UARTIntRegister(UART5_BASE,UART5_Handler);
    UARTIntEnable(UART5_BASE, UART_INT_RX|UART_INT_RT);//�������ڽ����жϺͽ��ճ�ʱ�ж�
    UARTIntClear(UART5_BASE, UART5_BASE);
    //���ô���0���жϲ������������жϿ�����
    IntEnable(INT_UART5);
    IntMasterEnable();
    //ʹ�ܴ���
    UARTEnable(UART5_BASE);
}
//void ConfigureUART0(void)
//{
//    //ʹ������
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//USART
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);//ʹ��UART0������USBתTTL���˿�COM6
//    //����PF1��PF2��PF3��Ϊ���������������LED
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
//    //��PA0��PA1�������óɴ�������
//    GPIOPinConfigure(GPIO_PA0_U0RX);//RX=GPIO_PIN_0
//    GPIOPinConfigure(GPIO_PA1_U0TX);//TX=GPIO_PIN_1
//    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
//    //���ô��ڲ���ʱ��Դ������
//    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
//    UARTConfigSetExpClk( UART0_BASE, SysCtlClockGet(),115200,           UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
//    //ʹ��FIFO������FIFO���
//    UARTFIFOEnable(UART0_BASE);
//    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_RX1_8,UART_FIFO_TX1_8);
//    //ע�ᴮ���жϺ���
//    UARTIntRegister(UART0_BASE, USART0_Handler); //UART0�жϺ���
//    UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);//�������ڽ����жϺͽ��ճ�ʱ�ж�
//    UARTIntClear(UART0_BASE, UART0_BASE);
//    //���ô���0���жϲ������������жϿ�����
//    IntEnable(INT_UART0);
//    IntMasterEnable();
//    //ʹ�ܴ���
//    UARTEnable(UART0_BASE);
//
//}
void ConfigureUART(void)//ʹ��UART0
{
    // ����UARTʹ�õ�GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // ʹ�� UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // ΪUART����GPIO���š�
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    // ��ʼ������̨I/O��UART
    UARTStdioConfig(0, 115200, SysCtlClockGet());//0-115200-16M
}
void ConfigureUART_BuleTooth(void)//ʹ��UART1
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//ʹ��PB
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);//ʹ��UART1
    GPIOPinConfigure(GPIO_PB0_U1RX);//RX=GPIO_PIN_0
    GPIOPinConfigure(GPIO_PB1_U1TX);//TX=PIO_PIN_1
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk( UART1_BASE, SysCtlClockGet(),115200,UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //ʹ��FIFO������FIFO���
    UARTFIFOEnable(UART1_BASE);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_RX1_8,UART_FIFO_TX1_8);
    //���ô����ж�
    UARTIntRegister(UART1_BASE, UART1_Handler_BuleTooth);
    UARTIntEnable(UART1_BASE, UART_INT_RX|UART_INT_RT);//�������ڽ����жϺͽ��ճ�ʱ�ж�
    UARTIntClear(UART1_BASE, UART1_BASE);
    //���ô���0���жϲ������������жϿ�����
    IntEnable(INT_UART1);
    IntMasterEnable();
    //ʹ�ܴ���
    UARTEnable(UART1_BASE);
}
