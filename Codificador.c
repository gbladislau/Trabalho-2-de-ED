#include "Codificador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Tabela que carrega os caracteres e seus
 *        respectivos códigos em bitmap;
 * 
 */
struct TabelaDeCod
{
    char *carac;
    bitmap **codigo;
};
//------------------------- Funções Privadas ----------------------------------------//
/**
 * @brief Abre o arquivo de saída com o nome do arquivo
 *        de entrada
 *
 * @param path - local do arquivo
 * @return FILE* - saida (<nome>.comp)
 */
static FILE *AbreSaida(char path[200]);

/**
 * @brief 
 * 
 * @param path - local e nome do arq. de entrada
 * @param saida  - arq de saida
 */
static void ColocaExtensaoNaSaida(char path[200], FILE* saida);

/**
 * @brief Monta o cabeçalho do arquivo comprimido
 * 
 * @param arvorebase - arvore de huffman 
 * @param saida - arquivo de saida
 */
static void ColocaArvoreNaSaida(Arv* arvorebase, FILE* saida);

/**
 * @brief Libera a memoria dinamicamente alocada
 * 
 * @param ent - arquivo de entrada
 * @param saida - arquivo de saida
 * @param vetor - vetor de frenquencia de char
 * @param lista - lista de arvore que carrega a arvore de huffman
 */
static void LiberaCodificador(FILE *ent, FILE *saida, VetChar *vetor, Listagen *lista);
//------------------------- Funções Privadas -------------------------------------------//

int main(int argc, char const *argv[])
{
    
    // if (argc < 2)
    // {
    //     printf("USO: ./prog <nomedoarquivo>\n");
    //     exit(1);
    // }
    

    char path[200];
   // strcpy(path,argv[1]);

    // DEBUG
    sprintf(path, "./teste.txt");

    // Abre arquivo de entrada
    FILE *arquivo = fopen(path, "r");
    // Abre arquivo de saida//////////
    FILE *saida = AbreSaida(path);
    
    ColocaExtensaoNaSaida(path,saida);

    // Cria vetor de frequencia de char
    VetChar *VetorFreq = VetCharCria(arquivo);

    // Faz lista de arvores
    Listagen *lista = IniciaListaArv();
    PreencheLista(lista, VetorFreq);

    // Prepara para Algoritmo de Huffman(menor para maior)
    lista = ReorganizaListaArv(lista);

    // Algoritmo
    Arv *arvorebase = FazArvoreHuffman(lista);

    // debug
    ArvImprime(arvorebase);

    //Faz o cabeçalho do arquivo de saida
    //ARVORE EXPORTADA COM SUCESSO, ATENÇÂO NA HORA DE LER (gastou 2 bytes para escrever o tamanho(19) com o teste = oi)
    ColocaArvoreNaSaida(arvorebase,saida);

    // Codifica o arquivo de acordo com a arvore de huffman
    CodificaArq(arquivo, arvorebase, VetorFreq, saida);

    // Liberando memoria dinamica alocada
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
    // Tabela está funcionando por enquanto
    // Escreve o tamanho total do arquivo - Subcabecalho do arquivo
    unsigned long int TAM_TOTAL = CalculaTamTotal(Vetor, tab, tam);
    fprintf(arqSaida, "%ld", TAM_TOTAL);

    // Codificacao do arquivo de fato
    char aux;
    int index;
    bitmap *codificando;
    while (!feof(arq))
    {
        // Ao ler um byte

        ///////////////////////////////////////////////////////////////////////////////////////////////////// 
        //////////////// ERRO: não lê ç Ç Á á ////// solução mudar char aux para unsigned int (tem q mudar la em cima tbm)/
        if (fread(&aux, 1, 1, arq))
        {
            // Procura o mesmo na tabela(precisa??????)
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
        // completa o resto do byte com 0's
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
            // para cada caracter existente no arquivo de saida um código é criado aqui
            // o i representa o caracter no vetor de frequencia
            tab->carac[count] = (char)i;
            tab->codigo[count] = CodificaChar(Huffman, tab->carac[count]);
            count++;
        }
    }
    return tab;
}

void LiberaTabela(Tabela *tab, int qntd)
{
    for (int i = 0; i < qntd; i++)
    {
        bitmapLibera(tab->codigo[i]);
    }
    free(tab->codigo);
    free(tab->carac);
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

static FILE *AbreSaida(char path[200])
{
    char aux2[200];
    sscanf(path, "./%[^.]", aux2);

    char aux3[205];
    sprintf(aux3, "%s.comp", aux2);

    return fopen(aux3, "w");
}

static void LiberaCodificador(FILE *ent, FILE *saida, VetChar *vetor, Listagen *lista)
{
    fclose(ent);
    fclose(saida);
    LiberaVetChar(vetor);
    LiberaListaArv(lista);
}

static void ColocaArvoreNaSaida(Arv* arvorebase, FILE* saida){
    bitmap *SaidaArvore = ExportaArvore(arvorebase);
    unsigned int tamArv = bitmapGetLength(SaidaArvore);
    fprintf(saida, "%d", tamArv);
    CompletaByteBitmap(SaidaArvore);
    fwrite(bitmapGetContents(SaidaArvore), 1, bitmapGetLength(SaidaArvore) / 8, saida);    
    bitmapLibera(SaidaArvore);
}

static void ColocaExtensaoNaSaida(char path[200], FILE* saida){
    char ext[200];
    sscanf(path,"./%*[^.]%s",ext);
    fprintf(saida, "%ld%s", strlen(ext),ext);
}