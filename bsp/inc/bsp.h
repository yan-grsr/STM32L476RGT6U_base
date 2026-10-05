/*
 * bsp.h
 *
 *  Created on: Oct 1, 2026
 *      Author: yan
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "stm32l4xx.h"

void LED_Init(void);
void LED_Toggle(void);
void LED_On(void);
void LED_Off(void);

void Button_Init(void);
uint8_t Button_Get_State(void);


void USART2_Init(void);

#endif /* INC_BSP_H_ */
