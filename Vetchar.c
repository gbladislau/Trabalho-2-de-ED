#include "Vetchar.h"

struct vetchar
{
    int vetor[MAX_VET];
};

static void PreencheVetChar(VetChar *vetorDfreq, FILE *arq);

VetChar *VetCharCria(FILE *arqbase)
{

    VetChar *saida = (VetChar *)malloc(sizeof(VetChar));
    for (int i = 0; i < MAX_VET; i++)
    {
        saida->vetor[i] = 0;
    }

    PreencheVetChar(saida, arqbase);
    rewind(arqbase);
    return saida;
}

void LiberaVetChar(VetChar *alvo)
{
    free(alvo);
}

int VetGetPos(VetChar *vet, int i)
{
    return vet->vetor[i];
}

static void PreencheVetChar(VetChar *vetorDfreq, FILE *arq)
{
    char aux;
    // TODO:VOLTAR AQUi
    while (!feof(arq))
    {
        if (fread(&aux, 1, 1, arq))
        {
            if (!aux)
                vetorDfreq->vetor[0]++;

            else
                vetorDfreq->vetor[aux]++;
        }
        else
            break;
    }
}