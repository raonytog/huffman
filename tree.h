#ifndef TREE_H_
#define TREE_H_

typedef struct Caracter Caracter;
typedef struct Tree Tree;

int RetornaPesoCaracter(Tree *arv);

int RetornaQuantidadeCaracteres(int *vetor);

void QuickSort(Tree **vet, int inicio, int fim);

int particao(Tree **vet, int inicio, int fim);

Caracter *CriaCaracter(int letter, int peso);

Tree **CriaVetorPorPeso(int *vetor);

Tree *QuickSortLista(Tree *inicio, Tree *fim);

Tree *OrganizaArvorePorPesos(Tree** vetorCaracter, int elementos, int inicio);

int Compara(const void *a, const void *b);

void ImprimeVetor(Tree **vetor, int quant);

void ImprimeArvore(Tree *treeNode);

#endif