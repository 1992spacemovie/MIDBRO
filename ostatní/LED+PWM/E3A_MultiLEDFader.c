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

void PWM(uint8_t r, uint8_t g, uint8_t b){
    uint8_t citac = 0;
    while(citac<255){
        citac++;
        if(r>=citac){
            RGBr=1;
            LED8r=1;
        }
        if(r<citac){
            RGBr=0;
            LED8r=0;
        }
        if(g>=citac){
            RGBg=1;
            LED8g=1;
        }
        if(g<citac){
            RGBg=0;
            LED8g=0;
        }
        if(b>=citac){
            RGBb=1;
            LED8y=1;
        }
        if(b<citac){
            RGBb=0;
            LED8y=0;
        }
        __delay_us(10);
    }
    return;
}

void prolinej(uint8_t sr, uint8_t sg, uint8_t sb, uint8_t er, uint8_t eg, uint8_t eb, uint8_t kroky){
    uint8_t dr = 0;
    uint8_t zr = 0;  // 0-> plus, 1-> minus
    if(er>sr){
        dr = (er-sr)/kroky;
        zr = 0;
    } else {
        dr = (sr-er)/kroky;
        zr = 1;
    }
    
    uint8_t dg = 0;
    uint8_t zg = 0;  // 0-> plus, 1-> minus
    if(eg>sg){
        dg = (eg-sg)/kroky;
        zg = 0;
    } else {
        dg = (sg-eg)/kroky;
        zg = 1;
    }
    
    uint8_t db = 0;
    uint8_t zb = 0;  // 0-> plus, 1-> minus
    if(eb>sb){
        db = (eb-sb)/kroky;
        zb = 0;
    } else {
        db = (sb-eb)/kroky;
        zb = 1;
    }
    
    // tady budu resit prolinani
    // mame deltu rozdelenou na kroky a vime znamenko
    uint8_t aktkrok=0;
    while(kroky>aktkrok){
        uint8_t newr = 0;
        uint8_t newg = 0;
        uint8_t newb = 0;
        if(zr){
            newr = sr - aktkrok*dr;
        } else {
            newr = sr + aktkrok*dr;
        }
        
        if(zg){
            newg = sg - aktkrok*dg;
        } else {
            newg = sg + aktkrok*dg;
        }
        
        if(zb){
            newb = sb - aktkrok*db;
        } else {
            newb = sb + aktkrok*db;
        }
        for(uint8_t z=0;z<3;z++){
            PWM(newr, newg, newb);
        }
        aktkrok++;
    }
    
    
    //PWM();
    
    return;
}

void prolinejNew(uint8_t sr, uint8_t sg, uint8_t sb, uint8_t er, uint8_t eg, uint8_t eb, uint8_t kroky){
    uint8_t dr = 0;
    uint8_t zr = 0; // 0=+ , 1=-
    if(sr>er){
        dr=sr-er;
        zr=1;
    } else {
        dr=er-sr;
        zr=0;
    }
    
    uint8_t dg = 0;
    uint8_t zg = 0; // 0=+ , 1=-
    if(sg>eg){
        dg=sg-eg;
        zg=1;
    } else {
        dg=eg-sg;
        zg=0;
    }
    
    uint8_t db = 0;
    uint8_t zb = 0; // 0=+ , 1=-
    if(sb>eb){
        db=sb-eb;
        zb=1;
    } else {
        db=eb-sb;
        zb=0;
    }
    
    for(uint8_t i=0;i<kroky;i++){
        uint16_t red;
        uint16_t green;
        uint16_t blue;
        if(zr){
            red = sr-((i*dr)/kroky);
        } else {
            red = sr+((i*dr)/kroky);
        }
        if(zg){
            green = sg-((i*dg)/kroky);
        } else {
            green = sg+((i*dg)/kroky);
        }
        if(zb){
            blue = sb-((i*db)/kroky);
        } else {
            blue = sb+((i*db)/kroky);
        }
        PWM(red&0xFF, green&0xFF, blue&0xFF);
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
    
    // funkce PWM()
    // vsechny RGB ledky jsou 1
    // potom 3 if, kazdy citac kontroluje, jestli citac==0
    // 
    // cast 2
    // funkce prechod postupne vola PWM - 
    // meni v ni cisla (od [RGB], do [RGB], cekej)
    
    while (1){
        //PWM(150,30,15);
        if(tl1){
           prolinejNew(255,0,0,0,250,255,50);
           prolinejNew(0,250,255,255,0,0,50);
        } else {
            prolinejNew(250,0,0,0,250,0,50);
            prolinejNew(0,250,0,0,0,250,50);
            prolinejNew(0,0,250,250,0,0,50);
        }
        
    }
}
