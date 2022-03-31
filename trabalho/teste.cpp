#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct grafo{
    int id;
    int tam_bloco;
    int cor;
    int x, y;
    vector <grafo*> vizinhos;
};

int n, // numero de linhas do tabuleiro
    m, // numero de colunas do tabuleiro
    k; // numero de cores presentes no tabuleiro
int** tab = NULL; // tabuleiro de tamanho nxm

int id_grafo = 0;
vector <grafo*> nos_grafo;

//
//==========================================================================
//
// Funções de impressão

void imprime_matriz(int **tab, int n, int m){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
}

void imprime_grafo(vector <grafo*> lista_nos){
    for(unsigned int i = 0; i < lista_nos.size(); i++){
        struct grafo* no = lista_nos[i];
        cout << "Nó id: " << no->id 
             << " cor: "  << no->cor
             << " tam: "  << no->tam_bloco << endl;

        cout << "Vizinhos: " << endl;
        for(unsigned int j = 0; j < no->vizinhos.size(); j++){
            struct grafo* viz = no->vizinhos[j];
            cout << "\tid: " << viz->id
                 << " cor: " << viz->cor
                 << " tam: " << viz->tam_bloco 
                 << " qtde_viz: " << viz->vizinhos.size() << endl;
        }
    }
}

// Acima estão as funções de impressão
//
//==========================================================================
//
// Vai recursivamente marcando todos os vizinhos que tem a mesma cor com o valor de marcacao (que será o id do bloco)
// e retorna o tamanho do bloco
int marca_bloco(int x, int y, int marcacao){
    int valor_original = tab[x][y];
    int tam_bloco = 1;
    tab[x][y] = marcacao;
    
    // verifica acima
    if((x - 1) >= 0){
        if(tab[x - 1][y] == valor_original)
            tam_bloco += marca_bloco(x - 1, y, marcacao);
    }

    //verifica aa direita
    if((y + 1) < m){
        if(tab[x][y + 1] == valor_original)
            tam_bloco += marca_bloco(x, y + 1, marcacao);
    }

    // verifica abaixo
    if((x + 1) < n){
        if(tab[x + 1][y] == valor_original)
            tam_bloco += marca_bloco(x + 1, y, marcacao);
    }

    //verifica aa esquerda
    if((y - 1) >= 0){
        if(tab[x][y - 1] == valor_original)
            tam_bloco += marca_bloco(x, y - 1, marcacao);
    }

    return tam_bloco;
}

//
//==========================================================================
//
// A ideia aqui é marcar com o id negativo os pontos do bloco que já foram visitados
// e aqueles cujo id é diferente inserir numa lista
void identifica_vizinhanca(int x, int y, int marcacao, vector <int>* lista){
    tab[x][y] = -marcacao;
    int dentro;

    // verifica acima
    if((x - 1) >= 0){
        if(tab[x - 1][y] == marcacao)
            identifica_vizinhanca(x - 1, y, marcacao, lista);
        else if (tab[x - 1][y] != -marcacao){
            dentro = 0;
            for(unsigned int i = 0; i < lista->size(); i++)
                if((*lista)[i] == abs(tab[x - 1][y]))
                    dentro = 1;
            if (!dentro)
                lista->push_back(abs(tab[x - 1][y]));
        }
    }

    //verifica aa direita
    if((y + 1) < m){
        if(tab[x][y + 1] == marcacao)
            identifica_vizinhanca(x, y + 1, marcacao, lista);
        else if (tab[x][y + 1] != -marcacao){
            dentro = 0;
            for(unsigned int i = 0; i < lista->size(); i++)
                if((*lista)[i] == abs(tab[x][y + 1]))
                    dentro = 1;
            if (!dentro)
                lista->push_back(abs(tab[x][y + 1]));
        }
    }

    // verifica abaixo
    if((x + 1) < n){
        if(tab[x + 1][y] == marcacao)
            identifica_vizinhanca(x + 1, y, marcacao, lista);
        else if (tab[x + 1][y] != -marcacao){
            dentro = 0;
            for(unsigned int i = 0; i < lista->size(); i++)
                if((*lista)[i] == abs(tab[x + 1][y]))
                    dentro = 1;
            if (!dentro)
                lista->push_back(abs(tab[x + 1][y]));
        }
    }

    //verifica aa esquerda
    if((y - 1) >= 0){
        if(tab[x][y - 1] == marcacao)
            identifica_vizinhanca(x, y - 1, marcacao, lista);
        else if (tab[x][y - 1] != -marcacao){
            dentro = 0;
            for(unsigned int i = 0; i < lista->size(); i++)
                if((*lista)[i] == abs(tab[x][y - 1]))
                    dentro = 1;
            if (!dentro)
                lista->push_back(abs(tab[x][y - 1]));
        }
    }
}

void cria_grafo(){
    int tam_bloco;
    int cor;
    struct grafo* no;

    // Cria todos os nós do grafo
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(tab[i][j] > 0){ // se a cor do nó for negativa, significa que o bloco já foi atribuído a um nó
                cor = tab[i][j];
                id_grafo++;
                tam_bloco = marca_bloco(i,j, -id_grafo);
                no = new struct grafo;
                no->id = id_grafo;
                no->cor = cor;
                no->tam_bloco = tam_bloco;
                no->x = i;
                no->y = j;
                nos_grafo.push_back(no);
            }
        }
    }

    // Atribui os vizinhos dos nós
    for(unsigned int i = 0; i < nos_grafo.size(); i++){

        // encontra o id dos vizinhos
        vector <int> lista_id_vizinhos;
        struct grafo* no = nos_grafo[i];
        identifica_vizinhanca(no->x, no->y, -(no->id), &lista_id_vizinhos);

        // encontra o endereco de cada vizinho e atribui
        for(unsigned int j = 0; j < lista_id_vizinhos.size(); j++){
            int id_viz = lista_id_vizinhos[j];
            int achou = 0;
            struct grafo* vizinho;
            for(unsigned int k = 0; k < nos_grafo.size() && !achou; k++){
                vizinho = nos_grafo[k];
                if(vizinho->id == id_viz)
                    achou = 1;
            }
            if(achou)
                no->vizinhos.push_back(vizinho);
        }
    }
}

int main(){
    // Inicia variáveis
    cin >> n >> m >> k;

    tab = new int*[n];
    for(int i = 0; i < n; i++){
        tab[i] = new int[m];
        for(int j = 0; j < m; j ++)
            cin >> tab[i][j];
    }

    cria_grafo();
    imprime_matriz(tab, n, m);
    imprime_grafo(nos_grafo);

    return 0;
}