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
#include <stdio.h>
#include <stdlib.h> 

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

#define TL1 RA5
#define POT1 RC3
#define PIEZO RB6
#define LED8r RC2

#define LCD_D7 RA4
#define LCD_D6 RA0
#define LCD_D5 RC5
#define LCD_D4 RA1
#define LCD_D3 RC4
#define LCD_D2 RA2
#define LCD_D1 RC6
#define LCD_D0 RC0

#define LCD_EN RC7
#define LCD_RW RC1 // RW = 0-Write, 1-Read
#define LCD_RS RB4 // log.1 - DATA, log.0 - instrukce

#define LCD_INSTR_CLR 0b00000001
#define LCD_INSTR_RETURN_HOME 0b00000010

void lcd_instruction(uint8_t data, uint8_t instr){
    LCD_RS = data&1;
    LCD_RW = 0;
    asm("nop");
    asm("nop");
    LCD_EN = 1;
    LCD_D0 = instr&1;
    LCD_D1 = instr>>1&1;
    LCD_D2 = instr>>2&1;
    LCD_D3 = instr>>3&1;
    LCD_D4 = instr>>4&1;
    LCD_D5 = instr>>5&1;
    LCD_D6 = instr>>6&1;
    LCD_D7 = instr>>7&1;
    asm("nop");
    asm("nop");
    LCD_EN = 0;
    __delay_ms(1);
}

void lcd_init(){
    __delay_ms(15);
    lcd_instruction(0,0b00110000); // Function set - RST
    __delay_ms(10); // 4.1ms delay
    lcd_instruction(0,0b00110000); // Function set - RST 
    __delay_ms(1); // 100us delay
    lcd_instruction(0,0b00110000); // Function set - RST 100us delay
    __delay_ms(1); // 100us delay
    
    lcd_instruction(0,0b00111000); // Function set - 2lin, 5x8 
    __delay_ms(1); // 100us delay
    lcd_instruction(0,0b00001000); // Display off 
    __delay_ms(2); // 2ms delay
    lcd_instruction(0,0b00000001); // Clear display
    __delay_ms(10); // 100us delay
    lcd_instruction(0,0b00000110); // entry mode set - increment, no shift
    __delay_ms(10);
    lcd_instruction(0,0b00001100); // Display on, Cur off, blink - TEST
    __delay_ms(2); // 2ms delay
}

void lcd_write_to_place(uint8_t row, char *text){
    // 0x40 secondline
    if(row==0){
        lcd_instruction(0, 0b10000000);
    } else {
        lcd_instruction(0, 0b11000000);
    }
    while(*text){
        lcd_instruction(1,*text);
        text++;
    }
}

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    ANSELbits.ANS7 = 1;
    ADCON0 = 0b10100111;
    ADCON1 = 0b01010000;
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = 0b00100000;
    TRISB = 0b00000000;
    TRISC = 0b00001000;
    
    LCD_D7 = LCD_D6 = LCD_D5 = LCD_D4 = LCD_D3 = LCD_D2 = LCD_D1 = LCD_D0 = 0;
    LCD_EN = 0;
    LCD_RW = 0;
    LCD_RS = 0;
        
    lcd_init();
    
    uint8_t radek1[9] = "Hello   ";
    uint8_t radek2[9] = "  world!";
    
    lcd_write_to_place(0, (char*)&radek1);
    lcd_write_to_place(1, (char*)&radek2);
    
    while(1){
        
    }
}