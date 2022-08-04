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
    //abrindo saida
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
    // pegando somente o nome sem a extensao .comp
    char aux2[200];
    sscanf(path, "./%[^.]", aux2);

    // pegando a extensao usada
    int ndebytes = 0;
    fscanf(entrada,"%d",&ndebytes);
    //+1 por causa do \0
    char ext[ndebytes+1];
    //lendo extensao
    for (int i = 0; i < ndebytes; i++)
    {
        fscanf(entrada,"%c",ext[i]);
    }
    
    //concatenando nome do arquivo + extensão
    char aux3[strlen(aux2)+strlen(ext)];
    sprintf(aux3, "%s%s", aux2,ext);

    //abrindo
    return fopen(aux,"w");
}

Arv* PegaArvore(FILE* entrada){
    //criando arv vazia
    Arv* arvore = ArvCriaVazia();
    //buscando quantidade de bits que ela gasta
    int qntDeBits;
    fscanf(entrada,"%d",&qntDeBits);
    
    // aqui estou simplesmente pegando o numero de bytes que
    // a arvore gasta no total (multiplos de 8);
    int qntDeBitsGastos = qntDeBits;
    while (qntDeBitsGastos%8)
        qntDeBitsGastos++;
    int bytes = qntDeBitsGastos%8;

    //iniciando bitmap com o tamanho 
    bitmap* arvore = bitmapInit(qntDeBitsGastos);
    unsigned char arv[bytes+1];
    
    //catou a arvore em bytes (agora começa a parte dificil, preciso de ajuda)
    fgets(arv,bytes,entrada);
    //arvore esta totalmente armazenada no vetor de char arv
    // aqui pode tudo mudar se vc achar melhor!!
    //Falta transformar esse vetor em bitmap e depois fazer uma função recursiva
    //Para montar a arvore de acordo com cada bit(usar bitmapGetBit deve ser a solução
    // que parece ser mais viavel e eficiente)
    
    
    PreencheArvRecursivamente();
    

    return arvore;
}

void PreencheArvRecursivamente(){
    
}