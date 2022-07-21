#include "Arvore.h"


//-------------------------------- Struct ----------------------------------------------//

/**
 * @brief Estrutura da Arvore que carega o peso do 
 *        caractere e o próprio caractere para implementação 
 *        do Algoritimo de Huffman.
 */
struct arv
{
    char letra;
    int peso;
    Arv* esq;
    Arv* dir;
};

//----------------------------------- Funções Privadas ----------------------------------//

/**
 * @brief Retorna max entre dois numeros inteiros.
 * 
 * @param a 
 * @param b 
 * @return int 
 */
static int max (int a, int b);

//------------------------------------ Funções Publicas ----------------------------------//

Arv* ArvCriaVazia (void){
    return NULL;
}

Arv* ArvCria (char letra, int peso , Arv* esq, Arv* dir){
    Arv* nova = (Arv*)malloc(sizeof(Arv));
    
    nova->peso = peso;
    nova->dir = dir;
    nova->esq = esq;

    return nova;
}

Arv* ArvLibera (Arv* a){
    if(a != NULL){
        ArvLibera(a->dir);
        ArvLibera(a->esq);
        free(a);
    }
}

int ArvVazia (Arv* a){
    if(!a) return 1;
    else return 0;
}

void ArvImprime (Arv* a){
    if(a){
        if(a->letra)
            printf("%c");
        printf("%d",a->peso);
        ArvImprime(a->esq);
        ArvImprime(a->dir);
    }
}

Arv* ArvPai (Arv* a, char c){
    if(a){
        if( a->esq && ArvChar(a->esq) == c){
            return a;
        }
        else if( a->dir && ArvChar(a->dir) == c){
            return a;
        }
        else{
            return(ArvPai(a->dir,c) ? ArvPai(a->dir,c) : ArvPai(a->esq,c));
        }
    }
    return NULL;
}

int QntdFolhas (Arv* a){
    if(!a){
        return 0;
    }
    if(a){
        int i = 0;
        if(ArvVazia(a->esq) && ArvVazia(a->dir)) i = 1;
        return(QntdFolhas(a->esq)+QntdFolhas(a->dir)+i);
    }
}

char ArvChar (Arv* a){
    return a->letra;
}

int ArvAltura (Arv* a){
    if (ArvVazia(a))
        return -1;
    else
        return 1 + max(ArvAltura(a->esq), ArvAltura(a->dir));
}

static int max (int a, int b){
    return (a > b) ? a : b;
}
