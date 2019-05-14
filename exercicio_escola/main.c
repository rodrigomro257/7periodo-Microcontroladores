#include <stdio.h>
#include <stdlib.h>
#include "escola.h"

int main(){

    Turma turma;
    printf("------- SISTEMA CONTROLE ALUNOS -------");
    printf("\n Informe o codigo da turma: ");
    scanf("%s", &turma.codigo);
    printf("\n Turma %c cadastrada com sucesso.\n\n", turma.codigo);

    int controle_aluno=0;
    char opcao=-1;
    while(opcao!=0){
        opcao=menu(&turma, controle_aluno);
        if(opcao==1) controle_aluno++;
    }
    printf("\n\n------- SISTEMA FINALIZADO. -------\n\n");

    return 0;
}
