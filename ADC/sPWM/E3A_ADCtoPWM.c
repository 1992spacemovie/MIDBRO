#include <xc.h>

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

// zadani 
// vezme hodnotu z AD a udela z ni PWM
// zkusit pipak z promennou freq (zmackne se cudlik - prommena frekvence podle potenciometru (200-4kHz))

/*uint8_t hodnotaSvetla(){
    ADCON0 = 0b10100111; //AN9 foto
    ADCON0bits.GO = 1;
    while(ADCON0bits.nDONE);
    foto = 0;
    foto = ADRESH;
    foto = (foto << 8) + ADRESL;
}*/

void main(void) {
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    ADCON0 = 0b10100111;
    ADCON1 = 0b01010000;
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
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
    
    while(1){
        // dostat data z potA
        ADCON0 = 0b00011111; //AN7 pot
        ADCON0bits.GO = 1;
        while(ADCON0bits.nDONE);

        // nyni budeme PWMkovat
        uint8_t PWMA = 0;
        while(PWMA<255){
            if(PWMA>ADRESH){
                LED8y=0;
            } else {
                LED8y=1;
            }
            PWMA++;
        }

        while(tl1){
            // dostat data z potB
            ADCON0 = 0b00100001; //AN8 pot
            ADCON0bits.GO = 1;
            while(ADCON0bits.nDONE);
            piezo=1;
            for(uint8_t i=0;i<ADRESH;i++){
                __delay_us(5);
            }
            piezo=0;
            for(uint8_t i=0;i<ADRESH;i++){
                __delay_us(5);
            }
        }
    }
    return;
}
