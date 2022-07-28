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

static void VarreduraArv(bitmap *mapa, Arv *a);

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
    if (ArvVazia(a))
        return -1;
    else
        return 1 + max(ArvAltura(a->esq), ArvAltura(a->dir));
}

bitmap *ExportaArvore(Arv *a)
{
    assert(a);

    unsigned int h = ArvAltura(a);
    unsigned int qntdfolhas = QntdFolhas(a);
    unsigned int tam = 1 + (h * 2) + (qntdfolhas * 8);

    bitmap *mapa = bitmapInit(tam);

    VarreduraArv(mapa, a);

    return mapa;
}

int EhNo(Arv *a)
{
    assert(a);
    if (a->dir || a->esq)
    {
        return 1;
    }
    return 0;
}

int EhFolha(Arv *a)
{
    assert(a);
    if (!a->dir && !a->esq)
    {
        return 1;
    }
    return 0;
}

void EscreveChar(bitmap *mapa, char letrona)
{
    unsigned int aux = (unsigned int)letrona;
    unsigned int enviado = 0;
    for (int i = 10000000; aux != 0; i /= 10)
    {
        enviado += (aux % 2) * i;
        aux = aux / 2;
    }

    for (int i = 0; i < 8; i++)
    {
        bitmapAppendLeastSignificantBit(mapa, enviado % 10);
        enviado = enviado / 10;
    }
}

static void VarreduraArv(bitmap *mapa, Arv *a)
{
    if (a != NULL)
    {
        if (EhFolha(a))
        {
            bitmapAppendLeastSignificantBit(mapa, 1);
            EscreveChar(mapa, a->letra);
        }
        if (EhNo(a))
        {
            bitmapAppendLeastSignificantBit(mapa, 0);
            VarreduraArv(mapa, a->esq);
            VarreduraArv(mapa, a->dir);
        }
    }
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}
