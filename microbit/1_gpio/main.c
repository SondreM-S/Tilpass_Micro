#include <stdint.h>

#define GPIO0 ((NRF_GPIO_REGS0*)0x50000000) //gpio 0 base adress
#define GPIO1 ((NRF_GPIO_REGS1*)0x50000300) //gpio 1 base adress

typedef struct {
	// From base adress to OUT at 0x504 = (504_16) 1284(_10) -> 321 shifts from 0x000 to 0x504 
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	// From DetectMode end 0x528 to pin_cnf 0x700 -> ((0x700 = 1792_10) - (0x528 = 1320_10)) / 4 = 472 / 4 = 118
	volatile uint32_t RESERVED1_0[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS0;

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1_1[120];
	volatile uint32_t PIN_CNF[10];
} NRF_GPIO_REGS1;

int main(){

	// Configure leds (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[21] = 0; //Row 1
	GPIO0->PIN_CNF[22] = 0; //Row 2
	GPIO0->PIN_CNF[15] = 0; //Row 3
	GPIO0->PIN_CNF[24] = 0; //Row 4
	GPIO0->PIN_CNF[19] = 0; //Row 5

	GPIO0->PIN_CNF[28] = 0; //Col 1
	GPIO0->PIN_CNF[11] = 0; //Col 2
	GPIO0->PIN_CNF[31] = 0; //Col 3
	GPIO1->PIN_CNF[5] = 0;  //Col 4
	GPIO0->PIN_CNF[30] = 0; //Col 5
	
	// Configure buttons (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
    //14 og 23 hentet fra schematics page 3

    volatile uint32_t btnA = 14;
    volatile uint32_t btnB = 23;
    GPIO0->PIN_CNF[btnA] = 0; // button A
    GPIO0->PIN_CNF[btnB] = 0; // button B



    int sleep = 0;
while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
        // if pin B is 1
        if (GPIO0->IN == 1 && GPIO0->PIN_CNF[btnB] == 1) {
            // turn LED on
            GPIO0->PIN_CNF[15] = 1; //Row 3
            GPIO0->PIN_CNF[31] = 1; //Col 3
        }

    /* Check if button A is pressed;
     * turn off LED matrix if it is. */
    if (GPIO0->IN == 1) && (GPIO0->PIN_CNF[btnA] == 1)) {
            GPIO0->PIN_CNF[15] = 1; //Row 3
            GPIO0->PIN_CNF[31] = 0; //Col 3
        }

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
