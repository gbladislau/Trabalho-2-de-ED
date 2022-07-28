#include "Vetchar.h"

struct vetchar
{
    int vetor[MAX_VET];
};

static void PreencheVetChar(VetChar* vetorDfreq, FILE* arq);

VetChar *VetCharCria(FILE *arqbase)
{
    // // Convertendo o file p um vetor de char//byte
    // char *buffer;
    // long tam;
    // // Ir no final do arq
    // fseek(arqbase, 0, SEEK_END);
    // // Pega o tam
    // tam = ftell(arqbase);
    // // Volta no inicio
    // rewind(arqbase);
    // // // Faz o buffer
    // // buffer = (char *)malloc(tam * sizeof(char));
    // // fread(buffer, tam, 1,arqbase);

    VetChar *saida = (VetChar *)malloc(sizeof(VetChar));
    for (int i = 0; i < MAX_VET; i++){
        saida->vetor[i] = 0;
    }
    

    PreencheVetChar(saida,arqbase);

    return saida;
}

void LiberaVetChar(VetChar *alvo)
{
    free(alvo);
}

int VetGetPos(VetChar* vet,int i){
    return vet->vetor[i];
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