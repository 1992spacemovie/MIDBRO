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

void prolinej(){
    uint8_t a=0;
    uint8_t b=0;
    while(a<255){
            b=0;
            LED8r=1;
            LED8y=0;
            while(b<a){
                b++;
                if(tl1||tl2){return;}
            }
            LED8r=0;
            LED8y=1;
            while(b<255){
                b++;
                if(tl1||tl2){return;}
            }
            a++;
    }
    while(a>0){
            b=0;
            LED8r=1;
            LED8y=0;
            while(b<a){
                b++;
                if(tl1||tl2){return;}
            }
            LED8r=0;
            LED8y=1;
            while(b<255){
                b++;
                if(tl1||tl2){return;}
            }
            a--;
    }
    return;
}

/* frekvence
C1 - 262Hz
D1 - 294Hz
E1 - 330Hz
F1 - 349Hz
G1 - 392Hz
A1 - 440Hz
B1 - 494Hz
C2 - 523Hz  
*/

void C(){
    for(uint8_t d=0;d<128;d++){
        piezo=1;
        __delay_us(1908);
        piezo=0;
        __delay_us(1908);
    }
}

void CP(){
    for(uint8_t d=0;d<64;d++){
        piezo=1;
        __delay_us(1908);
        piezo=0;
        __delay_us(1908);
    }
}

void D(){
    for(uint8_t d=0;d<143;d++){
        piezo=1;
        __delay_us(1701);
        piezo=0;
        __delay_us(1701);
    }
}

void DP(){
    for(uint8_t d=0;d<72;d++){
        piezo=1;
        __delay_us(1701);
        piezo=0;
        __delay_us(1701);
    }
}

void E(){
    for(uint8_t d=0;d<161;d++){
        piezo=1;
        __delay_us(1515);
        piezo=0;
        __delay_us(1515);
    }
}

void EP(){
    for(uint8_t d=0;d<80;d++){
        piezo=1;
        __delay_us(1515);
        piezo=0;
        __delay_us(1515);
    }
}

void F(){
    for(uint8_t d=0;d<170;d++){
        piezo=1;
        __delay_us(1433);
        piezo=0;
        __delay_us(1433);
    }
}

void G(){
    for(uint8_t d=0;d<191;d++){
        piezo=1;
        __delay_us(1276);
        piezo=0;
        __delay_us(1276);
    }
}

void A(){
    for(uint8_t d=0;d<214;d++){
        piezo=1;
        __delay_us(1136);
        piezo=0;
        __delay_us(1136);
    }
}

void H(){
    for(uint8_t d=0;d<241;d++){
        piezo=1;
        __delay_us(1012);
        piezo=0;
        __delay_us(1012);
    }
}

void C2(){
    for(uint8_t d=0;d<255;d++){
        piezo=1;
        __delay_us(956);
        piezo=0;
        __delay_us(956);
    }
}

void stupnice(){
    C();
    D();
    E();
    F();
    G();
    A();
    H();
    C2();
    __delay_ms(487);
    C2();
    H();
    A();
    G();
    F();
    E();
    D();
    C();
}

void OdeToJoy(){
    const uint8_t delkaMezery = 5;
    E();
    __delay_ms(delkaMezery);
    E();
    F();
    G();
    __delay_ms(delkaMezery);
    G();
    F();
    E();
    D();
    C();
    __delay_ms(delkaMezery);
    C();
    D();
    E();
    __delay_ms(delkaMezery);
    E();
    EP();
    DP();
    __delay_ms(delkaMezery);
    D();D();
    E();
    __delay_ms(delkaMezery);
    E();
    F();
    G();
    __delay_ms(delkaMezery);
    G();
    F();
    E();
    D();
    C();
    __delay_ms(delkaMezery);
    C();
    D();
    E();
    D();
    DP();
    CP();
    __delay_ms(delkaMezery);
    C();
}

void ChristmasTruce(){
    for(uint8_t ch=0;ch<12;ch++){
        E();
        H();
        C();
        A();
    }
}

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
    
    while(1){
        prolinej();
        if(tl1){
            stupnice();
        }
        if(tl2){
            OdeToJoy();
        }
    }
}
