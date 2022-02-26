#include "operacoes_no.h"

struct listaPrioridade{
    struct listaPrioridade *proximo;
    struct listaPrioridade *anterior;
    struct no *no;
};

void inicializaLista(struct listaPrioridade **comecoLista, struct no *primeiroNo);

void insereListaPrioridade(struct listaPrioridade **comecoLista, struct no *no);

void removePrimeiroListaPrioridade(struct listaPrioridade **comecoLista);

void imprimeListaPrioridade(struct listaPrioridade **comecoLista);