
#include"tree.h"
#define MAX 256
 struct caracter
{
    int peso;
    char letra;
};
struct tree;
struct tree{
    caracter *info;
    tree *direita, *esquerda;
};
int RetornaPesoCaracter(tree *arv){
    if(!arv) return 0;
    return arv->info->peso;
}

int RetornaQuantidadeCaracteres(int *vetor){
    if(!vetor) return 0;
    int quant = 0;
    for(int i = 0; i<MAX; i++){
        if(vetor[i]>0) quant++;
   }
    return quant;
}
caracter *CriaCaracter(int letter, int peso){
    if(!peso) return NULL;
    caracter *letra = malloc(sizeof(caracter));
    letra->letra = (char)letter;
    letra->peso = peso;
    return letra;
    }
tree **CriaVetorPorPeso(int *vetor){
   
   if(!vetor) return NULL;
   int quant = RetornaQuantidadeCaracteres(vetor);
   tree **CaracteresVetor = malloc(quant*(sizeof(tree*)));
   int cont = 0;
   for(int i = 0; i<MAX; i++){
        if(vetor[i]>0){
           caracter *letra = CriaCaracter(i, vetor[i]);
           CaracteresVetor[cont] = malloc(sizeof(tree));
           CaracteresVetor[cont]->info = letra;
           cont++;
        }
   }
    return CaracteresVetor;
}

void QuickSort(tree **vet, int inicio, int fim){
    if(inicio>=fim) return;
    int pivot = particao(vet, inicio, fim);
    QuickSort(vet, pivot +1, fim);
    QuickSort(vet, inicio, pivot-1);
}

int particao(tree **vet, int inicio, int fim){
    int i = inicio -1;
    tree *pivot = vet[fim];
    for(int j = inicio;j<fim;j++){
        if(RetornaPesoCaracter(pivot)>=RetornaPesoCaracter(vet[j])){
            i++;
            if(i!=j){
            tree *temp = vet[i];
            vet[i] = vet[j];
            vet[j] = temp;
            printf("\n");
            
        } 
        }    
    }
    tree *temporario = vet[fim];
    vet[fim] = vet[i+1];
    vet[i+1] = temporario;
    return i+1;
}
tree *criaArvore(tree *arvDir, tree*arvEsq, caracter *info){
    if(!info) return NULL;
    tree *temp = malloc(sizeof(caracter));
    temp->info = info;
    temp->direita = arvDir;
    temp->esquerda = arvEsq;
    return temp;
    
}

tree *ParticaoLista(tree *inicio, tree *fim){
    tree *pivot = inicio; 
    tree *front = inicio;
    caracter *temp = NULL; 
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
int Compara(const void *a, const void *b) {
    tree *arv1 = *(tree **)a;
    tree *arv2 = *(tree **)b;
    return arv1->info->peso - arv2->info->peso;
}

void ImprimeStruct(tree **vetor, int quant) {
    for (int i = 0; i <quant; i++)
        printf("%c: %d\n", vetor[i]->info->letra, vetor[i]->info->peso);
    printf("\n");
}

tree *OrganizaArvorePorPesos(tree** vetorCaracter, int elementos, int inicio){
if(!vetorCaracter || (inicio + 1)==elementos) return NULL;
        tree *arvore = NULL;
        int fim = elementos;
        while(elementos!=1){
           int peso1 = RetornaPesoCaracter(vetorCaracter[inicio]);
           int peso2 = + RetornaPesoCaracter(vetorCaracter[inicio+1]);
           caracter *c = CriaCaracter('\0', (peso1+peso2));
           inicio++;
           if(peso1>=peso2){
             arvore = criaArvore(vetorCaracter[inicio-1],vetorCaracter[inicio], c);}
          else{
              arvore = criaArvore(vetorCaracter[inicio] ,vetorCaracter[inicio-1],c);
           }
           vetorCaracter[inicio] = arvore;
           QuickSort(vetorCaracter,inicio, fim-1);
           elementos--;
        }
        return arvore;
        }
        
    