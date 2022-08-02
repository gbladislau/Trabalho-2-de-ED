#include "Decodificador.h"

FILE* AbreEntrada(char* arg);

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