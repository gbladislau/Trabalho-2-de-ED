#include "Arvore.h"
//#include "Listagen.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Arv *teste = ArvCria('i', 5,
                         ArvCria('g', 7,
                                 ArvCriaVazia(),
                                 ArvCria('h', 9,
                                         ArvCriaVazia(),
                                         ArvCriaVazia())),
                         ArvCriaVazia());

    // Teste de Arv Imprime
    ArvImprime(teste);
    printf("\n");

    // Teste de Arv Pai
    Arv *pai = ArvPai(teste, 'g');
    ArvImprime(pai);
    printf("\n");

    pai = ArvPai(teste, 'h');
    ArvImprime(pai);

    // Teste e Arv Libera
    ArvLibera(teste);
}