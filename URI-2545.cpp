/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/2545
 * Wrong answer (25%)
 *
 * URI 2545
 * 
 * Autor: Alfredo 
 * 
 * Universidade Federal de Lavras
 * Sistemas de Informação
 * GCC218 - Algoritmos em Grafos
 * 
 * Data: 09/jan/2021
 * 
 * resolução:
 * como o PC possui 4096 nucleos e o numero maximo de arquivos fonte é 1000 então pode-se compilar todos arquivos em 1 ciclo caso não possuam dependencias
 * a ideia do algorítmo é checar a cada iteração todos arquivos e compilar de uma vez todos que já tenham suas dependencias compiladas.
 * calcular quantos ciclos de 1 segundo foram feitos e imprimir no final caso seja possivel compilar o jogo.
 * 
 * */
 
#include <iostream>
#include <vector> 

using namespace std;


class Arquivo{
	public:
	int numDp; 									//numero de dependencias
	vector <int> dependencias;  				//vetor de dependencias
	bool compilado; 							//flag 0=não compilado / 1=compilado
	
	public:
	Arquivo(int ndp){
		this->numDp=ndp;
		this->compilado=false;
	}
	void addDp(int x){
		this->dependencias.push_back(x);
	}
	void compila(){
		this->compilado=true;
	}
};

int main (){
	int n;
	int ndp;
	int dp;
	vector <Arquivo> arquivos;
	Arquivo *aux;
	bool flagComp;
	int tempo;
	int nDpComp;
	
	while (cin >> n){
		tempo = 0;
		for(int i=0;i<n;i++){							//coleta informações do caso de uso
			cin >> ndp;
			aux = new Arquivo(ndp);
			arquivos.push_back(*aux);
			
			for(int j=0;j<ndp;j++){
				cin >> dp;
				arquivos[i].dependencias.push_back(dp);
			}
		}
		flagComp=true;
		while(flagComp){								
			flagComp=false;
			for(auto& it : arquivos){
				if (it.compilado==false){
					nDpComp=0;
					for(auto& iter : it.dependencias){
						if (arquivos[iter-1].compilado){
							nDpComp++;
						}
					}			
					if (nDpComp==it.numDp && it.compilado==false){
						it.compila();
						flagComp=true;
					}
				}
			}
			if(flagComp==true){
				tempo++;
			}
		}
		if (tempo==0){
			cout << -1 << endl;
		}else{
			cout << tempo << endl;
		}
		arquivos.clear();
	}
}
