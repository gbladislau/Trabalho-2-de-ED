#ifndef VC_h
#define VC_h

#define MAX_VET 256

#include <stdio.h>
#include <stdlib.h>
#include "Listagen.h"

typedef struct vetchar VetChar;

VetChar *VetCharCria(FILE *arqbase);

void LiberaVetChar(VetChar *alvo);

int VetGetPos(VetChar* vet,int i);

#endif