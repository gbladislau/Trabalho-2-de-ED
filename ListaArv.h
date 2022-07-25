#ifndef ListaARV
#define ListaARV
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listagen.h"
#include "Arvore.h"

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

// TODO: Comparar qual sera de maior utilidade
void RetiraListaArvPeso(Listagen *lista, int Peso);
void RetiraListaArvPeso(Listagen *lista, char letra);

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
 */
void ReorganizaListaArv(Listagen *lista);

// TODO: Qnd for discutido a necessidade do segundo argumento

/**
 * @brief Percorre a lista de arvores executando a funcao
 *        fornecida para cada elemento presente na lista
 *
 * @param lista - Lista de arvores valida
 * @param func - Funcao a ser executada
 * @return int - Sucesso (1), falha (0)
 */
int PercorreListaArv(Listagen *lista, void(func)(Arv *));

/**
 * @brief Retira as duas primeiras arvores da lista, cria um no raiz
 *        com o peso = soma dos pesos, insere o no no final da lista
 *
 * @param lista - Lista de arvores valida
 * @return int - Sucesso (1), falha (0)
 */
int FundePrimeiros(Listagen *lista);

#endif