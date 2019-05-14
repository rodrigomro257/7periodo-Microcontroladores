/* 
 * File:   exercicio_PIC_6_calendario.c
 * Author: Windows
 *
 * Created on 19 de Março de 2019, 15:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "relogio_calendario.h"

#define _XTAL_FREQ 20000000

#pragma CONFIG WTG=OFF

calendario ca;
relogio re;

void main(void){
//INCICIALIZAÇÕES    
    ca.ano = 2019;
    ca.mes = 1;
    ca.dia = 1;
    
    TRISDbits.TRISD0=0; // LED.
    
    T0CONbits.TMR0ON=1; // HABILITA O TIMER 0;
    
    INTCONbits.TMR0IE=1; // HABILITA A FLAG DE INTERRUPÇÃO.
    INTCONbits.TMR0IF=0; // LIMPA A FLAG.
    
    T0CONbits.T08BIT=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    T0CONbits.T0CS=0; // UTILIZAR CLOCK INTERNO.
    
    TMR0=2535; // ISSO É O CONTADOR DE ONDE INICIA. 
    
    T0CONbits.TMR0ON=1;
    
    // HABILITA PRA USAR INTERRUPÇÃO HIGH OU LOW. 
    INTCONbits.GIEH=1; 
    INTCONbits.GIEL=1;
    
    while(1){
        
    }
    
    return;
}

void __interrupt() pic_isr(void){
    
    // TIMER0 INTERRUPT?
    if(TMR0IF){  
        //PORTBbits.RB0=PORTBbits.RB0+1;
        TMR0=2535;
        INTCONbits.TMR0IF=0;
        contador++;
    }
    if(contador>9){
        tratar_relogio(&ca, &re);
        PORTDbits.RD0=PORTDbits.RD0+1;
        contador=0;
    }
}
