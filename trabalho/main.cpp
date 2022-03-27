#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class No_grafo {
    public:
        int id;
        int tam_bloco;
        int cor;
        int x;
        int y;
        vector <No_grafo> vizinhos;
        
        No_grafo(){};
        No_grafo(int _id, int _tam_bloco, int _cor){
            id = _id;
            tam_bloco = _tam_bloco;
            cor = _cor;
        }
};

vector <No_grafo> lista_nos;
int id_grafo = 0;

int n, // numero de linhas do tabuleiro
    m, // numero de colunas do tabuleiro
    k; // numero de cores presentes no tabuleiro
int** tab = NULL; // tabuleiro de tamanho nxm

void inicia_variaveis(){
    cin >> n >> m >> k;

    tab = new int*[n];
    for(int i = 0; i < n; i++){
        tab[i] = new int[m];
        for(int j = 0; j < m; j ++)
            cin >> tab[i][j];
    }
}

void imprime_matriz(int **tab, int n, int m){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cout << tab[i][j] << " ";
		}
		cout << "\n";
	}
}

int marca_bloco(int x, int y, int marcacao){
    //fprintf(stderr, "Olhando %d,%d valor %d\n", x,y, tab[x][y]);
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

void cria_nos_iniciais(){
    int tam_bloco;
    int cor;
    No_grafo* no;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(tab[i][j] > 0){
                cor = tab[i][j];
                id_grafo++;
                tam_bloco = marca_bloco(i,j, -id_grafo);
                no = new No_grafo();
                no->id = id_grafo;
                no->cor = cor;
                no->tam_bloco = tam_bloco;
                no->x = i;
                no->y = j;
                lista_nos.push_back(*no);
            }
        }
    }
}

void identifica_vizinhanca(int x, int y, int marcacao, vector <int>* lista){
    tab[x][y] = -marcacao;
    vector <int>::iterator it;


    // verifica acima
    if((x - 1) >= 0){
        if(tab[x - 1][y] == marcacao)
            identifica_vizinhanca(x - 1, y, marcacao, lista);
        else if (tab[x - 1][y] != -marcacao){
            it = find(lista->begin(), lista->end(), abs(tab[x - 1][y]));
            if (it == lista->end())
                lista->push_back(abs(tab[x - 1][y]));
        }
    }

    //verifica aa direita
    if((y + 1) < m){
        if(tab[x][y + 1] == marcacao)
            identifica_vizinhanca(x, y + 1, marcacao, lista);
        else if (tab[x][y + 1] != -marcacao){
            it = find(lista->begin(), lista->end(), abs(tab[x][y + 1]));
            if (it == lista->end())
                lista->push_back(abs(tab[x][y + 1]));
        }
    }

    // verifica abaixo
    if((x + 1) < n){
        if(tab[x + 1][y] == marcacao)
            identifica_vizinhanca(x + 1, y, marcacao, lista);
        else if (tab[x + 1][y] != -marcacao){
            it = find(lista->begin(), lista->end(), abs(tab[x + 1][y]));
            if (it == lista->end())
                lista->push_back(abs(tab[x + 1][y]));
        }
    }

    //verifica aa esquerda
    if((y - 1) >= 0){
        if(tab[x][y - 1] == marcacao)
            identifica_vizinhanca(x, y - 1, marcacao, lista);
        else if (tab[x][y - 1] != -marcacao){
            it = find(lista->begin(), lista->end(), abs(tab[x][y - 1]));
            if (it == lista->end())
                lista->push_back(abs(tab[x][y - 1]));
        }
    }
}

void atribui_vizinhanca(){
    vector <No_grafo>::iterator no;
    for(no = lista_nos.begin(); no != lista_nos.end(); no++){
        vector <int> lista_id_vizinhos;
        identifica_vizinhanca(no->x, no->y, -(no->id), &lista_id_vizinhos);

        vector <No_grafo>::iterator vizinho;
        for(const int& i : lista_id_vizinhos){
            vizinho = find_if(  lista_nos.begin(), 
                                lista_nos.end(), 
                                [&i](const No_grafo& obj) {return obj.id == i;});
            no->vizinhos.push_back(*vizinho);
        }
    }
}

void copia_grafo(vector <No_grafo> original, vector <No_grafo>* novo){
    No_grafo* no;
    vector <No_grafo>::iterator it;
    for(it = original.begin(); it != original.end(); it++){
        no = new No_grafo(it->id, it->tam_bloco, it->cor);
        novo->push_back(*no);
    }
    
    // Com todos os nos criados eh preciso atribuir os vizinhos dos novos nos
    for(int i = 0; i < original.size(); i++){
        vector <No_grafo>::iterator vizinho;
        for(vizinho = original[i].vizinhos.begin(); vizinho != original[i].vizinhos.end(); vizinho++){
            vector <No_grafo>::iterator v;
            v = find_if(  novo->begin(), 
                          novo->end(), 
                          [&vizinho](const No_grafo& obj) {return obj.id == vizinho->id;});
            (*novo)[i].vizinhos.push_back(*v);
        }
    }
}

int main(){
    inicia_variaveis();
    imprime_matriz(tab, n, m);
    cria_nos_iniciais();
    imprime_matriz(tab, n, m);
    atribui_vizinhanca();
    imprime_matriz(tab, n, m);

    // vector <No_grafo>::iterator no;
    // for(no = lista_nos.begin(); no != lista_nos.end(); no++){
    //     cout << "Vizinhos do nó " << no->id << " " << no->cor << " " << no->tam_bloco << ":\n";
    //     vector <No_grafo>::iterator viz;
    //     for(viz = no->vizinhos.begin(); viz != no->vizinhos.end(); viz++){
    //         cout << viz->id << " " << viz->cor << " " << viz->tam_bloco << "\n";
    //     }
    // }
    

    vector <No_grafo> nova_lista;
    copia_grafo(lista_nos, &nova_lista);

    // for(int i = 0; i < lista_nos.size(); i++){
    //     cout << "Nó " << lista_nos[i].id << " " << nova_lista[i].id << " " << &lista_nos[i] 
    //                                                                 << " " << &nova_lista[i] << "\n";
    //     for(int j = 0; j < lista_nos[i].vizinhos.size(); j++){
    //         cout << lista_nos[i].vizinhos[j].id << " " << nova_lista[i].vizinhos[j].id << "\n";
    //         cout << &lista_nos[i].vizinhos[j] << " " << &nova_lista[i].vizinhos[j] << "\n";
    //     }    
    // }



    return 0;
}