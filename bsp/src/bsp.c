/*
 * bsp.c
 *
 *  Created on: Oct 1, 2026
 *      Author: yan
 */

#include "bsp.h"

void LED_Init(void) {
	// Start GPIOA clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Configure PA5 (LED) as an GPIO output
	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk; // Set MODE5 to 00
	GPIOA->MODER |= (0x01 << GPIO_MODER_MODE5_Pos); // Set MODE5 to 01 (GPIO output)
}

void LED_Toggle(void) {
	// Toggle bit 5 of the output register (PA5 / LED)
	GPIOA->ODR ^= GPIO_ODR_OD5;
}

void LED_On(void) {
	GPIOA->ODR = GPIO_BSRR_BS5;
}

void LED_Off(void) {
	GPIOA->ODR = GPIO_BSRR_BR5;
}
