#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "debug.h"

typedef struct
{
    uint8_t *buffer;
    uint16_t head;
    uint16_t tail;
    uint16_t maxlenght;
}RINGBUFFER_t;

void RingBuffer_Init(RINGBUFFER_t *RingBuffer, uint8_t *Buffer, uint16_t Lenght);
int8_t RingBuffer_Push(RINGBUFFER_t *RingBuffer, uint8_t Data);
int8_t RingBuffer_Pop(RINGBUFFER_t *RingBuffer, uint8_t *Data);
uint8_t RingBuffer_Available(RINGBUFFER_t *RingBuffer);

#endif
