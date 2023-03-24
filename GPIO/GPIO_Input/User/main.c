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
 PC3 push-pull output.
 PD0 pull-up input, control LED1 by PC3
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

    uint8_t BUTTON_LastState = Bit_SET;

    while(1)
    {
        uint8_t BUTTON_CurrentState = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
        if(BUTTON_CurrentState != BUTTON_LastState)
        {
            Delay_Ms(20);

            if(BUTTON_CurrentState == Bit_RESET)
            {
                GPIO_TogglePin(GPIOC, GPIO_Pin_3);
            }

            BUTTON_LastState = BUTTON_CurrentState;
        }
    }
}

/*********************************************************************
 * @fn      GPIO_Config
 *
 * @brief   Initializes PC3 push-pull output, PD0 pull-up input
 *
 * @return  none
 */
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
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
