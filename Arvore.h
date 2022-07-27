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
 *
 * @param letra - Letra válida
 * @param peso - Peso válido
 * @param esq - Arvore válida
 * @param dir - Arvore válida
 * @return Arv* - Arvore criada com os parametros passados
 */
Arv *ArvCria(char letra, int peso, Arv *esq, Arv *dir);

/**
 * @brief Função para liberar todo o espaço ocupado pela
 *        árvore a, libera também suas raizes.
 *
 * @param a - Arvore valida
 * @return Arv* - Arvore totalmente liberada
 */
Arv *ArvLibera(Arv *a);

/**
 * @brief Função que retorna 1 se a árvore está vazia.
 *
 * @param a - Arvore existe
 * @return int - 1 caso vazia
 */
int ArvVazia(Arv *a);

/**
 * @brief Função que imprime a arvore a,
 *        em pré-ordem.
 *
 * @param a - Arvore válida
 */
void ArvImprime(Arv *a);

/**
 * @brief Procura o pai do nó que contém o caractere c.
 *
 * @param a - Arvore válida
 * @param c - Caractere válido
 * @return Arv*
 */
Arv *ArvPai(Arv *a, char c);

/**
 * @brief Retorna a quantidade de folhas de certa árvore.
 *
 * @param a - arvore valida
 * @return int - valor exato de folhas
 */
int QntdFolhas(Arv *a);

/**
 * @brief Retorna o caractere da árvore caso seja diferente de NULL
 *        Pré-condição: arvore conter um char.
 *        Pós-condição: retornar char.
 *
 * @param a - arvore valida
 * @return char* - caractere contido na arvore
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
 *
 * @param a - arvore valida
 * @return int - altura exata da arvore
 */
int ArvAltura(Arv *a);

/**
 * @brief Retorna o bitmap referente a arvore de codificacao
 *        seguindo a travessia de pre-ordem e bit de identificacao
 *        para folhas e nós.
 *
 * @param a - Arvore valida
 * @return bitmap* - Bitmap com a arvore
 */
bitmap *ExportaArvore(Arv *a);

//Retirar depois, esta aqui para teste na main
void EscreveChar(bitmap *mapa, char letrona);

#endif /* arvore_h */