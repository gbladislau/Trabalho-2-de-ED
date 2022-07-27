#include "ListaArv.h"
#include "Arvore.h"

static int MenosdeDoisElementos(Listagen *lista);

Listagen *IniciaListaArv()
{
    return IniciaListaGen();
}

void InsereListaArv(Listagen *lista, Arv *inserida)
{
    InsereItemGen(lista, inserida);
}

static int ComparaPeso(void *e1, void *e2)
{
    Arv *a1 = (Arv *)e1;
    int *peso = (int *)e2;
    return (ArvPeso(e1) == *peso);
}

static int ComparaLetra(void *e1, void *e2)
{
    Arv *a1 = (Arv *)e1;
    char *letra = (char *)e2;
    return (ArvChar(a1) == *letra);
}

void RetiraListaArvPeso(Listagen *lista, int Peso)
{
    void *arg = &Peso;
    RetiraDaListaGen(lista, arg, ComparaPeso);
}

void RetiraListaArvLetra(Listagen *lista, char letra)
{
    void *arg = &letra;
    RetiraDaListaGen(lista, arg, ComparaLetra);
}

static void ImprimeArvListada(void *e1)
{
    Arv *a1 = (Arv *)e1;
    return ArvImprime(a1);
}

void ImprimeListaArv(Listagen *lista)
{
    ImprimeListaGen(lista, ImprimeArvListada);
}

static int MenorPeso(void *e1, void *e2)
{
    Arv *a1 = (Arv *)e1;
    Arv *a2 = (Arv *)e2;
    return (ArvPeso(a1) < ArvPeso(a2));
}

void ReorganizaListaArv(Listagen *lista)
{
    ReorganizaLista(lista, MenorPeso);
}

// TODO: Ver como corrigir conversao inadequada aqui
int PercorreListaArv(Listagen *lista, void(func)(Arv *))
{
    return PercorreLista(lista, func);
}

int FundePrimeiros(Listagen *lista)
{
    if (MenosdeDoisElementos(lista) == 0)
    {
        Arv *esquerda = (Arv *)RetiraPrimeiro(lista);
        Arv *direita = (Arv *)RetiraPrimeiro(lista);

        Arv *inserido = ArvCria(NULL, ArvPeso(esquerda) + ArvPeso(direita), esquerda, direita);

        InsereUltItemGen(lista, inserido);
        return 1;
    }
    else
        return 0;
}

static int MenosdeDoisElementos(Listagen *lista)
{
    if (VaziaLista(lista) ||
        RetornaPrimeiro(lista) == RetornaUlt(lista))
        return 1;
    else
        return 0;
}

// SEM LIBERAR ARVORES
void LiberaListaArv(Listagen *lista)
{
    LiberaListaGen(lista, NULL);
}

// Avaliar se vale a pena criar um arq p vetchar, ja que tem apenas 2 func
//  Cria e Libera

// Preenche a lista
struct vetchar
{
    int vetor[256];
};

typedef struct vetchar VetChar;

// TODO: CONTINUAR ISSO
//  Faz o vetor
static VetChar *VetCharCria(FILE *arqbase)
{

    // Convertendo o file p um vetor de char//byte
    char *buffer;
    long tam;
    // Ir no final do arq
    fseek(arqbase, 0, SEEK_END);
    // Pega o tam
    tam = ftell(arqbase);
    // Volta no inicio
    rewind(arqbase);
    // Faz o buffer
    buffer = (char *)malloc(tam * sizeof(char));
    fread(buffer, tam, 1,arqbase);

    // Agora vem aqui e vai varrendo o vetor e fazendo a contagem 
    // de aparicoes colocando o resultado no vetchar
    // calloc p ser inicializado com 0
    VetChar *saida = (VetChar *)calloc(256, sizeof(int));
    char aux;

    //Antigo n funcional
    // while (fscanf("%c", &aux)) // Enquanto tem 8bits no arq
    // {
    //     saida->vetor[aux % 256]++;
    // }
    // return saida;
}
static void LiberaVetChar(VetChar *alvo)
{
    free(alvo);
}

// Dentro dessa funcao, criar um vetorchar, usar a func vetcharcria
// Apos utilizar-la tera um vetor de frequencia valido
// Com ela, preenche a lista de arvores inserindo todos com peso diff de 0
// Apos, chama organiza listadeArv, libera vetchar e retorna
void PreencheLista(Listagen *lista, FILE *base)
{
}
