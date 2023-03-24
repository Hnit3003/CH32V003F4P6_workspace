#ifndef _UART_H
#define _UART_H

#include "debug.h"
#include "ring_buffer.h"
void UART_Config(void);
void UART_RingBuffer_Init();
void UART_Receive_Rx(uint8_t Data_Rx);
uint8_t UART_Read_Data();
uint8_t UART_Available();

#endif
