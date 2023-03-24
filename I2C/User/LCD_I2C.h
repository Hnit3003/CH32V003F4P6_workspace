#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "debug.h"

void I2C_SendByte(char Data);
void LCD_SendCmd(char Cmd);
void LCD_SendData(char Data);
void LCD_Init (void);
void LCD_SendString(uint8_t *str);

#endif
