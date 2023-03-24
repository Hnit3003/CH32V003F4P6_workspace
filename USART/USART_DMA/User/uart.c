#include "uart.h"

#define UART_BAUDRATE           115200
#define UART_WORD_LENGTH        USART_WordLength_8b

#define BUFFER_MAX_LENGHT 8
uint8_t Buffer_UART[BUFFER_MAX_LENGHT];
RINGBUFFER_t RingBuffer;

/***************************************************************************
 * @fn      USART_Config
 *
 * @brief   Initializes the UART1_IT peripheral: UART_Rx(PD5), UART_Tx(PD6),
 *                                               StopBits_1, Parity_No
 * @return  none
 */
void UART_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 Tx-->PD5   Rx-->PD6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //Alternate Function Push Pull Mode
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //Input Floating
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = UART_BAUDRATE;
    USART_InitStructure.USART_WordLength = UART_WORD_LENGTH;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);          /*USART_IT_RXNE : specifies the interrupt source
                                                                              for the Rx buffer not empty interrupt.*/

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void UART_RingBuffer_Init()
{
    RingBuffer_Init(&RingBuffer, Buffer_UART, BUFFER_MAX_LENGHT);
}

void UART_Receive_Rx(uint8_t Data_Rx)
{
    RingBuffer_Push(&RingBuffer, Data_Rx);
}

uint8_t UART_Read_Data()
{
    uint8_t Data;
    RingBuffer_Pop(&RingBuffer, &Data);
    return Data;
}

uint8_t UART_Available()
{
    return RingBuffer_Available(&RingBuffer);
}
