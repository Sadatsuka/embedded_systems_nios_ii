#include <stdio.h>
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <math.h>
#include <stdbool.h>

void displayHEX(int num);
void displayLED(unsigned int num);

int main(){
	bool isTrue = true;
	int input = 0;

	while (isTrue){
		printf("Press Option from 1 - 4 on console to display:\n");
		printf("Option 1: Minimum Signed 8-bit Integer\n");
		printf("Option 2: Maximum Signed 8-bit Integer\n");
		printf("Option 3: Maximum Unsigned 8-bit Integer\n");
		printf("Option 4: Custom Signed 8-bit Integer\n");
		scanf ("%d", &input);

		if(input == 1){
			printf("Minimum Signed 8-bit Integer: -128\n");
			displayHEX(-128);
			displayLED(-128);
			IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0xBF); //Negative Sign

		}else if (input == 2){
			printf("Maximum Signed Integer: -127\n");
			displayHEX(127);
			displayLED(127);
		}else if (input == 3){
			printf("Maximum Unsigned 8-bit Integer: 255\n");
			displayHEX(255);
			displayLED(255);
		}else if (input == 4){
			int num;
			printf("Enter a value between -128 to 127: ");
			scanf("%d", &num);
			if(num > -128 && num < 127){
				displayHEX(num);
				displayLED(num);
				if (num < 0){
					IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0xBF); //Negative Sign
				}
			}else{
				printf("Number out of range..\n");
			}
		}else{
			isTrue = false;
			printf("Option out of range, program end.\n");
		}
	}
	return 0;
}

void displayHEX(int num){
	static const char LookUpTable[10]= {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0xF8, 0x00, 0x10};

	if (num < 0){
		num = num * (-1);
	}
	int num_of_HEX3 =(num/1000) % 10; // Hundrenth's Place
	int num_of_HEX2 =(num/100) % 10; // Hundrenth's Place
	int num_of_HEX1 =(num/10) % 10;  // Tenth's Place
	int num_of_HEX0 = num % 10;	  // Ones Place

	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, LookUpTable[num_of_HEX3]);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, LookUpTable[num_of_HEX2]);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, LookUpTable[num_of_HEX1]);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, LookUpTable[num_of_HEX0]);
}

void displayLED(unsigned int num){
 
	IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, num);
}
