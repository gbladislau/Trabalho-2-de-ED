#include "Codificador.h"

Arv *FazArvoreHuffman(Listagen *listabase);
void CompletaByteBitmap(bitmap *entrada);
void CodificaArq(FILE *arq, Arv *Huffman, VetChar *Vetor, FILE *saida);

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

    // Abre arquivo de saida
    // TODO: Arquivo de saida entra aqui, como vai entrar e pah
    FILE *saida = fopen(, "w");

    // Faz Cabecalho
    bitmap *SaidaArvore = ExportaArvore(arvorebase);
    int tamArv = bitmapGetLength(SaidaArvore);
    fprintf(saida, "%d", tamArv);
    CompletaByteBitmap(SaidaArvore);
    fwrite(bitmapGetContents(SaidaArvore), 1, bitmapGetLength(SaidaArvore) / 8, saida);
    bitmapLibera(SaidaArvore);

    // Codificacao e saida da arvore
    CodificaArq(arquivo, arvorebase, lista, saida);

    // Liberando memoria dinamica alocada
    fclose(arquivo);
    fclose(saida);
    LiberaListaArv(lista);
    LiberaVetChar(VetorFreq);

    return 0;
}

// Lembrar na hora de ler que a arvore vai comecar em um byte certinho, ou seja,
// q foi compensado aqui diferencas no tamanho da arvore
void CompletaByteBitmap(bitmap *entrada)
{
    while (bitmapGetLength(entrada) % 8)
    {
        bitmapAppendLeastSignificantBit(entrada, 0);
    }
}

Arv *FazArvoreHuffman(Listagen *listabase)
{
    while (FundePrimeiros(listabase))
    {
    }
    return RetornaPrimeiro(listabase);
}

void CodificaArq(FILE *arq, Arv *Huffman, VetChar *Vetor, FILE *saida)
{
    // 14MB
    bitmap *saida = bitmapInit(112000000);

    // Montando tabela de codificacao
    int tam = QntdFolhas(Huffman);
    int count = 0;
    char carac[tam];
    bitmap *codigo[tam];

    // Preenchendo a tabela
    for (int i = 0; i < MAX_VET; i++)
    {
        if (VetGetPos(Vetor, i) != 0)
        {
            carac[count] = (char)i;
            codigo[tam] = CodificaChar(Huffman, carac[count]);
            count++;
        }
    }

    // Codificacao do arquivo de fato
    char aux;
    int index;
    bitmap *codificando;
    while (!feof(arq))
    {
        // Ao ler um byte
        if (fscanf(arq, "%1[]", aux))
        {
            // Procura o mesmo na tabela
            index = 0;
            while (index < tam && carac[index] != aux)
            {
                index++;
            }
            codificando = codigo[index];

            // Escreve no bitmap de saida o codigo do mesmo
            for (int i = 0; i < bitmapGetLength(codificando); i++)
            {
                bitmapAppendLeastSignificantBit(saida,
                                                bitmapGetBit(codificando, i));
            }
        }

        // Escreve em disco caso buffer esteja maior que 7MB (50%) e tenha bytes completos
        if (bitmapGetLength(saida) > 56000000 && (bitmapGetLength(saida) % 8) == 0)
        {
            fwrite(bitmapGetContents(saida), 1, bitmapGetLength(saida) / 8, saida);
            bitmapLibera(saida);
            bitmap *saida = bitmapInit(112000000);
        }
    }

    // Garantia de que caso tenha algo a ser escrito, seja escrito
    if (bitmapGetLength(saida))
    {
        CompletaByteBitmap(saida);
        fwrite(bitmapGetContents(saida), 1, bitmapGetLength(saida) / 8, saida);
        bitmapLibera(saida);
    }

    // TODO: Resolver, como saber que acabou, como informar o decoder que acabou
}