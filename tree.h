#ifndef TREE_H_
#define TREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct caracter caracter;
typedef struct tree tree;

int RetornaPesoCaracter(tree *arv);

int RetornaQuantidadeCaracteres(int *vetor);

void QuickSort(tree **vet, int inicio, int fim);

int particao(tree **vet, int inicio, int fim);

caracter *CriaCaracter(int letter, int peso);

tree **CriaVetorPorPeso(int *vetor);

tree *QuickSortLista(tree *inicio, tree *fim);

tree *OrganizaArvorePorPesos(tree** vetorCaracter, int elementos, int inicio);

int Compara(const void *a, const void *b);

void ImprimeStruct(tree **vetor, int quant);
#endif