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

	// Set to low speed
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5_Msk; // Set OSPEEDR to 00

	// Pull-up
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_Msk;
	GPIOA->PUPDR |= (0x1 << GPIO_PUPDR_PUPD5_Pos);
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


void Button_Init(void) {
	// Start GPIOC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	// Configure PC13 as an GPIO input
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk; // Set MODE13 to 00 (GPIO input)

	// Pull-up
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13_Msk;
	GPIOC->PUPDR |= (0x1 << GPIO_PUPDR_PUPD13_Pos);
}

uint8_t Button_Get_State(void) {
	return (GPIOC->IDR & GPIO_IDR_ID13) != GPIO_IDR_ID13;
}
