// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)


#include <xc.h>

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

#define SEG_A RC2
#define SEG_B RC1
#define SEG_C RC0
#define SEG_D RA2
#define SEG_E RC4
#define SEG_F RB4
#define SEG_G RC5

#define MAXJAS 127

//      a 
//  f   g   b
//  e       c
//      d

uint8_t PWM = 0;

void nic(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 0;
    SEG_G = 0;
}

void nula(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 0;
    
}

void jedna(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 0;
    SEG_G = 0;
}

void dva(){
    SEG_A = 1;
    SEG_B = 0;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 0;
    SEG_F = 1;
    SEG_G = 1;
}

void tri(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 1;
    SEG_G = 1;
}

void ctyri(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 1;
    SEG_F = 0;
    SEG_G = 1;
}

void pet(){
    SEG_A = 0;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 0;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void sest(){
    SEG_A = 0;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void sedm(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 1;
    SEG_G = 0;
}

void osm(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void devet(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 0;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void pismA(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void pismB(){
    SEG_A = 0;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 0;
    SEG_G = 1;
}

void pismC(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 0;
}

void pismD(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 0;
    SEG_F = 0;
    SEG_G = 1;
}

void pismE(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void pismF(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 0;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void cislo(uint8_t cislo){
    switch(cislo){
        case 0:
        {
            nula();
            break;
        }
        case 1:
        {
            jedna();
            break;
        }
        case 2:
        {
            dva();
            break;
        }
        case 3:
        {
            tri();
            break;
        }
        case 4:
        {
            ctyri();
            break;
        }
        case 5:
        {
            pet();
            break;
        }
        case 6:
        {
            sest();
            break;
        }
        case 7:
        {
            sedm();
            break;
        }
        case 8:
        {
            osm();
            break;
        }
        case 9:
        {
            devet();
            break;
        }
        case 0xA:
        {
            pismA();
            break;
        }
        case 0xB:
        {
            pismB();
            break;
        }
        case 0xC:
        {
            pismC();
            break;
        }
        case 0xD:
        {
            pismD();
            break;
        }
        case 0xE:
        {
            pismE();
            break;
        }
        case 0xF:
        {
            pismF();
            break;
        }
        default:
        {
            nic();
            break;
        }
        
    }
}

void PWMcisla(uint8_t cislo_in, uint8_t pwm){
    for(uint8_t i=0;i<MAXJAS;i++){
        if(i<pwm){
            cislo(cislo_in);
        } else {
            cislo(17);
        }
    }
}

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = 0b00111011; // nastaveni pinu jsko vstupy a vystupy
    TRISB = 0b10000000;
    TRISC = 0b11001000;
    
    // vyrobit semafor -> L0 (jenom blikání LED)
                        //L1 (jedno tlacítko nocní rezim)
                        //L2 (plus pri stisknutem tlacitku zvuk pro slepce)
    
    while (1){
        for(uint8_t i=0;i<16;i++){
            for(uint8_t j=0;j<MAXJAS;j++){
                PWMcisla(i,j);
            }
            for(uint8_t j=MAXJAS;j>0;j--){
                PWMcisla(i,j);
            }
        }
        
    }
}
