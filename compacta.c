#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "bitmap.h"

#define MAX_ASCI 256  //tamanho maximo do vetor com as qts de uso de cada letra
#define MAX_TEXT 4096 // tamanho maximo do vetor q armazena o texto
#define MEGA 1000000

void PreencheVetor(int *vetor, char *text);

int main () {
    /** Preenche e armazena o vetor dos caracteres e o texto completo */
    int *vetor = calloc(MAX_ASCI, sizeof(int));
    char text[MAX_TEXT] = "\0";
    PreencheVetor(vetor, text);
    printf("%s\n", text);

    /** Organiza o vetor de arvore e o ordena com base nos pesos */
    Tree **vetorCaracteres = CriaVetorPorPeso(vetor);
    int qtd = RetornaQtdCaracteres(vetor);
    qsort(vetorCaracteres, qtd, sizeof(Tree*),Compara); 
    ImprimeVetor(vetorCaracteres, qtd);


    Tree *arvore = OrganizaArvorePorPesos(vetorCaracteres, qtd, 0);
    bitmap *map = bitmapInit(1000000);

    ImprimeArvore(arvore);

    bitmapLibera(map);
    LiberaArvore(arvore);
    free(vetorCaracteres);
    free(vetor);
    return 0;
}

void PreencheVetor(int *vetor, char *text) {
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
