/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Hnit (Base on WCH)
 * Version            : V1.0.1
 * Date               : 18/03/2023
 * Description        : Main program body.
*********************************************************************************/
/*
 *@Note
 PWM output routine:
 TIM1_CH1(PD2)
 This example demonstrates that the TIM_CH1(PD2) pin outputs PWM in PWM mode 1
 and PWM mode 2.
*/

#include "debug.h"

/*********************************************************************
 * Function prototype
 */
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp);

#include "debug.h"


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    Delay_Init();
    TIM1_PWMOut_Init(999, 47999, 0);
    SystemCoreClockUpdate();

    while(1)
    {
        for(uint16_t i = 0; i < 999; i++)
        {
          TIM_SetCompare1(TIM1, i);
          if(i == 998)
          {
              for(uint16_t j = 999; j > 0; j--)
              {
                  TIM_SetCompare1(TIM1, j);
              }
          }
        }

    }
}

/*********************************************************************
 * @fn      TIM1_Config
 *
 * @brief   Initializes TIM1 output compare. TIM_OCMode_PWM2
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOD, &GPIO_InitStructure );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}
