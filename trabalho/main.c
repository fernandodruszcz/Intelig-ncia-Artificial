#include <stdio.h>
#include <stdlib.h>

int n, // numero de linhas do tabuleiro
    m, // numero de colunas do tabuleiro
    k; // numero de cores presentes no tabuleiro
int **tab; // tabuleiro de tamanho nxm

void imprime_matriz(int **tab, int n, int m){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("%d ", tab[i][j]);
		}
		printf("\n");
	}
}

int idGrafo = 0;

struct noGrafo{
    int id;
    int valor_bloco;
    int tam_bloco;
    int qtde_vizinhos;
    struct noGrafo *vizinhos;
};


int bloco(int x, int y, int marcacao){
    //fprintf(stderr, "Olhando %d,%d valor %d\n", x,y, tab[x][y]);
    int valor_original = tab[x][y];
    int tam_bloco = 1;
    tab[x][y] = marcacao;
    
    // verifica acima
    if((x - 1) >= 0){
        if(tab[x - 1][y] == valor_original)
            tam_bloco += bloco(x - 1, y, marcacao);
    }

    //verifica aa direita
    if((y + 1) < m){
        if(tab[x][y + 1] == valor_original)
            tam_bloco += bloco(x, y + 1, marcacao);
    }

    // verifica abaixo
    if((x + 1) < n){
        if(tab[x + 1][y] == valor_original)
            tam_bloco += bloco(x + 1, y, marcacao);
    }

    //verifica aa esquerda
    if((y - 1) >= 0){
        if(tab[x][y - 1] == valor_original)
            tam_bloco += bloco(x, y - 1, marcacao);
    }

    return tam_bloco;
}

int encontra_posicao_novo_bloco(int *x, int *y){
    int x_original = *x;
    int y_original = *y;
     // verifica acima
    if((x_original - 1) >= 0){
        if(tab[x_original - 1][y_original] == -(idGrafo - 1)){
            *x = x_original - 1;
            encontra_posicao_novo_bloco(x, y);
        }
        else if(tab[x_original - 1][y_original] > 0){
            *x = x_original - 1;
            *y = y_original;
            return 1;
        }
    }

    //verifica aa direita
    if((y_original + 1) < m){
        if(tab[x_original][y_original + 1] == -(idGrafo - 1)){
            *y = *y + 1;
            encontra_posicao_novo_bloco(x, y + 1);
        }
        else if(tab[x_original][y_original + 1] > 0){
            *x = x_original;
            *y = y_original + 1;
            return 1;
        }
    }

    // verifica abaixo
    if((x_original + 1) < n){
        if(tab[x_original + 1][y_original] == -(idGrafo - 1)){
            *x = *x + 1;
            encontra_posicao_novo_bloco(x + 1, y);
        }
        else if(tab[x_original + 1][y_original] > 0){
            *x = x_original + 1;
            *y = y_original;
            return 1;
        }
    }

    //verifica aa esquerda
    if((y_original - 1) >= 0){
        if(tab[x_original][y_original - 1] == -(idGrafo - 1)){
            *y = *y - 1;
            encontra_posicao_novo_bloco(x, y - 1);
        }
        else if(tab[x_original][y_original - 1] > 0){
            *x = x_original;
            *y = y_original - 1;
            return 1;
        }
    }
    
    return 0;
}

struct noGrafo *criaGrafo(int x, int y){
    struct noGrafo *raiz = malloc(sizeof(struct noGrafo));
    raiz->id = ++idGrafo;
    raiz->valor_bloco = tab[x][y];
    raiz->tam_bloco = bloco(x, y,-raiz->id);
    raiz->qtde_vizinhos = 0;

    int novo_x = x;
    int novo_y = y;
    encontra_posicao_novo_bloco(&novo_x, &novo_y);
    printf("Novo bloco em %d,%d\n", novo_x, novo_y);
    
    
    imprime_matriz(tab, n, m);

    return raiz;
}

//
//
//


int main(){

    scanf("%d %d %d", &n, &m, &k);

    //
    // aloca matriz tab nxm
    // e atribui os valores
    //
    tab = (int **)malloc(sizeof(int *)*n);
    for (int i = 0; i < n; i++){
        tab[i] = (int *)malloc(sizeof(int)*m);
        for (int j = 0; j < m; j++){
            scanf("%d", &tab[i][j]);
        }
    }

    imprime_matriz(tab, n, m);

    struct noGrafo *raiz = criaGrafo(0,0);
    printf("Raiz: id = %d\tvalor = %d\ttamanho = %d\tqtde vizinhos = %d\n",
                raiz->id, raiz->valor_bloco, raiz-> tam_bloco, raiz->qtde_vizinhos);

    


    return 0;
}