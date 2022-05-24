/* 
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/1655
 * Accepted
 *
 * URI 1655 - Milhas para Chicago
 * 
 * Nome: Alfredo 
 * 
 * Universidade Federal de Lavras
 * Sistemas de Informação
 * 
 * GCC218 - Algoritmos em Grafos
 * 
 * Data: 14/02/2021
 * 
 * Resolução: 
 * A ideia é utilizar o algoritmo de Floyd-Warshall modificado (para mostrar a maior probabilidade), com modelagem do grafo em matriz de adjacencia.
 * O algoritmo vai calculando os caminhos intermediários e aplicando o valor calculado da melhor probabilidade ao caminho entre os vertices não intermediários.
 * Assim no final teremos qual a melhor probabilidade entre o vertice inicial e o final.
 * OBS: Por conta de o problema não pedir qual o caminho e somente o valor final, na implementação foi desconsiderada a criação da matriz de pais dos vértices.
 * 
 * 
*/

#include <iostream>
#include <iomanip>


using namespace std;

int main(){
	int n,m;
	int a,b,p;
	double probabIntermed = 0;
	double mProbab[100][100]= {{0}};
	double resultado;
	
	cin >> n;
	
	while(n != 0){
		cin >> m;
		
		//leitura das arestas do grafo
		for (int i=0; i < m ; i++){
			cin >> a >> b >>p;
			//transforma a probabilidade pra numero entre 0 e 1 para facilitar nos calculos seguintes
			mProbab[a-1][b-1] = (p/100.000000);
			mProbab[b-1][a-1] = (p/100.000000);
		}
		
		//floyd-warshall
		for (int k=0; k < n ; k++){
			for (int i=0; i < n ; i++){
				for (int j=0; j < n ; j++){
					probabIntermed = mProbab[i][k] * mProbab[k][j];
					if (mProbab[i][j] < probabIntermed){
						mProbab[i][j] = probabIntermed;
					}
				}
			}
		}
		
		//transformando de volta em porcentagem entre 0 e 100
		resultado = mProbab[0][n-1] * 100;
		
		//fixando a precisão do cout em 6 casas decimais
		cout << setprecision(6) << fixed;
		
		//printar 
		cout << resultado << " percent" << endl;
		
		//zera a matriz de adjacencia para um possível novo caso;
		for (int i=0; i<100; i++){
			for (int j=0; j<100; j++){
				mProbab[i][j] = 0.000000;
			}
		}
		
		cin >> n;
	}
	return 0;
}