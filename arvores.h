#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui
typedef struct no_
{
    int valor;
    struct no_ *esq;
    struct no_ *dir;
} no;

typedef struct no_avl {
    int valor;
    struct no_avl *esquerda;
    struct no_avl *direita;
    int altura;
} no_avl;

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES