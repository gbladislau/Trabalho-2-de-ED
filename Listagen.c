#include "Listagen.h"
#include <assert.h>

typedef struct celula Celula;

/**
 * @brief Sentinela da lista genérica, carrega prim e ult
 *
 */
struct listagen
{
    Celula *prim;
    Celula *ult;
};

/**
 * @brief Célula da lista genérica, carrega o item e ponteiros
 *        para próxima celula e anterior (lista duplamente encadeada).
 *
 */
struct celula
{
    void *item;
    Celula *prox;
    Celula *ant;
};

//---------------------------- Funções Privadas --------------------------------------------------------------------//
/**
 * @brief Retira um item da lista usando um ponteiro para a Celula
 *        onde o item está incluido.
 *
 * @param lista - Lista válida
 * @param Cel - Celula válida e incluida na lista
 * @return void * - Item da celula removida
 */
static void *RetiraDaListaGenPorCel(Listagen *lista, Celula *Cel);
//---------------------------------------------------------------------------------------------------------------------//

Listagen *IniciaListaGen()
{
    Listagen *lista = (Listagen *)malloc(sizeof(Listagen));
    assert(lista);

    lista->prim = NULL;
    lista->ult = NULL;
    return lista;
}

// INSERE NO INICIO
void InsereItemGen(Listagen *lista, void *item)
{
    assert(lista&& item);

    Celula* nova = (Celula*)malloc(sizeof(Celula));
    assert(nova != NULL);
    
    nova->ant = lista->ult;

    if(lista->ult)
        lista->ult->prox = nova;
    if(!lista->prim)
        lista->prim = nova;
    
    lista->ult = nova;
    nova->prox = NULL;
    nova->item = item;
}

void *RetiraDaListaGen(Listagen *lista, void *chave, int (*Comparador)(void *, void *))
{
    assert(lista || chave || Comparador);

    Celula *aux;
    aux = lista->prim;

    while (aux && Comparador(aux->item, chave) == 0)
    {
        aux = aux->prox;
    }

    if (!aux)
    {
        return NULL;
    }
    void *item = aux->item;

    //lista vazia
    if(aux == NULL) return NULL;

    if(aux == lista->prim){
        //unico da lista
        if(aux == lista->ult){
            free(aux);
            lista->prim = NULL;
            lista->ult = NULL;
        }
        //primeiro da lista
        else{
            aux->prox->ant = NULL;
            lista->prim = aux->prox;
            free(aux);
        }
    }
    //ultimo da lista
    else if(aux == lista->ult){
        aux->ant->prox = NULL;
        lista->ult = aux->ant;
        free(aux);
    }
    // meio da lista
    else{
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        free(aux);
    }

    return item;
}

static void *RetiraDaListaGenPorCel(Listagen *lista, Celula *aux)
{
    assert(lista);
    assert(aux);

    void *item = aux->item;

    //lista vazia
    if(aux == NULL) return NULL;

    if(aux == lista->prim){
        //unico da lista
        if(aux == lista->ult){
            free(aux);
            lista->prim = NULL;
            lista->ult = NULL;
        }
        //primeiro da lista
        else{
            aux->prox->ant = NULL;
            lista->prim = aux->prox;
            free(aux);
        }
    }
    //ultimo da lista
    else if(aux == lista->ult){
        aux->ant->prox = NULL;
        lista->ult = aux->ant;
        free(aux);
    }
    // meio da lista
    else{
        aux->ant->prox = aux->prox;
        if(aux->prox)
            aux->prox->ant = aux->ant;
        free(aux);
    }

    return item;
    
}

void ImprimeListaGen(Listagen *lista, void (*Imprime)(void *))
{
    assert(lista);
    if (lista->prim == NULL)
        return;
    else
    {
        Celula *aux;
        aux = lista->prim;
        while (aux != NULL)
        {
            Imprime(aux->item);
            aux = aux->prox;
        }
    }
    printf("\n");
}

// Pq destruir os itens aqui? (R)
//(Se destroi é NULL eles não são destruidos) (GB)
void LiberaListaGen(Listagen *lista, void (*Destroi)(void *))
{
    assert(lista);
    Celula *p = lista->prim;
    Celula *aux;
    while (p)
    {
        aux = p->prox;
        if (Destroi)
            Destroi(p->item);
        free(p);
        p = aux;
    }
    free(lista);
}

Listagen *ReorganizaLista(Listagen *lista, int (*MenorQ)(void *, void *))
{
    assert(MenorQ);

    if (lista)
    {
        Listagen *listaNova = IniciaListaGen();
        while (!VaziaLista(lista))
        {
            Celula *p = lista->prim;
            Celula *aux = p;
            for (; p && p->prox; p = p->prox)
            {
                 aux = p->prox;
                if (MenorQ(aux, p))
                {
                    aux = p;
                }
            }
            InsereItemGen(listaNova, aux->item);
            RetiraDaListaGenPorCel(lista, aux);
        }

        return listaNova;
    }
    return lista;
}

int VaziaLista(Listagen *lista)
{
    assert(lista);
    if (lista)
    {
        if (lista->prim == lista->ult && lista->prim == NULL)
        {
            return 1;
        }
        return 0;
    }
    return 1;
}

int PercorreLista(Listagen *lista, int (*cb)(void *))
{
    assert(lista);
    Celula *p = lista->prim;
    for (; p; p = p->prox)
    {
        int r = cb(p->item);
        if (r == 0)
            return r;
    }
    return 1;
}

// Funcoes de grande utilidade p uso de pilha

void *RetiraPrimeiro(Listagen *lista)
{
    assert(lista);
    void *aux;

    if (lista->prim)
    {
        if (lista->prim == lista->ult)
        {
            lista->ult = lista->prim->prox;
        }
        aux = lista->prim->item;
        Celula *liberar = lista->prim;
        lista->prim = lista->prim->prox;

        free(liberar);
        return aux;
    }
    else
        return NULL;
}

// INSERE NO FINAL
void InsereUltItemGen(Listagen *lista, void *item)
{
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->item = item;
    nova->prox = NULL;
    nova->ant = lista->ult;
    // encadeando
    if (lista->ult)
        lista->ult->prox = nova;
    // lista vazia
    if (lista->prim == NULL)
        lista->prim = nova;

    lista->ult = nova;
}

void *RetornaPrimeiro(Listagen *lista)
{
    if (lista->prim)
        return lista->prim->item;
    else
        return NULL;
}

void *RetornaUlt(Listagen *lista)
{
    if (lista->ult)
        return lista->ult->item;
    else
        return NULL;
}
// Compara entre arvore e char
void *BuscaLista(Listagen *lista, int (*Compara)(void *, void *), void *chave)
{
    Celula *p = lista->prim;
    while (!Compara(p->item, chave) && p)
    {
        p = p->prox;
    }
    if (p)
        return p->item;
    else
        return NULL;
}