#include <stdio.h>
#include <stdlib.h>

//#include "operacoes_problema.h"
#include "operacoes_lista_prioridade.h"

int jogadaRepetida(struct no *no, struct no* pai){
	if(pai == NULL){
		return 0;
	} else {
		int repetiu = 1;
		// verifica se matriz igual
		for(int i = 0; i < TAM; i++){
			for(int j = 0; j < TAM; j++){
				if(no -> matrizEstadoAtual[i][j] != pai -> matrizEstadoAtual[i][j])
					repetiu = 0;
			}
		}
		if(!repetiu)
			return jogadaRepetida(no, pai -> pai);
	}
	return 1;
}

void imprimeCaminho(struct no *no){
	if(no -> pai != NULL){
		imprimeCaminho(no -> pai);
		printf(" |\n");
		printf(" V\n");
	}
	imprimeMatriz(no -> matrizEstadoAtual);
}

struct no * aEstrela(struct no *raiz, struct listaPrioridade **comecoLista){
    if(raiz -> quantidadeMovimentosAteFim == 0){
        printf("\n\naEstrela: ENCONTROU RESULTADO\n\n");
        return raiz;    
    } else {
        // expande o no
        //fprintf(stderr, "			aEstrela: Expandindo nó\n");
		// imprimeCaminho(raiz);
		// fprintf(stderr, "			-----\n\n\n");
        removePrimeiroListaPrioridade(comecoLista);
		//fprintf(stderr, "			aEstrela: criando filhos\n");
        for(int i = 0; i < MAX_MOVS; i++){
            struct no *filho = criaFilho(raiz, i);
            if(filho != NULL){
                raiz -> filhos[raiz -> quantidadeFilhos] = filho;
                raiz -> quantidadeFilhos++;
				//imprimeNo(*filho);
				if(!jogadaRepetida(filho, raiz))
                	insereListaPrioridade(comecoLista, filho);
            }
        }
		//fprintf(stderr, "			aEstrela: filhos criados\n");
        if(*comecoLista != NULL){
			//imprimeListaPrioridade(comecoLista);
			//gets();
			struct listaPrioridade *aux = *comecoLista;
            return aEstrela(aux -> no, comecoLista);
        }
    }
    printf("\naEstrela: Não achou resposta \n");
    return NULL;
}



int main(){
    int matriz[TAM][TAM];
    iniciaMatriz(matriz);

    struct movimento movimento;;
    movimentosPossiveis(matriz, &movimento);

    //imprimeMatriz(matriz);
    //imprimeMovimentos(movimento);

    struct no raiz;
    iniciaRaiz(&raiz, matriz);
    imprimeNo(raiz);

    struct listaPrioridade **comecoLista;
	comecoLista = (struct listaPrioridade **)malloc(sizeof(struct listaPrioridade *));
    inicializaLista(comecoLista, &raiz);
    //imprimeListaPrioridade(comecoLista);
	//removePrimeiroListaPrioridade(comecoLista);
	//imprimeListaPrioridade(comecoLista);

	printf("\n\n\n");

	// for(int i = 0; i < MAX_MOVS; i++){
	// 	struct no *filho = criaFilho(&raiz, i);
	// 	if(filho != NULL){
	// 		raiz.filhos[raiz.quantidadeFilhos] = filho;
	// 		raiz.quantidadeFilhos++;
	// 		fprintf(stderr, "       Criou filho\n");
	// 		imprimeNo(*filho);
	// 		insereListaPrioridade(comecoLista, filho);
	// 	}
	// }

	imprimeListaPrioridade(comecoLista);
    printf("\n\n COMEÇANDO \n\n");
    struct no *estadoFinal = aEstrela(&raiz, comecoLista);
	imprimeCaminho(estadoFinal);
    return 0;
}