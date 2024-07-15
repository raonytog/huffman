#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void Descompacta(Tree *arvore, bitmap *bm, unsigned int *size);

int main () {
    Tree *arvore = NULL;
    bitmap *bm = NULL;
    unsigned int bmSize = 0;

    Descompacta(arvore, bm, &bmSize);
    printf("size %d\n", bmSize);
    bitmapPrint(bm);
    
    return 0;
}

void Descompacta(Tree *arvore, bitmap *bm, unsigned int *size) {
    FILE *fDescompactado = NULL;
    fDescompactado = fopen("texto.txt.comp", "rb");
    if (fDescompactado == NULL) {
        printf("Erro ao abrir o arquivo binario compactado\n");
        exit(EXIT_FAILURE);
    }
    
    /**
     * 1. String arvore
     * 2. Tamanho bitmap
     * 3. Bitmap
     */

    /** le a arvore bixa */

    /** Le tamanho do bitmap */
    fread(size, sizeof(unsigned int), 1, fDescompactado);

    /** Le o bitmap */
    unsigned char bit;
    bm = bitmapInit(*size);
    for (int i = 0; i < *size; i++) {
        fread(&bit, sizeof(unsigned char), 1, fDescompactado);
        bitmapAppendLeastSignificantBit(bm, bit);
    }
}
