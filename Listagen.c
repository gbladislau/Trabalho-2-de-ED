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
static void* RetiraDaListaGenPorCel(Listagen *lista, Celula *Cel);
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
    assert(lista || item);

    Celula *nova = (Celula *)malloc(sizeof(Celula));

    nova->item = item;

    nova->prox = lista->prim;
    nova->ant = NULL;

    // se não tiver nada na lista
    if (lista->prim == NULL)
    {
        lista->prim = nova;
        lista->ult = nova;
    }
    else
    {
        lista->prim = nova; // caso comum
        nova->prox->ant = nova;
    }

}


void* RetiraDaListaGen(Listagen *lista, void *chave, int (*Comparador)(void *, void *))
{
    assert(lista || chave || Comparador);

    Celula *p;
    p = lista->prim;

    while (p && Comparador(p->item, chave) == 0)
    {
        p = p->prox;
    }

    if(!p){
        return NULL;
    }
    void* item = p->item;
    // Unico
    if (lista->prim == p && p->prox == NULL)
    {
        lista->prim = NULL;
        lista->ult = NULL;
        free(p);
    }
    // Primeiro
    else if (lista->prim == p)
    {
        lista->prim = p->prox;
        p->prox->ant = NULL;
        free(p);
    }
    // Ultimo
    else if (lista->ult == p)
    {
        p->ant->prox = NULL;
        lista->ult = p->ant;
        free(p);
    }
    else
    {
        p->ant->prox = p->prox;
        p->prox->ant = p->ant;
        free(p);
    }
    return item;
}

static void* RetiraDaListaGenPorCel(Listagen *lista, Celula *Cel)
{
    assert(lista || Cel);

    void* item = Cel->item;
    // Unico
    if (lista->prim == Cel && Cel->prox == NULL)
    {
        lista->prim = NULL;
        lista->ult = NULL;
        free(Cel);
       
    }
    // Primeiro
    else if (lista->prim == Cel)
    {
        lista->prim = Cel->prox;
        Cel->prox->ant = NULL;
        free(Cel);
    }
    // Ultimo
    else if (lista->ult == Cel)
    {
        Cel->ant->prox = NULL;
        lista->ult = Cel->ant;
        free(Cel);
    }
    else
    {
        Cel->ant->prox = Cel->prox;
        Cel->prox->ant = Cel->ant;
        free(Cel);
    }
    return item;
}

void ImprimeListaGen(Listagen *lista, int (*Imprime)(void *))
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
            Celula *aux;
            for (; p; p = p->prox)
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
        if (lista->prim == lista->ult == NULL)
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
        if(lista->prim == lista->ult){
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
    //encadeando
    if(lista->ult) 
       lista->ult->prox = nova;
    //lista vazia
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
//Compara entre arvore e char
void * BuscaLista(Listagen* lista, int (*Compara)(void*, void*), void* chave){
    Celula* p = lista->prim;
    while (!Compara(p->item,chave) && p)
    {
        p = p->prox;
    }
    if(p)
        return p->item;
    else
        return NULL;
}