#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEGA 1000000
#include "tree.h"

int main (int argc, char const *argv[]) {
   if (argc <= 1) {
      printf("ERRO: diretorio de arquivos nao informado\n");
      exit(1);
   }

   char path[100]; 
   strcpy(path, argv[1]);

   FILE *fDescompactado = NULL;
   fDescompactado = fopen(path, "rb");
   if (fDescompactado == NULL) {
      printf("Erro ao abrir o arquivo binario compactado\n");
      exit(EXIT_FAILURE);
   }

   /** Recupera a Arvore do arquivo binario */
   Tree *arvore = NULL;    bitmap *bits = bitmapInit(10000);
   unsigned char *texto;   int short tamBits = 0;
   arvore =  RecuperaArvore(fDescompactado, arvore, bits);
   
   /** Path para arquivo de saida descopactado */
   char pathDecodificado[100]; strcpy(pathDecodificado, path);
   pathDecodificado[strlen(pathDecodificado)-5] = '\0';

   /** Escreve a quantidade de bytes de texto a ler */
   short int paradas = 0;
   fread(&paradas,sizeof(short int), 1, fDescompactado);

   FILE *fDecodifica = fopen(pathDecodificado, "wb");
   bitmap *bitmapTexto = bitmapInit(MEGA);
   short int num = 0;
   DecodificaTexto(arvore, fDescompactado, fDecodifica, bitmapTexto, paradas, &num);

   /** Libera a memoria do programa */
   LiberaArvore(arvore);
   
   bitmapLibera(bits);
   bitmapLibera(bitmapTexto);

   fclose(fDescompactado);
   fclose(fDecodifica);
   
   return 0;
}