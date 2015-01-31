#include "stm32f10x.h"

#define LED_GPIO GPIOB
#define LED_GPIO_RCC RCC_APB2Periph_GPIOB
#ifdef DEBUG
#define LED_Pin GPIO_Pin_0
#endif

#ifdef RELEASE
#define LED_Pin GPIO_Pin_1
#endif



void RCC_Conf(void)
{
  	ErrorStatus HSEStartUpStatus;
  	RCC_DeInit();
  	RCC_HSEConfig(RCC_HSE_ON);
  	HSEStartUpStatus = RCC_WaitForHSEStartUp();
  	if(HSEStartUpStatus == SUCCESS)
  	{
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    	FLASH_SetLatency(FLASH_Latency_2);
    	RCC_HCLKConfig(RCC_SYSCLK_Div1);
    	RCC_PCLK2Config(RCC_HCLK_Div1);
    	RCC_PCLK1Config(RCC_HCLK_Div2);
    	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_7);
    	RCC_PLLCmd(ENABLE);
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    	while(RCC_GetSYSCLKSource() != 0x08);


  	}
}

int main (void)
{
	volatile uint32_t count, count_max = 3000000;
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_Conf();
	/* LED_GPIO Periph clock enable */
	RCC_APB2PeriphClockCmd(LED_GPIO_RCC, ENABLE);

	/* Configure LED pin in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = LED_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);

	while (1)
	{
		/* Set */
		GPIO_SetBits(LED_GPIO, LED_Pin);
		/* Delay */
		for (count = 0; count < count_max; count++);
		/* Reset */
		GPIO_ResetBits(LED_GPIO, LED_Pin);
		/* Delay */
		for (count = 0; count < count_max; count++);
	}
}
