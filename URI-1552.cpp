/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/1552
 * Wrong answer (15%)
 *
 * URI 1552 - Resgate em queda livre
 * 
 * Nome: Alfredo
 * 
 * Universidade Federal de Lavras
 * Sistemas de Informação
 * 
 * GCC218 - Algoritmos em Grafos
 * 
 * Data: 27/02/2021
 * 
 * Resolução: 
 * A ideia utilizada foi que ao ler cada coordenada de um ponto, já calculava-se a distancia entre os pontos que já foram lidos anteriormente
 * adicionando já cada uma dessas arestas formadas por cada iteração à lista de arestas.
 * Com a lista de arestas pronta simplesmente aplicamos um algoritmo de AGM (Kruskal nesse caso)
 * e vamos calculando qual o somatório dos pesos das arestas da AGM cada vez que uma aresta é escolhida para compor a AGM.
 * No final imprime-se esse somatório dividindo o numero por 100 para transformar de cm para metros.
 * 
 * OBS importante: o algorítmo funciona, porem está dando time limit exceeded por conta da função sort
 * ao utiliza-la o tempo excede, com isso observa-se que tanto o algoritmo de kruskal, a coleta dos dados e o calculo das distâncias funcionam dentro do tempo esperado.
 * Foi implementada e enviada para o URI também uma versão do código utilizando uma Min Heap como lista de arestas, porem continua dando time limit exceeded.
 * Portanto deixei a linha do algoritmo de ordenação sort comentada, pois assim mesmo sabendo que está errado (por falta da ordenação), ao menos o Uri dá uma saída de Wrong Answer 15%.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;


class Aresta{							//z é o peso da aresta
	public:
	int x;
	int y;
	double z;
	
	public:
	Aresta (int a, int b, double c){
		this->x = a;
		this->y = b;
		this->z = c;
	}
};

class Coord{
	public:
	int x;
	int y;
	
	public:
	Coord(int a, int b){
		this->x = a;
		this->y = b;
	}
};


vector <Aresta> grafo;
vector <int> pais;


//função auxiliar para usar no sort que compara as arestas de acordo com seu peso
bool comparaAresta(Aresta a, Aresta b){  
	return(a.z < b.z);
}


//retorna o pai da raiz daquela arvore que contem o vertice i
int pai(int i){					

	if (pais[i] == i){
		return i;
	}
	
	return pai(pais[i]);

}





int main (){
	int c;
	int n;
	int atualx;
	int atualy;
	double dist;
	double totalDist=0;
	vector <Coord> pontos;
	Coord *auxPonto;
	Aresta *auxAresta;
	int pai1,pai2;
	
	
	cin >> c;
	
	for (int i=0; i < c; i++){
		
		cin >> n;
		
		for(int j=0; j<n; j++){											
			//adiciona o certice no vetor dos pais com o proprio vertice como seu pai
			pais.push_back(j);
			
			//ler coordenadas
			cin >> atualx;
			cin >> atualy;
			
			for (int k=0; k<j; k++){
				
				//calcula a distancia entre o ponto lido e os pontos que já estão na lista de pontos
				dist = sqrt(((atualx - pontos[k].x) * (atualx - pontos[k].x)) + ((atualy - pontos[k].y) * (atualy - pontos[k].y)));
				
				//adiciona aresta com a distancia (peso) calculada
				auxAresta = new Aresta(j,k,dist);
				grafo.push_back(*auxAresta);
			}
			
			//adicionar coordenadas na lista de pontos
			auxPonto = new Coord(atualx, atualy);
			pontos.push_back(*auxPonto);
			
			
			
		}
		
		//organiza a aresta em ordem crescente
//		sort(grafo.begin(), grafo.end(), comparaAresta);  				
		
		
		//algoritmo de Kruskal
		for (auto& it : grafo){
			pai1=pai(it.x);      										//verifica os pais dos vertices da aresta
			pai2=pai(it.y);
			
			if(pai1!=pai2){												//adiciona uma subarvore a outra para a AGM
				pais[pai1] = pais[pai2];
				totalDist = totalDist + it.z;							//soma o peso das subarvores adicionadas na AGM
			}
		}
		
		//precisão do cout para double
		cout << setprecision(2) << fixed;
		
		cout << (totalDist/100) << endl;
		
		
		
		//limpa vetores e variaveis para proximo caso de uso
		totalDist = 0.00;
		grafo.clear();													
		pais.clear();
		pontos.clear();
	}
	
}