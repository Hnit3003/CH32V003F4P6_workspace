#include "ring_buffer.h"

void RingBuffer_Init(RINGBUFFER_t *RingBuffer, uint8_t *Buffer, uint16_t Lenght)
{
    RingBuffer->buffer = Buffer;
    RingBuffer->head = 0;
    RingBuffer->tail = 0;
    RingBuffer->maxlenght = Lenght;
}

int8_t RingBuffer_Push(RINGBUFFER_t *RingBuffer, uint8_t Data)
{
    uint16_t next;
    next = RingBuffer->head + 1;

    if(next >= RingBuffer->maxlenght)
    {
        next = 0;
    }

    if(next == RingBuffer->tail)
    {
        return -1;
    }

    RingBuffer->buffer[RingBuffer->head] = Data;
    RingBuffer->head = next;

    return 0;
}

int8_t RingBuffer_Pop(RINGBUFFER_t *RingBuffer, uint8_t *Data)
{
    if(RingBuffer->head == RingBuffer->tail)
    {
        return -1;
    }

    uint16_t next;
    next = RingBuffer->tail + 1;

    if(next >= RingBuffer->maxlenght)
    {
        next = 0;
    }

    *Data = RingBuffer->buffer[RingBuffer->tail];
    RingBuffer->tail = next;

    return 0;
}

uint8_t RingBuffer_Available(RINGBUFFER_t *RingBuffer)
{
    if(RingBuffer->head >= RingBuffer->tail)
    {
        return (RingBuffer->head - RingBuffer->tail);
    }

    return (RingBuffer->maxlenght - RingBuffer->tail + RingBuffer->head);
}
