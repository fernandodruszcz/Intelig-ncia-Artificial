#include <stdio.h>

#include "operacoes_problema.h"

void main(){
    int matriz[TAM][TAM];
    iniciaMatriz(matriz);

    struct movimento movimento;;
    movimentosPossiveis(matriz, &movimento);

    imprimeMatriz(matriz);
    imprimeMovimentos(movimento);

    for(int origem = 0; origem < MAX_MOVS; origem++){
        printf("Movimento %d:\n", origem);
        realizaMovimento(matriz, movimento, origem);
        imprimeMatriz(matriz);
        movimentosPossiveis(matriz, &movimento);
    }

}