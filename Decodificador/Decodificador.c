#include "Decodificador.h"

/**
 * @brief
 *
 * @param arg
 * @return FILE*
 */
FILE *AbreEntrada(char *arg);

/**
 * @brief
 *
 * @param entrada
 * @return Arv*
 */
Arv *PegaArvore(FILE *entrada);

int main(int argc, char const *argv[])
{
    // if (argc < 2)
    // {
    //     printf("USO: ./prog <nomedoarquivo>\n");
    //     exit(1);
    // }

    // abrindo entrada.
    FILE *entrada = AbreEntrada(argv[1]);
    // abrindo saida
    FILE *saida = CriaSaida(entrada, argv[1]);

    // pegando arvore
    Arv *huffman = PegaArvore(entrada);


    return 0;
}

FILE *AbreEntrada(char *arg)
{
    char aux[200];
    strcpy(aux, arg);
    return fopen(aux, "r");
}

FILE *CriaSaida(FILE *entrada, char *path)
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
        fscanf(entrada, "%c", ext[i]);
    }

    // concatenando nome do arquivo + extensão
    unsigned char aux3[strlen(aux2) + strlen(ext)];
    sprintf(aux3, "%s%s", aux2, ext);

    // abrindo
    return fopen(aux, "w");
}

Arv *PegaArvore(FILE *entrada)
{
    // buscando quantidade de bits gasto pela codificacao da arv
    int qntDeBits;
    fscanf(entrada, "%d", &qntDeBits);

    // // aqui estou simplesmente pegando o numero de bytes que
    // // a arvore gasta no total (multiplos de 8);
    // int qntDeBitsGastos = qntDeBits;
    // while (qntDeBitsGastos % 8)
    //     qntDeBitsGastos++;
    // int bytes = qntDeBitsGastos / 8;

    // iniciando bitmap com o tamanho, +7 so p debug e garantia
    bitmap *arvore = bitmapInit(qntDeBits + 7);
    unsigned char arv;

    PreencheBitMapArquivo(arv, entrada, qntDeBits);
    Arv *arvoresaida = FazArvdeBitMap(arv);

    return arvore;
}

void PreencheBitMapArquivo(bitmap *arv, FILE *arquivo, int qntBit)
{
    unsigned char temp;

    int qntBy = qntBit / 8;
    int preenchimento = 8 - (qntBit % 8);
    if (qntBit % 8)
        qntBy++;

    int i = 0, j = 0;
    while (i <= qntBy)
    {
        fread(temp, 1, 1, arquivo);
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
            for (int i = 10000000; aux != 0; i /= 10)
            {
                enviado += (aux % 2) * i;
                aux = aux / 2;
            }
            // Garantir so escrever ate o ultimo bit que de fato vale algo
            while (j < qntBit)
            {
                bitmapAppendLeastSignificantBit(arv, enviado % 10);
                enviado = enviado / 10;
            }
        }
    }
}

/*  Tipo bitmap indexado, esta aqui temporariamente para
    facilitar acesso. Ele trata um bitmap como uma pilha */
typedef struct bitIndex BitIndex;

struct bitIndex
{
    bitmap *bitmap;
    int index;
};

BitIndex *IniciaBitIndex(bitmap *bitm)
{
    BitIndex *saida = (BitIndex *)malloc(sizeof(BitIndex));
    saida->bitmap = bitm;
    saida->index = 0;
    return saida;
}

unsigned char ProxBit(BitIndex *bitmap)
{
    bitmap->index++;
    return bitmapGetBit(bitmap->bitmap, bitmap->index - 1);
}

unsigned char LeCaractere(BitIndex *base)
{
    bitmap *temp = bitmapInit(9);

    for (int i = 0; i < 8; i++)
    {
        bitmapAppendLeastSignificantBit(temp, ProxBit(base));
    }

    return bitmapGetContents(temp);
}

// N libera o bitmap dentro!
void LiberaBitIndx(BitIndex *bitmap) { free(bitmap); }

// Fim de Bitmap Indexado

//Talvez isso deveria ir para arvore
//Funcao para iniciar o loop//recursao
Arv *FazArvdeBitMap(bitmap *bitmap)
{
    BitIndex *bitindexado = IniciaBitIndex(bitmap);
    Arv *saida;

    if (ProxBit(bitindexado)) // Eh folha
    {
        saida = ArvCria(LeCaractere(bitindexado), 0,
                        ArvCriaVazia(),
                        ArvCriaVazia());
    }
    else // Eh No
    {
        saida = ArvCria(NULL, 0,
                        ArvCriaVazia(),
                        ArvCriaVazia());
        RecursividadeArvBit(bitindexado, saida);
    }
    return saida;
}

//Aqui seguira o desenhado na folha - imagem no nagazap
void RecursividadeArvBit(BitIndex *bitmap, Arv *pai)
{
}