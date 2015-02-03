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
#define TERMINAL_PORT           GPIOB
#define TERMINAL_USART        USART3 //you must change in printf.c also
#define TERMINAL_SPEED     115200

#define BT_TX_PIN      GPIO_Pin_9
#define BT_RX_PIN      GPIO_Pin_10
#define BT_PORT             GPIOA   //USART and IO pins must be in the same port.
#define BT_USART          USART1
#define BT_ON     GPIO_Pin_11
#define BT_SPEED     115200

#define CH1_LED_TIM   TIM2
#define CH1_LED_PORT   GPIOA
#define CH1_R_LED_PIN   GPIO_Pin_0
#define CH1_G_LED_PIN   GPIO_Pin_1
#define CH1_B_LED_PIN   GPIO_Pin_2

#define CH2_LED_TIM   TIM4
#define CH2_LED_PORT   GPIOB
#define CH2_R_LED_PIN   GPIO_Pin_6
#define CH2_G_LED_PIN   GPIO_Pin_7
#define CH2_B_LED_PIN   GPIO_Pin_8

#define LED_FRESH_RATE  60
#define CPU_F                           16000000
#define PWM_RES                     255

#define START_BYTE          1
#define STOP_BYTE              START_BYTE + 2
#define FRAME_LENGTH    6


#endif /*HWCONF_H_ */
