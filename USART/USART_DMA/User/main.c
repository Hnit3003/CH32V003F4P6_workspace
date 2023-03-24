/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Hnit (base on WCH)
 * Version            : V1.0.0
 * Date               : 2023/03/14
 * Description        : Main program body.
*********************************************************************************/

/*
 *@Note
 USART DMA, master/slave mode transceiver routine:
 USART1_Tx(PD5)\USART1_Rx(PD6).

 This routine demonstrates that two boards use DMA to send and receive.

   Hardware connection:PD5 -- Rx
                       PD6 -- Tx
*/

#include "debug.h"
#include "uart.h"
#include "dma.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    UART_Config();
    DMA_Config();
    Delay_Init();
    UART_RingBuffer_Init();
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    Delay_Ms(1000);
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    while(1)
    {
        if(UART_Available() > 0)
        {
            uint8_t DATA_Transmit;
            DATA_Transmit = UART_Read_Data();
            USART_SendData(USART1, DATA_Transmit);
        }
    }
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @function_name      USART1_IRQHandler
 *
 * @brief   This function handles USART3 global interrupt request.
 *
 * @return  none
 */
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint16_t Data_Receive;
        Data_Receive = USART_ReceiveData(USART1);
        UART_Receive_Rx(Data_Receive);
    }
}
