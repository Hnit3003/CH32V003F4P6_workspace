/*
 *@Note
  Hardware connection: PCF8574 -- LCD1602
  P0 -- RS
  P1 -- RW
  P2 -- E
  P3 -- No Conection
  P4 -- D4
  P5 -- D5
  P6 -- D6
  P7 -- D7
*/

#include "LCD_I2C.h"

#define PCF8574_ADDRESS 0x4C //0100 [A2][A1][A0][R/W]: A2=1, A1=1, A=0, R/W=0

//void LCD_SendCmd(uint8_t Cmd)
//{
//    uint8_t Data_H, Data_L;
//    uint8_t Data_I2CTransmit[4];
//
//    Data_H = (Cmd&0xF0);
//    Data_L = ((Cmd<<4) & 0xF0);
//
//    Data_I2CTransmit[0] = Data_H | 0x0C;          //EN = 1, RS = 0
//    Data_I2CTransmit[1] = Data_H | 0x80;          //EN = 0, RS = 0
//    Data_I2CTransmit[2] = Data_L | 0x0C;          //EN = 1, RS = 0
//    Data_I2CTransmit[3] = Data_L | 0x80;          //EN = 0, RS = 0
//
//    I2C_GenerateSTART(I2C1, ENABLE);
//    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
//
//    I2C_Send7bitAddress(I2C1, PCF8574_ADDRESS, I2C_Direction_Transmitter);
//    while(!I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//
//    for(uint8_t i = 0; i < 4; i++)
//    {
//        if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)
//        {
//            Delay_Ms(100);
//            I2C_SendData(I2C1, Data_I2CTransmit[i]);
//        }
//    }
//
////    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//    I2C_GenerateSTOP(I2C1, ENABLE);
//}
//
//void LCD_SendData(uint8_t Data)
//{
//    uint8_t Data_H, Data_L;
//    uint8_t Data_I2CTransmit[4];
//    Data_H = (Data&0xF0);
//    Data_L = ((Data<<4)|0xF0);
//    Data_I2CTransmit[0] = Data_H | 0xD0;          //EN = 1, RS = 1
//    Data_I2CTransmit[1] = Data_H | 0x90;          //EN = 0, RS = 1
//    Data_I2CTransmit[2] = Data_L | 0xD0;          //EN = 1, RS = 1
//    Data_I2CTransmit[3] = Data_L | 0x90;          //EN = 0, RS = 1;
//
//    I2C_GenerateSTART(I2C1, ENABLE);
//    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
//
//    I2C_Send7bitAddress(I2C1, PCF8574_ADDRESS, I2C_Direction_Transmitter);
//    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//
//    for(uint8_t i = 0; i < 4; i++)
//    {
//        if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)
//        {
//            Delay_Ms(100);
//            I2C_SendData(I2C1, Data_I2CTransmit[i]);
//        }
//    }
//
////    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//    I2C_GenerateSTOP(I2C1, ENABLE);
//}
//
//void LCD_Init()
//{
//    //Power On and wait for more than 15ms after Vcc rise to 4.5V, wait for more than 40ms after Vcc rise to 2.7V
//    Delay_Ms(50);
//    //Special case of "Function set" (lower four bits are irrelevant) (0011 ****)
//    LCD_SendCmd(0x33);
//    //Wait for more than 4.1ms
//    Delay_Ms(5);
//    //Special case of "Function set" (lower four bits are irrelevant) (0011 ****)
//    LCD_SendCmd(0x33);
//    //Wait for more than 100us
//    Delay_Ms(1);
//    //Special case of "Function set" (lower four bits are irrelevant) (0011 ****)
//    LCD_SendCmd(0x33);
//    //Wait for more than 100us
//    Delay_Ms(1);
//    //Initial "Function Set" to change interface (lower four bit are irrelevant) (0010 ****)
//    LCD_SendCmd(0x32);
//    //Wait for 100us
//    Delay_Ms(1);
//
//    //Function Set (001[DL] [N][F][*][*]): 4 bit(DL=0), 2 lines(N=1), font=5x8 dots(F=0(N=1))
//    LCD_SendCmd(0x20 | 0x00 | 0x08 | 0x00);
//    //Wait for more than 53us or until busy flag is clear
//    Delay_Ms(1);
//
//    //Display ON/OFF (0000 1[D][C][B]): display off(D=0), display cursor off(C=0), character blink off(B=0)
//    LCD_SendCmd(0x08 | 0x00 | 0x00 | 0x00);
//    //Wait for more than 53us or until busy flag is clear
//    Delay_Ms(1);
//
//    //Clear Display (0000 0001): clears all display and returns cursor to the home position(Address 0)
//    LCD_SendCmd(0x01);
//    //Wait for more than 3ms or until busy flag is clear
//    Delay_Ms(3);
//
//    //Entry Mode Set (0000 01[I/D][S]: increment(I/D=1), display stand(S=0)
//    LCD_SendCmd(0x04 | 0x02 | 0x00);
//    //Wait for more than 53us or until busy flag is clear
//    Delay_Ms(1);
//
//    //Display ON/OFF (0000 1[D][C][B]): display on(D=1), display cursor off(C=0), character blink off(B=0)
//    LCD_SendCmd(0x08 | 0x04 | 0x00 | 0x00);
//    //Wait for more than 53us or until busy flag is clear
//    Delay_Ms(1);
//
////  //Cursor and Display Shift (0001 [S/R][R/L][*][*]: Shift cursor to the right (S/R=0, R/L=1)(Address Counter is incremented by 1)
////  LCD_SendCmd(0x01 | 0x00 | 0x04);
//
//    //Return Home (0000 001[*]): returns the cursor to the home position (Address 0), returns display to its original state if it was shifted
//    LCD_SendCmd(0x02);
//}



void I2C_SendByte(char Data)
{
    /*Send START condition*/
    I2C_GenerateSTART(I2C1, ENABLE);
    /*Test on EV5 and clear it*/
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    /*Send PC8574 address for write*/
    I2C_Send7bitAddress(I2C1, PCF8574_ADDRESS, I2C_Direction_Transmitter);
    /*Test on EV6 and clear it*/
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /*Send the byte to be written*/
    I2C_SendData(I2C1, Data);
    /*Test on EV8 and clear it*/
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /*Send STOP condition*/
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void LCD_SendCmd(char Cmd)
{
    char Cmd_H, Cmd_L;
    uint8_t Cmd_Transmit[4], i=0;
    Cmd_H = Cmd & 0xF0;
    Cmd_L = (Cmd<<4)&0xF0;
    Cmd_Transmit[0] = Cmd_H | 0x04;
    Cmd_Transmit[1] = Cmd_H | 0x00;
    Cmd_Transmit[2] = Cmd_L | 0x04;
    Cmd_Transmit[3] = Cmd_L | 0x08;
    for(i = 0; i < 4; i++)
    {
        I2C_SendByte(Cmd_Transmit[i]);
    }
}

void LCD_SendData(char Data)
{
    char Data_H, Data_L;
    uint8_t Data_Transmit[4], i=0;
    Data_H = Data & 0xF0;
    Data_L = (Data<<4)&0xF0;
    Data_Transmit[0] = Data_H | 0x0D;
    Data_Transmit[1] = Data_H | 0x09;
    Data_Transmit[2] = Data_L | 0x0D;
    Data_Transmit[3] = Data_L | 0x09;
    for(i = 0; i < 4; i++)
    {
        I2C_SendByte(Data_Transmit[i]);
    }
}

void LCD_Init()
{
    /*Set 4 bit interface*/
    LCD_SendCmd(0x33);
    Delay_Ms(10);
    LCD_SendCmd(0x32);
    Delay_Ms(50);
    /*Start to set LCD Function*/
    LCD_SendCmd(0x28);
    Delay_Ms(50);
    /*Clear LCD*/
    LCD_SendCmd(0x01);
    Delay_Ms(50);

    /*Set entry mode */
    LCD_SendCmd(0x06);
    Delay_Ms(50);
    /*Set display to on */
    LCD_SendCmd(0x0C);
    Delay_Ms(50);
    /*Move cursor to home and set data address to 0 */
    LCD_SendCmd(0x02);
    Delay_Ms(50);
}

void LCD_SendString(uint8_t *str)
{
    while(*str) LCD_SendData(*str++);
}

