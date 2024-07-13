#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "bitmap.h"

#define MAX_ASCI 256  //tamanho maximo do vetor com as qts de uso de cada letra
#define MAX_TEXT 4096 // tamanho maximo do vetor q armazena o texto
#define MEGA 1000000

void PreencheVetorTexto(int *vetor, char *text);
void PreencheBitMap(bitmap *bm, Tree *arv, char *text, char *vet, bitmap **tabela, int quant);

int main () {
    /** Preenche e armazena o vetor dos caracteres e o texto completo */
    int *vetor = calloc(MAX_ASCI, sizeof(int));
    char text[MAX_TEXT] = "\0";
    PreencheVetorTexto(vetor, text);
    printf("%s\n", text);

    /** Organiza o vetor de arvore e o ordena com base nos pesos */
    Tree **vetorCaracteres = CriaVetorPorPeso(vetor);
    int qtd = RetornaQtdCaracteres(vetor);
    char *caracteresEmOrdem  = calloc(qtd,sizeof(char));
    qsort(vetorCaracteres, qtd, sizeof(Tree*),Compara); 
    vetoresBase(caracteresEmOrdem, qtd, vetorCaracteres);
    ImprimeVetor(vetorCaracteres, qtd);
    Tree *arvore = OrganizaArvorePorPesos(vetorCaracteres, qtd, 0);
    bitmap **traducao = tabelaTraducao(caracteresEmOrdem, arvore, qtd);
    ImprimeArvore(arvore);
    printf("\n");

    bitmap *bm = bitmapInit(1000000);
    PreencheBitMap(bm, arvore, text, caracteresEmOrdem, traducao, qtd);
    bitmapPrint(bm);

    LiberaArvore(arvore);
    LiberaTabelaDeTraducao(traducao, qtd);
    free(vetorCaracteres);
    free(vetor);
    free(caracteresEmOrdem);
    bitmapLibera(bm);
    return 0;
}

void PreencheVetorTexto(int *vetor, char *text) {
    if (!vetor || !text) return;

    char letra = '\0';      int idx = 0;
    FILE *fText = fopen("texto.txt", "r");
    while ( !feof(fText) ) {
        letra = '\0';
        if (fscanf(fText, "%c", &letra) == 1) 
            vetor[letra]++;
            text[idx] = letra;
            idx++;
    }

    text[idx] = '\0';
    fclose(fText);
}


void PreencheBitMap(bitmap *bm, Tree *arv, char *text, char *vet, bitmap **tabela, int quant) {
    if (!bm || !arv || !text) return;
    for (int i = 0; text[i] != '\0'; i++) {  
       
        int index = achaIndexCaracter(vet, text[i], quant);

        for (int j = 0; j < bitmapGetLength(tabela[index]); j++) {
            unsigned char b = bitmapGetBit(tabela[index], j);
            bitmapAppendLeastSignificantBit(bm, b);
        }
        
        
    }
}
