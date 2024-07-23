#include <stdio.h>
 #include <unistd.h>
 #include "system.h"
 #include "altera_avalon_pio_regs.h"
void displayHEX(const char* letter);
void clearLEDS();
void flashLEDS();
int debounce(int key);
void displayNumHex(int num);
void howToOrder();
void flashLEDR();
void flashLEDG();

int main(){

    int total = 0;

while(1){
    while(!debounce(KEY3_BASE)){
    //Check if no keys are pressed, default to Welcome
    const char PressKY3[8] = {'P', 'R', 'E', 'S', 'S', ' ', 'B', '3'};
    displayHEX(PressKY3);
    usleep(2000000);
    const char toOrder[8] = {'T', 'O', ' ', 'O', 'R', 'D', 'E', 'R'};
    displayHEX(toOrder);
    usleep(2000000);
    }

    flashLEDS();
    howToOrder();
    howToOrder();
    while(total < 350){
        if(debounce(KEY2_BASE)){
            total += 25;
            flashLEDR();
        }else if (debounce(KEY1_BASE)){
            total += 10;
            flashLEDG();
        }

        displayNumHex(total);
    }

    //Pizza Dispensed
    total = 350-total;
    const char TEXT1[8] = {'P', 'I', 'Z', 'Z', 'A', ' ', ' ', ' '};
    displayHEX(TEXT1);
    usleep(1000000);
    const char TEXT2[8] = {'R', 'E', 'A', 'D', 'Y', ' ', ' ', ' '};
    displayHEX(TEXT2);
    usleep(2000000);
    const char totaltext[8] = {'T', 'O', 'T', 'A', 'L', ' ', ' ', ' '};
    displayHEX(totaltext);
    usleep(2000000);
    const char TEXT3[8] = {'C', 'H', 'A', 'N', 'G', 'E', ' ', ' '};
    displayHEX(TEXT3);
    usleep(2000000);
    displayNumHex(total);
    usleep(2000000);
    total = 0;
}
 return 0;
}

//Code to display Letters with corresponding HEX values from string array.
void displayHEX(const char* letter){
     const char lookUpLetterTable[128] = {
             ['0'] = 0x40, ['1'] = 0x79, ['2'] = 0x24, ['3'] = 0x30, //0-9
             ['4'] = 0x19, ['5'] = 0x12, ['6'] = 0x02, ['7'] = 0xF8,
             ['8'] = 0x00, ['9'] = 0x10,
             [' '] = 0xFF, ['A'] = 0x88, ['B'] = 0x83, ['C'] = 0xC6, //A-Z w/space
             ['D'] = 0xA1, ['E'] = 0x86, ['F'] = 0x8E, ['G'] = 0xC2,
             ['H'] = 0x89, ['I'] = 0xCF, ['J'] = 0xE1, ['K'] = 0x8A,
             ['L'] = 0xC7, ['M'] = 0xAA, ['N'] = 0xC8, ['O'] = 0xA3,
             ['P'] = 0x8C, ['Q'] = 0x98, ['R'] = 0xAF, ['S'] = 0x92,
             ['T'] = 0x87, ['U'] = 0xC1, ['V'] = 0xE3, ['W'] = 0xE2,
             ['X'] = 0x9B, ['Y'] = 0x91, ['Z'] = 0xA4
     };

     IOWR_ALTERA_AVALON_PIO_DATA(HEX7_BASE, lookUpLetterTable[(int)letter[0]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX6_BASE, lookUpLetterTable[(int)letter[1]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE, lookUpLetterTable[(int)letter[2]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE, lookUpLetterTable[(int)letter[3]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, lookUpLetterTable[(int)letter[4]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, lookUpLetterTable[(int)letter[5]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, lookUpLetterTable[(int)letter[6]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, lookUpLetterTable[(int)letter[7]]);
}

void display_green_LEDs(unsigned int value) {
IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, value);}
void display_red_LEDs(unsigned int value) {
IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, value);
}

void flashLEDS(){
    int delay = 0;
    while(delay < 16){
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b101010101010101010);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0b10101010);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0);
        delay++;
    }
}
void flashLEDR(){
    int delay = 0;
    while(delay < 2){
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 10101010);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 01010101);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0);
        delay++;
    }
}
void flashLEDG(){
    int delay = 0;
    while(delay < 2){
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b101010101010101010);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b010101010101010101);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0);
        delay++;
    }
}

int debounce(int key){
    int delay = 200000;
    if (IORD_ALTERA_AVALON_PIO_DATA(key) == 0){
        usleep(delay);
        if(IORD_ALTERA_AVALON_PIO_DATA(key) == 0){
            while (IORD_ALTERA_AVALON_PIO_DATA(key) == 0){
                usleep(delay);
            }
            return 1;
        }
    }
    return 0;
}


void displayNumHex(int num){
    static const char LookUpTable[10]= {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0xF8, 0x00, 0x10};

    if (num < 0){
        num = num * (-1);
    }


    int num_of_HEX2 =(num/100) % 10; // Hundrenth's Place
    int num_of_HEX1 =(num/10) % 10;  // Tenth's Place
    int num_of_HEX0 = num % 10;   // Ones Place

    IOWR_ALTERA_AVALON_PIO_DATA(HEX7_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX6_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, LookUpTable[num_of_HEX2]);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, LookUpTable[num_of_HEX1]);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, LookUpTable[num_of_HEX0]);

}

void howToOrder(){
    const char PressKY3[8] = {'P', 'R', 'E', 'S', 'S', ' ', ' ', ' '};
    displayHEX(PressKY3);
    const char priceOf[8] = {'B', '2', ' ', '4', ' ', '2', '5', 'C'};
    displayHEX(priceOf);
    usleep(2000000);
    const char ten[8] = {'B', '1', ' ', '4', ' ', '1', '0', 'C'};
    displayHEX(ten);
    usleep(2000000);
    const char toOrder[8] = {'T', 'O', ' ', 'O', 'R', 'D', 'E', 'R'};
    displayHEX(toOrder);
    usleep(2000000);
}




    int total = 0;

while(1){
    while(!debounce(KEY3_BASE)){
    //Check if no keys are pressed, default to Welcome
    const char PressKY3[8] = {'P', 'R', 'E', 'S', 'S', ' ', 'B', '3'};
    displayHEX(PressKY3);
    usleep(2000000);
    const char toOrder[8] = {'T', 'O', ' ', 'O', 'R', 'D', 'E', 'R'};
    displayHEX(toOrder);
    usleep(2000000);
    }

    flashLEDS();
    howToOrder();
    howToOrder();
    while(total < 350){
        if(debounce(KEY2_BASE)){
            total += 25;
            flashLEDR();
        }else if (debounce(KEY1_BASE)){
            total += 10;
            flashLEDG();
        }

        displayNumHex(total);
    }

    //Pizza Dispensed
    total = 350-total;
    const char TEXT1[8] = {'P', 'I', 'Z', 'Z', 'A', ' ', ' ', ' '};
    displayHEX(TEXT1);
    usleep(1000000);
    const char TEXT2[8] = {'R', 'E', 'A', 'D', 'Y', ' ', ' ', ' '};
    displayHEX(TEXT2);
    usleep(2000000);
    const char totaltext[8] = {'T', 'O', 'T', 'A', 'L', ' ', ' ', ' '};
    displayHEX(totaltext);
    usleep(2000000);
    const char TEXT3[8] = {'C', 'H', 'A', 'N', 'G', 'E', ' ', ' '};
    displayHEX(TEXT3);
    usleep(2000000);
    displayNumHex(total);
    usleep(2000000);
    total = 0;
}
 return 0;
}

//Code to display Letters with corresponding HEX values from string array.
void displayHEX(const char* letter){
     const char lookUpLetterTable[128] = {
             ['0'] = 0x40, ['1'] = 0x79, ['2'] = 0x24, ['3'] = 0x30, //0-9
             ['4'] = 0x19, ['5'] = 0x12, ['6'] = 0x02, ['7'] = 0xF8,
             ['8'] = 0x00, ['9'] = 0x10,
             [' '] = 0xFF, ['A'] = 0x88, ['B'] = 0x83, ['C'] = 0xC6, //A-Z w/space
             ['D'] = 0xA1, ['E'] = 0x86, ['F'] = 0x8E, ['G'] = 0xC2,
             ['H'] = 0x89, ['I'] = 0xCF, ['J'] = 0xE1, ['K'] = 0x8A,
             ['L'] = 0xC7, ['M'] = 0xAA, ['N'] = 0xC8, ['O'] = 0xA3,
             ['P'] = 0x8C, ['Q'] = 0x98, ['R'] = 0xAF, ['S'] = 0x92,
             ['T'] = 0x87, ['U'] = 0xC1, ['V'] = 0xE3, ['W'] = 0xE2,
             ['X'] = 0x9B, ['Y'] = 0x91, ['Z'] = 0xA4
     };

     IOWR_ALTERA_AVALON_PIO_DATA(HEX7_BASE, lookUpLetterTable[(int)letter[0]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX6_BASE, lookUpLetterTable[(int)letter[1]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE, lookUpLetterTable[(int)letter[2]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE, lookUpLetterTable[(int)letter[3]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, lookUpLetterTable[(int)letter[4]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, lookUpLetterTable[(int)letter[5]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, lookUpLetterTable[(int)letter[6]]);
     IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, lookUpLetterTable[(int)letter[7]]);
}

void display_green_LEDs(unsigned int value) {
IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, value);}
void display_red_LEDs(unsigned int value) {
IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, value);
}

void flashLEDS(){
    int delay = 0;
    while(delay < 16){
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b101010101010101010);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0b10101010);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0);
        delay++;
    }
}
void flashLEDR(){
    int delay = 0;
    while(delay < 2){
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 10101010);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 01010101);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, 0);
        delay++;
    }
}
void flashLEDG(){
    int delay = 0;
    while(delay < 2){
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b101010101010101010);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0b010101010101010101);
        usleep(100000);
        IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, 0);
        delay++;
    }
}

int debounce(int key){
    int delay = 200000;
    if (IORD_ALTERA_AVALON_PIO_DATA(key) == 0){
        usleep(delay);
        if(IORD_ALTERA_AVALON_PIO_DATA(key) == 0){
            while (IORD_ALTERA_AVALON_PIO_DATA(key) == 0){
                usleep(delay);
            }
            return 1;
        }
    }
    return 0;
}


void displayNumHex(int num){
    static const char LookUpTable[10]= {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0xF8, 0x00, 0x10};

    if (num < 0){
        num = num * (-1);
    }


    int num_of_HEX2 =(num/100) % 10; // Hundrenth's Place
    int num_of_HEX1 =(num/10) % 10;  // Tenth's Place
    int num_of_HEX0 = num % 10;   // Ones Place

    IOWR_ALTERA_AVALON_PIO_DATA(HEX7_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX6_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE,0xff);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, LookUpTable[num_of_HEX2]);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, LookUpTable[num_of_HEX1]);
    IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, LookUpTable[num_of_HEX0]);

}

void howToOrder(){
    const char PressKY3[8] = {'P', 'R', 'E', 'S', 'S', ' ', ' ', ' '};
    displayHEX(PressKY3);
    const char priceOf[8] = {'B', '2', ' ', '4', ' ', '2', '5', 'C'};
    displayHEX(priceOf);
    usleep(2000000);
    const char ten[8] = {'B', '1', ' ', '4', ' ', '1', '0', 'C'};
    displayHEX(ten);
    usleep(2000000);
    const char toOrder[8] = {'T', 'O', ' ', 'O', 'R', 'D', 'E', 'R'};
    displayHEX(toOrder);
    usleep(2000000);
}



