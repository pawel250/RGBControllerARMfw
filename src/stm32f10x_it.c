#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"
#include "hwConf.h"
#include "printf.h"


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

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint8_t readByte = USART_ReceiveData( USART1 );

        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
        USART_SendData(USART1, readByte);

        static uint8_t bytesReceived = 0; //ilosc odebranych bajtow
        static uint8_t buff[6];

        if( bytesReceived == 0 )
        {
            if( START_BYTE == readByte && bytesReceived == 0 ) //wykrycie markera poczatku
            {
                bytesReceived = 1;
            }
        }
        else if( bytesReceived <= FRAME_LENGTH )
        {
            buff[ bytesReceived - 1 ] = readByte;
            bytesReceived++;
        }
        else
        {
            if( readByte == STOP_BYTE)
            {
                printf_("Frame received successfully.\n");

                CH1_LED_TIM->CCR1 = buff[0];
                CH1_LED_TIM->CCR2 = buff[1];
                CH1_LED_TIM->CCR3 = buff[2];

                CH2_LED_TIM->CCR1 = buff[3];
                CH2_LED_TIM->CCR2 = buff[4];
                CH2_LED_TIM->CCR3 = buff[5];
            }
            else
            {
                printf_("Frame received with failure.\n");
            }
            bytesReceived = 0;
        }
    }

}

void USART3_IRQHandler(void)
{

}

void TIM1_UP_IRQHandler (void)
{
}
void TIM1_CC_IRQHandler(void)
{
}

void TIM2_IRQHandler(void)
{
}

void ADC1_2_IRQHandler  ( void    )
{
}

void DMA1_Channel1_IRQHandler(void)
{
}

