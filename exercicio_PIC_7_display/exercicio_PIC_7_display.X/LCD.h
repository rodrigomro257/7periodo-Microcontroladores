/* 
 * File:   LCD.h
 * Author: Windows
 *
 * Created on 30 de Abril de 2019, 16:33
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <delays.h>
    
void DelayFor18TCY(void){
    Delay10TCYx(120);
}

void DelayPORXLCD(void){
    Delay1KTCYx(180);
    return;
}
 
void DelayXLCD(void){
    Delay1KTCYx(60);
    return;

}

// INICIALIADOR DO DISPLAY LCD.
void init_XLCD(VOID){
    OpenXLCD(FOUR_BIT&LINES_5X7); // CONFIGURA LCD EM 4bit DE DADOS E 5X7 characters. 
    while (BusyXLCD()); // VERIFICA SE O CONTROLADOR DO DISPLAY ESTÁ OCUPADO. 
    WriteCmdXLCD(0x06); // MOVE O CURSOR PARA A ESQUERA. 
    WriteCmdXLCD(0x0C); // LIGA O DISPLAY. 
}



#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

