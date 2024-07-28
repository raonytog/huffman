#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "bitmap.h"

#define MAX_ASCI 256  /** tamanho maximo do vetor com as qts de uso de cada letra */
#define MAX_TEXT 4096 /** tamanho maximo do vetor q armazena o texto */
#define MEGA 4000000

void PreencheVetorTexto(int *vetor, char *text);
void PreencheBitMap(bitmap *bm, Tree *arv, char *text, char *vet, bitmap **tabela, int quant);
void Compacta(Tree *arvore, bitmap *bm);

int main () {
    /** Preenche e armazena o vetor dos caracteres e o texto completo */
    int *vetor = calloc(MAX_ASCI, sizeof(int));
    char text[MAX_TEXT] = "\0";
    PreencheVetorTexto(vetor, text);

    /** 
     * Cria, preenche e ordena o vetor de com os caracteres, com base em quais foram
     * mais utilizados durante a leitura do texto
     */
    Tree **vetorCaracteres = CriaVetorPorPeso(vetor);
    int qtd = RetornaQtdCaracteres(vetor);
    vetorCaracteres = AdicionaCodParada(vetorCaracteres, qtd);
    qtd++;
    
    qsort(vetorCaracteres, qtd, sizeof(Tree*),Compara); 
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
    PreencheBitMap(bm, arvore, text, caracteresEmOrdem, traducao, qtd);

    /**
     * Compacta o arquivo de texto traduzido para um arquivo binario,
     * que contem, em ordem:
     * 1. A árvore;
     * 2. O tamanho do mapa de bits
     * 3. O mapa de bits
     */
    Compacta(arvore, bm);

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

void PreencheVetorTexto(int *vetor, char *text) {
    if (!vetor || !text) return;

    unsigned char letra = '\0';  int idx = 0;
    FILE *fText = fopen("texto.txt", "rb");
    while (fread(&letra, sizeof( unsigned char), 1, fText) == 1) {
        vetor[letra]++;
        text[idx] = letra;
        idx++;
    }
    letra = '\0';
    fclose(fText);

}

void PreencheBitMap(bitmap *bm, Tree *arv, char *text, char *vet, bitmap **tabela, int quant) {
    if (!bm || !arv || !text) return;

    /** Insere os demais caracteres */
    for (int i = 0; text[i] != '\0'; i++) {  
        int index = achaIndexCaracter(vet, text[i], quant);

        for (int j = 0; j < bitmapGetLength(tabela[index]); j++) {
            unsigned char b = bitmapGetBit(tabela[index], j);
            bitmapAppendLeastSignificantBit(bm, b);
        }
    }

    /** Insere o caractere de paradas */
    int index = achaIndexCaracter(vet, '^', quant);
    for (int j = 0; j < bitmapGetLength(tabela[index]); j++) {
        unsigned char b = bitmapGetBit(tabela[index], j);
        bitmapAppendLeastSignificantBit(bm, b);
    }
}

void Compacta(Tree *arvore, bitmap *bm) {
    if (!arvore || !bm) return;

    FILE *fCompactado = NULL;
    fCompactado = fopen("texto.txt.comp", "wb");
    if (fCompactado == NULL) {
        printf("Erro ao criar o arquivo binario compactado\n");
        exit(EXIT_FAILURE);
    }

    /** Preenche bitmap com a arvore binaria */
    bitmap *arvBit = bitmapInit(100000);
    PreencheBitmapArvore(arvore, fCompactado,arvBit);  

    /** Escreve o tamanho do bitmap de arvore e, posteriormente, o bitmap da arvore */
    short int bitsArv = bitmapGetLength(arvBit);
    fwrite(&bitsArv, sizeof(short int), 1, fCompactado);
    ImprimeBitmapArquivo(arvBit, fCompactado);

    /** Escreve o bitmap do texto */
    ImprimeBitmapArquivo(bm, fCompactado);
    
    bitmapLibera(arvBit);
    fclose(fCompactado);
}