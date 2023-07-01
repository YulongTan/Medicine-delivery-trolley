/*
 * UART.c
 *
 *  Created on: 2023年6月30日
 *      Author: lenovo
 */
#include"UART.h"
void UART1_Handler_BuleTooth(void)
{
    int32_t rxbuf;
    //读取中断状态
    uint32_t status=UARTIntStatus(UART1_BASE,true);
    //清除中断标志位
    UARTIntClear(UART1_BASE, status);
    //检查FIFO中是否有字符，若有，读取出来
    while(UARTCharsAvail(UART1_BASE))
    {
      rxbuf=UARTCharGetNonBlocking(UART1_BASE);//接受数据
      UARTCharPutNonBlocking(UART1_BASE, rxbuf);//将读取到的字符再发送出去
    }
}
void UART5_Handler(void)//上位机通信
{
    int32_t rxbuf;
    //读取中断状态
    uint32_t status=UARTIntStatus(UART5_BASE,true);
    //清除中断标志位
    UARTIntClear(UART5_BASE, status);
    //检查FIFO中是否有字符，若有，读取出来
    while(UARTCharsAvail(UART5_BASE))
    {
      rxbuf=UARTCharGetNonBlocking(UART5_BASE);//接受数据
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
//      UARTCharPutNonBlocking(UART5_BASE, rxbuf);//将读取到的字符再发送出去

    }
}
void USART0_Handler(void)
{
    int32_t rxbuf;
    //读取中断状态
    uint32_t status=UARTIntStatus(UART0_BASE,true);
    //清除中断标志位
    UARTIntClear(UART0_BASE, status);
    //检查FIFO中是否有字符，若有，读取出来
    while(UARTCharsAvail(UART0_BASE))
    {
      rxbuf=UARTCharGetNonBlocking(UART0_BASE);
      UARTCharPutNonBlocking(UART0_BASE, rxbuf);//将读取到的字符再发送出去
    }
}
void ConfigureUART5(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);//使能PE
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);//使能UART5
    GPIOPinConfigure(GPIO_PE4_U5RX);//RX=GPIO_PIN_4
    GPIOPinConfigure(GPIO_PE5_U5TX);//TX=PIO_PIN_5
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTClockSourceSet(UART5_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk( UART5_BASE, SysCtlClockGet(),115200,UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //使能FIFO并设置FIFO深度
    UARTFIFOEnable(UART5_BASE);
    UARTFIFOLevelSet(UART5_BASE, UART_FIFO_RX1_8,UART_FIFO_TX1_8);
    //配置串口中断
    UARTIntRegister(UART5_BASE,UART5_Handler);
    UARTIntEnable(UART5_BASE, UART_INT_RX|UART_INT_RT);//开启串口接收中断和接收超时中断
    UARTIntClear(UART5_BASE, UART5_BASE);
    //启用串口0的中断并开启处理器中断控制器
    IntEnable(INT_UART5);
    IntMasterEnable();
    //使能串口
    UARTEnable(UART5_BASE);
}
//void ConfigureUART0(void)
//{
//    //使能外设
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//USART
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);//使能UART0，板载USB转TTL，端口COM6
//    //配置PF1、PF2、PF3作为输出，连接至板载LED
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
//    //将PA0、PA1引脚配置成串口引脚
//    GPIOPinConfigure(GPIO_PA0_U0RX);//RX=GPIO_PIN_0
//    GPIOPinConfigure(GPIO_PA1_U0TX);//TX=GPIO_PIN_1
//    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
//    //配置串口波特时钟源及参数
//    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
//    UARTConfigSetExpClk( UART0_BASE, SysCtlClockGet(),115200,           UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
//    //使能FIFO并设置FIFO深度
//    UARTFIFOEnable(UART0_BASE);
//    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_RX1_8,UART_FIFO_TX1_8);
//    //注册串口中断函数
//    UARTIntRegister(UART0_BASE, USART0_Handler); //UART0中断函数
//    UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);//开启串口接收中断和接收超时中断
//    UARTIntClear(UART0_BASE, UART0_BASE);
//    //启用串口0的中断并开启处理器中断控制器
//    IntEnable(INT_UART0);
//    IntMasterEnable();
//    //使能串口
//    UARTEnable(UART0_BASE);
//
//}
void ConfigureUART(void)//使用UART0
{
    // 启用UART使用的GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // 使能 UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // 为UART配置GPIO引脚。
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    // 初始化控制台I/O的UART
    UARTStdioConfig(0, 115200, SysCtlClockGet());//0-115200-16M
}
void ConfigureUART_BuleTooth(void)//使用UART1
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//使能PB
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);//使能UART1
    GPIOPinConfigure(GPIO_PB0_U1RX);//RX=GPIO_PIN_0
    GPIOPinConfigure(GPIO_PB1_U1TX);//TX=PIO_PIN_1
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk( UART1_BASE, SysCtlClockGet(),115200,UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //使能FIFO并设置FIFO深度
    UARTFIFOEnable(UART1_BASE);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_RX1_8,UART_FIFO_TX1_8);
    //配置串口中断
    UARTIntRegister(UART1_BASE, UART1_Handler_BuleTooth);
    UARTIntEnable(UART1_BASE, UART_INT_RX|UART_INT_RT);//开启串口接收中断和接收超时中断
    UARTIntClear(UART1_BASE, UART1_BASE);
    //启用串口0的中断并开启处理器中断控制器
    IntEnable(INT_UART1);
    IntMasterEnable();
    //使能串口
    UARTEnable(UART1_BASE);
}
