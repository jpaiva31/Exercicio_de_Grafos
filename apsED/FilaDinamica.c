#include <stdio.h>
#include <stdlib.h>
#include "FilaDinamica.h"
Fila *cria_Fila()
{
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
}
int vazia(Fila *f)
{
    return f->inicio == NULL ? 1 : 0;
}
void push(Fila *f, int x)
{

    Node *novo=(Node*) malloc(sizeof(Node));
    novo->info=x;

    if(f->fim!=NULL)
    {
        f->fim->prox=novo;
    }


    f->fim=novo;
    novo->prox=NULL;

    if(f->inicio==NULL)
    {
        f->inicio=novo;
    }

}
int pop(Fila *f)
{
    int x = f->inicio->info;
    Node *prox = f->inicio->prox;
    free(f->inicio);
    f->inicio=prox;
    if(f->inicio==NULL)
    {
        f->fim=NULL;
    }
    return x;
}
void fila_libera(Fila *f)
{
    Node *aux = f->inicio;
    Node *aux2;
    while (aux!=NULL)
    {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(f);
}
