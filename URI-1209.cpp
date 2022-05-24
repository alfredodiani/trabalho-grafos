/*
* Problema: https://www.beecrowd.com.br/judge/pt/runs/code/20442518
* Time limit exceededd
* 
* Autor: Alfredo
*/


#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class Grafo{
    public:
    int num_vertices; //numero de vertices
    bool **matAdj; //matriz adjacente

    public:
    Grafo (int v){
        this->num_vertices=v;

        matAdj = new bool* [v]; // Cria um array dinamico de ponteiros 
    
        for (int i=0; i<v; i++) // cria umacoluna pra cada ponteiro 
        { 
            matAdj[i] = new bool[v]; 
        
            // Inicializa todas as posições com falso;
            memset(matAdj[i], false, v*sizeof(bool)); 
        }
    }
    
    void addAresta(int x, int y){ //adiciona nova aresta
        matAdj[x-1][y-1]=true;
        matAdj[y-1][x-1]=true;
    }
    
    void imprime(){
        for(int i =0; i<num_vertices; i++){
            for(int j =0; j<num_vertices; j++){
                cout << matAdj[i][j] << " ";
            }
            cout << endl;
        }
    }

    void limpaGrafo(){
        for(int i =0; i<num_vertices; i++){
            for(int j =0; j<num_vertices; j++){
                matAdj[i][j] = false;
            }
            cout << endl;
        }
    }

};






int main(){
    int n; //numero de pessoas
    int m; //numero de relações
    int k; //numero minimo de amigos
    int origem;
    int destino;
    int count;
    bool flagConvidados;
/*
    n = 3;
    Grafo g(n);
    g.addAresta(1,2);
    g.imprime();
*/    

    cin >> n;
    while (n != EOF){
        cin >> m;
        cin >> k;
        Grafo *g = new Grafo(n);
        flagConvidados=false;

        for (int i=0; i<m; i++){
            cin >> origem;
            cin >> destino;
            g->addAresta(origem,destino);
        }

        for(int i=0; i<n; i++){
            count = 0;
            for (int j=0; j<n; j++){
                if (g->matAdj[i][j]==true){
                    count++;

                }
            }
            if(count >= k){
                cout << i+1;
                flagConvidados=true;
            }
        }
        if (flagConvidados = false){
            cout << 0;
        }
        cout << endl;

        //g->imprime();
        delete g;
        cin >> n;

    }


    return 0;
}