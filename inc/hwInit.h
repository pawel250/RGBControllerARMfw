/*
 * hwInit.h
 *
 *  Created on: 2 lut 2015
 *      Author: pawel
 */

#ifndef HWINIT_H_
#define HWINIT_H_

#include "stm32f10x.h"
#include "hwConf.h"
 void RCC_Conf(void);
 void NVIC_Conf(void);
 void UART_Conf(void);
 void GPIO_Conf(void);
 void TIM_Conf( TIM_TypeDef* TIMx );

#endif /* HWINIT_H_ */
