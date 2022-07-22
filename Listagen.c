#include "Listagen.h"


/**
 * @brief Percorre a lista usando uma função de callback
 *        (função usada para imprimir a lista).
 * 
 * @param lista 
 * @param cb 
 * @param dado 
 * @return int 
 */
static int PercorreLista(Listagen* lista, int (*cb)(void*,void*),void* dado);

/**
 * @brief Sentinela da lista genérica, carrega prim e ult
 * 
 */
struct listagen
{
    Celula* prim;
    Celula* ult;
};

/**
 * @brief Célula da lista genérica, carrega o item e ponteiros
 *        para próxima celula e anterior (lista duplamente encadeada).
 * 
 */
struct celula
{
    void * item;
    Celula* prox;
    Celula* ant;
};

Listagen* IniciaListaGen(){
    Listagen* lista = (Listagen*)malloc(sizeof(Listagen));
    assert(lista);

    lista->prim = NULL;
    lista->ult = NULL;
    return lista;
}

// INSERE NO INICIO
Listagen* InsereItemGen(Listagen* lista,void* item){
    assert(lista||item);
    
    Celula* nova = (Celula*)malloc(sizeof(Celula));


    nova->item = item;

    nova->prox = lista->prim;
    nova->ant = NULL;
    
    //se não tiver nada na lista
    if(lista->prim == NULL){
        lista->prim  = nova;
        lista->ult = nova;
    }
    else {
        lista->prim = nova; //caso comum
        nova->prox->ant = nova;
    }

    return lista;
}

Listagen* RetiraDaListaGen(Listagen* lista, void* chave, int (*Comparador) (void*, void*) ){
    assert(lista||chave||Comparador);

    Celula* p;
    p = lista->prim;
    
    while (Comparador(p->item,chave))
    {
        p = p->prox;
    }
    
    if(!p){
        return lista;
    }
    
    //Unico
    if(lista->prim == p && p->prox == NULL){
        lista->prim = NULL;
        lista->ult = NULL;
        free(p);
        return lista;
    }
    //Primeiro
    else if(lista->prim == p){
        lista->prim = p->prox;
        p->prox->ant = NULL;
        free(p);
        return lista;
    }
    //Ultimo
    else if(lista->ult == p){
        p->ant->prox = NULL;
        lista->ult = p->ant;
        free(p);
        return lista;
    }
    else{
        p->ant->prox = p->prox;
        p->prox->ant = p->ant;
        free(p);
        return lista;
    }
    
}

Listagen* RetiraDaListaGenPorCel(Listagen* lista,Celula* Cel){
    assert(lista||Cel);

    if(!Cel){
        return lista;
    }
    
    //Unico
    if(lista->prim == Cel && Cel->prox == NULL){
        lista->prim = NULL;
        lista->ult = NULL;
        free(Cel);
        return lista;
    }
    //Primeiro
    else if(lista->prim == Cel){
        lista->prim = Cel->prox;
        Cel->prox->ant = NULL;
        free(Cel);
        return lista;
    }
    //Ultimo
    else if(lista->ult == Cel){
        Cel->ant->prox = NULL;
        lista->ult = Cel->ant;
        free(Cel);
        return lista;
    }
    else{
        Cel->ant->prox = Cel->prox;
        Cel->prox->ant = Cel->ant;
        free(Cel);
        return lista;
    }
    
}

void ImprimeListaGen(Listagen* lista, int (*Imprime)(void*, void*)){
    assert(lista);
    PercorreLista(lista,Imprime,NULL);
}

void LiberaListaGen(Listagen* lista, void (*Destroi)(void*)){
    assert(lista);
    Celula* p = lista->prim;
    Celula* aux;
    while (p)
    {
        aux = p->prox;
        if(Destroi)
            Destroi(p->item);
        free(p);
        p = aux;
    }
    free(lista); 
}

Listagen* ReorganizaLista(Listagen* lista, int (*MenorQ) (void*,void*)){
    assert(MenorQ);

    if(lista){
        Listagen* listaNova = IniciaListaGen();
        while(!VaziaLista(lista))
        {  
            Celula*p = lista->prim;
            Celula* aux;
            for (; p ; p = p->prox){
                aux = p->prox;
                if(MenorQ(aux,p)){
                    aux = p;
                }
            }
            InsereItemGen(listaNova,aux->item);
            RetiraDaListaGenPorCel(lista,aux);
        }

        return listaNova;
    }
    return lista;
}

int VaziaLista(Listagen* lista){
    assert(lista);
    if(lista){
        if(lista->prim == lista->ult == NULL){
            return 1;
        }
        return 0;
    }
    return 1;
}

static int PercorreLista(Listagen* lista, int (*cb)(void*,void*),void* dado){
    assert(lista);
    Celula * p = lista->prim;
    for (; p; p = p->prox){
        int r = cb(p->item,dado);
        if( r == 0){
            return r;
        }
    }
    return 1;
}

