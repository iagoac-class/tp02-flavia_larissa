#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui
typedef struct no_
{
    int valor;
    struct no_ *esq;
    struct no_ *dir;
} no;

struct Node {
    int valor;
    struct Node *esquerda;
    struct Node *direita;
    int altura;
};

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES