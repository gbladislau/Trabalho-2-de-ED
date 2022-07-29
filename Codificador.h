#ifndef COD_h
#define COD_h

#include "ListaArv.h"
#include "Arvore.h"
#include "Vetchar.h"

typedef struct TabelaDeCod Tabela;

Arv *FazArvoreHuffman(Listagen *listabase);
void CompletaByteBitmap(bitmap *entrada);
void CodificaArq(FILE *arq, Arv *Huffman, VetChar *Vetor, FILE *saida);
static Tabela *MontandoTabela(Arv *Huffman, VetChar *vetor, int tam);

/**
 * @brief Retorna o codigo referente ao caractere dado, na codificacao da arvore fornecida
 *
 * @param a  - Arvore valida, preenchida
 * @param carac - Caractere a ser codificado
 * @return bitmap* - Codigo referente ao caractere
 */
bitmap *CodificaChar(const Arv *raiz, char carac);


#endif