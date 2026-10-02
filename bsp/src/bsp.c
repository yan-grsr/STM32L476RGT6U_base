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

void UART2_Init(void) {
	// Start GPIOA clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Configure PA2
	GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk; // Set MODE2 to 00
	GPIOA->MODER |= (0x10 << GPIO_MODER_MODE2_Pos); // Set MODE2 to 01 (AF)

	// Set to low speed
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2_Msk; // Set OSPEEDR to 00

	// Pull-up
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2_Msk;
	GPIOA->PUPDR |= (0x1 << GPIO_PUPDR_PUPD2_Pos);

	// AF7
	GPIOA->AFR &= (0x0000 << GPIO_AFRL_AFRL2);
	GPIOA->AFR |= (0x0111 << GPIO_AFRL_AFRL2);

	/*----------*/

	// Configure PA3
	GPIOA->MODER &= ~GPIO_MODER_MODE3_Msk; // Set MODE3 to 00
	GPIOA->MODER |= (0x10 << GPIO_MODER_MODE3_Pos); // Set MODE3 to 10 (AF)

	// Set to low speed
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3_Msk; // Set OSPEEDR to 00

	// Pull-up
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3_Msk;
	GPIOA->PUPDR |= (0x1 << GPIO_PUPDR_PUPD3_Pos);

	// AF7
	GPIOA->AFR &= (0x0000 << GPIO_AFRL_AFRL3);
	GPIOA->AFR |= (0x0111 << GPIO_AFRL_AFRL3);
}
