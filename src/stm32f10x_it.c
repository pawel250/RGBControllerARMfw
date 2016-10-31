 /*
 Copyright 2015 Paweł Domagalski
 This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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

void USART1_IRQHandler(void)
{
    if ( (BT_USART->SR & USART_SR_FE) ||
         (BT_USART->SR & USART_SR_IDLE) ||
         (BT_USART->SR & USART_SR_NE) ||
         (BT_USART->SR & USART_SR_ORE) )
    {
        errorUsart=BT_USART->SR;
    }

    if ( BT_USART->SR & USART_SR_RXNE )
    {
        uint8_t readByte = BT_USART->DR;

        //BT_USART->DR = readByte;

        static uint8_t bytesReceived = 0; //ilosc odebranych bajtow
        static uint8_t buff[FRAME_LENGTH];

        if( bytesReceived == 0 )
        {
            if( START_BYTE == readByte ) //wykrycie markera poczatku
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
                //printf_("Frame recv: success.\n");

                CH1_R_LED_CCR = buff[0];
                CH1_G_LED_CCR = buff[1];
                CH1_B_LED_CCR = buff[2];

                CH2_R_LED_CCR = buff[3];
                CH2_G_LED_CCR = buff[4];
                CH2_B_LED_CCR = buff[5];

                if (!( buff[6] & POWER_ON_CONF_BIT) )
                {
                    CH1_R_LED_CCR = 0;
                    CH1_G_LED_CCR = 0;
                    CH1_B_LED_CCR = 0;

                    CH2_R_LED_CCR = 0;
                    CH2_G_LED_CCR = 0;
                    CH2_B_LED_CCR = 0;
                    GPIO_WriteBit(POWER_ON_PORT, POWER_ON_PIN, POWER_OFF);
                }
                autoColor = 0;
                if ( buff[6] & AUTO_COLOR_CONF_BIT )
                {
                    autoColor = 0xff0000;
                    autoColorStage = 0;
                }

            }
            else
            {
                //printf_("Frame recv: fail.\n");
            }

            bytesReceived = 0;
        }
    }
    BT_USART->DR;
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
    //if( USART_GetITStatus( TERMINAL_USART, USART_IT_RXNE ) != RESET )
    if ( (TERMINAL_USART->SR & USART_SR_FE) ||
         (TERMINAL_USART->SR & USART_SR_IDLE) ||
         (TERMINAL_USART->SR & USART_SR_NE) ||
         (TERMINAL_USART->SR & USART_SR_ORE) )
    {
        errorUsart=TERMINAL_USART->SR;
    }


    if ( TERMINAL_USART->SR & USART_SR_RXNE )
    {
        static uint8_t buff[50];
        static uint8_t receivedBytes = 0;
        uint8_t readByte = USART_ReceiveData( TERMINAL_USART );

        USART_SendData( TERMINAL_USART, readByte );

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
    TERMINAL_USART->DR;
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

