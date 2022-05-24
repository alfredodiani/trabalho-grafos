/*
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/1773
 * Memory limit exceeded
 *
 * Autor: Alfredo
 *
 *
 */
 
 
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> bolso; //chaves que estão no bolso

class Sala{
    public:
    int id;
    char cor; // b=branco, c=cinza, p=preto
    vector<int> chaves; //array de chaves que estão nesta sala
    vector<Sala> corredores; //array de arestas

    Sala (int n){
        this->id = n;
        this->cor = 'b';
    }
};

class Castelo{
    public:
    int num_salas;
    int num_corredores;
    vector<Sala> salas;

    Castelo(int n,int m){
        this->num_salas = n;
        this->num_corredores = m;
    }

    void addSala(int id){
        Sala *s = new Sala(id);
        salas.push_back(*s);
    }
    bool isEmpty(){
        if (salas.size()!=0){
            return false;
        }else{
            return true;
        }
    }

};

int percorre (Castelo *c, Sala *s){
    bool temChave = false;
    int contador = 0;
    int atual;
    if(!c->isEmpty()){
        queue<int> q;
        queue<int> q2;
        contador++;
        q.push(s->id);
        s->cor='c';
        while(!q.empty()){
            atual = ((q.front())-1);
            for (auto& it : bolso){  //verifica se tem a chave para a sala a ser visitada
                if ((it==(atual+1)) or (atual==0)){
                    temChave=true;
                }else{
                    temChave=false;
                }
            }
            if(temChave){
                contador++;
                c->salas[atual].cor='c';
                for(auto& it : c->salas[atual].chaves){ //pega as chaves que estão na sala que está sendo visitada
                    bolso.push_back(it);
                }

                for(auto& it : c->salas[atual].corredores){
                    q.push(it.id);
                }
                q.pop();
                c->salas[atual].cor='p';
            }else{
                q2.push(q.front());
                q.pop();
            }
        }
        percorre(c,&(c->salas[q2.front()]));

    }
    return contador;
}


int main(){
    int n;
    int m;
    int origem;
    int destino;
    int ler;
    Castelo *c;

    while(cin >> n){
        cin >>m;
        c = new Castelo(n,m);

        for(int i=1; i<=n; i++){
            c->addSala(i);
        }
        for(int i=0; i<m; i++){
            cin >> origem;
            cin >> destino;
            c->salas[origem-1].corredores.push_back(c->salas[destino-1]);
            c->salas[destino-1].corredores.push_back(c->salas[origem-1]);
        }
        
        for (int i=2; i<=n; i++){
            cin >> ler;
            c->salas[ler-1].chaves.push_back(i);
        }
        
        Sala *s = &(c->salas[0]);
        ler = percorre(c,s);
        if (ler==n){
            cout << "sim" << endl;
        }else{
            cout << "nao" << endl;
        }
        
        delete c;
        bolso.clear();
     
    }

    return 0;
}