#include <stdio.h>
#include <stdlib.h>
#include "conta_bancaria.h"

int main(){
    printf("\n\n------- SISTEMA DE CONTA BANCARIA. -------\n\n");
    conta_bancaria conta1;
    inicializar(&conta1, 918556, 300);
    depositar(&conta1, 50);
    sacar(&conta1, 70);
    char opcao;
    while(opcao!=4) opcao=menu(&conta1);
    printf("\n\n------- SISTEMA FINALIZADO. -------\n\n");
    return 0;
}
