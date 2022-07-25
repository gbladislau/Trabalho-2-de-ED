#ifndef arvore_h
#define arvore_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "bitmap.h"

typedef struct arv Arv;

/**
 * @brief Cria arv Vazia.
 *
 * @return Arv* (NULL)
 */
Arv *ArvCriaVazia();

/**
 * @brief Função para criar Arvore, aqui podemos adicionar
 *        um caractere e seu peso correspodente na contagem
 *        do Algoritimo de Huffman.
 *        Pré-condição: letra, peso e filhos válidos.
 *        Pós-condição: Arvore criada.
 *
 * @param letra
 * @param peso
 * @param esq
 * @param dir
 * @return Arv*
 */
Arv *ArvCria(char letra, int peso, Arv *esq, Arv *dir);

/**
 * @brief Função para liberar todo o espaço ocupado pela
 *        árvore a, libera também suas raizes.
 *        Pré-condição: Arvore existe.
 *        Pós-condição: Arvore totalmente liberada.
 *
 * @param a
 * @return Arv*
 */
Arv *ArvLibera(Arv *a);

/**
 * @brief Função que retorna 1 se a árvore está vazia.
 *        Pré-condição: Arvore existe.
 *        Pós-condição: Return 1 or 0.
 *
 * @param a
 * @return int
 */
int ArvVazia(Arv *a);

/**
 * @brief Função que imprime a arvore a,
 *        em pré-ordem.
 *        Pré-condição: Arvore existe.
 *        Pós-condição: Arvore impressa na saida padrão.
 *
 * @param a
 */
void ArvImprime(Arv *a);

/**
 * @brief Procura o pai do nó que contém o caractere c.
 *        Pré-condição: a e c existem.
 *        Pós-condição: retornar a arvore pai
 *
 * @param a
 * @param c
 * @return Arv*
 */
Arv *ArvPai(Arv *a, char c);

/**
 * @brief Retorna a quantidade de folhas de certa árvore.
 *        Pré-condição: arv existe
 *        Pós-condição: retornar valor exato de folhas.
 *
 * @param a
 * @return int
 */
int QntdFolhas(Arv *a);

/**
 * @brief Retorna o caractere da árvore caso seja diferente de NULL
 *        Pré-condição: arvore conter um char.
 *        Pós-condição: retornar char.
 *
 * @param a
 * @return char*
 */
char ArvChar(Arv *a);

/**
 * @brief Retorna o peso da árvore caso seja diferente de NULL
 * 
 * @param a - Arvore valida
 * @return int - Peso referente a arvore fornecida
 */
int ArvPeso(Arv *a);

/**
 * @brief Retorna altura da arvore a.
 *        Pré-condição: arvore valida.
 *        Pós-condição: retornar altura exata.
 *
 * @param a
 * @return int
 */
int ArvAltura(Arv *a);

//TODO:
/**
 * @brief Retorna o bitmap referente a arvore de codificacao
 *        seguindo a travessia de pre-ordem e bit de identificacao
 *        para folhas e nos
 *        Pre-condicao: arvore valida
 *        Pos-condicao: retornar bitmap com arvore codificada
 * 
 * @param a 
 * @return bitmap* 
 */
bitmap *ExportaArvore(Arv *a);

#endif /* arvore_h */