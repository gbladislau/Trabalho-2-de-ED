#ifndef DEC_h
#define DEC_h
#include "Arvore.h"

/**
 * @brief Monta uma arvore de Huffman com base no cabecalho
 *        presente no arquivo de entrada
 * 
 * @param entrada - Arquivo de entrada contendo o cabecalho
 * @return Arv* - Arvore de huffman
 */
Arv *PegaArvore(FILE *entrada);

/**
 * @brief Dada a informacao presente no cabecalho, eh 
 *        criado o arquivo para a saida da decodificacao
 * 
 * @param entrada 
 * @param path 
 * @return FILE* 
 */
FILE *CriaSaida(FILE *entrada, const char *path);

/**
 * @brief Faz a abertura de um arquivo cujo caminho foi passado
 * 
 * @param arg - Diretorio do arquivo a ser aberto
 * @return FILE* - Arquivo aberto no formato utilizado no projeto
 */
FILE *AbreEntrada(const char *arg);

/**
 * @brief Preenche bitmap com a quantidade de bits informada do arquivo passado
 * 
 * @param arv - Bitmap a ser preenchido
 * @param arquivo - Arquivo base
 * @param qntBit - Quantidade de bits a serem colocados no bitmap
 */
void PreencheBitMapArquivo(bitmap *arv, FILE *arquivo, int qntBit);

/**
 * @brief Decodifica o arquivo de entrada com base na arvore de Huffman passada
 *        Escrevendo o resultado no arquivo de saida
 * 
 * @param entrada - Arquivo codificado, sem cabecalho de arvore
 * @param arvore - Arvore usada para a codificacao
 * @param saida - Arquivo de saida
 */
void DescodificarEntrada(FILE* entrada, Arv* arvore, FILE* saida);
#endif