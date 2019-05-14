/* 
 * File:   exercicio_PIC_4_timer.c
 * Author: Windows
 *
 * Created on 14 de Março de 2019, 15:12
 */

#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 20000000

#pragma CONFIG_WDT =OFF // DESABILITA WHATCH DOG.

void main(void){
    
    TRISDbits.TRISD0=0; // LED.
    
    T0CONbits.TMR0ON=1;
    
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    
    T0CONbits.T08BIT=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    T0CONbits.T0CS=0; // UTILIZAR CLOCK INTERNO.
    
    TMR0=2535; // ISSO É O CONTADOR DE ONDE INICIA. 
    
    T0CONbits.TMR0ON=1;
    
    int contador=0;
    
    while(1){ 
        if(INTCONbits.TMR0IF==1){
            //PORTBbits.RB0=PORTBbits.RB0+1;
            TMR0=2535;
            INTCONbits.TMR0IF=0;
            contador++;
        }  
        
        if(contador>9){ 
            PORTDbits.RD0=PORTDbits.RD0+1;
            contador=0;
        }
    }
    return;
}
