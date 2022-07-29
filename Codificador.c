#include "Codificador.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("USO: ./prog <nomedoarquivo>\n");
        exit(1);
    }

    char aux[200];
    sprintf(aux, "%s", argv[1]);

    // Faz lista de arvores
    FILE *arquivo = fopen(aux, "r");
    Listagen *lista = IniciaListaArv();
    VetChar *VetorFreq = VetCharCria(arquivo);
    PreencheLista(lista, VetorFreq);

    // Algoritmo de Huffman
    ReorganizaListaArv(lista);
    Arv *arvorebase = FazArvoreHuffman(lista);

    // debug
    ArvImprime(arvorebase);

    bitmap *SaidaArvore = ExportaArvore(arvorebase);

    return 0;
}

Arv *FazArvoreHuffman(Listagen *listabase)
{
    while (FundePrimeiros(listabase))
    {
    }
    return RetornaPrimeiro(listabase);
}

bitmap *CodificaArq(FILE *arq, Arv *Huffman, VetChar *Vetor)
{
    int tam = QntdFolhas(Huffman);
    int count = 0;
    char carac[tam];
    int codigo[tam];
    

    for (int i = 0; i < MAX_VET; i++)
    {
        if (VetGetPos(Vetor, i) != 0)
        {
            carac[count] = (char)i;
            codigo[tam] = CodificaChar(Huffman, carac[count]);
            count++;
        }
    }
}
