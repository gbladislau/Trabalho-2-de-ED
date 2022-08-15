#include "Arvore.h"

//-------------------------------- Struct ----------------------------------------------//

/**
 * @brief Estrutura da Arvore que carega o peso do
 *        caractere e o próprio caractere para implementação
 *        do Algoritimo de Huffman.
 */
struct arv
{
    unsigned char letra;
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
 * @return int - Maior dos dois numeros passados
 */
static int max(int a, int b);

/**
 * @brief Funcao recusiva auxiliar de ExportaArvore.
 *        Varre a arvore de Huffman para exporta-la
 *        para o cabeçalho do arquivo de saída.
 *
 * @param mapa - bitmap de saida
 * @param a - Arvore a ser exportada
 */
static void VarreduraArv(bitmap *mapa, Arv *a);

/**
 * @brief Percorre a arvore buscando o caractere passado,
 *        adicionando 0's e 1's no bitmap para descobrir como
 *        tal caractere está codificado na arvore de Huffman.
 *
 * @param codificando - Bitmap de saida
 * @param a - Arvore de Huffman
 * @param c - Caractere sendo buscado
 */
static void Recursiva(bitmap *codificando, Arv *a, unsigned char c);

/**
 * @brief Funcao recursiva auxiliar de FazArvdeBitMap.
 *        Nessa funcao, lemos o bitmap indexado
 *        contendo a arvore serializada bit a bit, a desserializando
 *
 * @param bitmap - Bitmap indexado contend a arvore serializada
 * @return Arv* - Arvore desserializada
 */
Arv *RecursividadeCriadora(BitIndex *bitmap);

/**
 * @brief Funcao recusiva auxiliar de PercorreArvorePorBitEEscreveSaida.
 *        Faz a decodificacao de um caractere presente no Bitmap Indexado,
 *        dada a arvore de huffman
 *
 * @param p - Bitmap Indexado contendo o caractere a ser decodificado
 * @param arvore - Arvore de Huffman
 * @param contadorDebits - Auxiliar para uso na funcao principal
 * @return unsigned char - Caractere decodificado
 */
unsigned char RetornaCharRecursivamente(BitIndex *p, Arv *arvore, unsigned long int *contadorDebits);
//------------------------------------ Funções Publicas ----------------------------------//

Arv *ArvCriaVazia()
{
    return NULL;
}

Arv *ArvCria(unsigned char letra, int peso, Arv *esq, Arv *dir)
{
    Arv *nova = (Arv *)malloc(sizeof(Arv));
    assert(nova);

    nova->letra = letra;
    nova->peso = peso;
    nova->esq = esq;
    nova->dir = dir;

    return nova;
}

Arv *ArvLibera(Arv *a)
{
    if (a)
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
    printf("<");
    if (a)
    {
        if (a->letra)
            printf("%c-", a->letra);
        printf("%d", a->peso);
        ArvImprime(a->esq);
        ArvImprime(a->dir);
    }
    printf(">");
}

Arv *ArvPai(Arv *a, unsigned char c)
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

unsigned char ArvChar(Arv *a)
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
    unsigned int tam = (1 + (h * 2) + (qntdfolhas * 8) * 2);
    while (tam % 8)
    {
        tam++;
    }

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

int PosiscaoChar(Arv *raiz, unsigned char c)
{
    if (raiz)
    {
        if (ExisteChar(raiz->esq, c))
            return 0;
        else
            return 1;
    }
}

int ExisteChar(Arv *a, unsigned char c)
{
    if (a)
    {
        if (a->letra == c)
        {
            return 1;
        }
        else
        {
            return (ExisteChar(a->esq, c) || ExisteChar(a->dir, c));
        }
    }
    return 0;
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

static void Recursiva(bitmap *codificando, Arv *a, unsigned char c)
{
    // Tem que verificar se eh um no, pq caso seja uma folha nao precisa codificar
    if (EhNo(a))
    {
        if (!PosiscaoChar(a, c)) // Esta na esquerda
        {
            bitmapAppendLeastSignificantBit(codificando, 0);
            Recursiva(codificando, a->esq, c);
        }
        else // Esta na direita
        {
            bitmapAppendLeastSignificantBit(codificando, 1);
            Recursiva(codificando, a->dir, c);
        }
    }
}

bitmap *CodificaChar(Arv *raiz, unsigned char carac)
{
    bitmap *codigo = bitmapInit(ArvAltura(raiz) * 2);
    if (ExisteChar(raiz, carac))
    {
        Recursiva(codigo, raiz, carac);
    }
    return codigo;
}

Arv *RecursividadeCriadora(BitIndex *bitmap)
{
    Arv *saida;
    if (ProxBit(bitmap)) // Se for folha
    {
        saida = ArvCria(LeCaractere(bitmap), 1,
                        ArvCriaVazia(),
                        ArvCriaVazia());
        return saida;
    }
    else // Eh no
    {
        saida = ArvCria('\0', 0,
                        ArvCriaVazia(),
                        ArvCriaVazia());
        saida->esq = RecursividadeCriadora(bitmap);
        saida->dir = RecursividadeCriadora(bitmap);
        return saida;
    }
    return saida;
}

Arv *FazArvdeBitMap(bitmap *bitmap)
{
    BitIndex *bitindexado = IniciaBitIndex(bitmap);
    Arv *saida;
    saida = RecursividadeCriadora(bitindexado);
    LiberaBitIndx(bitindexado);
    return saida;
}

void PercorreArvorePorBitEEscreveSaida(BitIndex *arquivo, Arv *arvore, unsigned long int tamTotalBits, FILE *saida)
{
    unsigned long int contadorDebits[1];
    contadorDebits[0] = tamTotalBits;
    unsigned char aux;
    while (contadorDebits[0] != 0)
    {
        aux = RetornaCharRecursivamente(arquivo, arvore, contadorDebits);
        fwrite(&aux, 1, 1, saida);
    }
}

unsigned char RetornaCharRecursivamente(BitIndex *p, Arv *arvore, unsigned long int *contadorDebits)
{
    if (EhNo(arvore))
    {
        contadorDebits[0]--;
        if (ProxBit(p))
        {
            return RetornaCharRecursivamente(p, arvore->dir, contadorDebits);
        }
        else
        {
            return RetornaCharRecursivamente(p, arvore->esq, contadorDebits);
        }
    }
    if (EhFolha(arvore))
    {
        return arvore->letra;
    }
}