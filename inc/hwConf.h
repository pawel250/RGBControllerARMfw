/*
 * hwConf.h
 *
 *  Created on: 2 lut 2015
 *      Author: pawel
 */

#ifndef HWCONF_H_
#define HWCONF_H_

#define TERMINAL_TX_PIN    GPIO_Pin_10
#define TERMINAL_RX_PIN    GPIO_Pin_11
#define TERMINAL_PORT      GPIOB
#define TERMINAL_USART     USART3 //you must change in printf.c also
#define BT_TX_PIN       GPIO_Pin_9
#define BT_RX_PIN       GPIO_Pin_10
#define BT_PORT         GPIOA   //USART and IO pins must be in the same port.
#define BT_USART        USART1

#define CH1_LED_TIM     TIM2
#define CH1_LED_PORT    GPIOA
#define CH1_R_LED_PIN   GPIO_Pin_0
#define CH1_G_LED_PIN   GPIO_Pin_1
#define CH1_B_LED_PIN   GPIO_Pin_2
#define CH1_R_LED_CCR   CH1_LED_TIM->CCR1
#define CH1_G_LED_CCR   CH1_LED_TIM->CCR2
#define CH1_B_LED_CCR   CH1_LED_TIM->CCR3

#define CH2_LED_TIM     TIM3
#define CH2_R_LED_PORT  GPIOA
#define CH2_G_LED_PORT  GPIOA
#define CH2_B_LED_PORT  GPIOB
#define CH2_R_LED_PIN   GPIO_Pin_6
#define CH2_G_LED_PIN   GPIO_Pin_7
#define CH2_B_LED_PIN   GPIO_Pin_0
#define CH2_R_LED_CCR   CH2_LED_TIM->CCR1
#define CH2_G_LED_CCR   CH2_LED_TIM->CCR2
#define CH2_B_LED_CCR   CH2_LED_TIM->CCR3

#define POWER_ON_PIN    GPIO_Pin_3
#define POWER_ON_PORT   GPIOA
#define POWER_ON        Bit_RESET
#define POWER_OFF       Bit_SET
#define POWER_ON_CONF_BIT       0b1
#define AUTO_COLOR_CONF_BIT     0b10

#define LED_FRESH_RATE  60
#define PWM_RES         255

#define CPU_F           72000000

#define START_BYTE              1
#define STOP_BYTE               START_BYTE + 2
#define FRAME_LENGTH            7

#define AUTO_COLOR_LOOP_DELAY   20000

extern volatile uint16_t errorUsart;
extern volatile uint32_t autoColor;
extern volatile uint8_t autoColorStage;

#endif /*HWCONF_H_ */
