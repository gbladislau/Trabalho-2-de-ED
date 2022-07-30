#ifndef ListaARV
#define ListaARV
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listagen.h"
#include "Arvore.h"
#include "Vetchar.h"

/**
 * @brief Inicializa lista de Arvores
 *
 * @return Listagen* - Lista de arvores inicializada
 */
Listagen *IniciaListaArv();

/**
 * @brief Insere arvore na lista passada
 *
 * @param lista - Lista de arvores valida
 * @param inserida - Arvore a ser inserida
 */
void InsereListaArv(Listagen *lista, Arv *inserida);

/**
 * @brief Retira a arvore da lista usando como chave de busca o peso
 *
 * @param lista - Lista valida
 * @param Peso - Peso buscado
 */
void RetiraListaArvPeso(Listagen *lista, int Peso);

/**
 * @brief Retira a arvore da lista usando como chave de busca a letra
 *
 * @param lista - Lista valida
 * @param letra - Letra buscada
 */
void RetiraListaArvLetra(Listagen *lista, char letra);

/**
 * @brief Imprime a lista de arvores
 *
 * @param lista - Lista de arvores valida
 */
void ImprimeListaArv(Listagen *lista);

/**
 * @brief Reorganiza lista baseada em peso
 *
 * @param lista - Lista de arvores valida
 * @return Listagen* - Lista organizada
 */
Listagen* ReorganizaListaArv(Listagen *lista);

/**
 * @brief Percorre a lista de arvores executando a funcao
 *        fornecida para cada elemento presente na lista
 *
 * @param lista - Lista de arvores valida
 * @param func - Funcao a ser executada
 * @return int - Sucesso (1), falha (0)
 */
int PercorreListaArv(Listagen *lista, int (*func)(void *));

/**
 * @brief Retira as duas primeiras arvores da lista, cria um no raiz
 *        com o peso = soma dos pesos, insere o no no final da lista
 *
 * @param lista - Lista de arvores valida
 * @return int - Sucesso (1), falha (0)
 */
int FundePrimeiros(Listagen *lista);

/**
 * @brief Preenche a lista de arvores com os dados presentes no arquivo 
 *        passado como parametro
 * 
 * @param lista - Lista de arvores inicializada e valida
 * @param base  - Arquivo valido
 */
void PreencheLista(Listagen *lista, VetChar *VetTemp);

/**
 * @brief Faz a liberacao da lista de Arvores, liberando suas arvores
 *
 * @param lista - Lista valida
 */
void LiberaListaArv(Listagen *lista);

/**
 * @brief Preenche a lista de arvores com os dados presentes no vetor
 *
 * @param lista - Lista de arvores valida
 * @param vetor - VetorChar valido preenchido
 */
void ConverteVetorALista(Listagen *lista, VetChar *vetor);

Arv* BuscaArvChar(Listagen* lista, char c);

// Listagen* CopiaLista(Listagen* origem);

#endif
