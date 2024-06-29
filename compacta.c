#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

void PreencheVetor(int *vetor) {
    char letra = '\0';
    FILE *fText = fopen("texto.txt", "r");
    while ( !feof(fText) ) {
        if (fscanf(fText, "%c", &letra) == 1) 
            vetor[letra]++;
    }
}

void PrintVetor(int *vetor) {
    for (int i = 0; i < MAX; i++)
        printf("%c: %d\n", i, vetor[i]);
    printf("\n");
}

int main () {
    int *vetor = calloc(MAX, sizeof(int));
    PreencheVetor(vetor);
    PrintVetor(vetor);

    return 0;
}