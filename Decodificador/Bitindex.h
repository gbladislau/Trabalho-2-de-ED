#ifndef BI_H
#define BI_H
#include "bitmap.h"
#include <stdlib.h>

typedef struct bitIndex BitIndex;

/**
 * @brief Inicia um Bitmap indexado, dado um bitmap comum
 * 
 * @param bitm - Bitmap base
 * @return BitIndex* - Bitmap indexado
 */
BitIndex *IniciaBitIndex(bitmap *bitm);

/**
 * @brief Retorna o proximo bit do bitmap, 
 *        caso omesmo fosse tratado como uma pilha
 * 
 * @param bitmap - Bitmap Indexado 
 * @return unsigned char - Bit obtido
 */
unsigned char ProxBit(BitIndex *bitmap);

/**
 * @brief Retorna os proximos 8 bits do bitmap, concatenados em um char
 * 
 * @param base - Bitmap Indexado
 * @return unsigned char - Bits obtidos concatenados
 */
unsigned char LeCaractere(BitIndex *base);

/**
 * @brief Libera a estrutura de BitIndexado, 
 *        sem liberar o bitmap em que foi baseado
 * 
 * @param bitmap - Bitmap Indexado a ser liberado
 */
void LiberaBitIndx(BitIndex *bitmap);


#endif