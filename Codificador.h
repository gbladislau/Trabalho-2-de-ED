#ifndef COD_h
#define COD_h

#include "ListaArv.h"
#include "Arvore.h"
#include "Vetchar.h"

#include <strings.h>

/**
 * @brief Dada uma lista de arvores, aplica o algoritmo de Huffman
 *        e retorna a raiz da arvore resultante
 *
 * @param listabase - Lista de arvores preenchida e valida
 * @return Arv* - Arvore resultante do algoritmo de Huffman
 */
Arv *FazArvoreHuffman(Listagen *listabase);

/**
 * @brief Funcao que verifica o bitmap e caso o mesmo esteja com o byte
 *        final incompleto, completa-o com 0's
 *
 * @param entrada - bitmap a ser verificado
 */
void CompletaByteBitmap(bitmap *entrada);

/**
 * @brief Utilizando da arvore fornecida, codifica o arquivo de entrada senguindo o algotimo de Huffman,
 *        escrevendo o resultado a cada aproximadamente 7MB no arquivo de saida
 *
 * @param arq - Arquivo de entrada valido, a ser codificado
 * @param Huffman - Arvore de Huffman
 * @param Vetor  - Vetor de Frequencia referente a arvore
 * @param saida  - Arquivo de saida
 */
void CodificaArq(FILE *arq, Arv *Huffman, VetChar *Vetor, FILE *saida);

/**
 * @brief Faz o calculo de quantos bits serao ocupados pelo arquivo a ser codificado
 *        dada a arvore de Huffman que será usada
 *
 * @param arq - Arquivo de entrada valido, a ser codificado
 * @param Huffman - Arvore de Huffman
 * @param Vetor - Vetor de Frequencia referente a arvore
 * @return long long int - Numero bits que serao ocupados pelo arquivo apos o aloritmo
 */
long long int TamArq(FILE *arq, Arv *Huffman, VetChar *Vetor);

/**
 * @brief Troca a extensao do arquivo de entrada para a extensao 
 *        referente a saida do programa
 *
 * @param arqEntrada
 * @param arqSaida
 */
void AdicionaExtensao(char *arqEntrada, char *arqSaida);

#endif