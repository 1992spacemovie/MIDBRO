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
// RC0 RC1 RA2
#define RGBr RA2
#define RGBg RC0
#define RGBb RC1

#define LED8r RC2
#define LED8y RB4
#define LED8g RB5

#define piezo RB6

#define tl1 RA4
#define tl2 RA5

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = 0b00111011; // nastaveni pinu jsko vstupy a vystupy
    TRISB = 0b10000000;
    TRISC = 0b11001000;

    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    LED8r = 0;
    LED8y = 0;
    LED8g = 0;
    piezo = 0;
    tl1 = 0;
    tl2 = 0;
    
    RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=1;
    __delay_ms(1000);
    RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=0;
    __delay_ms(1000);
    
    uint8_t a=0;
    uint8_t b=0;
    
    while(1){  
        for(uint8_t d=0;d<3;d++){
            while(a<255){
                b=0;
                RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=1;
                while(b<a){
                    b++;
                    for(uint8_t c=0;c<10;c++){}
                }
                RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=0;
                while(b<255){
                    b++;
                    for(uint8_t c=0;c<10;c++){}
                }
                a++;
            }

            while(a>0){
                b=0;
                RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=1;
                while(b<a){
                    b++;
                    for(uint8_t c=0;c<10;c++){}
                }
                RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=0;
                while(b<255){
                    b++;
                    for(uint8_t c=0;c<10;c++){}
                }
                a--;
            }
        }
        
        for(uint8_t d=0;d<15;d++){
            RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=1;
            __delay_ms(150);
            RGBr=RGBg=RGBb=LED8r=LED8y=LED8g=0;
            __delay_ms(150);
        }
    }
}