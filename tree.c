#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree.h"

#define MAX 256

 struct Caracter {
    int peso;
    unsigned char letra;
};

struct Tree{
    Caracter *info;
    Tree *direita, *esquerda;
};

/** Funcoes de get */
int RetornaPesoCaracter(Tree *arv) {
    if (!arv) return 0;
    return arv->info->peso;
}

unsigned char RetornaCaractere(Tree *arv) {
    if (!arv) return '\0';
    return arv->info->letra;
}

int RetornaQtdCaracteres(int *vetor) {
    if(!vetor) return 0;

    int quant = 0;
    for(int i = 0; i<MAX; i++){
        if(vetor[i]>0) quant++;
    }

    return quant;
}

int achaIndexCaracter(unsigned char *letras, unsigned char procurada, int tam){
    if(!letras) return -1;

    for(int i = 0; i < tam;i++)
        if (procurada == letras[i]) return i;

    return -1;
}

/** Funcoes para ordenacao */
int Compara(const void *a, const void *b) {
    Tree *arv1 = *(Tree **)a, *arv2 = *(Tree **)b;
    return arv1->info->peso - arv2->info->peso;
}

void QuickSort(Tree **vet, int inicio, int fim){
    if(inicio>=fim) return;

    int pivot = particao(vet, inicio, fim);
    QuickSort(vet, pivot +1, fim);
    QuickSort(vet, inicio, pivot-1);
}

int particao(Tree **vet, int inicio, int fim) {
    Tree *pivot = vet[fim];

    int i = inicio -1;
    for(int j = inicio; j<fim; j++) {
        if (RetornaPesoCaracter(pivot) >= RetornaPesoCaracter(vet[j])) {
            i++;

            if (i != j) {
                Tree *temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }

    Tree *temporario = vet[fim];
    vet[fim] = vet[i+1];
    vet[i+1] = temporario;
    return i+1;
}

Tree *ParticaoLista(Tree *inicio, Tree *fim){
    Tree *pivot = inicio, *front = inicio;
    Caracter *temp = NULL; 

    while (front && front != fim) { 
        if (RetornaPesoCaracter(front) < RetornaPesoCaracter(fim)) { 
            pivot = inicio; 
            temp = inicio->info; 
            inicio->info= front->info; 
            front->info = temp; 
            inicio = inicio->direita; 
        } 
        front = front->direita; 
    }
    
    temp = inicio->info; 
    inicio->info= fim->info; 
    fim->info = temp; 
    return pivot; 
}

/** Funcoes gerais do tad*/
Caracter *CriaCaracter(int letter, int peso){
    if(!peso) return NULL;

    Caracter *letra = malloc(sizeof(Caracter));
    letra->letra = (unsigned char)letter;
    letra->peso = peso;

    return letra;
}
 
Tree **CriaVetorPorPeso(int *vetor){
    if (!vetor) return NULL;

    int quant = RetornaQtdCaracteres(vetor);
    Tree **CaracteresVetor = malloc((quant+1)*(sizeof(Tree*)));

    int cont = 0;
    for(int i = 0; i < MAX; i++){
        if(vetor[i] > 0){
            Caracter *letra = CriaCaracter(i, vetor[i]);
            CaracteresVetor[cont] = malloc(sizeof(Tree));
            CaracteresVetor[cont]->direita = CaracteresVetor[cont]->esquerda = NULL;
            CaracteresVetor[cont]->info = letra;
            cont++;
        }
    }
    return CaracteresVetor;
}

Tree *criaArvore(Tree *arvDir, Tree*arvEsq, Caracter *info){
    if(!info) return NULL;

    Tree *temp = malloc(sizeof(Tree));
    if (temp) {
        temp->info = info;
        temp->direita = arvDir;
        temp->esquerda = arvEsq;
    }

    return temp;
}

Tree *OrganizaArvorePorPesos(Tree** vetorCaracter, int elementos, int inicio) {
    if(!vetorCaracter || (inicio + 1) == elementos) return NULL;
    
    Tree *arvore = NULL;
    int fim = elementos;
    while(elementos!=1){
        int peso1 = RetornaPesoCaracter(vetorCaracter[inicio]);
        int peso2 = + RetornaPesoCaracter(vetorCaracter[inicio+1]);
        Caracter *c = CriaCaracter('\0', (peso1+peso2));
        inicio++;

        if( peso1>=peso2) 
            arvore = criaArvore(vetorCaracter[inicio-1], vetorCaracter[inicio], c);

        else 
            arvore = criaArvore(vetorCaracter[inicio], vetorCaracter[inicio-1], c);
        
        vetorCaracter[inicio] = arvore;
        vetorCaracter[inicio - 1] = NULL;
        QuickSort(vetorCaracter,inicio, fim-1);
        elementos--;
    }

    return arvore;
}

bitmap *BuscaBinaria(bitmap *bm, Tree *arv, unsigned char c, int *cont) {
    if (!arv) return NULL;
    
    // se achou
    if (arv->info->letra == c && !arv->direita && !arv->esquerda){
        *(cont) = 1;
        return bm;}
    
    // se esta na esquerda
    if (arv->esquerda) {
        bitmapAppendLeastSignificantBit(bm, 0);
        bm = BuscaBinaria(bm, arv->esquerda, c, cont);
        if(*(cont)) return bm;
        bitmapRemoveLeastSignificantBit(bm);
    }

    // se esta na direita
    if (arv->direita) {
        bitmapAppendLeastSignificantBit(bm, 1);
        bm = BuscaBinaria(bm, arv->direita, c, cont);
        if(*(cont)) return bm;
        bitmapRemoveLeastSignificantBit(bm);
    }

    return bm;
}

bitmap **tabelaTraducao(unsigned char *letras, Tree *arv, int quant){
    if(!arv) return NULL;

    bitmap **tabela = malloc(quant*sizeof(bitmap*));
    bitmap *sosia = NULL;

    int achou = 0;
    for(int i = 0; i < quant;i++){
        sosia = bitmapInit(256);
        sosia = BuscaBinaria(sosia, arv, letras[i], &achou);
        tabela = traslantionGuide(tabela, i, sosia);
        printf("Caracter: %c - ", letras[i]);
        bitmapPrint(sosia);
        achou = 0;
    }

    return tabela;
}
void vetoresBase(unsigned char *letras, int quant, Tree **lista){
    if(!lista || !quant) return;

    for(int i = 0;i<quant;i++)
        letras[i] = lista[i]->info->letra;
}

int IsLeaf(Tree *arv) {
    if (!arv) return 0;

    if (!arv->direita && !arv->esquerda) return 1;
    return 0;
}

void ImprimeVetor(Tree **vetor, int quant) {
    if (!vetor) return;

    for (int i = 0; i <quant; i++)
        printf("%c: %d\n", vetor[i]->info->letra, vetor[i]->info->peso);

    printf("\n");
}

void ImprimeArvore(Tree *treeNode) {
    printf("<");
    if (treeNode) {
        if (treeNode->info->letra != '\0') 
        printf("%c", treeNode->info->letra);
        ImprimeArvore(treeNode->esquerda);
        ImprimeArvore(treeNode->direita);
    }
    printf(">");
}

bitmap *ImprimeArvoreArquivo(Tree *tree, FILE *fCompactado, bitmap *arvBit) {
    if (!tree || !fCompactado) return;
    if (IsLeaf(tree)) {
        bitmapAppendLeastSignificantBit(arvBit, 1);
        unsigned char *byte = CharToByte(tree->info->letra);
        for(int i=0;i<8;i++){
            if(byte[i]=='0') bitmapAppendLeastSignificantBit(arvBit, 0);
            if(byte[i]=='1') bitmapAppendLeastSignificantBit(arvBit, 1);
            }
       
    } else{
        bitmapAppendLeastSignificantBit(arvBit, 0);
        } 

    ImprimeArvoreArquivo(tree->esquerda, fCompactado, arvBit);
    ImprimeArvoreArquivo(tree->direita, fCompactado,  arvBit);

}

/** Funcoes de liberacao */
void LiberaArvore(Tree *treeNode) {
    if (!treeNode) return;

    LiberaCaractere(treeNode->info);
    LiberaArvore(treeNode->direita);
    LiberaArvore(treeNode->esquerda);
    free(treeNode);
}

void LiberaCaractere(Caracter *character) {
    if (!character) return;
    free(character);
}

Tree **AdicionaCodParada(Tree **arv, int quant){
    if(!arv || !quant) return NULL;
    arv[quant] = malloc(sizeof(Tree));
    Caracter *nulo =  malloc(sizeof(Caracter));
    nulo->letra = '^';
    nulo->peso = 1;
    arv[quant]->info = nulo;
    return arv;

}

unsigned char *CharToByte(unsigned char c) {
    int num = (int)c;
    unsigned char *convertido = malloc(8 * sizeof(unsigned char));

    if (convertido == NULL) {
        printf("Erro de alocação de memória\n");
        return NULL;
    }

    // Calcula o número em binário
    for (int i = 7; i >= 0; i--) {
        convertido[i] = (num % 2) + '0'; // Convertendo para '0' ou '1'
        num /= 2;
    }

    // Imprime o resultado
    // for (int i = 0; i < 8; i++) 
    //     printf("%c", convertido[i]);
    // printf("\n");

    return convertido;
}

unsigned char ByteToChar(unsigned char *byte) {
    unsigned char c = 0;
    
    for (int i = 0; i < 8; i++) {
        if (byte[i] == '1') {
            c += pow(2, 7 - i);
        }
    }

    return c;
}

Tree *RecuperaArvore(FILE *compactado, Tree *arv, unsigned char *texto, bitmap *bits){
    if(!compactado) return NULL;
    short int tamBits = 0;
    unsigned int num = 0;
    fread(&tamBits,sizeof(short int), 1, compactado);
    InsereLenght(tamBits, bits);
    LerBitmapArquivo(bits, compactado);
    arv = ColocandoConteudoArvore(arv, bits, &num);
    return arv;
    /*for(int i = 0; i<tamBits; i++){
        unsigned char bit = bitmapGetBit(bits, i);
        if(bit == 0){
            temp->info = CriaCaracter('\0',-1);
            //temp->esquerda = RecuperaArvore(compactado,temp->esquerda, texto, bits);
            //temp->direita = RecuperaArvore(compactado,temp->direita,texto, bits);
        }
    else{   /*unsigned char letra[8];
            fread(&letra, sizeof(unsigned char),8,compactado);
            temp->info = CriaCaracter(ByteToChar(letra), -1);*/
            
        
    }
    

Tree *ColocandoConteudoArvore(Tree *arv, bitmap *bits, unsigned int *tamAtual){
        arv = malloc(sizeof(Tree));
        int bit = bitmapGetBit(bits, (*tamAtual));
        if(bit == 0){
            arv->info = CriaCaracter('\0',-1);
            (*tamAtual)++;
            arv->esquerda = ColocandoConteudoArvore(arv->esquerda, bits, tamAtual);
            arv->direita = ColocandoConteudoArvore(arv->direita, bits, tamAtual);
        }
    else if(bit == 1)
        {   unsigned char letra[8];
            (*tamAtual++);
            for(int j = 0;j<8;j++){
               
                letra[j] = bitmapGetBit(bits,*tamAtual);
                (*tamAtual++);
            }
            arv->info = CriaCaracter(ByteToChar(letra), -1);
            return arv;
        } 
}
/*
 if(!compactado) return NULL;
    Tree *temp = malloc(sizeof(Tree));
    unsigned int i = bitmapGetLength(bits);
    //fread(&bits, sizeof(bitmap),1,compactado);
    /*if(texto[bitmapGetLength(bits)] == '0'){
            temp->info = CriaCaracter('\0',-1);
            temp->esquerda = RecuperaArvore(compactado,temp->esquerda, texto, bits);
            temp->direita = RecuperaArvore(compactado,temp->direita,texto, bits);
        }
    else if(texto[bitmapGetLength(bits)] == '1')
        {   unsigned char letra[8];
            fread(&letra, sizeof(unsigned char),8,compactado);
            temp->info = CriaCaracter(ByteToChar(letra), -1);
            return temp;
        } 
    return temp;*/