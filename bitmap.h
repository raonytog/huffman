/** Define um TAD representando um mapa de bits.
 * @file bitmap.h
 * @author Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br)
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdio.h>
typedef struct Tree Tree;

/**
 * Estrutura para representar um mapa de bits.
 */
typedef struct map bitmap;

unsigned char* bitmapGetContents(bitmap* bm);

unsigned int bitmapGetMaxSize(bitmap* bm);

unsigned int bitmapGetLength(bitmap* bm);

bitmap* bitmapInit(unsigned int max_size);

unsigned char bitmapGetBit(bitmap* bm, unsigned int index);

void bitmapAppendLeastSignificantBit(bitmap* bm, unsigned char bit);

void bitmapLibera(bitmap* bm);

/**
 * Funcoes implementadas para o TAD
 */

void bitmapRemoveLeastSignificantBit(bitmap* bm);

void bitmapPrint(bitmap *bm);

bitmap **traslantionGuide(bitmap **mae, int index, bitmap *filha);

void LiberaTabelaDeTraducao(bitmap **traducao, int quant);

bitmap *EsvaziaBitMap(bitmap *bm);
void InsereLenght(short int tam, bitmap *bm);
void ImprimeBitmapArquivo(bitmap *bm, FILE *fCompactado);
void LerBitmapArquivo(bitmap *bm, FILE *fCompactado);
int LerTextoBinArquivo(bitmap *bm, FILE *fCompactado, unsigned int max);
#endif /*BITMAP_H_*/
