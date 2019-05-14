#ifndef DISPLAY_H
#define	DISPLAY_H

#include <xc.h>
#include "relogio_calendario.h"

#define _XTAL_FREQ 20000000

char display[]={
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
};

void controlador_variavel_display(relogio *re, calendario *ca);
void checa_botao_pressionado(relogio *re, calendario *ca);

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */
