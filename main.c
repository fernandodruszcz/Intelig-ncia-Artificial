#include <stdio.h>
#include <stdlib.h>

//#include "operacoes_problema.h"
#include "operacoes_lista_prioridade.h"
int globalCounter = 0;


// int aEstrela(struct no *raiz, struct listaPrioridade *listaPrioridade){
//     if(raiz -> quantidadeMovimentosAteFim == 0){
//         printf("\n\nENCONTROU FIM\n\n");
//         return 1;    
//     } else {
//         // expande o no
//         printf("        Expandindo nó:\n");
//         imprimeListaPrioridade(listaPrioridade);
//         imprimeNo(*raiz);
//         listaPrioridade = removePrimeiroListaPrioridade(listaPrioridade);
//         fprintf(stderr, "        REMOVEU-SE\n");
//         fprintf(stderr, "           %p\n", listaPrioridade);
//         imprimeListaPrioridade(listaPrioridade);
//         for(int i = 0; i < MAX_MOVS; i++){
//             struct no *filho = criaFilho(raiz, i);
//             if(filho != NULL){
//                 raiz -> filhos[raiz -> quantidadeFilhos] = filho;
//                 raiz -> quantidadeFilhos++;
//                 fprintf(stderr, "       Criou filho\n");
//                 imprimeNo(*filho);
//                 insereListaPrioridade(listaPrioridade, filho);
//             }
//         }
//         return aEstrela(listaPrioridade -> no, listaPrioridade);
//     }
//     printf("\n Não achou resposta \n");
//     return 0;
// }



int main(){
    int matriz[TAM][TAM];
    iniciaMatriz(matriz);

    struct movimento movimento;;
    movimentosPossiveis(matriz, &movimento);

    imprimeMatriz(matriz);
    imprimeMovimentos(movimento);

    struct no raiz;
    iniciaRaiz(&raiz, matriz);
    imprimeNo(raiz);

    struct listaPrioridade **comecoLista;
	comecoLista = (struct listaPrioridade **)malloc(sizeof(struct listaPrioridade *));
    inicializaLista(comecoLista, &raiz);
    imprimeListaPrioridade(comecoLista);
	//removePrimeiroListaPrioridade(comecoLista);
	//imprimeListaPrioridade(comecoLista);

	printf("\n\n\n");

	for(int i = 0; i < MAX_MOVS; i++){
		struct no *filho = criaFilho(&raiz, i);
		if(filho != NULL){
			raiz.filhos[raiz.quantidadeFilhos] = filho;
			raiz.quantidadeFilhos++;
			fprintf(stderr, "       Criou filho\n");
			imprimeNo(*filho);
			insereListaPrioridade(comecoLista, filho);
		}
	}

	imprimeListaPrioridade(comecoLista);
    //printf("\n\n COMEÇANDO \n\n");
    //aEstrela(&raiz, &listaPrioridade);

    return 0;
}