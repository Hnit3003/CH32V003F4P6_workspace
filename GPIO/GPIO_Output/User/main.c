/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Hnit (Base on WCH)
 * Version            : V1.0.1
 * Date               : 18/03/2023
 * Description        : Main program body.
*********************************************************************************/
/*
 *@Note
 GPIO routine:
 PD0, PC3 push-pull output. Toggle LED1 and LED2.
*/

#include "debug.h"

/*********************************************************************
 * Function prototype
 */
void GPIO_Config(void);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    GPIO_Config();
    Delay_Init();

    while(1)
    {
        GPIO_TogglePin(GPIOD, GPIO_Pin_0);
        Delay_Ms(500);
        GPIO_TogglePin(GPIOC, GPIO_Pin_3);
    }
}

/*********************************************************************
 * @fn      GPIO_Config
 *
 * @brief   Initializes PD0, PC3 push-pull output
 *
 * @return  none
 */
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      GPIO_TogglePin
 *
 * @brief   Invert the state of the Px_Pin signal
 *
 * @return  none
 */
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if(GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
    {
        GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);
    }
}
