#include "Bitindex.h"

/*  Tipo bitmap indexado, esta aqui temporariamente para
    facilitar acesso. Ele trata um bitmap como uma pilha */
struct bitIndex
{
    bitmap *bitmap;
    int index;
};

BitIndex *IniciaBitIndex(bitmap *bitm)
{
    BitIndex *saida = (BitIndex *)malloc(sizeof(BitIndex));
    saida->bitmap = bitm;
    saida->index = 0;
    return saida;
}

unsigned char ProxBit(BitIndex *bitmap)
{
    bitmap->index++;
    return bitmapGetBit(bitmap->bitmap, bitmap->index - 1);
}

unsigned char* LeCaractere(BitIndex *base)
{
    bitmap *temp = bitmapInit(9);

    for (int i = 0; i < 8; i++)
    {
        bitmapAppendLeastSignificantBit(temp, ProxBit(base));
    }

    return bitmapGetContents(temp);
}

// N libera o bitmap dentro!
void LiberaBitIndx(BitIndex *bitmap) {
    free(bitmap);
}

int ReturnIndex(BitIndex* b){
    return b->index;
}

// Fim de Bitmap Indexado