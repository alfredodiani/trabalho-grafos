/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/1314
 * Wrong answer (25%)
 *
 * URI 1314
 * 
 * Nome: Alfredo 
 * 
 * Universidade Federal de Lavras
 * Sistemas de Informação
 * 
 * GCC218 - Algoritmos em Grafos
 * 
 * Data: 10/jan/2021
 * 
 * resolução:
 * a ideia utilizada no algoritmo é de utilizando uma lista de adjacencia
 * obter a lista de todas arestas que são ponte no grafo
 * depois navegar pelo grafo de Lista de adjacencia de pontes e verificar
 * pode sair da origem e chegar ao destino, caso sim print Y caso contrario print N
 * 
*/

#include <iostream>
#include <vector>
#define MAX 10001

using namespace std;

class Aresta{
	public:
	int x;
	int y;
	
	public:
	Aresta(int u,int v){
		this->x=u;
		this->y=v;
	}
	
};

vector<int> listaAdj[MAX];
vector<int> listaAdjPontes[MAX];
vector<Aresta> listaConsultas;
vector<Aresta> listaPontes;
int n,m,q;
int d[MAX];
int pai[MAX];
int low[MAX];
int tempo=0;
char cor[MAX];

void inicializaArray(int *w,int n){
	for (int i=0;i<n;i++){
		w[i]=-1;
	}
}

void inicializaArrayCor(char *w,int n){
	for (int i=0;i<n;i++){
		w[i]='B';
	}
}




void pontes(int u){
	d[u] = tempo;
	tempo = tempo + 1;
	int minimo = d[u];
	
	for(auto& it : listaAdj[u]){
			if (d[it] == -1){
				pai[it] = u;
				pontes(it);
				
				if (low[it]< minimo){
					minimo = low[it];
				}
			}else if (d[it] < minimo && it != pai[u]){
				minimo = d[it];
			}
	}
	low[u]=minimo;
}

void obtemPontes(){
	Aresta *aux;
	for (int i=0;i<n;i++){
		if(pai[i]==-1){
			pai[i] = i;
			pontes(i);
		}
	}
	listaPontes.clear();
	for (int i=0;i<n;i++){
		if (low[i]==d[i] && pai[i]!=i){
			aux = new Aresta(pai[i],i);
			listaPontes.push_back(*aux);
		}
	}
}





bool DfsVisit(int s, int t){
	bool resp;
	cor[s] = 'C';
	
	for(auto& it : listaAdjPontes[s]){
		if(cor[it]=='B'){
			if(s==t){
				return true;
			}
			cor[it] = 'C';
			resp = DfsVisit(it,t);
			if(resp==true){
				return true;
			}
		}
	}
	cor[s] = 'P';
	//remover arestas
	return false;
}






int main(){

	int x,y;
	bool resposta;
	
	Aresta *aux;
	
	cin >> n >> m >> q;
	
	while (n!=0 && m!=0 && q!=0){
		for(int i=0;i<m;i++){
			cin >> x >> y;
			aux = new Aresta(x,y);
			listaAdj[x-1].push_back(y);
			listaAdj[y-1].push_back(x);
		}
		
		for(int i=0;i<q;i++){
			cin >> x >> y;
			aux = new Aresta(x,y);
			listaConsultas.push_back(*aux);
		}
		inicializaArray(pai,n);
		inicializaArray(d,n);
		inicializaArray(low,n);
		inicializaArrayCor(cor,n);
		tempo = 0;
		
		obtemPontes();
		
		for (auto& it : listaPontes){
			listaAdjPontes[it.x].push_back(it.y);
			listaAdjPontes[it.y].push_back(it.x);
		}
		
		for(auto& it :listaConsultas){
			resposta=DfsVisit((it.x)-1, (it.y)-1);
			if (resposta){
				cout << "Y" << endl;
			}else{
				cout << "N" << endl;
			}
		}
		cout << "-" << endl;
		
		
		
		//limpa vetores e variaveis para prox caso de teste
		listaPontes.clear();
		listaConsultas.clear();
		for (int i=0;i<n;i++){
			listaAdj[i].clear();
		}
		for (int i=0;i<n;i++){
			listaAdjPontes[i].clear();
		}
		cin >> n >> m >> q;
	}
	
}
