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

/**
 * Retorna o conteudo do mapa de bits.
 * @param bm O mapa de bits.
 */
unsigned char* bitmapGetContents(bitmap* bm);

/**
 * Retorna o tamanho maximo do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho maximo do mapa de bits.
 */
unsigned int bitmapGetMaxSize(bitmap* bm);

/**
 * Retorna o tamanho atual do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho atual do mapa de bits.
 */
unsigned int bitmapGetLength(bitmap* bm);

/**
 * Constroi um novo mapa de bits, definindo um tamanho maximo.
 * @param max_size O tamanho maximo para o mapa de bits.
 * @return O mapa de bits inicializado.
 */
bitmap* bitmapInit(unsigned int max_size);

/**
 * Retorna o valor do bit na posicao index.
 * @param bm O mapa de bits.
 * @param index A posicao do bit.
 * @pre index<bitmapGetLength(bm)
 * @return O valor do bit.
 */
unsigned char bitmapGetBit(bitmap* bm, unsigned int index);

/**
 * Adiciona um bit no final do mapa de bits.
 * @param bm O mapa de bits.
 * @param bit O novo valor do bit.
 * @pre bitmapGetLength(bm) < bitmapGetMaxSize(bm)
 * @post (bitmapGetBit(bm,bitmapGetLength(bm) @ pre)==bit) 
 * and (bitmapGetLength(bm) == bitmapGetLength(bm) @ pre+1)
 */
void bitmapAppendLeastSignificantBit(bitmap* bm, unsigned char bit);

/**
 * Libera a memória dinâmica alocada para o mapa de bits.
 * @param bm O mapa de bits.
 */
void bitmapLibera(bitmap* bm);

/**
 * Funcoes implementadas para o TAD
 */

/// @brief Remove o bit mais significativo do mapa de bits
/// @param bm O mapa de bits
void bitmapRemoveLeastSignificantBit(bitmap* bm);

/// @brief Imprime o mapa de bits
/// @param bm O mapa de bits
void bitmapPrint(bitmap *bm);

/// @brief Atribui a filha a mae de indice index
/// @param mae lista de mapa de bits
/// @param index indice
/// @param filha novo valor
/// @return mae[index] = filha
bitmap **traslantionGuide(bitmap **mae, int index, bitmap *filha);

/// @brief Libera a memoria alocada para a lista de mapa de bits
/// @param traducao lista de mapa de bits
/// @param quant quantidade de mapas de bits 
void LiberaTabelaDeTraducao(bitmap **traducao, int quant);

/// @brief Esvazia o conteudo do mapa de bits, sem desaloca-lo.
/// @param bm 
/// @return mapa de bits sem conteudo, mas alocado
bitmap *EsvaziaBitMap(bitmap *bm);

/// @brief Altera o lenght do mapa de bits
/// @param tam novo tamanho do mapa
/// @param bm mapa a se alterar
void InsereLenght(long long int tam, bitmap *bm);

/// @brief Imprime o mapa de bits no arquivo
/// @param bm mapa de bits
/// @param fCompactado arquivo de compactacao
/// @param final inteiro representando a necessidade de completar byte ou nao
void ImprimeBitmapArquivo(bitmap *bm, FILE *fCompactado, int final);

/// @brief Recupera o mapa de bits do dado arquivo
/// @param bm mapa de bits
/// @param fCompactado arquivo compactado
void LerBitmapArquivo(bitmap *bm, FILE *fCompactado);

/// @brief Recupera o mapa de bits de dado arquivo, sem saber o tamanho maximo dele
/// @param bm mapa de bits
/// @param fCompactado arquivo compactado
/// @return 0 caso o mapa tenha lotado, 1 caso contrário
int LerTextoBinArquivo(bitmap *bm, FILE *fCompactado);

#endif /*BITMAP_H_*/
