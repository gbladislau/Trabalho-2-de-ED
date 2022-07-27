#include "Arvore.h"
#include "Listagen.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
        Arv *teste = ArvCria('i', 5,
                             ArvCria('h', 7,
                                     ArvCria('k', 7,
                                             ArvCriaVazia(),
                                             ArvCriaVazia()),
                                     ArvCria('h', 9,
                                             ArvCriaVazia(),
                                             ArvCriaVazia())),
                             ArvCria('d', 9,
                                     ArvCriaVazia(),
                                     ArvCriaVazia()));

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
        // ArvLibera(teste);

        bitmap *testador = ExportaArvore(teste);
        // // bitmapAppendLeastSignificantBit(testador, 0);
        // // bitmapAppendLeastSignificantBit(testador, 1);
        // // bitmapAppendLeastSignificantBit(testador, 1);
        // // bitmapAppendLeastSignificantBit(testador, 0);

        // // bitmapAppendLeastSignificantBit(testador, 0);
        // // bitmapAppendLeastSignificantBit(testador, 0);
        // // bitmapAppendLeastSignificantBit(testador, 0);
        // // bitmapAppendLeastSignificantBit(testador, 1);
        // EscreveChar(testador, '{');
        unsigned char *saida = bitmapGetContents(testador);
        // printf("%s", saida);

        int lalala = 1;
}