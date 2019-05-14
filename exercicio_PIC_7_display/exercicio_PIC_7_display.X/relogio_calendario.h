#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

    int qtdDias_mes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int contador=0;

    typedef struct{
        int dia;
        int mes;
        int ano;
    }calendario;

    typedef struct{
        int minuto;
        int segundo;
        int hora;
    }relogio;
    
    void tratar_relogio(calendario *c, relogio *r);
    void verifica_b(int ano);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

