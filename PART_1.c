#include <stdio.h>
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <math.h>
#include <stdbool.h>

void delay();
void resetLEDS();
int displayLED(int num);

int main()
{
	resetLEDS();
//PART ONE (1) BASIC LED CONTROL
  int num = 0;

  printf("Enter an option to turn on LEDG0-LEDG3\n");
  //printf("Option (1-4): ");
  scanf("%d", &num);

  if(num == 1){
  		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b0001);
  	  }else if(num == 2){
  		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b0010);
  	  }else if(num == 3){
  		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b0100);
  	  }else if(num == 4){
  		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b1000);
  	  }else{
  		 printf("Wrong value, default to LEG0\n");
  		 num = 1;
  	  }

  //PART ONE (2) SCROLLING LEDS
  int scrollingLED = 0;
  printf("Option 5: Enter 5 to scroll LED to the left,\n");
  printf("Option 6: Enter 6 to scroll LED to the right\n");
  scanf("%d", &scrollingLED);

  if(scrollingLED == 5){
	  num = num+1;
	  displayLED(num);
  }else if(scrollingLED == 6){
	  num = num-1;
	  displayLED(num);
  }else{
	  printf("Incorrect selection, num value: %d \n", num);
  }

  //PART ONE (3) ADDITIONAL FUNCTIONALITY
  int blinkingVal = 0; //Blinking Function
  printf("Current Number: %d \n", num);
  printf("Option 7: Enter 1 to activate blinking leds otherwise 0 to continue:");
  scanf("%d", &blinkingVal);
  int end = 0;
  if(blinkingVal == 1){
	  while(end < 10){
		  displayLED(num);
		  delay();
		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0);
		  delay();
		  end++;
	  }
  }else{
	  printf("Incorrect Input\n");
  }



  int displayPattern = 0;
  printf("Option 8: Enter 1 to activate a pattern otherwise 0 to continue to the next option: ");
  scanf("%d", &displayPattern);
  if(displayPattern == 1){
	  printf("Pattern displayed: Alternating LEDS\n");
	  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b10101010);
  }else{
	  printf("Incorrect Input\n");
  }

  displayPattern = 0;
  printf("Option 9: Enter 1 to activate your own sequence of LED states otherwise 0 to end:");
  scanf("%d", &displayPattern);
  int states = 0;
  if(displayPattern == 1){
	  printf("How many states for your sequence? Enter a value between 1-8:");
	  scanf("%d", &states);
	  char sequence[states];
	  char *sequence_ptr;

	  printf("Enter the binary sequence with specified state:");
	  scanf("%s", sequence);

	  //long int strtol(const char *str, char **endptr, int base)
	  long int convertVal = strtol(sequence, &sequence_ptr, 2);
	  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, convertVal);

  }else{
	  printf("Incorrect Input\n");
  }

  printf("End of Program");

  return 0;
}

void delay(){
	int delaying = 0;
	while (delaying < 750000){
		delaying++;
	}
}

void resetLEDS(){
	  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0);
	  IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0);
}

int displayLED(int num){
	if(num == 1){
		num = 0b0001;
		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b0001);
	  }else if(num == 2){
		  num = 0b0010;
		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b0010);
	  }else if(num == 3){
		  num = 0b0100;
		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b0100);
	  }else if(num == 4){
		  num = 0b1000;
		  IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b1000);
	  }else{
		 printf("Wrong value, default to LEG0\n");
		 num = 1;
		 IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b0001);
	  }
	return num;
}
