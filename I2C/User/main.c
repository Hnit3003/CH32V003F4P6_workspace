/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 23/03/2023
 * Description        : Main program body.
********************************************************************************/
/*
 *@Note
 7-bit addressing mode, master/slave mode, transceiver routine:
 I2C1_SCL(PC2)\I2C1_SDA(PC1).
  This routine demonstrates that Master sends and Slave receives.
  Note: The two boards download the Master and Slave programs respectively,
   and power on at the same time.
      Hardware connection:
            PC2 -- PC2
            PC1 -- PC1
*/

#include "debug.h"
#include "I2C.h"
#include "LCD_I2C.h"

/*********************************************************************
 * Function prototype
 */


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
    I2C_Initial();
    LCD_Init();

    while(1)
    {
        for(uint8_t i = 17; i < 256; i++)
        {
            LCD_SendData(i);
        }
    }
}
