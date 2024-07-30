#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "bitmap.h"

#define MAX_ASCI 256  /** tamanho maximo do vetor com as qts de uso de cada letra */
#define MEGA 1000000

void PreencheVetorTexto(int *vetor);
void PreencheBitMap(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant, FILE *arq);
void Compacta(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant);

int main () {
    /** Preenche e armazena o vetor dos caracteres e o texto completo */
    int *vetor = calloc(MAX_ASCI, sizeof(int));
    PreencheVetorTexto(vetor);

    /** 
     * Cria, preenche e ordena o vetor de com os caracteres, com base em quais foram
     * mais utilizados durante a leitura do texto
     */
    Tree **vetorCaracteres = CriaVetorPorPeso(vetor);
    int qtd = RetornaQtdCaracteres(vetor);
    vetorCaracteres = AdicionaCodParada(vetorCaracteres, qtd);
    qtd++;
    
    qsort(vetorCaracteres, qtd, sizeof(Tree*), Compara); 
    ImprimeVetor(vetorCaracteres, qtd);

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
    // PreencheBitMap(bm, arvore, text, caracteresEmOrdem, traducao, qtd);

    /**
     * Compacta o arquivo de texto traduzido para um arquivo binario,
     * que contem, em ordem:
     * 1. A árvore;
     * 2. O tamanho do mapa de bits
     * 3. O mapa de bits
     */
    Compacta(bm, arvore, caracteresEmOrdem, traducao, qtd);

    /**
     * Funcoes de liberacao 
     */
    LiberaTabelaDeTraducao(traducao, qtd);
    bitmapLibera(bm);

    for (int i = 0; i < qtd; i++)
        LiberaArvore(vetorCaracteres[i]);
    free(vetorCaracteres);

    free(vetor);
    free(caracteresEmOrdem);

    return 0;
}

void PreencheVetorTexto(int *vetor) {
    if (!vetor) return;

    unsigned char letra = '\0';  int idx = 0;
    FILE *fText = fopen("biblia.txt", "rb");
    while (fread(&letra, sizeof(unsigned char), 1, fText) == 1) {
        vetor[letra]++;
    }
    fclose(fText);
}

void PreencheBitMap(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant, FILE *arq) {
    if (!bm || !arv) return;

    /** Insere os demais caracteres */
    unsigned char letra = '\0';
    FILE *fText = fopen("biblia.txt", "rb");
    while (fread(&letra, sizeof(unsigned char), 1, fText) == 1) {
        int index = achaIndexCaracter(vet, letra, quant);

        for (int j = 0; j < bitmapGetLength(tabela[index]); j++) {
            unsigned char b = bitmapGetBit(tabela[index], j);
            bitmapAppendLeastSignificantBit(bm, b);

            /** Verifica se o bitmap esta cheio */
            if (bitmapGetLength(bm)+1 >= bitmapGetMaxSize(bm)) {
                ImprimeBitmapArquivo(bm, arq);
                bm = EsvaziaBitMap(bm);
            }
        }
    }

    /** Insere o caractere de paradas */
    int index = achaIndexCaracter(vet, '^', quant);
    for (int j = 0; j < bitmapGetLength(tabela[index]); j++) {
        unsigned char b = bitmapGetBit(tabela[index], j);
        bitmapAppendLeastSignificantBit(bm, b);

        if (bitmapGetLength(bm)+1 >= bitmapGetMaxSize(bm)) {
            ImprimeBitmapArquivo(bm, arq);
            bm = EsvaziaBitMap(bm);
        }
    }

    // fclose(fText);
}

void Compacta(bitmap *bm, Tree *arv, char *vet, bitmap **tabela, int quant) {
    if (!bm || !arv) return;

    FILE *fCompactado = NULL;
    fCompactado = fopen("texto.txt.comp", "wb");
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
    ImprimeBitmapArquivo(arvBit, fCompactado);
    
    /** Escreve o bitmap do texto */
    PreencheBitMap(bm, arv, vet, tabela, quant, fCompactado);
    ImprimeBitmapArquivo(bm, fCompactado);
    
    bitmapLibera(arvBit);
    fclose(fCompactado);
}