/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Hnit (base on WCH)
 * Version            : V1.0.0
 * Date               : 2023/03/14
 * Description        : Main program body.
*********************************************************************************/

/*@Note
 Multiprocessor communication mode routine:
 Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 it and sends it (baud rate 115200).
 Inverts lowercase to uppercase, uppercase to lowercase, send invalid message if
 recieve an invalid character

 Hardware connection:PD5 -- Rx
                     PD6 -- Tx

*/

#include "debug.h"

uint8_t DATA;

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
void USART_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void USART_Convert_SendData(uint8_t Data);

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);

    USART_Config();

    while(1)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {
            /* waiting for receiving finish */
        }

        USART_Convert_SendData((uint8_t)USART_ReceiveData(USART1));

        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        {
            /* waiting for sending finish */
        }
    }
}

void USART_Convert_SendData(uint8_t Data)
{
    if(Data >= 0x61 && Data <= 0x7A)
    {
        USART_SendData(USART1, Data - 32);
    }
    else if(Data >= 0x41 && Data <= 0x5A)
    {
        USART_SendData(USART1, Data + 32);
    }
    else if((Data >= 0x20 && Data <= 0x40) || (Data >= 0x5B && Data <= 0x60) || (Data >= 0x7B && Data <= 0x7E))
    {
        USART_SendData(USART1, Data);
    }
    else
    {
        printf("*{Invalid character}*");
    }
}
