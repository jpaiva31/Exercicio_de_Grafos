#ifndef FILADINAMICA_H_INCLUDED
#define FILADINAMICA_H_INCLUDED
typedef struct Node
{
    int info;
    struct Node *prox;
} Node;
typedef struct
{
    struct Node *inicio, *fim;
} Fila;
Fila *cria_Fila();
int vazia(Fila *f);
void push(Fila *f, int x);
int pop(Fila *f);
void fila_libera(Fila *f);
#endif // FILADINAMICA_H_INCLUDED
