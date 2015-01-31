#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"



void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	//disk_timerproc();
}

void USART1_IRQHandler(void)
{

}

void USART2_IRQHandler(void)
{

}

void TIM1_UP_IRQHandler (void)
{
/*	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  	{
    	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    	//printf_(" TEST ");
    	//printf_("\n\rT2=%d",TIM_GetCounter (TIM2));
  	}*/
}
void TIM1_CC_IRQHandler(void)
{
/*  	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
  	{
    	TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
		//printf_("\n\rT2=%d",TIM_GetCounter (TIM2));
  		//printf_("u");
  	}*/
}

void TIM2_IRQHandler(void)
{
/*	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}*/
}

void ADC1_2_IRQHandler  ( void    )
{
	/*if( ADC_GetITStatus(ADC1,ADC_IT_JEOC))
	{
		ADC_ClearITPendingBit (ADC1, ADC_IT_JEOC);
	}
	if( ADC_GetITStatus(ADC1,ADC_IT_EOC))
	{
		ADC_ClearITPendingBit (ADC1, ADC_IT_EOC);
		//printf_("T");
	}*/
}

void DMA1_Channel1_IRQHandler(void)
{
/*	if( DMA_GetITStatus(DMA1_IT_TE1))
	{
		DMA_ClearITPendingBit(DMA1_IT_TE1);
		DMA_Cmd(DMA1_Channel1, DISABLE);
		DMA_Cmd(DMA1_Channel1, ENABLE);
	}
	if( DMA_GetITStatus(DMA1_IT_TC1))
	{
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
	*/
}

