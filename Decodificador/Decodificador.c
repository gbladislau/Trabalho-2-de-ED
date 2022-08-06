#include "Decodificador.h"

Arv *PegaArvore(FILE *entrada);

FILE *CriaSaida(FILE *entrada, const char *path);

FILE *AbreEntrada(const char *arg);

void PreencheBitMapArquivo(bitmap *arv, FILE *arquivo, int qntBit);

Arv *FazArvdeBitMap(bitmap *bitmap);

int main(int argc, char const *argv[])
{
    // if (argc < 2)
    // {
    //     printf("USO: ./prog <nomedoarquivo>\n");
    //     exit(1);
    // }

    // abrindo entrada.
    // FILE *entrada = AbreEntrada(argv[1]);
    FILE *entrada = AbreEntrada("./teste.comp");
    // abrindo saida
    // FILE *saida = CriaSaida(entrada, argv[1]);
    FILE *saida = CriaSaida(entrada, "./teste.comp");

    // pegando arvore
    Arv *arvore = PegaArvore(entrada);

    ArvImprime(arvore);

    // ler arquivo e usar arvore para descoficiar
    DescodificarEntrada(entrada, arvore, saida);

    return 0;
}

FILE *AbreEntrada(const char *arg)
{
    char aux[200];
    strcpy(aux, arg);
    return fopen(aux, "r");
}

FILE *CriaSaida(FILE *entrada, const char *path)
{
    char aux[200];
    strcpy(aux, path);
    // pegando somente o nome sem a extensao .comp
    char aux2[200];
    sscanf(path, "./%[^.]", aux2);

    // pegando a extensao usada
    int ndebytes = 0;
    fscanf(entrada, "%d", &ndebytes);
    //+1 por causa do \0
    unsigned char ext[ndebytes + 1];
    // lendo extensao
    for (int i = 0; i < ndebytes; i++)
    {
        fscanf(entrada, "%c", &ext[i]);
    }

    // concatenando nome do arquivo + extensão
    unsigned char aux3[strlen(aux2) + strlen(ext) + 1];
    sprintf(aux3, "%s%s", aux2, ext);

    // abrindo
    return fopen(aux3, "w");
}

Arv *PegaArvore(FILE *entrada)
{
    // buscando quantidade de bits gasto pela codificacao da arv
    int qntDeBits;
    fscanf(entrada, "%d", &qntDeBits);
    // fread(qntDeBits,1,1,entrada);

    // iniciando bitmap com o tamanho, +7 so p debug e garantia
    bitmap *arvore = bitmapInit(qntDeBits + 7);

    PreencheBitMapArquivo(arvore, entrada, qntDeBits);
    Arv *arvoresaida = FazArvdeBitMap(arvore);
    bitmapLibera(arvore);

    return arvoresaida;
}

void PreencheBitMapArquivo(bitmap *arv, FILE *arquivo, int qntBit)
{
    unsigned char temp;

    int qntBy = qntBit / 8;
    int preenchimento = 8 - (qntBit % 8);
    if (qntBit % 8)
        qntBy++;

    int i = 0, j = 0;
    while (i < qntBy)
    {
        fread(&temp, 1, 1, arquivo);
        
        // Se nao eh o final da arvore
        if (j < qntBit - 7)
        {
            EscreveChar(arv, temp);
            j += 8;
        }
        else // Ultimo byte
        {
            unsigned int aux = (unsigned int)temp;
            unsigned int enviado = 0;
            bitmap *temporarioInvertido = bitmapInit(8);
            for (int i = 0; i < 8; i++)
            {
                bitmapAppendLeastSignificantBit(temporarioInvertido, aux % 2);
                aux = aux / 2;
            }
            for (int i = 0; i < (qntBit - j); i++)
            {
                bitmapAppendLeastSignificantBit(arv, bitmapGetBit(temporarioInvertido, 7 - i));
                enviado = enviado / 10;
            }
        }
        i++;
    }
}

void DescodificarEntrada(FILE *entrada, Arv *arvore, FILE *saida)
{
    // pega tam do arq (tam sem lixo)
    unsigned long int tamTotalBits;
    fscanf(entrada, "%ld", &tamTotalBits);

    unsigned char aux;

    int tamTotalBitsGastos = tamTotalBits;

    // tam com lixo
    while (tamTotalBitsGastos % 8)
        tamTotalBitsGastos++;

    // inicializando bitmap do arquivo
    bitmap *btmapArq = bitmapInit(tamTotalBitsGastos);
    BitIndex *arquivo = IniciaBitIndex(btmapArq);

    int counter = 0;

    while (counter != tamTotalBitsGastos / 8)
    {
        if (fread(&aux, 1, 1, entrada) == 0)
            break;

        // escreve um byte em bitmap
        EscreveChar(btmapArq, aux);
        counter++;
    }

    PercorreArvorePorBitEEscreveSaida(arquivo, arvore, &tamTotalBits, saida);

    bitmapLibera(btmapArq);
    LiberaBitIndx(arquivo);
}