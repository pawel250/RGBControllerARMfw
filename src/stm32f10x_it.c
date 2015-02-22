#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"
#include "hwConf.h"
#include "printf.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


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
#ifdef DEBUG
    #define BUFF_LENGTH 255
    char bufferForPrint[BUFF_LENGTH] = {0};
#endif /*DEBUG*/

void USART1_IRQHandler(void)
{

    if( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET)
    {
        uint8_t readByte = USART_ReceiveData( USART1 );

       // USART_SendData(USART1, readByte);

        static uint8_t bytesReceived = 0; //ilosc odebranych bajtow
        static uint8_t buff[6];

        if( bytesReceived == 0 )
        {
            #ifdef DEBUG
                snprintf(bufferForPrint, BUFF_LENGTH, "%sBRecv:%d\n", bufferForPrint, bytesReceived);
            #endif
            if( START_BYTE == readByte ) //wykrycie markera poczatku
            {
                #ifdef DEBUG
                    snprintf(bufferForPrint, BUFF_LENGTH, "%sF start\n", bufferForPrint);
                #endif
                bytesReceived = 1;
            }
        }
        else if( bytesReceived <= FRAME_LENGTH )
        {
            buff[ bytesReceived - 1 ] = readByte;
            bytesReceived++;
            #ifdef DEBUG
                snprintf(bufferForPrint, BUFF_LENGTH, "%sIsRecv\n", bufferForPrint);
            #endif
        }
        else
        {
            if( readByte == STOP_BYTE)
            {
                printf_("Frame recv: success.\n");

                CH1_R_LED_CCR = buff[0];
                CH1_G_LED_CCR = buff[1];
                CH1_B_LED_CCR = buff[2];

                CH2_R_LED_CCR = buff[3];
                CH2_G_LED_CCR = buff[4];
                CH2_B_LED_CCR = buff[5];

                if (    buff[0] == 0 &&
                        buff[1] == 0 &&
                        buff[2] == 0 &&
                        buff[3] == 0 &&
                        buff[4] == 0 &&
                        buff[5] == 0 )
                {
                    GPIO_WriteBit(POWER_ON_PORT, POWER_ON_PIN, POWER_OFF);
                }
            }
            else
            {
                printf_("Frame recv: fail.\n");
            }

            bytesReceived = 0;
        }

        #ifdef DEBUG
            printf_("%s", bufferForPrint);
        #endif
    }
    USART_ClearITPendingBit( USART1, USART_IT_RXNE );
}

void cmdHandler( uint8_t *buff )
{
    char *cmd = strtok( (char*)buff, " " );
    char *param = strtok(NULL, " ");

    uint8_t paramInt = atoi(param);

    if( !strcmp(cmd, "1r") )
    {
        CH1_R_LED_CCR = paramInt;
    }
    else if( !strcmp(cmd, "1g") )
    {
        CH1_G_LED_CCR = paramInt;
    }
    else if( !strcmp(cmd, "1b") )
    {
        CH1_B_LED_CCR = paramInt;
    }
    else if( !strcmp(cmd, "2r") )
    {
        CH2_R_LED_CCR = paramInt;
    }
    else if( !strcmp(cmd, "2g") )
    {
        CH2_G_LED_CCR = paramInt;
    }
    else if( !strcmp(cmd, "2b") )
    {
        CH2_B_LED_CCR = paramInt;
    }
}

void USART3_IRQHandler(void)
{
    if( USART_GetITStatus( USART3, USART_IT_RXNE ) != RESET )
    {
        static uint8_t buff[50];
        static uint8_t receivedBytes = 0;
        uint8_t readByte = USART_ReceiveData( USART3 );

        USART_SendData( USART3, readByte );

        if( receivedBytes < sizeof( buff ) )
        {
            if( readByte == 0x0D || readByte == 0x0A) //CR LF
            {
                buff[receivedBytes++] = '\0';
                cmdHandler( buff );
                receivedBytes = 0;
            }
            else
            {
                buff[receivedBytes++] = readByte; //reading command
            }

        }
        else
        {
            receivedBytes = 0; //reset bytes counter
        }
    }

    USART_ClearITPendingBit( USART3, USART_IT_RXNE );
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

