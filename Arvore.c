#include "Arvore.h"

//-------------------------------- Struct ----------------------------------------------//

/**
 * @brief Estrutura da Arvore que carega o peso do
 *        caractere e o próprio caractere para implementação
 *        do Algoritimo de Huffman.
 */
struct arv
{
    char letra;
    int peso;
    Arv *esq;
    Arv *dir;
};

//----------------------------------- Funções Privadas ----------------------------------//

/**
 * @brief Retorna max entre dois numeros inteiros.
 *
 * @param a
 * @param b
 * @return int
 */
static int max(int a, int b);

//------------------------------------ Funções Publicas ----------------------------------//

Arv *ArvCriaVazia()
{
    return NULL;
}

Arv *ArvCria(char letra, int peso, Arv *esq, Arv *dir)
{
    Arv *nova = (Arv *)malloc(sizeof(Arv));
    assert(nova);

    nova->letra = letra;
    nova->peso = peso;
    nova->dir = dir;
    nova->esq = esq;

    return nova;
}

Arv *ArvLibera(Arv *a)
{
    if (a != NULL)
    {
        ArvLibera(a->dir);
        ArvLibera(a->esq);
        free(a);
    }
}

int ArvVazia(Arv *a)
{
    if (!a)
        return 1;
    else
        return 0;
}

void ArvImprime(Arv *a)
{
    if (a)
    {
        if (a->letra)
            printf("%c ", a->letra);
        printf("%d; ", a->peso);
        ArvImprime(a->esq);
        ArvImprime(a->dir);
    }
}

Arv *ArvPai(Arv *a, char c)
{
    if (a)
    {
        if (a->esq && ArvChar(a->esq) == c)
        {
            return a;
        }
        else if (a->dir && ArvChar(a->dir) == c)
        {
            return a;
        }
        else
        {
            return (ArvPai(a->dir, c) ? ArvPai(a->dir, c) : ArvPai(a->esq, c));
        }
    }
    return NULL;
}

int QntdFolhas(Arv *a)
{
    if (!a)
    {
        return 0;
    }
    if (a)
    {
        int i = 0;
        if (ArvVazia(a->esq) && ArvVazia(a->dir))
            i = 1;
        return (QntdFolhas(a->esq) + QntdFolhas(a->dir) + i);
    }
}

char ArvChar(Arv *a)
{
    assert(a);
    return a->letra;
}

int ArvPeso(Arv *a)
{
    assert(a);
    return a->peso;
}

int ArvAltura(Arv *a)
{
    assert(a);
    if (ArvVazia(a))
        return -1;
    else
        return 1 + max(ArvAltura(a->esq), ArvAltura(a->dir));
}

bitmap *ExportaArvore(Arv *a){
    assert(a);

    int h = ArvAltura(a);
    int qntdfolhas = QntdFolhas(a);
    int tam = h+(qntdfolhas*9);
    bitmap* mapa = bitmapInit(tam);

    return mapa;
}

int EhNo(Arv* a){
    assert(a);
    if(a->dir || a->esq){
        return 1;
    }
    return 0;
}

int EhFolha(Arv* a){
    assert(a);
    if(!a->dir && !a->esq){
        return 1;
    }
    return 0;
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

