/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/2429
 * Accepted
 *
 * Autor: Alfredo
 *
 * Resolução exercicio avaliativo REO4 de Algoritmos em grafos
 * Rodovias
 * 
 * OBS: como o problema necessita de que o numero de arestas seja igual
 * ao numero de vertices, para a solução funcionar devemos ter somente 
 * uma entrada e uma saída para cada cidade
 * 
 */

#include <iostream>
#include <vector>

using namespace std;


class Cidade{
	public:
	int id;
	int numEntradas;
	int numSaidas;
	bool visitada; 		//true caso a cidade já tenha sido visitada, false caso ainda não tenha sido visitada
	int saida;  		//para qual cidade pode-se ir partindo dessa
	
	public:
	
	Cidade(int id){
		this->id = id;
		this->numEntradas = 0;
		this->numSaidas = 0;
		this->visitada = false;
	}
	
	void addEntrada(){
		this->numEntradas = this->numEntradas + 1;
	}
	
	void addSaida(int s){
		this->numSaidas = this->numSaidas + 1;
		this->saida = s;
	}
	
	void visita(){
		this->visitada = true;
	}
	
};


int main() {
	int n; 								//numero de cidades
	int origem; 						//cidade de origem da estrada
	int destino; 						//cidade de destino da estrada
	int countCidadesVisitadas; 			//contagem de cidades visitadas
	char resultado = 'S';
	vector <Cidade> grafo;
	Cidade *aux;
	

	cin >> n;
	
	for (int i = 0; i<n; i++) {      //inicializa os vetores
		aux = new Cidade(i+1);
		grafo.push_back(*aux);
	}

	for (int i = 0; i<n; i++) {
		cin >> origem;
		cin >> destino;
		grafo[origem-1].addSaida(destino);
		grafo[destino-1].addEntrada();
	}

	for (int i = 0; i<n; i++) {                									//como só temos o numero de arestas igual ao numero de vértices então o numero de entradas e de saídas da cidade precisa ser igual a 1
		if ((grafo[i].numEntradas != 1) || (grafo[i].numSaidas != 1)) {		//caso qualquer cidade tenha numero 0 significa que não é possivel chegar nela, se o numero for maior que 1 então existem mais de 1 caminho 
			resultado = 'N';													//para a mesma cidade, o que significa que alguma cidade deixou de ter um caminho de chegada ou de saída, não fechando assim um cliclo hamiltoniano.
			cout<<resultado<<endl;	
			return 0;
		}
	}

	int i = 0;
	countCidadesVisitadas = 0;

	while (grafo[i].visitada == false) {
		grafo[i].visita();
		countCidadesVisitadas++;
		i = grafo[i].saida-1;       														//aponta para o proximo a visitar
	}
	 
	if (countCidadesVisitadas != n){ 											//se o numero de cidades visitadas não for igual o numero total de cidades muda resposta para N
		resultado = 'N';
	}
	
	cout<<resultado<<endl;
	
	return 0;
}