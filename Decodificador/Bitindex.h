#ifndef BI_H
#define BI_H
#include "bitmap.h"

typedef struct bitIndex BitIndex;

/**
 * @brief 
 * 
 * @param bitm 
 * @return BitIndex* 
 */
BitIndex *IniciaBitIndex(bitmap *bitm);

/**
 * @brief 
 * 
 * @param bitmap 
 * @return unsigned char 
 */
unsigned char ProxBit(BitIndex *bitmap);

/**
 * @brief 
 * 
 * @param base 
 * @return unsigned char 
 */
unsigned char LeCaractere(BitIndex *base);

// N libera o bitmap dentro!
void LiberaBitIndx(BitIndex *bitmap);


#endif