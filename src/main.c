// Description----------------------------------------------------------------|
/*
 *
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#define STM32F051												   //COMPULSORY
#include "stm32f0xx.h"											   //COMPULSORY
#include "lcd_stm32f0.h"
#include <stdio.h>

// GLOBAL VARIABLES ----------------------------------------------------------|


// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);                                                   //COMPULSORY

// MAIN FUNCTION -------------------------------------------------------------|
void display_on_LCD(uint8_t num);
void init_LEDS(void);
void display_on_LEDs(uint8_t number);

void main(void)
{
	init_LCD();
	init_LEDS();

	while(1)
	{



	}
}

// OTHER FUNCTIONS -----------------------------------------------------------|

void display_on_LCD(uint8_t num){
	char str[3];
	sprintf(str,"%d",num); // convert number to string
	lcd_putstring(str); // put string on LCD
}

void init_LEDS(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable Port B
	GPIOB->MODER |= GPIO_MODER_MODER0_0|
					GPIO_MODER_MODER1_0|
					GPIO_MODER_MODER2_0|
					GPIO_MODER_MODER3_0|
					GPIO_MODER_MODER4_0|
					GPIO_MODER_MODER5_0|
					GPIO_MODER_MODER6_0|
					GPIO_MODER_MODER7_0; // Make it input mode

}
void display_on_LEDs(uint8_t number){
	GPIOB->ODR = number;
}

