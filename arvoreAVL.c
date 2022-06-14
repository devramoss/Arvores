#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 99999
#define MIN 1
#define QTDE 99999
#define MAX 100000

/*
       Nó para a Árvore AVL
*/
typedef struct no
{
    int valor;
    struct no *esquerdo, *direito;
    short altura;
} No;

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
No *novoNo(int x)
{
    No *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b)
{
    return (a > b) ? a : b;
}

/*
      Retorna a altura de um nó ou -1 caso ele seja null
*/
short alturaDoNo(No *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

/*
    Insere um novo nó na árvore
    raiz -> raiz da árvore
    x -> valor a ser inserido
    Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
No *inserir(No *raiz, int x)
{
    if (raiz == NULL) // árvore vazia
        return novoNo(x);
    else
    { // inserção será à esquerda ou à direita
        if (x < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        else if (x > raiz->valor)
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // verifica a necessidade de rebalancear a árvore

    return raiz;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
No *remover(No *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else
    { // procura o nó a remover
        if (raiz->valor == chave)
        {
            // remove nós folhas (nós sem filhos)
            if (raiz->esquerdo == NULL && raiz->direito == NULL)
            {
                free(raiz);
                /*printf("Elemento folha removido: %d !\n", chave);*/
                return NULL;
            }
            else
            {
                // remover nós que possuem 2 filhos
                if (raiz->esquerdo != NULL && raiz->direito != NULL)
                {
                    No *aux = raiz->esquerdo;
                    while (aux->direito != NULL)
                        aux = aux->direito;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                   /* printf("Elemento trocado: %d !\n", chave);*/
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else
                {
                    // remover nós que possuem apenas 1 filho
                    No *aux;
                    if (raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                   /* printf("Elemento com 1 filho removido: %d !\n", chave);*/
                    return aux;
                }
            }
        }
        else
        {
            if (chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore

        return raiz;
    }
}

/*
     Procedimento para imprimir uma árvore AVL
*/
void imprimir(No *raiz, int nivel)
{
    int i;
    if (raiz)
    {
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}

void inOrder(No *raiz)
{
    // Caso de base
    if (raiz == NULL)
    {
        return;
    }
    // Percorre primeiro a subárvore da esquerda.
    inOrder(raiz->esquerdo);
    // Imprime o valor do nó atual.
    printf("%d ", raiz->valor);
    // Percorre em seguida a subárvore da direita.
    inOrder(raiz->direito);
}

void preOrder(No *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    // Imprime o valor do nó atual.
    printf("%d ", raiz->valor);
    // Percorre a subárvore da esquerda.
    preOrder(raiz->esquerdo);
    // Percorre a subárvore da direita.
    preOrder(raiz->direito);
}

void postOrder(No *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    // Percorre primeiro a subárvore da esquerda.
    postOrder(raiz->esquerdo);
    // Percorre em seguida a subárvore da direita.
    postOrder(raiz->direito);
    // Imprime o valor do nó atual.
    printf("%d ", raiz->valor);
}

void shuffle(int *array)
{
    for (int i = MAX - MIN - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
}

No *busca(No *raiz, int chave)
{
    if (raiz == NULL)
    {
        /*printf("\nElemento NAO encontrado!");*/
        return raiz;
    }

    if (raiz->valor == chave)
    {
       /* printf("\nElemento ENCONTRADO!");*/
        return raiz;
    }

    if (raiz->valor > chave)
        return busca(raiz->esquerdo, chave);
    else
        return busca(raiz->direito, chave);
}

int main()
{
    int opcao, i = 0;

    No *raiz = NULL;

    srand(time(NULL));

    int *numeros = malloc((MAX - MIN) * sizeof(int));

    if (!numeros)
        exit(EXIT_FAILURE);

    for (int i = 0; i < MAX - MIN; i++)
    {
        numeros[i] = i + MIN;
    }

    shuffle(numeros);

    clock_t begin = clock();

    for (i = 0; i < N; i++)
    {
        raiz = inserir(raiz, numeros[i]);
    }

    clock_t end = clock();
    double time_spent = (float)(end - begin) / CLOCKS_PER_SEC;

    printf("O tempo em segundos para insercao foi: %f\n", time_spent);

    clock_t begin2 = clock();
    
    for (i = 0; i < N; i++)
    {
        busca(raiz, numeros[i]);
    }
    
    clock_t end2 = clock();
    time_spent = (float)(end2 - begin2) / CLOCKS_PER_SEC;

    printf("O tempo em segundos para busca foi: %f\n", time_spent);

    
    begin = clock();

    for (i = 0; i < N; i++)
    {
        raiz = remover(raiz, numeros[i]);
    }

    end = clock();
    time_spent = (float)(end - begin) / CLOCKS_PER_SEC;

    printf("O tempo em segundos para remocao foi: %f\n", time_spent);

    return 0;
}