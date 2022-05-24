/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/1908
 * Wrong answer (20%)
 *
 * URI 1908
 * 
 * Nome: Alfredo 
 * 
 * Universidade Federal de Lavras
 * Sistemas de Informação
 * GCC218 - Algoritmos em Grafos
 * 
 * Data: 10/jan/2021
 * 
 * resolução:
 * A ideia utilizada na resolucao é descobrir quais linhas tem ligacoes entre si, 
 * montar um grafo das linhas interligadas e aplicar um algoítmo de BFS nesse grafo de linhas.
 * Neste caso, cada nó é uma linha e cada aresta é a interseccao dessas linhas.
 * 
 * */


#include <iostream>
#include <vector>
#include <queue>


using namespace std;




class Linha {
	public:
	int id;
	int numEstacoes;
	vector <int> estacoes;
	char cor;										//b = branco / c = cinza / p = preto
	vector <int> ligaLinhas;
	
	public:
	Linha(int n){
		this->numEstacoes = n;
		this->cor = 'b';
	}
	void addEstacao(int n){
		this->estacoes.push_back(n);
	}
	void addLinha(int n){
		this->ligaLinhas.push_back(n);
	}
};

int n, k, numEst, c;
vector<Linha> linhas;
Linha *aux;


int bfs(int origem,int destino){
	queue<int> fila;
	int atual;
	int custo=1;
	
	atual=origem;
	fila.push(origem);
	while(!fila.empty()){
		linhas[atual].cor='c';
		for(auto& it : linhas[atual].ligaLinhas){
			if(linhas[it].cor=='b'){
				fila.push(it);
			}
		}
		linhas[atual].cor='p';
		fila.pop();
		atual=fila.front();
		custo++;
		if(atual==destino){
			return custo;
		}
	}
	return custo;
}

int main (){
	bool flag=false;
	int resp=999999;
	vector<int> origem,destino;
	int a;
	
	//captura os dados
	cin >> n;
	cin >> k;
	for (int i=0;i<k;i++){
		cin >> numEst;
		aux = new Linha(numEst);
		linhas.push_back(*aux);
		for(int j=0;j<numEst;j++){
			cin >> c;
			linhas[i].addEstacao(c);
			if(c==1){
				origem.push_back(i);
			}
			if(c==n){
				destino.push_back(i);
			}
		}
		
	}
	
	//procura e cria todas ligações entre as linhas

	int tam = linhas.size();
	for (int i=0;i<tam;i++){
		for (auto& it : linhas[i].estacoes){
			for(int j=(i+1); j<k; j++){
				for (auto& iter : linhas[j].estacoes){
					if(iter==it){
						flag=false;
						for (auto& iterat : linhas[i].ligaLinhas){
							if(iterat==j){
								flag=true;
							}
						}
						if (flag==false){
							linhas[i].addLinha(j);
							linhas[j].addLinha(i);
						}
					}
				}
			}

		}
	}
	
	//bfs entre todas linhas que contem o campus 1 e todas linhas que contem campus n
	for(auto& it : origem){
		for(auto& iter : destino){
			a = bfs(it,iter);
			if(a<resp){
				resp = a;
			}
			
		}
	}
	
	cout << resp;
	
	
	
	
	
	
	
	
	return 0;
}
