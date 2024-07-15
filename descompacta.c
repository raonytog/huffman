// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "tree.h"

// /**
//  * Ordem para recuperacao:
//  * 1. String arvore
//  * 2. Tamanho bitmap
//  * 3. Bitmap
//  */

// bitmap *RecuperaBitmap(unsigned int *size, FILE *fDescompactado);

// int main () {
//     FILE *fDescompactado = NULL;
//     fDescompactado = fopen("texto.txt.comp", "rb");
//     if (fDescompactado == NULL) {
//         printf("Erro ao abrir o arquivo binario compactado\n");
//         exit(EXIT_FAILURE);
//     }

//     Tree *arvore = NULL;
//     bitmap *bm = NULL;
//     unsigned int bmSize = 0;

//     // Descompacta(arvore, bm, &bmSize);
//     bm = RecuperaBitmap(&bmSize, fDescompactado);
//     bitmapPrint(bm);
//     printf("size %d\n", bmSize);
    
//     return 0;
// }

// bitmap *RecuperaBitmap(unsigned int *size, FILE *fDescompactado) {
//     if (!fDescompactado) {
//         printf("Erro ao tentar recuperar o bitmap do arquivo compactado");
//         return NULL;
//     }

//     /** Le tamanho do bitmap */
//     fread(size, sizeof(unsigned int), 1, fDescompactado);

//     /** Le o bitmap */
//     unsigned char bit;
//     bitmap *bm = bitmapInit(*size);
//     for (int i = 0; i < *size; i++) {
//         fread(&bit, sizeof(unsigned char), 1, fDescompactado);
//         bitmapAppendLeastSignificantBit(bm, bit);
//     }

//     return bm;
// }
 

// void Descompacta(Tree *arvore, bitmap *bm, unsigned int *size) {
    
//     /**
//      * 1. String arvore
//      * 2. Tamanho bitmap
//      * 3. Bitmap
//      */

//     /** le a arvore bixa */

// }
