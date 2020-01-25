/*
 * File:   lab_1.c
 * Author: Juan Castillo
 * Student ID: 17074
 *
 * Created on Jan. 24, 2020
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 4000000
//variables a utilizar
char carrera1 = 1;
char carrera2 = 1;
char i = 3;

unsigned char SEGMENTOS[] = {0X3F,0x06,0x5B,0x4F};


void main(void) {
    OSCCON = 0b110;
    TRISC = 0;//PORTC output
    TRISDbits.TRISD2 = 0;//PORTD output
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    //TRISEbits.TRISE0 = 1; //RE0 input
    //TRISEbits.TRISE1 = 1; //RE1 input
    TRISEbits.TRISE3 = 1; //RE2 input
    //TRISA = 0; //PORTD output
    //TRISB = 0; //PORTB output
    ANSELH = 0;
    ANSEL = 0;
    
        /*for (int i=0; i<=3; i++){
             PORTC = ~SEGMENTOS[i];
             __delay_ms(5);
        }*/
    PORTC = SEGMENTOS[0];
    if (PORTEbits.RE3 ==1){
        PORTC = SEGMENTOS[i];
        PORTDbits.RD2 = 1;
        PORTDbits.RD3 = 0;
        PORTDbits.RD4 = 0;
        __delay_ms(5);
        i = i-1;
        
        PORTC = SEGMENTOS[i];
        PORTDbits.RD2 = 0;
        PORTDbits.RD3 = 1;
        PORTDbits.RD4 = 0;
        __delay_ms(5);
        i = i-1;
        PORTC = SEGMENTOS[i];
        PORTDbits.RD2 = 0;
        PORTDbits.RD3 = 0;
        PORTDbits.RD4 = 1;
        __delay_ms(5);
        i = i-1;
        PORTC = SEGMENTOS[i];
        PORTDbits.RD2 = 1;
        PORTDbits.RD3 = 1;
        PORTDbits.RD4 = 1;
        __delay_ms(5);
    }
    else {
        PORTDbits.RD2 = 0;
        PORTDbits.RD3 = 0;
        PORTDbits.RD4 = 0;
        i = 3;
    } 
    return;
}

/*void setup (void){
    OSCCON 0b110;
    TRISC = 0;//PORTC output
    TRISD = 0; //PORTD output
    TRISEbits.TRISE0 = 1; //RE0 input
    TRISEbits.TRISE1 = 1; //RE1 input
    TRISEbits.TRISE2 = 1; //RE2 input
    TRISA = 0; //PORTD output
    TRISB = 0; //PORTB output
    ANSELH = 0;
    ANSEL = 0;
}*/
/*void display (void){
    while(1){
        for (int i=0; i<=3; i++){
             PORTD = ~7SEGMENTOS[i];
             __delay_ms(5);
        }
        if (PORTEbits.RE0 !=1){
            PORTD = ~SEGMENTOS[i];
            __delay_ms(5);
            i = i-1;
            PORTD = ~SEGMENTOS[i];
            __delay_(5);
            i = i-1;
            PORTD = ~SEGMENTOS[i];
            __delay_ms(5);
            i = i-1;
            PORTD = ~SEGMENTOS[i];
        }
    }
}*/