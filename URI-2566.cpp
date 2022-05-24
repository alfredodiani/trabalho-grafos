/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/2566
 * Wrong answer (15%)
 *
 * URI 2566
 * 
 * Nome: Alfredo
 * 
 * Universidade Federal de Lavras
 * Sistemas de Informação
 * 
 * GCC218 - Algoritmos em Grafos
 * 
 * Data: 30/jan/2021
 * 
 * resolução:
 * a ideia utilizada no algorítmo é de separar as arestas de cada meio de transporte e criar dois grafos separados, um para cada meio,
 * rodar o algorítmo de Bellman-Ford em cada um desses grafos
 * e finalmente comparar o custo obtido em cada grafo no vertice de numero 'n' e imprimir qual for o menor.
 * 
 * neste caso do exercicio
 * a função bellmanford não necessita de passar qual o source 's' pois sabemos que é sempre o primeiro elemento da listaVertices
 * tambem não necessita de verificação de ciclos negativos, pois não existe passagem com custo negativo
 * obs: as funções relaxar e inicializar já estão imbutidas no algorítmo.
 * 
*/


#include <iostream>
#include <vector>

using namespace std;



class Aresta{
	public:
	int origem, destino, t, r;
	
	public:
	Aresta(int a,int b,int t,int r){
		this->origem = a;
		this->destino = b;
		this->t = t;
		this->r = r;
	}
};

class Vertice{
	public:
	int id;
	vector<Aresta> listaArestas;
	Vertice *pai;
	int d;
	
	public:
	Vertice (int id){
		this->id = id;
		this->pai = NULL;
		this->d = 99999999;
	}
	
	void addAresta (int a,int b,int t,int r){
		Aresta *aux;
		aux = new Aresta(a,b,t,r);
		this->listaArestas.push_back(*aux);
	}
	
};


class Grafo{
	public:
	int n;
	vector<Vertice> listaVertices;
	
	public:
	Grafo (int n){
		this->n = n;
	}
	
	void addVertice (int id){
		Vertice *aux;
		aux = new Vertice(id);
		this->listaVertices.push_back(*aux);
	}
	
};




void bellmanford(Grafo *g){				
	int a,b;	
	g->listaVertices[0].d = 0;
	for (int i=0;i < g->n;i++){
		for(auto& it : g->listaVertices[i].listaArestas){
			a = it.origem -1;
			b = it.destino -1;
			if ((g->listaVertices[b].d) > ((g->listaVertices[a].d) + (it.r))){
				g->listaVertices[b].d = (g->listaVertices[a].d) + (it.r);
				g->listaVertices[b].pai = &g->listaVertices[a];
			}
		}
	}
}



int main (){
	
	int n,m;
	int a,b,t,r;
	
	Grafo *gAviao;
	Grafo *gOnibus;
	
	
	while(cin >> n >> m){
		
		gAviao = new Grafo(n);
		gOnibus = new Grafo(n);
		
		//adiciona n vertices aos 2 grafos
		for(int i=0;i<n;i++){
			gAviao->addVertice(i);
			gOnibus->addVertice(i);
		}
		
		//adiciona a aresta no grafo correspondente ao meio de transporte
		for(int i=0; i<m;i++){
			cin >> a >> b >> t >> r;
			
			if(t==0){
				gOnibus->listaVertices[a-1].addAresta(a,b,t,r);
			}else{
				gAviao->listaVertices[a-1].addAresta(a,b,t,r);
			}
			
		}
		
		//roda Bellman-Ford para os dois grafos
		bellmanford(gOnibus);
		bellmanford(gAviao);
		
		// verifica qual o resultado menor e imprime-o
		if (gOnibus->listaVertices[n-1].d > gAviao->listaVertices[n-1].d ){
			cout << gAviao->listaVertices[n-1].d << endl;
		}else{
			cout << gOnibus->listaVertices[n-1].d << endl;
		}
		
		delete gAviao;
		delete gOnibus;
	}
	
	
}