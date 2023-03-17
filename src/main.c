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

void main(void)
{
	init_LCD();
	display_on_LCD(113);

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


