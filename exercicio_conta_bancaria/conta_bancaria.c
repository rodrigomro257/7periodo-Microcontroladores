#include <stdio.h>
#include <stdlib.h>
#include "conta_bancaria.h"

void inicializar(conta_bancaria *conta, int numero, int valor){
    conta->numero=numero;
    conta->valor=valor;
    printf("\nCONTA %d COM O VALOR %d INICIALIZADA COM SUCESSO.\n\n", numero, valor);
    imprimir(conta);
}

void sacar(conta_bancaria *conta, int valor){
    conta->valor-=valor;
    printf("\nSAQUE NO VALOR DE %d EFETUADO COM SUCESSO.\n\n", valor);
    imprimir(conta);
}

void depositar(conta_bancaria *conta, int valor){
    conta->valor+=valor;
    printf("\nDEPOSITO NO VALOR DE %d EFETUADO COM SUCESSO.\n\n", valor);
    imprimir(conta);
}

void imprimir(conta_bancaria *conta){
    printf("\nA conta %d possui o valor %d.\n\n", conta->numero, conta->valor);
}

char menu(conta_bancaria *conta){
    char opcao;
    int valor=0;
    printf("\n1. Sacar.\n2. Depositar.\n3. Imprimir.\n4. Finalizar.\n\nQue operacao deseja efetuar? ");
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
            printf("Que valor deseja sacar? ");
            scanf("%d",&valor);
            sacar(conta, valor);
            break;
        case 2:
            printf("Que valor deseja depositar? ");
            scanf("%d",&valor);
            depositar(conta, valor);
            break;
        case 3:
            imprimir(conta);
            break;
        case 4:
            break;
        default:
            printf("\n\nOpcao invalida.\n\n");
            break;
    }
    return opcao;
}
