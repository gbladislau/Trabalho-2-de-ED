#ifndef COD_h
#define COD_h

#include "ListaArv.h"
#include "Arvore.h"
#include "Vetchar.h"

typedef struct TabelaDeCod Tabela;

/**
 * @brief Retorna o codigo referente ao caractere dado, na codificacao da arvore fornecida
 *
 * @param a  - Arvore valida, preenchida
 * @param carac - Caractere a ser codificado
 * @return bitmap* - Codigo referente ao caractere
 */
bitmap *CodificaChar(const Arv *raiz, char carac);

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
 * @brief Inicia uma tabela de codificacao, a preenchendo com a informacao obtida a partir do
 *        vetor de frequencia e Arvore de Huffman
 *
 * @param Huffman - Arvore de Huffman
 * @param vetor - Vetor de frequencia
 * @param tam - Tamanho//Quantidade de linhas da tabela
 * @return Tabela* - Tabela de codificacao preenchida e valida
 */
Tabela *MontandoTabela(Arv *Huffman, VetChar *vetor, int tam);

/**
 * @brief Libera a memoria alocada por uma tabela de codificacao
 * 
 * @param tab - Tabela de codificacao preenchida e valida
 * @param qntd - Tamanho//Quantidade de linhas da tabela
 */
void LiberaTabela(Tabela *tab, int qntd);

/**
 * @brief Faz o calculo de quantos bits serao ocupados pelo arquivo a ser codificado
 *        dada a tabela de codificacao que será aplicada
 *
 * @param Vetor - Vetor frequencia referente ao arquivo
 * @param tab - Tabela de codificacao preenchida e valida
 * @param tam - Tamanho//Quantidade de linhas da tabela
 * @return unsigned long int - Quantidade de bits que serao utilizados apos a codificacao
 */
unsigned long int CalculaTamTotal(VetChar *Vetor, Tabela *tab, int tam);

#endif