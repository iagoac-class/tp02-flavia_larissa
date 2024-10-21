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

no * aloca_no(int valor);
no * busca_no(no * raiz, int valor);
no* buscaPai(no * raiz, no * filho);
no* remove_Raiz(no *raiz);
no* remove_no(no *raiz, int valor);
void libera_memoria(no * raiz);
no * insere(no *raiz, no *novo_no);
double arvore_binaria(int instancia_num);
int altura(no_avl * N);
int max(int a, int b);
no_avl * newNode(int valor);
no_avl *direitaRotate(no_avl *y);
no_avl *esquerdaRotate(no_avl *x);
int balanceamento(no_avl *N);
no_avl* inserir_avl(no_avl* node, int valor);
no_avl * busca_avl(no_avl * raiz, int k);
no_avl * buscaPai_avl(no_avl * raiz, int filho);
no_avl * removerRaiz(no_avl * raiz);
no_avl * remover_avl(no_avl * node, int valor);
void caminho_em_ordem(no_avl* raiz);
void libera_memoria_avl(no_avl * raiz);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES