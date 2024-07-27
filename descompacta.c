#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

// /**
//  * Ordem para recuperacao:
//  * 1. Tamanho bitmap arvore
//  * 2. Bitmap arvore
//  * 3. Tamanho bitmap texto
//  * 4. Bitmap texto
//  */

bitmap *RecuperaBitmap(unsigned int *size, FILE *fDescompactado);

int main () {
   FILE *fDescompactado = NULL;
   fDescompactado = fopen("texto.txt.comp", "rb");
   if (fDescompactado == NULL) {
      printf("Erro ao abrir o arquivo binario compactado\n");
      exit(EXIT_FAILURE);
   }

   Tree *arvore = NULL;
   bitmap *bits = bitmapInit(10000);
   unsigned char *texto = bitmapGetContents(bits);
   int short tamBits = 0;
   //fread(&tamBits,sizeof(short int), 1, fDescompactado);
   arvore =  RecuperaArvore(fDescompactado, arvore, texto, bits);
   ImprimeArvore(arvore);
   return 0;
}

bitmap *RecuperaBitmap(unsigned int *size, FILE *fDescompactado) {
   if (!fDescompactado) {
      printf("Erro ao tentar recuperar o bitmap do arquivo compactado");
      return NULL;
   }

   /** Le tamanho do bitmap */
   fread(size, sizeof(unsigned int), 1, fDescompactado);

   /** Le o bitmap */
   unsigned char bit;
   bitmap *bm = bitmapInit(*size);
   for (int i = 0; i < *size; i++) {
      fread(&bit, sizeof(unsigned char), 1, fDescompactado);
      bitmapAppendLeastSignificantBit(bm, bit);
   }

   return bm;
}

