#include "operacoes_lista_prioridade.h"

void inicializaLista(struct listaPrioridade **comecoLista, struct no *primeiroNo){
    //fprintf(stderr, "	inicializaLista: Começando\n");
    struct listaPrioridade *primeiroItem = (struct listaPrioridade *)malloc(sizeof(struct listaPrioridade));
	//fprintf(stderr, "	inicializaLista: primeiroItem criado\n");
    primeiroItem -> proximo = NULL;
    primeiroItem -> anterior = NULL;
    primeiroItem -> no = primeiroNo;
	//fprintf(stderr, "	inicializaLista: primeiroItem atribuido\n");
    *comecoLista = primeiroItem;
    //fprintf(stderr, "	inicializaLista: Finalizando\n");
}


void insereListaPrioridade(struct listaPrioridade **comecoLista, struct no *no){
	//fprintf(stderr, "	insereListaPrioridade: Começando\n");
	if(*comecoLista == NULL){
		//fprintf(stderr, "	insereListaPrioridade: Lista vazia\n");
		inicializaLista(comecoLista, no);
	} else {
		// encontra posicao que deve ser inserido
		struct listaPrioridade *aux = *comecoLista;
		struct listaPrioridade *novoItem = (struct listaPrioridade *)malloc(sizeof(struct listaPrioridade));
		novoItem -> no = no;
		novoItem -> anterior = NULL;
		novoItem -> proximo = NULL;
		//fprintf(stderr, "	insereListaPrioridade: Criou item\n");

		// se o primeiro item for maior, insere como primeiro
		if(aux -> no -> quantidadeMovimentosEsperada > novoItem -> no -> quantidadeMovimentosEsperada){
			//fprintf(stderr, "	insereListaPrioridade: Inserindo item como primeiro\n");
			aux -> anterior = novoItem;
			novoItem -> proximo = aux;
			*comecoLista = novoItem;
		} else {
			while((aux -> proximo != NULL) && 
				(aux -> no -> quantidadeMovimentosEsperada < novoItem -> no -> quantidadeMovimentosEsperada)){
				aux = aux -> proximo;
			} // fim while
			// se o proximo de aux for nulo,
			// significa que encontrou uma posicao entre dois itens existentes
			if(aux -> proximo != NULL){
				//fprintf(stderr, "	insereListaPrioridade: Inserindo item no meio\n");
				if(aux -> anterior != NULL){
					aux -> anterior -> proximo = novoItem;
				} else {
					*comecoLista = novoItem;
				}
				novoItem -> anterior = aux -> anterior;
				novoItem -> proximo = aux;
			} else {
				// se o proximo eh nulo,
				// entao tem que verificar se o item deve ser o ultimo ou o penultimo
				if(aux -> no -> quantidadeMovimentosEsperada < novoItem -> no -> quantidadeMovimentosEsperada){
					//fprintf(stderr, "	insereListaPrioridade: Inserindo item no fim\n");
					aux -> proximo = novoItem;
					novoItem -> anterior = aux;				
				} else {
					//fprintf(stderr, "	insereListaPrioridade: Inserindo item como penultimo\n");
					if(aux -> anterior != NULL){
						aux -> anterior -> proximo = novoItem;
					} else {
						// se o anterior for nulo, esta inseirndo no comeco da lista
						*comecoLista = novoItem;
					}
					novoItem -> anterior = aux -> anterior;
					novoItem -> proximo = aux;
				}
			}
		} // fim segundo else
	} // fim primeiro else
	//fprintf(stderr, "	insereListaPrioridade: Finalizando\n");
} // fim insereListaPrioridade

void removePrimeiroListaPrioridade(struct listaPrioridade **comecoLista){
	//fprintf(stderr, "	removePrimeiroListaPrioridade: Começando\n");
	struct listaPrioridade *aux = *comecoLista;
	// se so tiver um item na lista
	if(aux -> proximo == NULL){
		//fprintf(stderr, "	removePrimeiroListaPrioridade: removendo lista de único item\n");
		*comecoLista = NULL;
		free(aux);
	} else {
		//fprintf(stderr, "	removePrimeiroListaPrioridade: removendo primeiro item\n");
		aux -> proximo -> anterior = NULL;
		*comecoLista = aux -> proximo;
		free(aux);
	}
    //fprintf(stderr, "	removePrimeiroListaPrioridade: Finalizando\n");
}

void imprimeListaPrioridade(struct listaPrioridade **comecoLista){
    fprintf(stderr, "	imprimeListaPrioridade: Começando\n");
    if(*comecoLista != NULL){
        struct listaPrioridade *aux = *comecoLista;
        while(aux -> proximo != NULL){
			fprintf(stderr, "	imprimeListaPrioridade: Item:\n");
            imprimeNo(*(aux -> no));
            aux = aux -> proximo;
        }
		fprintf(stderr, "	imprimeListaPrioridade: Item final:\n");
        imprimeNo(*(aux -> no));
    }
    fprintf(stderr, "	imprimeListaPrioridade: Finalizando\n");
}