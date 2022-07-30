#include "Codificador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct TabelaDeCod
{
    char *carac;
    bitmap **codigo;
};

/**
 * @brief Abre o arquivo de saída com o nome do arquivo 
 *        de entrada
 * 
 * @param path 
 * @return FILE* 
 */
static FILE* AbreSaida(char path[200]);


static void LiberaCodificador(FILE* ent, FILE* saida, VetChar* vetor, Listagen* lista);

int main(int argc, char const *argv[])
{
    /*
    if (argc < 2)
    {
        printf("USO: ./prog <nomedoarquivo>\n");
        exit(1);
    }
    */

    //  Não precisa
    // strcpy(aux, argv[0]);
    // for (int i = strlen(aux); aux[i] != '/' && i > 0; i--)
    // {
    //     aux[i] = '\0';
    // }

    char path[200];
    
//    strcat(path, argv[1]);

    //DEBUG
    sprintf(path,"./teste.txt");    
    
    //Abre arquivo de entrada
    FILE *arquivo = fopen(path, "r");
    // Abre arquivo de saida//////////
    FILE* saida = AbreSaida(path);

    //Cria vetor de frequencia de char
    VetChar *VetorFreq = VetCharCria(arquivo);
    
    // Faz lista de arvores
    Listagen *lista = IniciaListaArv();
    PreencheLista(lista, VetorFreq);

    // Prepara para Algoritmo de Huffman(menor para maior)
    lista = ReorganizaListaArv(lista);
    // Precisa verificar a lista após reoganização
    // imprimir lista ;

    // Algoritmo
    Arv *arvorebase = FazArvoreHuffman(lista);

    // debug
    ArvImprime(arvorebase);

    // Faz Cabecalho 
    // Pode virar uma função? FazCabecalho();
    bitmap *SaidaArvore = ExportaArvore(arvorebase);
    int tamArv = bitmapGetLength(SaidaArvore);
    fprintf(saida, "%d", tamArv);
    CompletaByteBitmap(SaidaArvore);
    fwrite(bitmapGetContents(SaidaArvore), 1, bitmapGetLength(SaidaArvore) / 8, saida);
    bitmapLibera(SaidaArvore);

    // Codificacao e saida da arvore
    // Resto todo parece funcionar sem problemas (ALG de Huffman parece estar ok)
    // porém 
    // CODIFICA CHAR COM PROBLEMAS (HELP!!!)
    // Olhei a fundo e precisamos resolver a parte que o código não esta sendo escrito no Bitmap(dando muito errado);
    CodificaArq(arquivo, arvorebase, VetorFreq, saida);

    // Liberando memoria dinamica alocada
    //Pode virar função? LiberaCodificador()

    LiberaCodificador(arquivo,saida,VetorFreq,lista);
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

void CodificaArq(FILE *arq, Arv *Huffman, VetChar *Vetor, FILE *arqSaida)
{
    // 14MB
    bitmap *saida = bitmapInit(112000000);
    int tam = QntdFolhas(Huffman);

    Tabela *tab = MontandoTabela(Huffman, Vetor, tam);
    unsigned long int TAM_TOTAL = CalculaTamTotal(Vetor, tab, tam);
    fprintf(arqSaida, "%ld", TAM_TOTAL);

    // Codificacao do arquivo de fato
    char aux;
    int index;
    bitmap *codificando;
    while (!feof(arq))
    {
        // Ao ler um byte
        if (fread(&aux,1,1,arq))
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
            fwrite(bitmapGetContents(saida), 1, bitmapGetLength(saida) / 8, arqSaida);
            bitmapLibera(saida);
            bitmap *saida = bitmapInit(112000000);
        }
    }

    // Garantia de que caso tenha algo a ser escrito, seja escrito
    if (bitmapGetLength(saida))
    {
        CompletaByteBitmap(saida);
        fwrite(bitmapGetContents(saida), 1, bitmapGetLength(saida) / 8, arqSaida);
    }

    bitmapLibera(saida);
    LiberaTabela(tab, tam);
    rewind(arq);
}

Tabela *MontandoTabela(Arv *Huffman, VetChar *vetor, int tam)
{
    // Montando tabela de codificacao

    Tabela *tab = (Tabela *)malloc(sizeof(Tabela));

    int count = 0;

    tab->carac = (char *)malloc(tam * sizeof(char));
    tab->codigo = (bitmap **)malloc(tam * sizeof(bitmap *));

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

void LiberaTabela(Tabela *tab, int qntd)
{
    free(tab->carac);
    for (int i = 0; i < qntd; i++)
    {
        bitmapLibera(tab->codigo[i]);
    }
    free(tab);
}

unsigned long int CalculaTamTotal(VetChar *Vetor, Tabela *tab, int tam)
{
    unsigned long int TAM_TOTAL = 0;
    for (int i = 0; i < MAX_VET; i++)
    {
        if (VetGetPos(Vetor, i) != 0)
        {
            for (int j = 0; j < tam; j++)
            {
                if (tab->carac[j] == (char)i)
                {
                    TAM_TOTAL += VetGetPos(Vetor, i) * bitmapGetLength(tab->codigo[j]);
                }
            }
        }
    }
    return TAM_TOTAL;
}

static FILE* AbreSaida(char path[200]){
    char aux2[200];
    sscanf(path,"./%[^.]",aux2);
    
    char aux3[205];
    sprintf(aux3,"%s.comp",aux2);
    
    return fopen(aux3, "w");
}

static void LiberaCodificador(FILE* ent, FILE* saida, VetChar* vetor, Listagen* lista){
    fclose(ent);
    fclose(saida);
    LiberaVetChar(vetor);
    LiberaListaArv(lista);
}