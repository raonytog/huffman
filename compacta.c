#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "bitmap.h"

#define MAX_ASCI 256  /** tamanho maximo do vetor com as qts de uso de cada letra */
#define MEGA 1000000 /** tamanho maximo do mapa de bits */


/// @brief Le o arquivo a ser compactado pela primeira vez, a fim de criar 
/// o vetor com os pesos de cara caracter usado
/// @param vetor vetor de pesos
/// @param path caminho do arquivo
void PreencheVetorTexto(int *vetor, char *path);

/// @brief Preenche o mapa de bits do arquivo a ser compactado
/// @param bm mapa de bits do arquivo
/// @param arv arvore binaria
/// @param vet vetor de caracteres
/// @param tabela tabela de traducao com os caracteres e seus codigos
/// @param quant quantidade de indices no vetor de caracteres
/// @param arq arquivo a ser impresso o mapa de bits, quanto lotado
/// @param path caminho para criacao do arquivo compactado
void PreencheBitMap(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant, FILE *arq, char *path);

/// @brief Compacta o arquivo, escrevendo suas informações no arquivo binario na seguinte ordem:
/// 1. Tamanho do mapa de bits da arvore
/// 2. Mapa de bits da arvore
/// 3. Quantidade de caracteres de parada presentes no arquivo
/// 4. Mapa de bits do arquivo compactado
/// @param bm mapa de bits do arquivo
/// @param arv arvore binaria
/// @param vet vetor de letras
/// @param tabela tabalea de traducao de letra
/// @param quant tamanho do vetor de letras
/// @param path caminho onde o arquivo sera salvo
/// @param parada quantidade de caracteres de parada
void Compacta(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant, char *path, short int parada);

/// @brief Retorna a quantidade de caracteres de parada presentes no arquivo
/// @param vetor vetor de peso dos caracteres
/// @param c caractere de paraa
/// @return quantidade de caracteres de parada no arquivo
short int retornaQtdParada(int *vetor, char c);

int main (int argc, char const *argv[]) {
    if (argc <= 1) {
        printf("ERRO: diretorio de arquivos nao informado\n");
        exit(1);
    }

    char path[100]; 
    strcpy(path, argv[1]);

    /** Preenche e armazena o vetor dos caracteres e o texto completo */
    int *vetor = calloc(MAX_ASCI, sizeof(int));
    PreencheVetorTexto(vetor, path);
    short int CaracterParada = retornaQtdParada(vetor, 3);

    /** 
     * Cria, preenche e ordena o vetor de com os caracteres, com base em quais foram
     * mais utilizados durante a leitura do texto
     */
    Tree **vetorCaracteres = CriaVetorPorPeso(vetor);
    int qtd = RetornaQtdCaracteres(vetor);
    vetorCaracteres = AdicionaCodParada(vetorCaracteres, qtd);
    qtd++;
    
    qsort(vetorCaracteres, qtd, sizeof(Tree*), Compara); 

    /** 
     * Cria e preenche o vetor contendo apenas os caracteres 
     * usados no texto
     */
    char *caracteresEmOrdem  = calloc(qtd, sizeof(char));
    vetoresBase(caracteresEmOrdem, qtd, vetorCaracteres);

    /**
     * Organiza a arvore binaria de acordo com os criterios 
     * da codificacao de huffman
     */
    Tree *arvore = OrganizaArvorePorPesos(vetorCaracteres, qtd, 0);

    /**
     * Cria e preeche o mapa de bits com o texto codificado
     */
    bitmap **traducao = tabelaTraducao(caracteresEmOrdem, arvore, qtd);
    bitmap *bm = bitmapInit(MEGA);

    /**
     * Compacta o arquivo de texto traduzido para um arquivo binario,
     * que contem, em ordem:
     * 1. A árvore;
     * 2. O tamanho do mapa de bits
     * 3. O mapa de bits
     */
    Compacta(bm, arvore, caracteresEmOrdem, traducao, qtd, path, CaracterParada);

    /**
     * Funcoes de liberacao 
     */
    LiberaTabelaDeTraducao(traducao, qtd);

    for (int i = 0; i < qtd; i++)
        LiberaArvore(vetorCaracteres[i]);
    free(vetorCaracteres);

    free(vetor);
    free(caracteresEmOrdem);

    return 0;
}

short int retornaQtdParada(int *vetor, char c){
    if(!vetor) return EXIT_FAILURE;
    return vetor[c]+1;
}

void PreencheVetorTexto(int *vetor, char* path) {
    if (!vetor) return;

    unsigned char letra = '\0';  int idx = 0;
    FILE *fText = fopen(path, "rb");
    if (!fText) {
        printf("Texto nao abriu!");
        exit(EXIT_FAILURE);
    }

    while (fread(&letra, sizeof(unsigned char), 1, fText) == 1) {
        vetor[letra]++;
    }
    fclose(fText);
}

void PreencheBitMap(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant, FILE *arq, char *path) {
    if (!bm || !arv) return;

    unsigned char letra = '\0';
    int qtd = 0;
    FILE *fText = fopen(path, "rb");
    if (!fText) {
        printf("Arquivo nao abriu em PreencheBitMap\n");
        exit(EXIT_FAILURE);
    }
    while (fread(&letra, sizeof(unsigned char), 1, fText) == 1) {
        int index = achaIndexCaracter(vet, letra, quant);

        for (int j = 0; j < bitmapGetLength(tabela[index]); j++) {
            unsigned char b = bitmapGetBit(tabela[index], j);
            bitmapAppendLeastSignificantBit(bm, b);

            /** Verifica se o bitmap esta cheio */
            if (bitmapGetLength(bm) == bitmapGetMaxSize(bm)) {
                ImprimeBitmapArquivo(bm, arq, 0);
                bitmapLibera(bm);
                bm = bitmapInit(MEGA);
                qtd++;
            }
        }
    }

    /** Insere o caractere de paradas */
    int index = achaIndexCaracter(vet, 3, quant);
    for (int j = 0; j < bitmapGetLength(tabela[index]); j++) {
        unsigned char b = bitmapGetBit(tabela[index], j);
        bitmapAppendLeastSignificantBit(bm, b);

        if (bitmapGetLength(bm) == bitmapGetMaxSize(bm) && bitmapGetLength(tabela[index]) != j+1){
            ImprimeBitmapArquivo(bm, arq, 0);
            bitmapLibera(bm);
            bm = bitmapInit(MEGA);
            qtd++;
            
        }else if(bitmapGetLength(tabela[index]) == j+1){
            ImprimeBitmapArquivo(bm, arq, 1);
            bitmapLibera(bm);
        }
    }

    fclose(fText);
}

void Compacta(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant, char *path, short int parada) {
    if (!bm || !arv) return;

    char newPath[100]; strcpy(newPath, path); strcat(newPath, ".comp");
    FILE *fCompactado = fopen(newPath, "wb");
    if (fCompactado == NULL) {
        printf("Erro ao criar o arquivo binario compactado\n");
        exit(EXIT_FAILURE);
    }

    /** Preenche bitmap com a arvore binaria */
    bitmap *arvBit = bitmapInit(100000);
    PreencheBitmapArvore(arv, fCompactado, arvBit);

    /** Escreve o tamanho do bitmap de arvore e, posteriormente, o bitmap da arvore */
    short int bitsArv = bitmapGetLength(arvBit);
    fwrite(&bitsArv, sizeof(short int), 1, fCompactado);
    ImprimeBitmapArquivo(arvBit, fCompactado, 1);
    
    /** Escreve o bitmap do texto e a quantidade de caracteres de parada */
    long long int qtdBitsTxt = 0;
    fwrite(&parada, sizeof(short int), 1, fCompactado);
    PreencheBitMap(bm, arv, vet, tabela, quant, fCompactado, path);
    
    
    bitmapLibera(arvBit);
    fclose(fCompactado);
}