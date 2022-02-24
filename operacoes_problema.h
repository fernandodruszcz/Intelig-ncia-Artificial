#include <stdio.h>

#define TAM 3
#define MAX_MOVS 4

struct posicao {
    int x;
    int y;
};

struct movimento {
    struct posicao origens[4];
    struct posicao destino;
};

void iniciaMatriz(int matriz[TAM][TAM]);

void imprimeMatriz(int m[TAM][TAM]);

void movimentosPossiveis(int matriz[TAM][TAM], struct movimento *movimento);

void imprimeMovimentos(struct movimento movimento);

int realizaMovimento(int matriz[TAM][TAM], struct movimento movimento, int origem);
