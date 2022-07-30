#include "ListaArv.h"
#include "Arvore.h"

static int MenosdeDoisElementos(Listagen *lista);

static int ComparaPeso(void *e1, void *e2);

static int ComparaLetra(void *e1, void *e2);

static int MenorPeso(void *e1, void *e2);

static void ImprimeArvListada(void *e1);

Listagen *IniciaListaArv()
{
    return IniciaListaGen();
}

void InsereListaArv(Listagen *lista, Arv *inserida)
{
    InsereItemGen(lista, inserida);
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

void ImprimeListaArv(Listagen *lista)
{
    ImprimeListaGen(lista, ImprimeArvListada);
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

        Arv *inserido = ArvCria(NULL, ArvPeso(esquerda) + ArvPeso(direita),
                                esquerda, direita);

        InsereUltItemGen(lista, inserido);
        return 1;
    }
    else
        return 0;
}

void ArvListadaLibera(void *e1)
{
    Arv *a1 = e1;
    ArvLibera(a1);
}

// LIBERANDO ARVORES
void LiberaListaArv(Listagen *lista)
{
    LiberaListaGen(lista, ArvListadaLibera);
}

// Dentro dessa funcao, Usar VetCHAR para preencher a lista gen com as arvores respectivas.
// Com ela, preenche a lista de arvores inserindo todos com peso diff de 0
// Apos, chama organiza listadeArv, libera vetchar e retorna
void PreencheLista(Listagen *lista, VetChar *VetTemp)
{
    for (int i = 0; i < MAX_VET; i++)
    {
        if (VetGetPos(VetTemp, i))
        {
            Arv *a = ArvCria((char)i, VetGetPos(VetTemp, i), ArvCriaVazia(), ArvCriaVazia());
            InsereListaArv(lista, a);
        }
    }
}

Arv *BuscaArvChar(Listagen *lista, char c)
{
    return BuscaLista(lista, ComparaLetra, &c);
}

static int MenosdeDoisElementos(Listagen *lista)
{
    if (VaziaLista(lista) ||
        RetornaPrimeiro(lista) == RetornaUlt(lista))
        return 1;
    else
        return 0;
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

static int MenorPeso(void *e1, void *e2)
{
    Arv *a1 = (Arv *)e1;
    Arv *a2 = (Arv *)e2;
    return (ArvPeso(a1) < ArvPeso(a2));
}

static void ImprimeArvListada(void *e1)
{
    Arv *a1 = (Arv *)e1;
    return ArvImprime(a1);
}

// void ConverteVetorALista(Listagen *lista, VetChar *vetor)
// {
//     for (int i = 0; i < MAX_VET; i++)
//     {
//         if ((VetGetPos(vetor, i)) != 0)
//         {
//             InsereListaArv(lista, ArvCria((char)i, VetGetPos(vetor, i),
//                                           ArvCriaVazia(), ArvCriaVazia()));
//         }
//     }
// }