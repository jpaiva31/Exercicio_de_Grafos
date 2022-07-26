#ifndef FILAESTATICA_H_INCLUDED
#define FILAESTATICA_H_INCLUDED
typedef struct Fila
{
    int *v, inicio, fim;
}Fila;
Fila *cria_Fila();
int vazia(Fila *f);
void push(Fila *f,int x);
int pop(Fila *f);
void fila_libera(Fila *f);
#endif // FILAESTATICA_H_INCLUDED
