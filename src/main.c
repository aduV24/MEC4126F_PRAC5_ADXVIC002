// Description----------------------------------------------------------------|
/*
 *
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#define STM32F051												   //COMPULSORY
#define SW1Pressed (((GPIOA->IDR) & (GPIO_IDR_1))==0)
#define SW2Pressed (((GPIOA->IDR) & (GPIO_IDR_2))==0)
#define SW3Pressed (((GPIOA->IDR) & (GPIO_IDR_3))==0)
#include "stm32f0xx.h"											   //COMPULSORY
#include "lcd_stm32f0.h"
#include <stdio.h>

// GLOBAL VARIABLES ----------------------------------------------------------|
uint8_t SW3_press_count = 0;
uint8_t count = 0;

// FUNCTION DECLARATIONS -----------------------------------------------------|
void display_on_LCD(uint8_t num);
void init_LEDS(void);
void display_on_LEDs(uint8_t number);
void init_switches(void);
void init_external_interrupts(void);
void main(void);                                                   //COMPULSORY

// MAIN FUNCTION -------------------------------------------------------------|


void main(void)
{
	init_LCD();
	init_LEDS();
	init_switches();
	init_external_interrupts();


	while(1)
	{
		if((SW3_press_count%2) != 0)
				{

					// Check for push button1
					if(SW1Pressed)
					{
						if(count==0xFF); // check that count is not > 225
						else{
							count+=1;
						}


					}
					// Check for push buttton2
					else if(SW2Pressed){
						count-=1;
					}
					// Display count on LED and LCD
					display_on_LEDs(count);
					display_on_LCD(count);
					delay(70000);

				}
		else
		{
			count = 0;
			lcd_command(CLEAR);
			display_on_LEDs(count);
		}




	}

}

// OTHER FUNCTIONS -----------------------------------------------------------|

void display_on_LCD(uint8_t num){
	lcd_command(CLEAR);
	char str[3];
	sprintf(str,"%d",num); // convert number to string
	lcd_putstring(str); // put string on LCD
}

void init_LEDS(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;	 // Enable Port B
	GPIOB->MODER |= GPIO_MODER_MODER0_0|
					GPIO_MODER_MODER1_0|
					GPIO_MODER_MODER2_0|
					GPIO_MODER_MODER3_0|
					GPIO_MODER_MODER4_0|
					GPIO_MODER_MODER5_0|
					GPIO_MODER_MODER6_0|
					GPIO_MODER_MODER7_0; // Make it ouput mode

}
void display_on_LEDs(uint8_t number){
	GPIOB->ODR = number;
}

void init_switches(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Enable Port A
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_0; // Enable PUPDR for pin1
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR2_0; // Enable PUPDR for pin2
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_0; // Enable PUPDR for pin3

}

void init_external_interrupts(void){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA; //Route PA to EXTI3
	EXTI->IMR |= EXTI_IMR_IM3; //Unmask the interrupt
	EXTI->FTSR |= EXTI_FTSR_TR3;//falling-edge Trigger

	NVIC_EnableIRQ(EXTI2_3_IRQn); //Enable the EXTI2_3 NVIC
}

void EXTI2_3_IRQHandler(void){
		SW3_press_count+=1; // increment count variable

		// Clear interrupt pending bit by writing to it
		EXTI->PR |= EXTI_PR_PR3;

}

