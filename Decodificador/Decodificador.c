#include "Decodificador.h"

/**
 * @brief 
 * 
 * @param arg 
 * @return FILE* 
 */
FILE* AbreEntrada(char* arg);

/**
 * @brief 
 * 
 * @param entrada 
 * @return Arv* 
 */
Arv* PegaArvore(FILE* entrada);

int main(int argc, char const *argv[])
{
    // if (argc < 2)
    // {
    //     printf("USO: ./prog <nomedoarquivo>\n");
    //     exit(1);
    // }
    
    //abrindo entrada.
    FILE* entrada = AbreEntrada(argv[1]);
    FILE* saida = CriaSaida(entrada,argv[1]);
    
    //pegando arvore
    Arv* huffman = PegaArvore(entrada);

    return 0;
}


FILE* AbreEntrada(char* arg){
    char aux[200];
    strcpy(aux,arg);
    return fopen(aux,"r");
}

FILE* CriaSaida(FILE* entrada, char* path){
    char aux[200];
    strcpy(aux,path);

    char aux2[200];
    sscanf(path, "./%[^.]", aux2);

    int ndebytes = 0;
    fscanf(entrada,"%d",&ndebytes);
    char ext[20];
    for (int i = 0; i < ndebytes; i++)
    {
        fscanf(entrada,"%c",ext[i]);
    }
    

    char aux3[205];
    sprintf(aux3, "%s%s", aux2,ext);

    return fopen(aux,"w");
}

Arv* PegaArvore(FILE* entrada){
    Arv* arvore = ArvCriaVazia();
    int qntDeBits;
    fscanf(entrada,"%d",&qntDeBits);

    int qntDeBitsGastos = qntDeBits;
    while (qntDeBitsGastos%8)
        qntDeBitsGastos++;
    int bytes = qntDeBitsGastos%8;


    bitmap* arvore = bitmapInit(qntDeBitsGastos);
    unsigned char arv[bytes+1];
    
    //catou a arvore em bytes (agora começa a parte dificil, preciso de ajuda)
    fgets(arv,bytes,entrada);
    
    
    
    PreencheArvRecursivamente();
    

    return arvore;
}

Arv* PreencheArvRecursivamente(){
    
}