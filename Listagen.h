#ifndef ListaGEN
#define ListaGEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct listagen Listagen;

/**
 * @brief Inicia a lista vazia.
 *        Pré-condição: Nenhuma.
 * 
 * @return Listagen* 
 */
Listagen* IniciaListaGen();

/**
 * @brief Insere um item no inicio da lista.
 *        Pré-condição: lista e item válidos.
 * 
 * @param lista 
 * @param item 
 * @return Listagen* 
 */
Listagen* InsereItemGen(Listagen* lista,void* item);

/**
 * @brief Retira um item da lista comparando com uma função 
 *        de callback do tipo de item.
 *        Pré-condição: lista, chave e comparador existem.
 * 
 * @param lista 
 * @param chave 
 * @param Comparador 
 * @return Listagen* 
 */
Listagen* RetiraDaListaGen(Listagen* lista, void* chave, int (*Comparador) (void*, void*) );

/**
 * @brief Retira um item da lista usando um ponteiro para a Celula
 *        onde o item está incluido.
 *        Pré-condição: a célula deve ser da lista passada como parâmetro.
 * 
 * @param lista 
 * @param Cel 
 * @return Listagen* 
 */
Listagen* RetiraDaListaGenPorCel(Listagen* lista,Celula* Cel);

/**
 * @brief Imprime a Lista Generica usando função de callback,
 *        função que imprime o tipo do item incluido na lista.
 *        Pré-condição: lista e função passados são válidas.
 * 
 * @param lista 
 * @param Imprime 
 */
void ImprimeListaGen(Listagen* lista, int (*Imprime)(void*, void*));

/**
 * @brief Libera a lista dando free também no item dela caso
 *        a função de destruir do tipo seja passada como argumento.
 *        Pré-condição: lista válida.
 * 
 * @param lista 
 * @param Destroi 
 */
void LiberaListaGen(Listagen* lista, void (*Destroi)(void*));

/**
 * @brief Função para organizar a lista dependendo da função passada como argumento,
 *        (Cria uma nova lista incluindo itens da antiga na nova, de acordo com a ordem
 *         estabelecida pela função de callback).
 *        Pré-condição: Lista e função são válidas.
 * 
 * @param lista 
 * @param MenorQ 
 * @return Listagen* 
 */
Listagen* ReorganizaLista(Listagen* lista, int (*MenorQ) (void*,void*));

/**
 * @brief Retorna 1 se a lista esta vazia, 0 caso contrário.
 *        Pré-condição: lista válida.
 *  
 * @param lista 
 * @return int 
 */
int VaziaLista(Listagen* lista);

#endif