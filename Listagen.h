#ifndef ListaGEN
#define ListaGEN
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listagen Listagen;

/**
 * @brief Inicia a lista vazia.
 *        Pré-condição: Nenhuma.
 *        Pós-condição: Lista criada.
 *
 * @return Listagen* - Lista alocada
 */
Listagen *IniciaListaGen();

/**
 * @brief Insere um item no inicio da lista.
 *        Pré-condição: lista e item válidos.
 *        Pós-condição: lista inserida no inicio;
 *
 * @param lista - Lista válida
 * @param item - Item Válido
 * @return void
 */
void InsereItemGen(Listagen *lista, void *item);

/**
 * @brief Retira um item da lista comparando com uma função
 *        de callback do tipo de item.
 * 
 * @param lista - lista válida
 * @param chave - chave válida
 * @param Comparador - Função Valida
 * @return void * - Item da Célula removida
 */
void *RetiraDaListaGen(Listagen *lista, void *chave, int (*Comparador)(void *, void *));

/**
 * @brief Imprime a Lista Generica usando função de callback,
 *        função que imprime o tipo do item incluido na lista.
 *        Pré-condição: lista e função passados são válidas.
 *        Pós-condição: lista impressa no terminal.
 *
 * @param lista
 * @param Imprime
 */
void ImprimeListaGen(Listagen *lista, int (*Imprime)(void *));

/**
 * @brief Libera a lista dando free também no item dela caso
 *        a função de destruir do tipo seja passada como argumento.
 *
 * @param lista - Lista válida
 * @param Destroi 
 */
void LiberaListaGen(Listagen *lista, void (*Destroi)(void *));

/**
 * @brief Função para organizar a lista dependendo da função passada como
 *        argumento, (Cria uma nova lista incluindo itens da antiga na nova, de acordo
 *        com a ordem estabelecida pela função de callback).
 *
 * @param lista - Lista válida
 * @param MenorQ - Função válida
 * @return Listagen* -Lista organizada
 */
Listagen *ReorganizaLista(Listagen *lista, int (*MenorQ)(void *, void *));

/**
 * @brief Retorna 1 se a lista esta vazia, 0 caso contrário.
 *
 * @param lista - Lista válida
 * @return int - 1 se vazia
 */
int VaziaLista(Listagen *lista);

/**
 * @brief Percorre a lista executando a funcao passada como parametro, tendo
 *        como segundo argumento da funcao o dado passado
 *
 * @param lista - Lista valida
 * @param cb - Funcao a ser executada
 * @param dado - Dado a ser passado a funcao
 * @return int
 */
int PercorreLista(Listagen *lista, int (*cb)(void *));

/**
 * @brief Retorna item presente no primeiro elemento da lista
 * 
 * @param lista - Lista valida
 * @return void* - Elemento presente no primeiro elemento
 */
void *RetornaPrimeiro(Listagen *lista);

/**
 * @brief Retorna item presente no ultimo elemento da lista
 * 
 * @param lista - Lista valida
 * @return void* - Elemento presente no ultimo elemento
 */
void *RetornaUlt(Listagen *lista);

// Funcoes de grande utilidade p uso de pilha

/**
 * @brief Retira o primeiro item da lista, retornando o objeto ligado a ele
 *
 * @param lista - Lista valida
 * @return void* - Objeto presente na lista//Null caso vazia
 */
void *RetiraPrimeiro(Listagen *lista);

/**
 * @brief Insere um item no final da lista.
 *
 * @param lista - lista e item válidos.
 * @param item - lista com item inserido no final
 */
void InsereUltItemGen(Listagen *lista, void *item);

#endif