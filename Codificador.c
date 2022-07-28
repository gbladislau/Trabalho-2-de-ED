#include "Codificador.h"

int main(int argc, char const *argv[])
{
    if(argc<2){
        printf("USO: ./prog <nomedoarquivo>\n");
        exit(1);
    }
  
    char aux[200];
    sprintf(aux,"%s",argv[1]);

    FILE* arquivo = fopen(aux,"r");
    VetChar* vet = VetCharCria(arquivo);
    Listagen* lista = IniciaListaArv();

    PreencheLista(lista,vet,arquivo);
    ReorganizaListaArv(lista);


    return 0;
}
