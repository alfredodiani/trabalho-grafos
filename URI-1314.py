'''
 * 
 * Problema: https://www.beecrowd.com.br/judge/pt/problems/view/1314
 * Time limit exceeded
 * Python
 * 
 * URI 1314
 * 
 * Autor: Alfredo
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
 * depois navegar pelo grafo comparando se a as arestas utilizadas para sair
 * da origem e chegar ao destino são pontes, caso sim print Y caso contrario print N
 * 
'''


def obtemPontes(listaAdj):
    for v in range(n):
        if(pai[v] == -1):
            pai[v] = v
            pontes(listaAdj, v)
    
    listaPontes = []

    for v in range(n):
        if(low[v] == d[v] and pai[v] != v):
            listaPontes.append((pai[v],v))
            
    return listaPontes


def pontes(listaAdj, u):
    global tempo
    d[u] = tempo
    tempo = tempo + 1

    minimo = d[u] 
    
    for v in listaAdj[u]:
        if(d[v] == -1): 
            pai[v] = u
            pontes(listaAdj, v)
            
            if(low[v] < minimo):
                minimo = low[v]
        
        elif(d[v] < minimo and v != pai[u]):
            minimo = d[v]
    
    low[u] = minimo
    
    
def DFS_VISIT(grafo, s, t):
    cor[s] = 'C'
    
    vizinhos = obtemVizinhos(grafo, s)
    
    for v in vizinhos:
        if(cor[v] == 'B'):
            
            arvore.append((s,v))
            if(s==t):
                contArvore = 0
                for v2 in arvore:
                    if v2 in listaPontes:
                        contArvore = contArvore + 1
                if (contArvore==len(arvore)):
                    return True
            cor[v] = 'C'
            resp = DFS_VISIT(grafo, v, t)
            if (resp==True):
                return True
    cor[s] = 'P'
    return False

            
def obtemVizinhos(grafo, u):
    return grafo[u]



n, m, q = [int(x) for x in input().split()]


while(n!=0 and m!=0 and q!=0):
    d = [-1 for i in range(n)]
    pai = [-1 for i in range(n)]
    low = [-1 for i in range(n)]
    tempo=0
    cor = ['B' for i in range(n)]
    arvore = []

    E =[]
    Q =[]
    for i in range(m):
        x,y = [int(x) for x in input().split()]
        E.append((x,y))

    listaAdj = [ [] for i in range(n)]
    for e in E:
        listaAdj[e[0]-1].append(e[1]-1)
        listaAdj[e[1]-1].append(e[0]-1)

    listaPontes = obtemPontes(listaAdj)

    for i in range(q):
        origem,destino = [int(x) for x in input().split()]
        Q.append((origem,destino))
        
    for i in range(q):
        resposta=DFS_VISIT(listaAdj,origem,destino)
        if(resposta):
            print("Y")
        else:
            print("N")

    print("-")
    
    n, m, q = [int(x) for x in input().split()]
