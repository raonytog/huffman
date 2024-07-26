#ifndef TREE_H_
#define TREE_H_

#include "bitmap.h"

typedef struct Caracter Caracter;
typedef struct Tree Tree;

/** 
 * Funcoes de get 
 */

int RetornaPesoCaracter(Tree *arv);

int RetornaQtdCaracteres(int *vetor);

unsigned char RetornaCaractere(Tree *arv);

int achaIndexCaracter(unsigned char *letras, unsigned char procurada, int tam);

/** 
 * Funcoes de ordenacao 
 */

int Compara(const void *a, const void *b);

void QuickSort(Tree **vet, int inicio, int fim);

int particao(Tree **vet, int inicio, int fim);

Tree *QuickSortLista(Tree *inicio, Tree *fim);

/**
 *  Funcoes gerais da arvore
 */

Caracter *CriaCaracter(int letter, int peso);

Tree **CriaVetorPorPeso(int *vetor);

Tree *OrganizaArvorePorPesos(Tree** vetorCaracter, int elementos, int inicio);

bitmap *BuscaBinaria(bitmap *bm, Tree *arv, unsigned char c, int *cont);

bitmap *EsvaziaBitMap(bitmap *bm);

bitmap **tabelaTraducao(unsigned char *letras, Tree *arv, int quant);

void vetoresBase(unsigned char *letras, int quant, Tree **lista);

int IsLeaf(Tree *arv);

Tree **AdicionaCodParada(Tree **arv, int quant);

unsigned char *CharToByte(unsigned char c);

unsigned char ByteToChar(unsigned char *byte);

/**
 * Funcoes de impressao
 */

void ImprimeVetorArvore(Tree **vetor, int quant);

void ImprimeArvore(Tree *treeNode);

bitmap *ImprimeArvoreArquivo(Tree *tree, FILE *fCompactado, bitmap *arvBit);

void ImprimeVetor(Tree **vetor, int quant);

/** 
 * Funcoes de liberacao 
 */

void LiberaArvore(Tree *treeNode);

void LiberaCaractere(Caracter *caractereStruct);

Tree *RecuperaArvore(FILE *compactado, Tree *arv, unsigned char *texto, bitmap *bits);

#endif