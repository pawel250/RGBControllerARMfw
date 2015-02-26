#include <stdlib.h>
#include "printf.h"
#include "hwInit.h"
#include "hwConf.h"
#include <stdbool.h>

bool checkStage( unsigned int color)
{
    unsigned int r = (color >> 16) & 0xFF;
    unsigned int g = (color >> 8) & 0xFF;
    unsigned int b = color & 0xFF;

    //two zero detecting
    if( r + g + b == 255)
    {
        return true;
    }
    else if ( r + g + b == 255*2) //two 255 detecting
    {
        return true;
    }
    return false;
}

void delay()
{
    for(int i = 0; i < AUTO_COLOR_LOOP_DELAY ; i++)
    {
        if(errorUsart != 0)
        {
           if ( errorUsart & USART_SR_FE)
           {
             printf_("F");
           }
           if ( errorUsart & USART_SR_IDLE)
           {
            // printf_("I");
           }
           if ( errorUsart & USART_SR_NE)
           {
             printf_("N");
           }
           if ( errorUsart & USART_SR_ORE)
           {
             printf_("O");
           }

           errorUsart = 0;
        }
    }
}

void autoColorLoop()
{

}

int main(void)
{
 	RCC_Conf();
  	GPIO_Conf();
  	UART_Conf();
  	TIM_Conf( CH1_LED_TIM );
    TIM_Conf( CH2_LED_TIM );
  	NVIC_Conf();

  	unsigned int stepValues[6]={
  	            +0x1,
  	            -0x10000,
  	            +0x100,
  	            -0x1,
  	            +0x10000,
  	            -0x100
  	        };
  	printf_("RgbController:>");

    while(1)
    {
        BT_USART->CR1 &= ~USART_CR1_RXNEIE; //turn off it
        if(autoColor)
        {
            CH1_R_LED_CCR = (autoColor >> 16) & 0xFF;
            CH1_G_LED_CCR = (autoColor >> 8) & 0xFF;
            CH1_B_LED_CCR = (autoColor) & 0xFF;

            CH2_R_LED_CCR = (autoColor >> 16) & 0xFF;
            CH2_G_LED_CCR = (autoColor >> 8) & 0xFF;
            CH2_B_LED_CCR = (autoColor) & 0xFF;

            autoColor = autoColor + stepValues[autoColorStage];
            if( checkStage(autoColor) )
            {
                autoColorStage++;
            }
            if( autoColorStage >= 6 ) autoColorStage = 0;
        }
        BT_USART->CR1 |= USART_CR1_RXNEIE; //turn on it
        delay();
    }

}


