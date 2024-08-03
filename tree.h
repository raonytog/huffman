#ifndef TREE_H_
#define TREE_H_

#include "bitmap.h"
typedef struct Caracter Caracter;
typedef struct Tree Tree;

/** 
 * Funcoes de get 
 */

/// @brief Retorna o peso atrelado ao no com o caractere
/// @param arv arvore
/// @return peso
int RetornaPesoCaracter(Tree *arv);

/// @brief Retorna a quantidade de caracteres usados mais de uma vez vetor
/// @param vetor vetor de inteiros
/// @return quantidade de caracteres
int RetornaQtdCaracteres(int *vetor);

/// @brief Retorna o caractere do no
/// @param arv arvore
/// @return caractere do no
unsigned char RetornaCaractere(Tree *arv);

/// @brief Retorna o indice do caractere no vetor com as letras utilizadas
/// @param letras vetor com as letras utilizadas
/// @param procurada caractere procurado
/// @param tam tamanho do vetor
/// @return indice do caractere
int achaIndexCaracter(unsigned char *letras, unsigned char procurada, int tam);

/// @brief Transforma um caractere em byte
/// @param c caractere
/// @return byte
unsigned char *CharToByte(unsigned char c);

/// @brief Transforma um byte em um caractere (mas no codigo ascii)
/// @param byte byte
/// @return caractere (em ascii)
int ByteToChar(unsigned char *byte);

/// @brief Retorna o lado com o maior numero de caracteres
/// @param arv 
/// @return o maior numero de caracteres
int NumMaxCaracteres(Tree *arv);
/** 
 * Funcoes de ordenacao 
 */

/// @brief Compara se a > b
/// @param a lista de arvore
/// @param b lista de arvore
/// @return o maior
int Compara(const void *a, const void *b);

/// @brief Ordena em ordem crescente o vetor de arvores
/// @param vet vetor de arvores
/// @param inicio inicio
/// @param fim fim
void QuickSort(Tree **vet, int inicio, int fim);

/// @brief Funcao auxiliar para realizar o quicksort
/// @param vet vetor de nos de arvores
/// @param inicio inicio
/// @param fim fim
/// @return idx do pivot
int particao(Tree **vet, int inicio, int fim);

/**
 *  Funcoes gerais da arvore
 */

/// @brief Cria uma estrutura de caracteres, armazenando a letra e seu peso
/// @param letter codigo ascii da letra
/// @param peso peso
/// @return caractere
Caracter *CriaCaracter(int letter, int peso);

/// @brief Cria o vetor de nos binarios de caracteres, caso o peso do caractere seja maior que 0
/// @param vetor vetor de caracteres
/// @return vetor de caracteres
Tree **CriaVetorPorPeso(int *vetor);

/// @brief Organiza o vetor de arvores de acordo com o peso, de acordo com o passo a passo
/// da codificacao huffman
/// @param vetorCaracter vetor com os caracteres
/// @param elementos qts de elementos no vetor
/// @param inicio comeco do vetor
/// @return Arvore organizada
Tree *OrganizaArvorePorPesos(Tree** vetorCaracter, int elementos, int inicio);

/// @brief Busca um caractere. A cada no percorrido, o mapa de bit sera adicionado com 0
/// quando encontrar o no, sera adicionado 1 
/// @param bm mapa de bits
/// @param arv arvore binaria percorrida
/// @param c letra a procurar
/// @param cont contador para identificar se achou a letra
/// @return mapa de bits com o caminho para a letra
bitmap *BuscaBinaria(bitmap *bm, Tree *arv, unsigned char c, int *cont);


/// @brief Cria um vetor que armazena o codigo binario traduzido de cada caractere
/// em uso no arquivo
/// @param letras vetor de letras
/// @param arv arvore binaria
/// @param quant quantidade de letras no vetor
/// @return 
bitmap **tabelaTraducao(unsigned char *letras, Tree *arv, int quant);


/// @brief Cria um vetor apenas com as letras utilizadas na lista de arvores, em ordem crescente
/// @param letras vetor de letras
/// @param quant quantidade de items nos dois vetores
/// @param lista lista de arvores
void vetoresBase(unsigned char *letras, int quant, Tree **lista);

/// @brief Verifica se o no atual eh uma folha
/// @param arv 
/// @return 1 se for uma folha, 0 caso contrario
int IsLeaf(Tree *arv);

/// @brief Adiciona o codigo de parada '\003' ao final do vetor de letras do texto
/// @param arv vetor de arvores
/// @param quant tamanho do vetor
/// @return Vetor de arvores atualizado, com o caractere de parada
Tree **AdicionaCodParada(Tree **arv, int quant);

/// @brief Le do arquivo o bitmap da arvore e a preenche
/// @param compactado arquivo compactado
/// @param arv arvore vazia
/// @param bits bitmap da arvore
/// @return arvore recuperada
Tree *RecuperaArvore(FILE *compactado, Tree *arv, bitmap *bits);

/// @brief Percorre o bitmap na arvore ate encontrar um no folha para criar o caractere
/// @param arv arvore
/// @param bits mapa de bits
/// @param tamAtual tamanho atual do mapa de bits
/// @return arvore preenchica
Tree *ColocandoConteudoArvore(Tree *arv, bitmap *bits,  unsigned int *tamAtual);


/// @brief Percorre o bitmap para buscar cada letra e inserir no texto
/// @param arv arvore binaria com as letras
/// @param fDescompactado arquivo compactado a ser lido
/// @param fDecofificado arquivo decodificado a ser escrito (saida)
/// @param bm mapa de bits
/// @param paradas quantidade de caracteres de parada existentes no arquivo
/// @param numAtual numero atual de caracteres de parada
void DecodificaTexto(Tree *arv, FILE *fDescompactado, FILE *fDecofificado, bitmap *bm, short int paradas, short int *numAtual);

/**
 * Funcoes de impressao
 */

/// @brief Imprime toda os filhos do no
/// @param treeNode no da arvore
void ImprimeArvore(Tree *treeNode);

/// @brief Percorre a arvore e breenche o bitmap com 1, caso seja folha e 0 caso contrário
/// @param tree no da arvore binaria
/// @param arvBit mapa de bits da arvore
/// @return mapa de bits da arvore
bitmap *PreencheBitmapArvore(Tree *tree, FILE *fCompactado, bitmap *arvBit);

/// @brief Imprime as letras e seus pesos correspondentes no vetor
/// @param vetor vetor de nos com as letras do texto
/// @param quant quantidade de nos do vetor
void ImprimeVetor(Tree **vetor, int quant);

/** 
 * Funcoes de liberacao 
 */

/// @brief Libera toda a arvore binaria
/// @param treeNode 
void LiberaArvore(Tree *treeNode);

/// @brief Libera a estrutura de caractere
/// @param caractereStruct 
void LiberaCaractere(Caracter *caractereStruct);

#endif
