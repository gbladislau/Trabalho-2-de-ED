#include "Codificador.h"

Arv *FazArvoreHuffman(Listagen *listabase);
void CompletaByteBitmap(bitmap *entrada);
void CodificaArq(FILE *arq, Arv *Huffman, VetChar *Vetor, FILE *saida);
static Tabela* MontandoTabela(Arv* Huffman,VetChar* vetor, int tam);

struct TabelaDeCod
{
    char * carac;
    bitmap** codigo;
};



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
    char aux2[200];
    sprintf(aux2,"./%[^.].comp",aux);

    FILE *saida = fopen(aux2, "w");

    // Faz Cabecalho
    bitmap *SaidaArvore = ExportaArvore(arvorebase);
    int tamArv = bitmapGetLength(SaidaArvore);
    fprintf(saida, "%d", tamArv);
    CompletaByteBitmap(SaidaArvore);
    fwrite(bitmapGetContents(SaidaArvore), 1, bitmapGetLength(SaidaArvore) / 8, saida);
    bitmapLibera(SaidaArvore);

    // Codificacao e saida da arvore
    CodificaArq(arquivo, arvorebase, VetorFreq, saida);

    // Liberando memoria dinamica alocada
    fclose(arquivo);
    fclose(saida);
    LiberaListaArv(lista);
    LiberaVetChar(VetorFreq);
    ArvLibera(arvorebase);

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
    int tam = QntdFolhas(Huffman);

    Tabela* tab = MontandoTabela(Huffman,Vetor,tam);

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
            while (index < tam && tab->carac[index] != aux)
            {
                index++;
            }
            codificando = tab->codigo[index];

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

    // TODO: Resolver, como saber que acabou, como informar o decoder que acabou (calcular antes o tamanho em bits e ir somando)
}

static Tabela* MontandoTabela(Arv* Huffman,VetChar* vetor,int tam){
    // Montando tabela de codificacao

    Tabela* tab = (Tabela*)malloc(sizeof(Tabela));

    int count = 0;
    
    tab->carac =(char*)malloc(tam*sizeof(char));
    tab->codigo = (bitmap**)malloc(tam*sizeof(bitmap*));
    
    
    // Preenchendo a tabela
    for (int i = 0; i < MAX_VET; i++)
    {
        if (VetGetPos(vetor, i) != 0)
        {
            tab->carac[count] = (char)i;
            tab->codigo[count] = CodificaChar(Huffman, tab->carac[count]);
            count++;
        }
    }
    return tab;
}