#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

#define CAMINHO_FIXO "instancias/"


//Funções utilizadas na árvore binária simples
no * aloca_no(int valor)
{
    no *novo = (no *)malloc(sizeof(no));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// para buscar um nó, fazemos:
no * busca_no(no *raiz, int valor)
{
    if (raiz == NULL){return NULL;}
    else{
        if (raiz->valor == valor)
        {
            return raiz;
        }
        else
        {
            if (valor < raiz->valor)
            {
                return busca_no(raiz->esq, valor);
            }
            else
            {
                return busca_no(raiz->dir, valor);
            }
        }
    }
}
//implementando a função de armazenar o endereço do noPai
no* buscaPai(no * raiz, no * filho){

    if (raiz == NULL){return NULL;}
    else{
        if (raiz->esq == filho || raiz->dir == filho){
            return raiz;
        }else{
            no* pai = buscaPai(raiz->esq, filho);
            if(pai == NULL){
                pai = buscaPai(raiz->dir, filho);
            }
            return pai;
        }
    }

}
// Função para remover um nó raiz corretamente
no* remove_Raiz(no *raiz) {
    if (raiz->esq == NULL && raiz->dir == NULL) {
        // Caso a raiz não tenha filhos, basta removê-la
        free(raiz);
        return NULL;
    } else if (raiz->esq == NULL) {
        // Caso a raiz tenha apenas o filho direito
        no *aux = raiz;
        raiz = raiz->dir;
        free(aux);
        return raiz;
    } else if (raiz->dir == NULL) {
        // Caso a raiz tenha apenas o filho esquerdo
        no *aux = raiz;
        raiz = raiz->esq;
        free(aux);
        return raiz;
    } else {
        // Caso a raiz tenha dois filhos
        no *aux = raiz->esq;
        no *pai_aux = raiz;

        // Encontrar o nó mais à direita da subárvore esquerda
        while (aux->dir != NULL) {
            pai_aux = aux;
            aux = aux->dir;
        }

        // Substituir o valor da raiz pelo valor do nó mais à direita
        raiz->valor = aux->valor;

        // Remover o nó auxiliar (mais à direita)
        if (pai_aux->dir == aux) {
            pai_aux->dir = aux->esq;
        } else {
            pai_aux->esq = aux->esq;
        }

        free(aux);
        return raiz;
    }
}
// Função para remover um nó qualquer (não apenas a raiz)
no* remove_no(no *raiz, int valor) {
    // Buscar o nó a ser removido
    no *n = busca_no(raiz, valor);

    if (n != NULL) {
        // Buscar o pai do nó a ser removido
        no *pai = buscaPai(raiz, n);
        if (pai != NULL) {
            // Verificar se o nó a ser removido é filho à direita ou à esquerda
            if (pai->dir == n) {
                pai->dir = remove_Raiz(n);
            } else {
                pai->esq = remove_Raiz(n);
            }
        } else {
            // Se não houver pai, o nó a ser removido é a raiz
            raiz = remove_Raiz(raiz);
        }
    }

    return raiz;
}
// Função para liberar a memória da árvore
void libera_memoria(no * raiz){

    if(raiz != NULL){
        libera_memoria(raiz->esq);
        libera_memoria(raiz->dir);
        free(raiz);
    }

}

no * insere(no *raiz, no *novo_no)
{
    if (raiz == NULL)
    {
        return novo_no;
    }
    else
    {
        if (novo_no->valor < raiz->valor)
        {
            raiz->esq = insere(raiz->esq, novo_no);
        }
        else
        {
            raiz->dir = insere(raiz->dir, novo_no);
        }
    }
    return raiz;
}

double arvore_binaria(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    // Nome do arquivo baseado no número da instância
    char caminho_completo[256];

    // Concatenar o caminho fixo com o número da instância
    snprintf(caminho_completo, sizeof(caminho_completo), "%s%d", CAMINHO_FIXO, instancia_num);
    printf("Caminho completo: %s\n", caminho_completo);

    // Abrir o arquivo
    FILE* file = fopen(caminho_completo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(0);
    }

    // Ler os valores do arquivo e inserir/remover na árvore binária
    no* raiz = NULL;
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        char operacao;
        int valor;
        sscanf(linha, "%c %d", &operacao, &valor);
        if (operacao == 'I') {
            raiz = insere(raiz, aloca_no(valor));
        } else if (operacao == 'R') {
            raiz = remove_no(raiz, valor);
        }
    }

    // Fechar o arquivo
    fclose(file);

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;

    libera_memoria(raiz);
    return (tempo);
}

//Funções utilizadas na árvore balanceada
// Obtem a altura da AVL
int altura(no_avl * N) { 
    if (N == NULL) {
        return 0; 
    }
    return N->altura; 
} 
  
// Obtem o máximo entre dois inteiros
int max(int a, int b)  { 
    if (a < b) {
        return (b);
    } 
    return (a); 
} 
  
/* Cria um novo nó com apontadores esquerda e direita nulos */
no_avl * newNode(int valor) { 
    no_avl* node = (no_avl*) malloc(sizeof(no_avl)); 
    node->valor     = valor; 
    node->esquerda  = NULL; 
    node->direita   = NULL; 
    node->altura    = 1;  // Novo nó é adicionado como folha
    return(node); 
} 
  
// Faz a rotação a direita na raiz y
no_avl *direitaRotate(no_avl *y) { 
    no_avl *x = y->esquerda; 
    no_avl *T2 = x->direita; 
  
    // Realiza a rotação
    x->direita = y; 
    y->esquerda = T2; 
  
    // Atualiza as alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1; 
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1; 
  
    // Retorna a nova raiz
    return x; 
} 
  
// Faz a rotação a esquerda na raiz x
no_avl *esquerdaRotate(no_avl *x) { 
    no_avl *y = x->direita; 
    no_avl *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    
    // Retorna a nova raiz
    return y; 
} 
  
// Obtem o fator de balanceamento para o nó N
int balanceamento(no_avl *N) { 
    if (N == NULL) {
        return 0; 
    }
    return (altura(N->esquerda) - altura(N->direita)); 
} 

//Faz a inserção do nó na árvore (função recursiva)
no_avl* inserir_avl(no_avl* node, int valor) { 
    /* 1.  Realiza a inserção normal de árvore binária */
    if (node == NULL) {
        return(newNode(valor)); 
    }
  
    if (valor < node->valor) {
        node->esquerda  = inserir_avl(node->esquerda, valor); 
    } else if (valor > node->valor){ 
        node->direita = inserir_avl(node->direita, valor); 
    } else { 
        // Valores duplicados não são permitidos na AVL
        return node; 
    }
    /* 2. Atualiza a altura de seu antecessor */
    node->altura = 1 + max(altura(node->esquerda), 
                        altura(node->direita)); 
  
    /* 3. Obtem o fator de balanceamento da raiz */
    int balance = balanceamento(node); 

    // Se a árvore está desbalanceada, então existem quatro casos possíveis
  
    // Caso esquerda esquerda
    if (balance > 1 && valor < node->esquerda->valor) {
        return direitaRotate(node); 
    }
    // Caso direita direita
    if (balance < -1 && valor > node->direita->valor) {
        return esquerdaRotate(node); 
    }
    //Caso esquerda direita
    if (balance > 1 && valor > node->esquerda->valor) { 
        node->esquerda =  esquerdaRotate(node->esquerda); 
        return direitaRotate(node); 
    } 
    //Caso direita esquerda
    if (balance < -1 && valor < node->direita->valor) { 
        node->direita = direitaRotate(node->direita); 
        return esquerdaRotate(node); 
    } 

    //retorna o ponteiro para a raiz
    return node;
}

//faz a busca na arvore avl
//(diferencia-se da árvore binária apenas no tipo dos parâmetros)
no_avl * busca_avl(no_avl * raiz, int k){
    if(raiz==NULL || (*raiz).valor == k)
        return raiz;
    if((*raiz).valor > k)
        return busca_avl((*raiz).esquerda, k);
    else
        return busca_avl((*raiz).direita, k);
}

//faz a busca do pai na árvore avl
//(diferencia-se da árvore binária apenas no tipo dos parâmetros)
no_avl * buscaPai_avl(no_avl * raiz, int filho){
    if(raiz == NULL || (*raiz).valor == filho){
        return NULL;
    }else{
        if(((*raiz).esquerda != NULL && (*(*raiz).esquerda).valor == filho) || ((*raiz).direita != NULL && (*(*raiz).direita).valor == filho)){
            return raiz;
        }else{
            no_avl * pai = buscaPai_avl((*raiz).esquerda, filho);
            if(pai == NULL){
                pai = buscaPai_avl((*raiz).direita, filho);
            }
            return pai;
        }
    }
}

//remove a raiz da arvore avl
//diferencia-se da arvore binaria apenas pelo tipo dos parâmetros
no_avl * removerRaiz(no_avl * raiz){
    if(raiz == NULL){
        return NULL;
    }

    if((*raiz).esquerda == NULL && (*raiz).direita == NULL){
        free(raiz);
        return NULL;
    }else if ((*raiz).esquerda == NULL){
        no_avl * aux = raiz;
        raiz = (*raiz).direita;
        free(aux);
        return raiz;
    }else if ((*raiz).direita == NULL){
        no_avl *aux = raiz;
        raiz = (*raiz).esquerda;
        free(aux);
        return raiz;
    }else{
        no_avl * aux = (*raiz).esquerda;
        no_avl * aux_pai = raiz;
        while((*aux).direita != NULL){
            aux_pai = aux;
            aux = (*aux).direita;
        }
        (*raiz).valor = (*aux).valor;
        if((*aux_pai).direita == aux){
            (*aux_pai).direita = (*aux).esquerda;
        }else{
            (*aux_pai).esquerda = (*aux).esquerda;
        }
        free(aux);
        return raiz;
    } 
}

//remove um nó na árvore avl
no_avl * remover_avl(no_avl * node, int valor){
    //faz a remoção de uma árvore binária normal
    no_avl * n = busca_avl(node,valor);
    if(n!=NULL){
        no_avl * pai = buscaPai_avl(node, (*n).valor);
        if(pai!=NULL){
            if((*pai).direita == n){
                (*pai).direita = removerRaiz(n);
            }else{
                (*pai).esquerda = removerRaiz(n);
            }
        }else{
            node = removerRaiz(n);
        }
    }
    /* 2. Atualiza a altura de seu antecessor */
    node->altura = 1 + max(altura(node->esquerda), 
                        altura(node->direita)); 
  
    /* 3. Obtem o fator de balanceamento da raiz */
    int balance = balanceamento(node); 

    // Se a árvore está desbalanceada, então existem quatro casos possíveis
  
    // Caso esquerda esquerda
    if (balance > 1 && valor < node->esquerda->valor) {
        return direitaRotate(node); 
    }
    // Caso direita direita
    if (balance < -1 && valor > node->direita->valor) {
        return esquerdaRotate(node); 
    }
    //Caso esquerda direita
    if (balance > 1 && valor > node->esquerda->valor) { 
        node->esquerda =  esquerdaRotate(node->esquerda); 
        return direitaRotate(node); 
    } 
    //Caso direita esquerda
    if (balance < -1 && valor < node->direita->valor) { 
        node->direita = direitaRotate(node->direita); 
        return esquerdaRotate(node); 
    } 

    //retorna o ponteiro para a raiz
    return node;
}

void caminho_em_ordem(no_avl* raiz){
    if(raiz == NULL){
        printf("arvore vazia\n");
        return;
    }
    if((*raiz).esquerda != NULL){
        caminho_em_ordem((*raiz).esquerda);
    }
    printf("no: %d, altura: %d\n", (*raiz).valor, (*raiz).altura);
    if((*raiz).direita != NULL){
        caminho_em_ordem((*raiz).direita);
    }
}

void libera_memoria_avl(no_avl * raiz){

    if(raiz != NULL){
        libera_memoria_avl(raiz->esquerda);
        libera_memoria_avl(raiz->direita);
        free(raiz);
    }

}


double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    // Nome do arquivo baseado no número da instância
    char caminho_completo[256];

    // Concatenar o caminho fixo com o número da instância
    snprintf(caminho_completo, sizeof(caminho_completo), "%s%d", CAMINHO_FIXO, instancia_num);
    printf("Caminho completo: %s\n", caminho_completo);

    // Abrir o arquivo
    FILE* file = fopen(caminho_completo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(0);
    }

    // Ler os valores do arquivo e inserir/remover na árvore binária
    no_avl* raiz = NULL;
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        char operacao;
        int valor;
        sscanf(linha, "%c %d", &operacao, &valor);
        if (operacao == 'I') {
            raiz = inserir_avl(raiz, valor);
        } else if (operacao == 'R') {
            raiz = remover_avl(raiz, valor);
        }
        caminho_em_ordem(raiz);
        printf("---\n");

    }

    // Fechar o arquivo
    fclose(file);

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    libera_memoria_avl(raiz);
    return (tempo);
}


int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);

    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);
    return (1);
}