/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/1152
 * Accepted
 *
 * URI 1152
 * 
 * Nome: Alfredo 
 * 
 * GCC218 - Algoritmos em Grafos
 * Universidade Federal de Lavras - UFLA
 * 
 * Data: 08/jan/2021
 * */

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;




class Aresta{
	public:
	int x;
	int y;
	int z;
	
	public:
	Aresta (int a, int b, int c){
		this->x = a;
		this->y = b;
		this->z = c;
	}
};

vector <Aresta> grafo;
vector <int> pais;


bool comparaAresta(Aresta a, Aresta b){  //função auxiliar para usar no sort
	return(a.z < b.z);
}

int pai(int i){					//retorna o pai da raiz daquela arvore que contem o vertice i

	if (pais[i] == i){
		return i;
	}
	
	return pai(pais[i]);

}



int main(){
	int v;
	int m;
	int x;
	int y;
	int z;
	int totalZ;
	int totalZAGM;
	int pai1;
	int pai2;
	Aresta *aux;
	
	cin >> v;
	cin >> m;
	
	while (v!=0 && m!=0){
		totalZ = 0;
		totalZAGM = 0;
		
		
		for(int i=0; i<v; i++){											//adiciona o certice no vetor dos pais com o proprio vertice como seu pai
			pais.push_back(i);
		}
		
		for(int i=0; i<m; i++){											//adiciona aresta lida e seu peso
			cin >>x;
			cin >>y;
			cin >>z;
			totalZ = totalZ + z;
			aux = new Aresta(x,y,z);
			grafo.push_back(*aux);		
		}
		
		sort(grafo.begin(), grafo.end(), comparaAresta);  				//organiza a aresta em ordem crescente
		
		
		for (auto& it : grafo){
			pai1=pai(it.x);      										//verifica os pais dos vertices da aresta
			pai2=pai(it.y);
			
			if(pai1!=pai2){												//adiciona uma subarvore a outra para a AGM
				pais[pai1] = pais[pai2];
				totalZAGM = totalZAGM + it.z;							//soma o peso das subarvores adicionadas na AGM
			}
		}
		
		
		cout << totalZ-totalZAGM << endl;								//printa resultado
		
		grafo.clear();													//limpa vetores para proximo caso de uso
		pais.clear();
		
		cin >> v;
		cin >> m;
	}
}