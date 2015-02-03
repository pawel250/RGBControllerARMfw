#include <stdlib.h>
#include "printf.h"
#include "hwInit.h"

int main(void)
{
 	RCC_Conf();
  	GPIO_Conf();
  	UART_Conf();
  	TIM_Conf( CH1_LED_TIM );
    TIM_Conf( CH2_LED_TIM );
  	NVIC_Conf();

   // printf_("hello\n");
  	while(1);
}


