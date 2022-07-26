#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaEstatica.h"
#define MAX 100
#define TAM 255
Fila *cria_Fila(void)
{
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->v = (int*)malloc(sizeof(int)*MAX);
    f->inicio = f->fim = 0;
}
int vazia(Fila *f)
{
    return f->inicio == f->fim ? 1 : 0;
}
void push(Fila *f, int x)
{
    f->v[f->fim] = x;
    f->fim = (f->fim + 1)%MAX;
}
int pop(Fila *f)
{
    if(f->fim == f->inicio)
    {
        return  0;
    }
    else
    {
        int x = f->v[f->inicio];
        f->inicio = (f->inicio + 1)%MAX;
        return x;
    }
}
void fila_libera(Fila *f){
     free(f->v);
     free(f);
}
