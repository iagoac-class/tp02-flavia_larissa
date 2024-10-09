#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

#define CAMINHO_FIXO "instancias/"

typedef struct no_
{
    int valor;
    struct no_ *esq;
    struct no_ *dir;
} no;

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
        no *aux = raiz->dir;
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
    return (tempo);
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
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