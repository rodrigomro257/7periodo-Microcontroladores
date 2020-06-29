/* 
 * File:   display_LCD.h
 * Author: Windows
 *
 * Created on 25 de Abril de 2019, 14:59
 */

#ifndef DISPLAY_LCD_H
#define	DISPLAY_LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <delays.h>
    
#include "relogio.h"
#include "variaveis_globais.h"
    
#define FREQ 20000000 // DEFINE FREQUENCIA.
#define _XTAL_FREQ 20000000 // DEFINE FREQUENCIA. 
    
void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);

// INICIALIADOR DO DISPLAY LCD.
void init_XLCD(VOID);

void exibir_lcd(relogio *Relogio, relogio *Despertador, calendario *Calendario);
void checa_botao(relogio *Relogio, relogio *despertador, calendario *Calendario);
void pisca_cursor();
void trocar_tela();
void posiciona_cursor();
//void gambiarra_pro_serial();

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_LCD_H */

