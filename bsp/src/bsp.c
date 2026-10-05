/*
 * bsp.c
 *
 *  Created on: Oct 1, 2026
 *      Author: yan
 */

#include "bsp.h"


/*
 * Initialize LED2 on PA5
 */

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


/*
 * Toggle the LED
 */

void LED_Toggle(void) {
	// Toggle bit 5 of the output register (PA5 / LED)
	GPIOA->ODR ^= GPIO_ODR_OD5;
}

/*
 * Turn the LED on
 */

void LED_On(void) {
	GPIOA->ODR = GPIO_BSRR_BS5;
}


/*
 * Turn the LED off
 */

void LED_Off(void) {
	GPIOA->ODR = GPIO_BSRR_BR5;
}


/*
 * Initialize the button on PC13
 */

void Button_Init(void) {
	// Start GPIOC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	// Configure PC13 as an GPIO input
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk; // Set MODE13 to 00 (GPIO input)

	// Pull-up
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13_Msk);
	GPIOC->PUPDR |= (0x1 << GPIO_PUPDR_PUPD13_Pos);
}

/*
 * Read the button state
 * Return 1 if it is pressed
 * else 0
 */
uint8_t Button_Get_State(void) {
	return (GPIOC->IDR & GPIO_IDR_ID13) != GPIO_IDR_ID13;
}


/*
 * Initialize USART2 at 9600 bauds/s on PA2 and PA3
 */

void USART2_Init(void) {
	// Start GPIOA clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Configure PA2 and PA3
	GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk); // Set MODE2 to 00
	GPIOA->MODER |= (0x2 << GPIO_MODER_MODE2_Pos) | (0x2 << GPIO_MODER_MODE3_Pos); // Set MODE2 to 10 (AF)

	// Pull-up
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2_Msk | GPIO_PUPDR_PUPD3_Msk);
	GPIOA->PUPDR |= (0x1 << GPIO_PUPDR_PUPD2_Pos) | (0x1 << GPIO_PUPDR_PUPD3_Pos);

	// AF7
	GPIOA->AFR[0] &= ~(0x0000FF00);
	GPIOA->AFR[0] |=  (0x00007700);


	// Configure UART2

	// Start UART2 clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	// Set SYSCLK as uart2 clock f = 4MHz
	RCC->CCIPR &= ~RCC_CCIPR_USART2SEL_Msk;
	RCC->CCIPR |= (0x1 << RCC_CCIPR_USART2SEL_Pos);

	USART2->CR1 |= USART_CR1_OVER8;
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;

	// BRR = 2*f/bdr = 2 * 4 *10^6 / 115200 = 69.444
	// BRR = 2*f/bdr = 2 * 4 *10^6 / 9600 = 833.333
	// UART2 at 9600 baud/s
	USART2->BRR = 833;

	// Enable USART2
	USART2->CR1 |= USART_CR1_UE;

}


/*
 * Initialize I2C3 peripheral at 100 kHz on PC0 (SCL) and PC1 (SDA)
 */

void I2C3_Init(void) {
	// Enable GPIOC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	// Set PC0 and PC1 as SCL and SDA

	GPIOC->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER |= (0x2 << GPIO_MODER_MODE0_Pos | 0x2 << GPIO_MODER_MODE1_Pos);

	// Setup Open-Drain
	GPIOC->OTYPER |= GPIO_OTYPER_OT_0 | GPIO_OTYPER_OT_1;

	// Set to very high speed
	GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0_Msk | GPIO_OSPEEDR_OSPEED1_Msk); // Set OSPEEDR to 00
	GPIOC->OSPEEDR |= (0x3 << GPIO_OSPEEDR_OSPEED0_Pos) | (0x3 << GPIO_OSPEEDR_OSPEED1_Pos);

	// Do not use the internal pull up resistors , they are to big. Use 1 kOhms resistors instead
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk | GPIO_PUPDR_PUPD1_Msk);
	//GPIOC->PUPDR |= (0x1 << GPIO_PUPDR_PUPD0_Pos) | (0x1 << GPIO_PUPDR_PUPD1_Pos);

	// AF4
	GPIOC->AFR[0] &= ~(0x000000FF);
	GPIOC->AFR[0] |=  (0x00000044);

	// Use SYSCLK as I2C3 clock | f = 4MHz
	RCC->CCIPR &= ~RCC_CCIPR_I2C3SEL_Msk;
	RCC->CCIPR |= (0x1 << RCC_CCIPR_I2C3SEL_Pos);

	// Enable I2C3 clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_I2C3EN;

	// Make sure I2C3 is disabled
	I2C3->CR1 &= ~I2C_CR1_PE;

	// Reset I2C3 Configuration to default values
	I2C3->CR1 	  = 0x00000000;
	I2C3->CR2 	  = 0x00000000;
	I2C3->TIMINGR = 0x00000000;

	// Configure timing for fSCL = 100kHz, 50% duty cycle
	I2C3->TIMINGR |= ((1 - 1) <<I2C_TIMINGR_PRESC_Pos); // Clock prescaler
	I2C3->TIMINGR |= (20 << I2C_TIMINGR_SCLH_Pos);  // High half-period = 5µs
	I2C3->TIMINGR |= (20 << I2C_TIMINGR_SCLL_Pos);  // Low  half-period = 5µs

	// Enable 12C3
	I2C3->CR1 |= I2C_CR1_PE;

}


