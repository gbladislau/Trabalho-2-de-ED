#ifndef VC_h
#define VC_h

#define MAX_VET 257

#include <stdio.h>
#include <stdlib.h>
#include "Listagen.h"

typedef struct vetchar VetChar;

/**
 * @brief Faz a criacao de um vetor frequencia dado um arquivo base
 *
 * @param arqbase - Arquivo base
 * @return VetChar* - Vetor frequencia
 */
VetChar *VetCharCria(FILE *arqbase);

/**
 * @brief Libera o vetor frequencia
 *
 * @param alvo - Vetor frequencia a ser liberado
 */
void LiberaVetChar(VetChar *alvo);

/**
 * @brief Retorna quantas vezes uma dada combinacao de btis apareceu no arquivo
 *
 * @param vet - Vetor frequencia
 * @param i - Numero dado a combinacao de bits procurada
 * @return int - Aparicoes dessa combinacao de bits
 */
int VetGetPos(VetChar *vet, int i);

#endif