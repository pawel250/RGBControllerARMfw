/*
 * hwInit.c
 *
 *  Created on: 2 lut 2015
 *      Author: pawel
 */
#include "hwInit.h"
#include "hwConf.h"

void UART_Conf(void)
{
    //bt
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = BT_SPEED ;//460800;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init( BT_USART, &USART_InitStructure);
	USART_ITConfig(BT_USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(BT_USART, USART_IT_TXE, DISABLE);
	USART_Cmd(BT_USART, ENABLE);

	//terminal
	USART_InitStructure.USART_BaudRate = TERMINAL_SPEED;
	USART_Init( TERMINAL_USART, &USART_InitStructure);
	USART_ITConfig(TERMINAL_USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(TERMINAL_USART, USART_IT_TXE, DISABLE);
	USART_Cmd(TERMINAL_USART, ENABLE);

}

void TIM_Conf( TIM_TypeDef* TIMx  )
{
    TIMx->CCMR1 |= TIM_CCMR1_OC1M  | TIM_CCMR1_OC2M  |  //output compare mode
                                    TIM_CCMR1_OC2PE | TIM_CCMR1_OC1PE;//preload enable
    TIMx->CCMR2 |= TIM_CCMR2_OC3M  |  //output compare mode
                                    TIM_CCMR1_OC2PE;
     TIMx->CCER |= TIM_CCER_CC1E | //TIM_CCER_CC1P |
                                 TIM_CCER_CC2E | //TIM_CCER_CC2P |
                                 TIM_CCER_CC3E;// | TIM_CCER_CC3P; //oc enable, polarity, now is inversed
     TIMx->PSC = CPU_F / (LED_FRESH_RATE * PWM_RES) - 1; //60hz if pwm has 255 resolution and hsck haas 2div.
     TIMx->ARR = PWM_RES;
     TIMx->CCR1 = 0;
     TIMx->CCR2 = 0;
     TIMx->CCR3 = 0;

     TIMx->CR1 |= TIM_CR1_CEN;//  | TIM_CR1_DIR;  //timer on
}

void GPIO_Conf(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
//BT Tx
    GPIO_InitStructure.GPIO_Pin = BT_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BT_PORT, &GPIO_InitStructure);
 //Terminal Tx
#ifdef DEBUG
  	GPIO_InitStructure.GPIO_Pin = TERMINAL_TX_PIN;
  	GPIO_Init(TERMINAL_PORT, &GPIO_InitStructure);
#endif
//BT rx
    GPIO_InitStructure.GPIO_Pin = BT_RX_PIN ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(BT_PORT, &GPIO_InitStructure);
//Terminal Rx
#ifdef DEBUG
  	GPIO_InitStructure.GPIO_Pin = TERMINAL_RX_PIN ;
  	GPIO_Init(TERMINAL_PORT, &GPIO_InitStructure);
#endif

  	//BT power
  	GPIO_InitStructure.GPIO_Pin = BT_ON;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BT_PORT, &GPIO_InitStructure);
	//reset BTM
	GPIO_ResetBits(BT_PORT, BT_ON);

	//ch1 led
    GPIO_InitStructure.GPIO_Pin = CH1_R_LED_PIN | CH1_G_LED_PIN | CH1_B_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(CH1_LED_PORT, &GPIO_InitStructure);

    //ch1 led
    GPIO_InitStructure.GPIO_Pin = CH2_R_LED_PIN | CH2_G_LED_PIN | CH2_B_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(CH2_LED_PORT, &GPIO_InitStructure);
}


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
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_2); //watch out on this prescaler !!!
    	RCC_PLLCmd(ENABLE);
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    	while(RCC_GetSYSCLKSource() != 0x08);
  	}

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);
    #ifdef DEBUG
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    #endif

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
}

void NVIC_Conf(void)
{
	 NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM
  	// Jezeli tablica wektorow w RAM, to ustaw jej adres na 0x20000000
  	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  // VECT_TAB_FLASH
  	// W przeciwnym wypadku ustaw na 0x08000000
  	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  	// Wybranie grupy priorytetow

 	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 	// Wlacz przerwanie od USART1
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; // Wlacz przerwanie od USART3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
