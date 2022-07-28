#include "Vetchar.h"

struct vetchar
{
    int vetor[256];
};

static void PreencheVetChar(VetChar* vetorDfreq, FILE* arq);

VetChar *VetCharCria(FILE *arqbase)
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
    // // Faz o buffer
    // buffer = (char *)malloc(tam * sizeof(char));
    // fread(buffer, tam, 1,arqbase);

    VetChar *saida = (VetChar *)malloc(sizeof(VetChar));

    PreencheVetChar(saida,arqbase);

    return saida;
}
void LiberaVetChar(VetChar *alvo)
{
    free(alvo);
}

static void PreencheVetChar(VetChar* vetorDfreq, FILE * arq){
    char aux;
    while ( !feof(arq) )
    {
        if(fscanf(arq,"%1[]",aux))
        {
            if(!aux)
                vetorDfreq->vetor[0]++;

            else
                vetorDfreq->vetor[aux]++;
        }
        else break;
    }
}