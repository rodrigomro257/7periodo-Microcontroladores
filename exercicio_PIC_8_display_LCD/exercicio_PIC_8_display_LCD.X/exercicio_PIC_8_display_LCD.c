/*
 * File:   exercicio_PIC_8_display_LCD.c
 * Author: Windows
 *
 * Created on 25 de Abril de 2019, 12:17
 */

#include <xc.h>
#include <plib/usart.h>
#include <p18f4550.h>
#include <xlcd.h>
#include <delays.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "relogio.h"
#include "display_LCD.h"
#include "variaveis_globais.h"

#define POLY 0x8408 // O QUE ISSO FAZ???
#define _XTAL_FREQ 20000000 // DEFINE FREQUENCIA. 

#pragma config PBADEN = OFF // O QUE ISSO FAZ???
#pragma config WDT = OFF // DESATIVA WATCH DOG. 

void main(void){
    
    Relogio.segundo=0;
    Relogio.minuto=0;
    Relogio.hora=0;
    
    Despertador.segundo=5;
    Despertador.minuto=0;
    Despertador.hora=0;
    
    Calendario.dia=1;
    Calendario.mes=1;
    Calendario.ano=19;
    
    T0CONbits.TMR0ON=1; // HABILITA O TIMER 0;
    
    INTCONbits.TMR0IE=1; // HABILITA A FLAG DE INTERRUPÇÃO.
    INTCONbits.TMR0IF=0; // LIMPA A FLAG.
    
    // UTILIZAR CLOCK INTERNO.
    T0CONbits.T08BIT=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    T0CONbits.T0CS=0; 
    
    TMR0=2535; // DE ONDE INICIA O CONTADOR. 
    
    T0CONbits.TMR0ON=1;

    // HABILITA PRA USAR INTERRUPÇÃO HIGH OU LOW. 
    INTCONbits.GIEH=1; 
    INTCONbits.GIEL=1;
   
    init_XLCD(); // FUNÇÃO DE INICIALIZAÇÃO DO DISPLAY.
    
    // -------------------------------------------------------------------------
    
    // LEDS DE TESTE. 
    TRISAbits.TRISA0=0; // PISCA QUANDO PASSA 1 SEGUNDO.
    TRISAbits.TRISA1=0; // ASCENDE QUANDO DESPERTA.
    
    // LCD.
    TRISB=0x00; // PARA LIGAR O LCD.
    
    // BOTÕES. 
    TRISDbits.TRISD0=1; // BOTÃO PARA CONTROLAR EXIBIÇÃO RELÓGIO/DESPERTADOR.
    TRISDbits.TRISD1=1; // BOTÃO PARA INCREMENTAR MANUALMENTE.
    TRISDbits.TRISD2=1; // BOTÃO PARA DECREMENTAR MANUALMENTE.
    TRISDbits.TRISD3=1; // BOTÃO PARA MOVER O CURSOR. 
    
    while(1){    
        
        // MANTER O CURSOR DESLIGADO AO EXIBIR ALGO NA TELA. 
 //       WriteCmdXLCD(0x0C); // DESLIGA O CURSOR. 
 //       exibir_lcd(&Relogio, &Despertador, &Calendario); // MANTÉM O LDC FUNCIONANDO. 
 //       WriteCmdXLCD(0x0F); // LIGA O CURSOR. 
        
        checa_botao(&Relogio, &Despertador, &Calendario); // LISTENER DO BOTÃO.
 //       pisca_cursor(); // PISCA O CURSOR NO LOCAL DA EDIÇÃO.
        
        // FLAG ATIVADA PELA interrupt CONTA 1 SEGUNDO.
        if(flag_time==1){
            tratar_relogio(&Relogio, &Calendario); // TRATA O RELÓGIO.
            
            // MANTER O CURSOR DESLIGADO AO EXIBIR ALGO NA TELA. 
            WriteCmdXLCD(0x0C); // DESLIGA O CURSOR. 
            exibir_lcd(&Relogio, &Despertador, &Calendario); // MANTÉM O LDC FUNCIONANDO. 
            WriteCmdXLCD(0x0F); // LIGA O CURSOR. 
            
            pisca_cursor(); // PISCA O CURSOR NO LOCAL DA EDIÇÃO.
            
            // PISCA UM LED PARA MOSTRAR A CONTAGEM DE SEGUNDOS. 
            PORTAbits.RA0=1;
            __delay_ms(70);
            PORTAbits.RA0=0;    
            if(despertar==true) controle_tempo_despertar++;          
        }
        
        // ATIVA O DESPERTADOR.
        if(Relogio.segundo==Despertador.segundo
        && Relogio.minuto==Despertador.minuto
        && Relogio.hora==Despertador.hora){           
            despertar=true;
        }
        if(despertar==true && controle_tempo_despertar<10){ // TEMPO DE DURAÇÃO DO DESPERTADOR.
            PORTAbits.RA1=1;            
        }
        if(controle_tempo_despertar==10){
            controle_tempo_despertar=0;
            despertar=false;
        }
        
    }
    return;
}

void __interrupt() pic_isr(void){
    // TIMER0 INTERRUPT?
    if(TMR0IF){  
        TMR0=2535;
        INTCONbits.TMR0IF=0;
        contador++;
        flag_time=0;
    }
    //if(contador>9){
    if(contador>0){ // PARA FAZER O TEMPO PASSAR MAIS RÁPIDO.
        flag_time=1; // LEVANTA UMA FLAG PARA A MAIN EXIBIR O VALOR. 
        contador=0;
    }
}
