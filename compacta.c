#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#define MAX_ASCI 256  //tamanho maximo do vetor com as qts de uso de cada letra
#define MAX_TEXT 4096 // tamanho maximo do vetor q armazena o texto
 struct caracter
{
    int peso;
    char letra;
};
void *PreencheVetor(int *vetor, char *text) {
    char letra = '\0';
    int idx = 0;
    FILE *fText = fopen("texto.txt", "r");
    while ( !feof(fText) ) {
        letra = '\0';
        if (fscanf(fText, "%c", &letra) == 1) 
            vetor[letra]++;
            text[idx] = letra;
            idx++;
    }
    text[idx] = '\0';
}

void PrintVetor(int *vetor) {
    for (int i = 0; i < MAX_ASCI; i++)
        printf("%c: %d\n", i, vetor[i]);
    printf("\n");
}

int main () {
    // armazena as qts usadas de cada caractere
    int *vetor = calloc(MAX_ASCI, sizeof(int));

    // armazena o texto original
    char text[MAX_TEXT] = "\0";
    PreencheVetor(vetor, text);
    tree **vetorCaracteres = CriaVetorPorPeso(vetor);
    int quant = RetornaQuantidadeCaracteres(vetor);
    qsort(vetorCaracteres, quant, sizeof(tree*),Compara); 
    ImprimeStruct(vetorCaracteres, quant);
    tree *arvore = OrganizaArvorePorPesos(vetorCaracteres, quant, 0);
    return 0;
}