#include "operacoes_problema.h"

#define TAM 3
#define MAX_MOVS 4

void iniciaMatriz(int matriz[TAM][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            matriz[i][j] = (TAM - i)*TAM - j - 1;
        }
    }
}

void imprimeMatriz(int m[TAM][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void movimentosPossiveis(int matriz[TAM][TAM], struct movimento *movimento){
    // Primeiro encontramos o espaço "vazio" e depois atribuimos os movimentos possiveis
    int x = 0;
    int y = 0;
    int encontrou = 0;
    for(int i = 0; (i < TAM) && !encontrou; i++){
        for(int j = 0; (j < TAM) && !encontrou; j++){
            if(matriz[i][j] == 0){
                x = i;
                y = j;
                encontrou = 1;
            }
        }
    }
    movimento -> destino.x = x;
    movimento -> destino.y = y;

    // Zera todos os movimentos anteriores
    for(int i = 0; i < MAX_MOVS; i++){
        movimento -> origens[i].x = -1;
        movimento -> origens[i].y = -1;
    }

    // Verifica movimento esquerda direita
    if((y - 1) >= 0){
        movimento -> origens[0].x = x;
        movimento -> origens[0].y = y - 1;
    }
    // Verifica movimento direita esquerda
    if((y + 1) < TAM){
        movimento -> origens[1].x = x;
        movimento -> origens[1].y = y + 1;
    }
    // Verifica movimento cima baixo
    if((x - 1) >= 0){
        movimento -> origens[2].x = x - 1;
        movimento -> origens[2].y = y;
    }
    // Verifica movimento baixo cima
    if((x + 1) < TAM){
        movimento -> origens[3].x = x + 1;
        movimento -> origens[3].y = y;
    }
    
}

void imprimeMovimentos(struct movimento movimento){
    printf("Movimentos possíveis:\n");
    for(int i = 0; i < MAX_MOVS; i++){
        if((movimento.origens[i].x >= 0) && (movimento.origens[i].y >= 0))
            printf("%d,%d -> %d,%d\n",  movimento.origens[i].x, movimento.origens[i].y,
                                        movimento.destino.x, movimento.destino.y);
    }
}

int realizaMovimento(int matriz[TAM][TAM], struct movimento movimento, int origem){
    int origemX = movimento.origens[origem].x;
    int origemY = movimento.origens[origem].y;
    if((origemX >= 0) && (origemY >= 0)){

        matriz[movimento.destino.x][movimento.destino.y] = matriz[origemX][origemY];
        matriz[origemX][origemY] = 0;

        return 1;
    } else return -1;
}
