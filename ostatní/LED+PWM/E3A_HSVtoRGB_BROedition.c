// CONFIG
#pragma config FOSC = INTRCIO  
#pragma config WDTE = OFF      
#pragma config PWRTE = OFF     
#pragma config MCLRE = ON      
#pragma config CP = OFF        
#pragma config CPD = OFF       
#pragma config BOREN = OFF     
#pragma config IESO = ON     
#pragma config FCMEN = OFF      

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

typedef struct RgbColor
{
    UINT8 r;
    UINT8 g;
    UINT8 b;
} RgbColor;

typedef struct HsvColor
{
    UINT8 h;
    UINT8 s;
    UINT8 v;
} HsvColor;

#define RGBg RA2
#define RGBb RC0
#define RGBr RC1
#define LED8r RC2
#define LED8y RB4
#define LED8g RB5
#define piezo RB6
#define tl1 RA4
#define tl2 RA5

#include <xc.h>

#define cykl 2
UINT8 i, i2, cekej;

UINT16 out = 0;
    UINT8 count = 0, count2 = 1;

RgbColor RGBcol;
RgbColor RGBsat;
RgbColor RGBout;


void PWM(UINT8 r, UINT8 g, UINT8 b)
{
    i2 = cykl;
    while(i2--)
    {
        i = 0;
        RGBr = RGBb = RGBg = 1;
        while(i < 250)
        {
            
            if(i == b) RGBb = 0;            
            if(i == g) RGBg = 0;
            if(i == r) RGBr = 0;
            i++;
        }
    }
}
void PWMset(UINT8 r, UINT8 g, UINT8 b, UINT8 i2)
{
    //i2 = cykl;
    while(i2--)
    {
        i = 0;
        RGBr = RGBb = RGBg = 1;
        while(i < 250)
        {
            if(i == b) RGBb = 0;            
            if(i == g) RGBg = 0;
            if(i == r) RGBr = 0;
            i++;
        }
    }
}

void setup()
{
    
    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    while(tl2); 
    LED8r = 1;
    __delay_ms(10);
    while(!tl2)
    {
        if(tl1) RGBout.r++;
        
        PWMset(RGBout.r, RGBout.g, RGBout.b, 3);
    }
    LED8r = 0;
    
    while(tl2); 
    LED8y = 1;
    __delay_ms(10);
    while(!tl2)
    {
        if(tl1) RGBout.g++;
        
        PWMset(RGBout.r, RGBout.g, RGBout.b, 3);
    }
    LED8y = 0;
    
    while(tl2); 
    LED8g = 1;
    __delay_ms(10);
    while(!tl2)
    {
        if(tl1) RGBout.b++;
        
        PWMset(RGBout.r, RGBout.g, RGBout.b, 3);
    }
    LED8g = 0;
    
    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    while(tl2);
    __delay_ms(10);
}

void convert_color(UINT16 in)
{
    if(in < 254)
    {
       RGBcol.r = in; 
       RGBcol.g = 0;
       RGBcol.b = 254 - in;
       return;
               
    }
    if(in < 508)
    {
       RGBcol.r = 254 - (in - 254); 
       RGBcol.g = in - 254;
       RGBcol.b = 0;
       return;
    }
    if(in < 762)
    {
       RGBcol.r = 0; 
       RGBcol.g = 254 - (in - 508);
       RGBcol.b = in - 508;
       return;
    }
    if(in < 1016)
    {
       RGBcol.r = in - 762; 
       RGBcol.g = 0;
       RGBcol.b = 254 - (in - 762);
       return;
    }
    
    
}
void convert_sat(UINT8 sat)
{
    UINT16 r,g,b;
       r = RGBcol.r; 
       g = RGBcol.g;
       b = RGBcol.b;
       
       r = r + sat;
       g = g + sat;
       b = b + sat;
       
       if(r >= 254) r = 254;
       if(g >= 254) g = 254;
       if(b >= 254) b = 254;
       
       RGBsat.r = r; 
       RGBsat.g = g;
       RGBsat.b = b;
}

void convert_val(UINT8 val)
{
       UINT16 r,g,b;
       r = RGBsat.r; 
       g = RGBsat.g;
       b = RGBsat.b;
       
       r = r / val;
       g = g / val;
       b = b / val;
       
       if(r >= 254) r = 254;
       if(g >= 254) g = 254;
       if(b >= 254) b = 254;
       
       RGBout.r = r; 
       RGBout.g = g;
       RGBout.b = b;
}

void setup_alt()
{
    
    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    while(tl2); 
    LED8r = 1;
    __delay_ms(10);
    while(!tl2)
    {
        if(tl1){ out++; if(out > 762) out = 0;}
        
        convert_color(out);
        convert_sat(count);
        convert_val(count2);
        
        PWMset(RGBout.r, RGBout.g, RGBout.b, 3);
    }
    LED8r = 0;
    
    while(tl2); 
    LED8y = 1;
    __delay_ms(10);
    while(!tl2)
    {
        if(tl1){ count++; if(count >= 150) count = 0;}
        
        convert_sat(count);
        convert_val(count2);
        
        PWMset(RGBout.r, RGBout.g, RGBout.b, 3);
    }
    LED8y = 0;
    
    while(tl2); 
    LED8g = 1;
    __delay_ms(10);
    while(!tl2)
    {
        if(tl1){ count2++; if(count2 >= 12) count2 = 1;}
        
        convert_val(count2);
        
        PWMset(RGBout.r, RGBout.g, RGBout.b, 20);
    }
    LED8g = 0;
    
    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    while(tl2);
    __delay_ms(10);
}

void main(void) {
    OSCCON = 0b01110101;
    
    TRISC = 0b11001000;
    TRISA = 0b00111011;
    TRISB = 0b10000000;
   
    ADCON1 = 0b01010000;
    ADCON0 = 0b00100111; //ZAROVANNI DOLEVA!
    
    ANSEL = 0b10000000;
    ANSELH = 0b00000011;
    
    
    
    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    LED8r = 0;
    LED8y = 0;
    LED8g = 0;
    piezo = 0;
    tl1 = 0;
    tl2 = 0;
    
    
    RGBout.r = 0;
    RGBout.g = 0;
    RGBout.b = 254;

    while(1)
    {
        if(tl2) setup_alt();
        
        
        //RGBout = HsvToRgb(HSVin);
        PWM(RGBout.r, RGBout.g, RGBout.b);
    }
}
