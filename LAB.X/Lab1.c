/*
 * First lab for Digital 2 course
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
// definimos variables para puertos
#define _XTAL_FREQ 4000000

#define estado_jugador1 RE2
#define estado_jugador2 RE2
//variables a utilizar
char Estado = 0;
char EJ1 = 0;
char EJ2 = 1;
char i = 3;
char x = 0;
char y = 0;

unsigned char SEGMENTOS[] = {0X3F,0x06,0x5B,0x4F};
unsigned char jugador1[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char jugador2[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
void JUEGO ();

void main(void) {
    OSCCON = 0b110;
    TRISC = 0;//PORTC output
    TRISDbits.TRISD2 = 0;//PORTD output
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    TRISA = 0; //PORTA output
    TRISEbits.TRISE1 = 1; //RE1 input
    TRISEbits.TRISE2 = 1; //RE2 input
    TRISEbits.TRISE3 = 1; //RE3 input
    //TRISB = 0; //PORTB output
    ANSELH = 0;
    ANSEL = 0;
   
    while(1){
        PORTC = 0;
        PORTA = 0;
        PORTDbits.RD2 = 0;
        PORTDbits.RD3 = 0;
        PORTDbits.RD4 = 0;
        if (PORTEbits.RE3 == 1){ 
            Estado = 1;
        }
        if (PORTEbits.RE3 == 0 && Estado == 1){ 
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
            Estado = 0;
            __delay_ms(5); 
            JUEGO();
        }
    } 
}
    


void JUEGO (){
    while(1){
        if (PORTEbits.RE1 == 1){
                EJ1 = 1;
            }
        if (PORTEbits.RE1 == 0 && EJ1 == 1){
            x=x+1;
            PORTA = jugador1[x];
            EJ1 = 0;
        }
        if (x==8){
            PORTA = 0;
        }
        if(x==9){
            x=0;
            i=3;
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 0;
            PORTDbits.RD4 = 0;
            return; 
        }    
        if (PORTEbits.RE2 == 1){
            EJ2 = 1;
        }
        if (PORTEbits.RE2 == 0 && EJ2 == 1){
            y=y+1;
            PORTB = jugador2[y];
            EJ2 = 0;
        }
        if (y==8){
            PORTB = 0;
        }
        if(y==9){
            y=0;
            i=3;
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 0;
            PORTDbits.RD4 = 0;
            return; 
    }    
}
}