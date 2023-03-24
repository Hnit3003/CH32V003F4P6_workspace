/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Hnit (base on WCH)
 * Version            : V1.0.1
 * Date               : 19/203/023
 * Description        : Main program body.
********************************************************************************/
/*
 *@Note
 Systick interrupt routine:
 Config System timer interrupt with Systick reload value 48000-1 to callback
 SysTick_Handler each 1ms
*/

#include "debug.h"
#include <stdint.h>

volatile uint32_t uwTick = 0;
//static uint32_t uwTick = 0;
static uint32_t counter = 0;

/*********************************************************************
 * Function prototype
 */
void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick_Handler(void);
void Inc_Tick(void);
uint32_t Get_Tick();
void Print_RunningTime(void);

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
    printf("SystemClk:%d\r\n", SystemCoreClock);
    Delay_Init();
    NVIC_EnableIRQ(SysTicK_IRQn);
    SysTick->SR &= ~(1 << 0);
    SysTick->CMP = SystemCoreClock/1000 - 1;
    SysTick->CNT = 0;
    SysTick->CTLR = 0xF;

    while(1)
    {
//        if(Get_Tick() - counter >= 1000)
//        {
//            if(counter < 60000)
//            {
//                printf("Running time: %ds\r\n", counter/1000);
//            }
//            else if(counter >= 60000 && counter < 60000*60)
//            {
//                printf("Running time: %dmin %ds\r\n", (counter/1000)/60, (counter/1000)%60);
//            }
//            else if(counter >60000*60){
//                printf("Running time: %dhour %dmin %ds\r\n", (counter/1000)/(60*60), ((counter/1000)%(60*60))/60, ((counter/1000)%(60*60))%60);
//            }
//            counter = Get_Tick();
//        }
//        Print_RunningTime();
        uint32_t timer;
        timer = Get_Tick();
        if(timer - counter >= 1000)
        {
            counter = Get_Tick();
            if(counter < 60000)
            {
                printf("Running time: %ds\r\n", counter/1000);
            }
            else if(counter >= 60000 && counter < 60000*60)
            {
                printf("Running time: %dmin %ds\r\n", (counter/1000)/60, (counter/1000)%60);
            }
            else if(counter >60000*60)
            {
                printf("Running time: %dhour %dmin %ds\r\n", (counter/1000)/(60*60), ((counter/1000)%(60*60))/60, ((counter/1000)%(60*60))%60);
            }
        }
    }
}



/*********************************************************************
 * @fn      ADC1_IRQHandler
 *
 * @brief   ADC1_2 Interrupt Service Function.
 *
 * @return  none
 */
void SysTick_Handler(void)
{

    SysTick->SR = 0;
//    printf("Systick, uwTick = %d\r\n", uwTick);

//    Print_RunningTime();

    Inc_Tick();
}

void Inc_Tick(void)
{
    uwTick++;
}

uint32_t Get_Tick()
{
    return uwTick;
}

void Print_RunningTime()
{
    if(Get_Tick() - counter >= 1000)
    {
        counter = Get_Tick();
        if(counter < 60000)
        {
            printf("Running time: %ds\r\n", counter/1000);
        }
        else if(counter >= 60000 && counter < 60000*60)
        {
            printf("Running time: %dmin %ds\r\n", (counter/1000)/60, (counter/1000)%60);
        }
        else if(counter >60000*60)
        {
            printf("Running time: %dhour %dmin %ds\r\n", (counter/1000)/(60*60), ((counter/1000)%(60*60))/60, ((counter/1000)%(60*60))%60);
        }
    }
}
