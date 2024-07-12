#ifndef TREE_H_
#define TREE_H_

typedef struct Caracter Caracter;
typedef struct Tree Tree;

/** Funcoes de get */

int RetornaPesoCaracter(Tree *arv);

int RetornaQtdCaracteres(int *vetor);

unsigned char RetornaCaractere(Tree *arv);

/** Funcoes de ordenacao */

int Compara(const void *a, const void *b);

void QuickSort(Tree **vet, int inicio, int fim);

int particao(Tree **vet, int inicio, int fim);

Tree *QuickSortLista(Tree *inicio, Tree *fim);

/** Funcoes gerais da arvore*/
Caracter *CriaCaracter(int letter, int peso);

Tree **CriaVetorPorPeso(int *vetor);

Tree *OrganizaArvorePorPesos(Tree** vetorCaracter, int elementos, int inicio);

void ImprimeVetor(Tree **vetor, int quant);

void ImprimeArvore(Tree *treeNode);

/** Funcoes de liberacao */

void LiberaArvore(Tree *treeNode);

void LiberaCaractere(Caracter *caractereStruct);

#endif