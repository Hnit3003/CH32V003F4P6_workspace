/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Hnit (Base on WCH)
 * Version            : V1.0.0
 * Date               : 2023/16/03
 * Description        : Main program body.
********************************************************************************/
/*
 *@Note
 Hardware flow control mode, master/slave mode, transceiver routine:
 USART1_Tx(PD5)\USART1_Rx(PD6)\USART1_CTS(PD3)\USART1_RTS(PC2)
 This example demonstrates UART1 hardware flow control data sending and receiving,
 connect the UART1 Tx and Rx pins to the serial port tool respectively,View through
 the host computer tool
 CTS(Clear to send):
  --connected to VCC: data cannot be sent
  --connected to GND, data can be sent normally
*/

#include "debug.h"

/*********************************************************************
 * @fn      USART1_CFG
 *
 * @brief   Initialize the USART1.
 *          *USART1_Tx(PD5)\USART1_Rx(PD6)
 *          *USART1_CTS(PD3)\USART1_RTS(PC2)
 *
 * @return  none
 */
void USART1_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; /* RTS-->C.2 */
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; /* CTS-->D.3 */
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    Delay_Init();
    USART1_CFG();

    printf("USART1 Hardware Flow Control TEST\r\n");

    while(1)
    {
        USART_SendData(USART1, 'H');
        Delay_Ms(500);
    }
}
