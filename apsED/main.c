//Código desenvolvido por Igor Anthony Lara e João Paulo Andrade Paiva.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "FilaDinamica.h"

typedef struct ListaDeVertice
{
    int tam;
    int *visitado;
    struct nodo **listaAdj;
} ListaDeVertice;
typedef struct nodo
{
    double peso;
    int info;
    struct nodo *prox;
} nodo;
nodo *criaNodo(int vertice, int peso);
ListaDeVertice *criaListaVertice(int N);
void *insere_aresta(ListaDeVertice *lista, int A, int B, int W, int cont);
double imprime_peso(ListaDeVertice *lista, int A, int B);
void imprime_matriz(ListaDeVertice *lista);
void vizinhos(ListaDeVertice *lista, int A);
void popular(ListaDeVertice *lista);
double DFS(ListaDeVertice *lista, int vertice, double peso_total);
void DFS2(ListaDeVertice *lista, int i);
void BFS(ListaDeVertice *lista, int A, int B);
void *tira_aresta(ListaDeVertice *lista, int A, int B, int parada);
void imprime_pai(int p[], int A, int i, int aux_inverte[], int vertice, int vertices_total);
double peso(ListaDeVertice *lista, int invertido[], int total_vertices, int i, double peso_t);
void destroy(nodo *limpeza);
void destroy2(ListaDeVertice *lista);
int main()
{
    int N;    //numero de nodos
    int A,B,W;
    char aux[255];
    double peso_aux = 0;
    scanf("%d", &N);
    while(N > 100 || N < 1){//laço apenas para garantir que o usuario nunca digite um N alem do suportado
        printf("numero de vertices alem do suportado! digite um valor novamente até 100 vertices:");
        scanf("%d", &N);
    }
    ListaDeVertice *lista= criaListaVertice(N);
    while(1)
    {
        scanf("%s", aux);
        if((strcmp(aux,"+")==0))//aqui começa uma sequencia de if/else if pra saber qual comando o usuario deseja colocar
        {
            scanf("%d %d %d", &A, &B, &W);
            insere_aresta(lista, A, B, W, 0);
        }
        else if((strcmp(aux,"w")==0))
        {
            scanf("%d %d", &A, &B);
            peso_aux = imprime_peso(lista, A, B);
            if(peso_aux == DBL_MAX)
            {
                printf("aresta inexistente\n");
            }
            else
            {
                printf("%.0f\n", peso_aux);
            }
        }
        else if((strcmp(aux,"matriz"))==0)
        {
            imprime_matriz(lista);
        }
        else if((strcmp(aux,"vizinhos"))==0)
        {
            scanf("%d", &A);
            vizinhos(lista, A);
        }
        else if((strcmp(aux,"popular"))==0)
        {
            popular(lista);
        }
        else if((strcmp(aux,"dfs"))==0)
        {
            for(int i = 1 ; i <= lista->tam; i++)
            {
                lista->visitado[i] = 0;
            }
            DFS2(lista, 1);
        }
        else if((strcmp(aux,"bfs"))==0)
        {
            scanf("%d %d", &A, &B);
            if(lista->listaAdj[A]!=NULL && lista->listaAdj[B]!=NULL){//caso exista vizinhos ele vai executar a bfs, se não ele nem vai executar e já vai imprimir que não existe caminho
                BFS(lista, A, B);
            }else{
                    printf("(sem caminho)\n");
            }
        }
        else if((strcmp(aux,"-")==0))
        {
            scanf("%d %d", &A, &B);
            if(lista->listaAdj[A]!=NULL && lista->listaAdj[B]!=NULL)tira_aresta(lista, A, B, 0);
        }
        else if((strcmp(aux,"F")==0))
        {
            destroy2(lista);
            return 0;
        }
    }
}
nodo *criaNodo(int vertice, int peso)
{
    nodo *novo = (nodo *)malloc(sizeof (nodo));
    novo->peso = peso;
    novo->info = vertice;
    novo->prox = NULL;
    return novo;
}
ListaDeVertice *criaListaVertice(int N)//Funcao que cria a lista principal
{
    ListaDeVertice *l = (ListaDeVertice *)malloc(sizeof (ListaDeVertice));
    l->tam = N;
    l->listaAdj = (nodo**)malloc(sizeof(nodo*)*(N+1));//cria N+1 listas dinamicamente
    l->visitado = (int*)malloc(sizeof(int)*(l->tam+1));
    for(int i = 1; i < N+1; i++)//define os valores iniciais dos nodos da lista adjacente
    {
        l->listaAdj[i] = NULL;
        l->visitado[i] = 0;
    }
    return l;
}
void *insere_aresta(ListaDeVertice *lista, int A, int B, int W, int cont)//insere a aresta no A
{
    nodo *aux;
    nodo *novoA = criaNodo(B, W);//é criado um novo nodo de peso W
    aux = lista->listaAdj[A];//aux=lista->listaAdj[A] para que possamos percorrer a lista adjacente A
    if(aux == NULL)//caso a lista esteja vazia
    {
        lista->listaAdj[A] = novoA;
    }
    else if(aux!=NULL)//caso a lista nao esteja vazia
    {
        while(aux->prox !=NULL)//while percorre ate o ultimo nodo da lista
        {
            aux = aux->prox;
        }
        aux->prox = novoA;//define o novo nodo como o ultimo da lista
    }
    if(cont == 1)return;
    insere_aresta(lista, B, A, W, cont + 1);//função recursiva para colocar no B agora, ent inverte os valores na chamada da função e como precisa que execute mais uma vez apenas, foi feito um contador para isso
}
double imprime_peso(ListaDeVertice *lista, int A, int B)//função para imprimir peso
{
    double i = 0;
    nodo *aux;
    aux=lista->listaAdj[A];
    for(aux = lista->listaAdj[A]; aux!=NULL; aux = aux->prox)//pra percorrer na lista adjacente
    {
        if(aux->info == B)//se encontrar o nodo B na lista adjascente de A, coloca i=1, isso me indica que existe um valor
        {
            i = 1;
            break;
        }
    }
    if(i == 0)//se o i for = 0, quer dizer que não existe essa aresta
    {
        i = DBL_MAX;//ai é passado o DBL_MAX para representar o infinito(que não existe peso) e assim o computador entende
    }
    else
    {
        i=aux->peso;//se nao for 0, coloca o valor de i o peso, que sera retornado, informando o peso
    }
    return i;
}
void imprime_matriz(ListaDeVertice *lista)//imprime a matriz de adj
{
    int i, j;
    nodo *aux;
    double **matriz_adj = (double**)malloc((sizeof(double*))*(lista->tam+1));//aloco a quantidade linhas, ela é criada como double por conta do uso do DBL_MAX para representar infinito
    for(i = 1; i <= lista->tam; i++)
    {
        matriz_adj[i] = (double*)malloc(sizeof(double)*(lista->tam+1));//aloco as colounas
    }
    for(i = 1; i <= lista->tam; i++)//passo infinito para todos os valores
    {
        for(j = 1; j <= lista->tam; j++)
        {
            matriz_adj[i][j] = DBL_MAX;
        }
    }
    for(i = 1; i <= lista->tam; i++)//percorro a matriz passando os valores dos pesos
    {
       aux = lista->listaAdj[i];
       for(;aux!=NULL;aux=aux->prox)
        {
            matriz_adj[i][aux->info] = aux->peso;
        }
    }
    for(i = 1; i <= lista->tam; i++)//percorro linha
    {
        for(j = 1; j <= lista->tam; j++)//percorro coluna
        {
            if(matriz_adj[i][j] == DBL_MAX)//se for DBL_MAX, é pq não existe aresta, ent imprime "-"
            {
                printf("- ");
            }
            else
            {
                printf("%.0f ", matriz_adj[i][j]);
            }
        }
        printf("\n");
    }
    for(i = 1; i <= lista->tam ; i++)//libero a matriz criada na memoria
    {
        free(matriz_adj[i]);
    }
    free(matriz_adj);
    matriz_adj = NULL;
}
void vizinhos(ListaDeVertice *lista, int A)//imprime todos os vizinhos
{
    nodo *aux = lista->listaAdj[A];
    if(aux == NULL)//se a lista for null, é pq não existe nenhum vizinho
    {
        printf("(nenhum)");
    }
    else
    {
        for(aux = lista->listaAdj[A]; aux!=NULL; aux = aux->prox)//percorre os vizinhos
        {
            printf("%d ", aux->info);
        }
    }
    printf("\n");
}
void popular(ListaDeVertice *lista)//imprime o vertice com mais vizinhos
{
    int i = 1, maior = 0, maior_i = 0;
    nodo *aux;
    int vetor_popularidade[lista->tam + 1];//declaro um vetor para salvar a quantidade de vizinhos, cada posição do vetor é um vertice
    for(i = 1; i <= lista->tam; i++)
    {
        vetor_popularidade[i]= 0;
    }

    for(i=1; i <= lista->tam; i++)
    {
        for(aux = lista->listaAdj[i]; aux != NULL; aux = aux->prox)//laço para percorrer os vizinhos dos vertices e somar em sua posição + 1 caso exista vizinho
        {
            vetor_popularidade[i] += 1;
        }
    }
    maior = vetor_popularidade[1];//salva quantidade de vizinhos do vertice 1
    maior_i = 1;
    for(i = 2; i < lista->tam; i++)//for usado para percorrer o vetor popularidade
    {
        if(maior <= vetor_popularidade[i])//se o conteudo desse vertice for maior que da minha variavel maior
        {
            if(maior == vetor_popularidade[i]){//condição caso sejam iguais
                if(maior_i > i){
                    maior_i = i;
                }
            }else{
                maior = vetor_popularidade[i];//variavel maior recebe o conteudo
                maior_i = i;//recebe qual é o vertice de maior valor
            }

        }

    }
    printf("%d (%d vizinhos)\n", maior_i, maior);
}
double DFS(ListaDeVertice *lista, int vertice, double peso_total)//Essa função percorre a lista de adj e retorna o seu peso
{
    nodo *aux = lista->listaAdj[vertice];//recebo o endereço da lista desse vertice no aux
    lista->visitado[vertice] = 1;//marca como visitado
    printf("%d", vertice);//imprime o vertice
    for(;aux!=NULL; aux=aux->prox)//laço para percorrer os vizinhos
    {
        peso_total+=aux->peso;//soma ao peso já existente com o peso da aresta
        if(lista->visitado[aux->info]==0)
        {
            printf(" ");
            peso_total = DFS(lista, aux->info, peso_total);//chamada recursiva para verificar se os seus vizinhos já foram visitados, se não foram, vai fazer a msm chamada recursiva até todos serem visitados
        }
    }
    return peso_total;
}
void DFS2(ListaDeVertice *lista, int i)//Essa função dfs2 vai percorrer os vertices
{
    int componentes = 0;
    for(int j = i; j <= lista->tam; j++)
    {
        if(lista->visitado[j] == 0)//se ele não foi visitado, vai visitar e imprimir todos os seus vizinhos e seu peso
        {
            printf("[");
            printf("], peso total %.0f\n", (DFS(lista, j, 0)/2));//como ele percorre o caminho de ida e volta, então o retorno é dividido por 2
            lista->visitado[j] = 1;
            componentes++;
        }
    }
    printf("%d componente(s)\n", componentes);
}
void BFS(ListaDeVertice *lista, int A, int B)
{
    int enfilerado[(lista->tam)+1];//Esse vetor foi criada para me dizer se o vertice foi enfilerado, ele foi criado com o tam do vertice + 1, pois não existe vertice 0.
    int pai[(lista->tam)+1];//vetor que vai ser usado para saber o menor caminho
    int nivel[(lista->tam)+1];//me mostra a quantidade de arestas até ele
    for(int i = 1; i <= lista->tam; i++)
    {
        nivel[i] = 0;
        enfilerado[i] = 0;
        pai[i] = 0;
    }
    int x;
    Fila *f = cria_Fila();//crio a fila
    nodo *aux;
    push(f, A);//enfilero o primeiro valor que é o do vertice A
    enfilerado[A] = 1;
    while(vazia(f)==0)//enquanto essa função não me retornar 1, quer dizer que ela não está zerado
    {
        x = pop(f);//
        for(aux = lista->listaAdj[x]; aux!=NULL; aux = aux->prox)//for usado para percorrer a lista de adj e enfilerar todos os vizinhos
        {
            if(enfilerado[aux->info] == 0)//condição que vai verifica se o viznho foi enfilerado ou não, se não for ele vai entrar
            {
                enfilerado[aux->info] = 1;//marca como enfilerado
                push(f,aux->info);//enfilera
                pai[aux->info] = x;//salva no pai quem é o pai desse vertice
                nivel[aux->info] = nivel[x] + 1;//o nivel dele é o nivel do pai + 1
            }
        }
    }
    if(enfilerado[A] == 1 && enfilerado[B] == 1)
    {
        int aux_inverte[nivel[B]+1];
        aux_inverte[nivel[B]] = B;
        imprime_pai(pai, A, B, aux_inverte, nivel[B] - 1, nivel[B]+1);
        printf("\n%d aresta(s), peso total %.0f\n", nivel[B], peso(lista, aux_inverte, nivel[B]+1, 0, 0));
    }
    else
    {
        printf("(sem caminho)\n");
    }
    fila_libera(f);
}
void *tira_aresta(ListaDeVertice *lista, int A, int B, int parada)/*essa função é usada para remover uma aresta da lista de adj*/
{
    int cont = 0;//vai ser usado para auxiliar em alguns casos que precisam de cuidado
    nodo *aux, *anterior = NULL;//o anterior ele vai guardar o nodo anterior
    aux = lista->listaAdj[A];//vai ser usado para percorrer
    anterior = aux;
    while(aux!=NULL)
    {
        if(aux->info == B)//se entrar nesse if quer dizer que cheguei no valor da aresta desejada
        {
            if(cont >= 1)//quer dizer que existem valores após esse vertice e o valor desejado nao é o primeiro valor na ordem da lista
            {
                anterior->prox = aux->prox;
            }
            if(cont == 0 && aux->prox != NULL)//ele está como primeiro na ordem da lista de adj e existem valores após ele
            {
                lista->listaAdj[A] = aux->prox;
            }
            else if(cont == 0)//nao existem valores após esse vertice
            {
                lista->listaAdj[A] = NULL;
            }
            break;
        }
        cont++;
        anterior = aux;
        aux = aux->prox;
    }
    free(aux);//libero a casa alocada
    if(parada == 1) return;//condição de parada
    tira_aresta(lista, B, A, parada + 1);//chamada recursiva agr para o remover no outro vertice a aresta
}
double peso(ListaDeVertice *lista, int invertido[], int total_vertices, int i, double peso_t)//função usada para retornar o valor do peso do caminho o pai é chamado de invertido, ele é usado para acessar os
{                                                                                            //valores do caminho, assim essa função consegue percorrer o menor caminho e armazenar o peso
    if(i == total_vertices)                                                                    //a cada passo recursivo
    {
        return peso_t;
    }
    else
    {
        nodo *aux;
        int j = invertido[i+1];
        aux = lista->listaAdj[invertido[i]];
        while(aux != NULL)
        {
            if(aux->info == j)
            {
                peso_t += aux->peso;
            }
            aux = aux->prox;
        }
    }
    peso(lista, invertido, total_vertices, i+1, peso_t);
}
void imprime_pai(int p[], int A, int i, int aux_inverte[], int vertice, int vertices_total)//função para imprimir o menor o caminho, esse caminho está no vetor pai
{                                                                                          //mas como ele está invertido, foi criado um vetor para receber os valores de maneira recursiva, ai ele começo da ultima casa
                                                                                           //assim o caminho inverso é colocado na msm ordem, logo após todos valores serem passados ele imprime esse vetor
    int cont = 0;
    if(i == A)
    {
        int z=0;
        while(z<vertices_total)
        {
            printf("%d ",aux_inverte[z]);
            z++;
        }
        return;
    }
    aux_inverte[vertice]=p[i];
    cont++;
    imprime_pai(p, A, p[i], aux_inverte, vertice - 1, vertices_total);
}
void destroy(nodo *limpeza)//Função recursiva usada para percorrer a lista de adj e liberar os nodos criados
{
    if(limpeza == NULL)return;
    nodo *aux = limpeza;
    limpeza = limpeza->prox;
    free(aux);
    destroy(limpeza);
}
void destroy2(ListaDeVertice *lista){//função principal para liberar da memoria, é usada um laço for para analisar se existem nodos na lista de adj
    for(int i = 1; i <= lista->tam; i++){
        if(lista->listaAdj[i]!=NULL){
            destroy(lista->listaAdj[i]);
        }
    }
    free(lista->visitado);
    free(lista->listaAdj);
    free(lista);
    lista = NULL;
}
