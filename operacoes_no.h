#include<stdio.h>
#include<stdlib.h>

#include "operacoes_problema.h"

struct no{
    struct no *filhos[MAX_MOVS];
    int quantidadeFilhos;
    struct no *pai;
    int quantidadeMovimentos; // custo // g()
    int quantidadeMovimentosAteFim; // heuristica // h()
    int quantidadeMovimentosEsperada; // f() = g() + h()
    int matrizEstadoAtual[TAM][TAM];
    struct movimento movimentosPossiveis;
};

void copiaMatriz(int original[TAM][TAM], int copia[TAM][TAM]);

void atribuiEsperadoAteFim(struct no *no);

void atribuiCusto(struct no *filho);

void atribuiTotalEsperado(struct no *filho);

void iniciaRaiz(struct no *raiz, int matrizInicial[TAM][TAM]);

void imprimeNo(struct no no);

struct no * criaFilho(struct no *pai, int origemMovimento);