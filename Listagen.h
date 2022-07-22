#ifndef ListaGEN
#define ListaGEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct listagen Listagen;

typedef struct celula Celula;

/**
 * @brief Inicia a lista vazia.
 *        Pré-condição: Nenhuma.
 *        Pós-condição: Lista criada.
 *
 * @return Listagen*
 */
Listagen *IniciaListaGen();

/**
 * @brief Insere um item no inicio da lista.
 *        Pré-condição: lista e item válidos.
 *        Pós-condição: lista inserida no inicio;
 *
 * @param lista
 * @param item
 * @return Listagen*
 */
Listagen *InsereItemGen(Listagen *lista, void *item);

/**
 * @brief Retira um item da lista comparando com uma função
 *        de callback do tipo de item.
 *        Pré-condição: lista, chave e comparador existem.
 *        Pós-condição: item removido e lista encadeada corretamente.
 *
 * @param lista
 * @param chave
 * @param Comparador
 * @return Listagen*
 */
Listagen *RetiraDaListaGen(Listagen *lista, void *chave, int (*Comparador)(void *, void *));

/**
 * @brief Retira um item da lista usando um ponteiro para a Celula
 *        onde o item está incluido.
 *        Pré-condição: a célula deve ser da lista passada como parâmetro.
 *        Pós-condição: celula retirada da lista e lista encadeada corretamente.
 *
 * @param lista
 * @param Cel
 * @return Listagen*
 */
Listagen *RetiraDaListaGenPorCel(Listagen *lista, Celula *Cel);

/**
 * @brief Imprime a Lista Generica usando função de callback,
 *        função que imprime o tipo do item incluido na lista.
 *        Pré-condição: lista e função passados são válidas.
 *        Pós-condição: lista impressa no terminal.
 *
 * @param lista
 * @param Imprime
 */
void ImprimeListaGen(Listagen *lista, int (*Imprime)(void *, void *));

/**
 * @brief Libera a lista dando free também no item dela caso
 *        a função de destruir do tipo seja passada como argumento.
 *        Pré-condição: lista válida.
 *        Pós-condição: lista liberada e itens destruidos caso destroi valida
 *
 * @param lista
 * @param Destroi
 */
void LiberaListaGen(Listagen *lista, void (*Destroi)(void *));

/**
 * @brief Função para organizar a lista dependendo da função passada como argumento,
 *        (Cria uma nova lista incluindo itens da antiga na nova, de acordo com a ordem
 *         estabelecida pela função de callback).
 *        Pré-condição: Lista e função são válidas.
 *        Pós-condição: Lista organizada da forma que a função de comparar estabelecer.
 *
 * @param lista
 * @param MenorQ
 * @return Listagen*
 */
Listagen *ReorganizaLista(Listagen *lista, int (*MenorQ)(void *, void *));

/**
 * @brief Retorna 1 se a lista esta vazia, 0 caso contrário.
 *        Pré-condição: lista válida.
 *        Pré-condição: retornar 1 ou 0.
 *
 * @param lista
 * @return int
 */
int VaziaLista(Listagen *lista);

#endif