/*
* Problema: https://www.beecrowd.com.br/judge/pt/runs/code/28111113
* Presentation error (5%)
* 
* Autor: Alfredo
*/

#include <iostream>
#include<bits/stdc++.h>
#include <vector>
using namespace std;


int nivel = 0; //usado para fazer a identação

class Vertice{
    public:
    char cor; //b=branco / c=cinza / p=preto

    public:
    Vertice(){
        this->cor = 'b';
    }
};

class Grafo{
    public:
    int num_v; //numero de vertices
    int num_e; //numero de arestas
    bool **matAdj; //matriz adjacente
    vector<Vertice> listaVertices;

    public:
    Grafo (int v, int e){
        this->num_v=v;
        this->num_e=e;

        matAdj = new bool* [v]; // Create a dynamic array of pointers 
    
        for (int i=0; i<v; i++) // Create a row for every pointer 
        { 
            // Note : Rows may not be contiguous 
            matAdj[i] = new bool[v]; 
        
            // Inicializa todas as posições com falso;
            memset(matAdj[i], false, v*sizeof(bool)); 
        }
        alocaVertices();
    }
    void addAresta(int x, int y){ //adiciona nova aresta
        matAdj[x][y]=true;
    }
    void alocaVertices(){
        for(int i=0; i<num_v ; i++){
            Vertice vert;
            listaVertices.push_back(vert);
        }
    }
};

bool DFSVisit(Grafo *graf, int vert){ //retorna 1 caso exista ao menos 1 aresta neste vertice / retorna 1 caso não ache arestas nesse vertice
    bool ret=false;
    nivel++;
    graf->listaVertices[vert].cor='c'; //muda cor para cinza
    for(int i=0;i<graf->num_v;i++){ //procura qual vertice tem aresta com o vertice atual
        if(graf->matAdj[vert][i]==true){       //verifica se é aresta
            ret=true;
            for (int count=0; count<nivel; count++){ //identação
                cout << "  ";
            }
            cout << vert << "-" << i; 
            if(graf->listaVertices[i].cor=='b'){   //sempre q achar um vertice branco imprime o pathR e visita o proximo vertice
                cout << " pathR (G," << i << ")" << endl;
                DFSVisit(graf,i);
            }
            else{
                cout << endl; //somente termina a linha caso seja uma aresta de retorno
            }
        }
    }
    graf->listaVertices[vert].cor='p'; //pinta o vertice de preto ao terminar a visita
    nivel--;
    return ret;
}

int main() {

    int n; //numero de casos
	int v; //numero de vertices
	int e; //numero de arestas
    int x; //vertice de origem da aresta
    int y; //vertice de destino da aresta
    int r; // retorno da funçao dfsvisit (para tratar o caso similar ao do vertice 9 no caso 1 que imprime uma linha a mais por não ter arestas e ser visitado)

    cin >> n;

    for (int l=0; l<n;l++){   //roda para n casos
        cin >> v;
        cin >> e;
        Grafo g(v,e);
        for (int p=0; p<e ; p++){ //le as arestas e monta o grafo
            cin >> x; 
            cin >> y;
            g.addAresta(x,y);
        }
        cout << "Caso " << l+1 << ":" << endl;
        for (int i=0; i<v; i++){ //varre todos os vertices do grafo e se for branco faz a DFS (por linha)
            if(g.listaVertices[i].cor=='b'){
                r = DFSVisit(&g,i); //visita o vertice
                if(r){ //tratando o caso do vertice que não tem nenhuma aresta (para não imprimir uma linha a mais)
                    cout << endl; //pula uma linha quando muda de componente do grafo
                }
            }
            
        }
    }
    return 0;
}