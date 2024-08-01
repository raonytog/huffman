#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEGA 1000000
#include "tree.h"

// // /**
// //  * Ordem para recuperacao:
// //  * 1. Tamanho bitmap arvore
// //  * 2. Bitmap arvore  
// //  * 3. Tamanho bitmap texto
// //  * 4. Bitmap texto
// //  */

bitmap *RecuperaBitmap(unsigned int *size, FILE *fDescompactado);

int main (int argc, char const *argv[]) {
   if (argc <= 1) {
      printf("ERRO: diretorio de arquivos nao informado\n");
      exit(1);
   }

    char path[100]; 
    strcpy(path, argv[1]);

// int main() {
//     char path[100] = "dua_lipa.jpg.comp";

   FILE *fDescompactado = NULL;
   fDescompactado = fopen(path, "rb");
   if (fDescompactado == NULL) {
      printf("Erro ao abrir o arquivo binario compactado\n");
      exit(EXIT_FAILURE);
   }

   /** Recupera a Arvore do arquivo binario */
   Tree *arvore = NULL;    bitmap *bits = bitmapInit(10000);
   unsigned char *texto;   int short tamBits = 0;
   arvore =  RecuperaArvore(fDescompactado, arvore, texto, bits);
   
   /** Path para arquivo de saida descopactado */
   char pathDecodificado[100] = "desc_"; strcat(pathDecodificado, path);
   pathDecodificado[strlen(pathDecodificado)-5] = '\0';

   short int paradas = 0;
   fread(&paradas,sizeof(short int), 1, fDescompactado);
   FILE *fDecodifica = fopen(pathDecodificado, "wb");
   bitmap *bitmapTexto = bitmapInit(MEGA);
   short int num = 0;
   int decodifica = LerTextoBinArquivo(bitmapTexto, fDescompactado);
   while(!decodifica){
      DecodificaTexto(arvore, fDescompactado, fDecodifica, bitmapTexto, paradas, &num);
      bitmapLibera(bitmapTexto);
      bitmapTexto = bitmapInit(MEGA);
      decodifica = LerTextoBinArquivo(bitmapTexto, fDescompactado);
   }
   if(decodifica) DecodificaTexto(arvore, fDescompactado, fDecodifica, bitmapTexto, paradas, &num);

   LiberaArvore(arvore);
   
   bitmapLibera(bits);
   bitmapLibera(bitmapTexto);

   fclose(fDescompactado);
   fclose(fDecodifica);
   
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
