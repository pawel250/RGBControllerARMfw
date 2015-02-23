#include <stdlib.h>
#include "printf.h"
#include "hwInit.h"

volatile uint16_t errorUsart = 0;

int main(void)
{
 	RCC_Conf();
  	GPIO_Conf();
  	UART_Conf();
  	TIM_Conf( CH1_LED_TIM );
    TIM_Conf( CH2_LED_TIM );
  	NVIC_Conf();

    printf_("hello\n");
  	while(1)
  	{

/*  	    if(errorUsart != 0)
  	    {
  	      if ( errorUsart & USART_SR_FE)
  	      {
  	          printf_("F");
  	      }
          if ( errorUsart & USART_SR_IDLE)
          {
              printf_("I");
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
  	    }*/
  	}
}


