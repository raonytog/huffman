
/*#include"tree.h"
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
tree *CriaListaPorPeso(int *vetor){
   
   if(!vetor) return;
   tree *lista = NULL;
   for(int i = 0; i<MAX; i++){
        if(vetor[i]>0){
           caracter *letra = malloc(sizeof(caracter));
           letra->letra = (char)i;
           letra->peso = vetor[i];
           lista = InsereNaListaSimples(lista, letra);
        }
   }
    return lista;
}

tree *InsereNaListaSimples(tree *lista, caracter *letra){
    if(!letra) return;
    tree *temp = malloc(sizeof(caracter));
    temp->info = letra;
    temp->direita = lista;
    return temp;
    
}

tree *QuickSortLista(tree *inicio, tree *fim){
    if(inicio==fim)return;
    tree *pivot = ParticaoLista(inicio, fim);
    if(pivot && pivot->direita) QuickSortLista(pivot->direita, fim);
    if(pivot && inicio) QuickSortLista(inicio, pivot);
    return pivot;
    
}

tree *RetornaUltimoNo(tree *lista){
    tree *t = lista;
    while(t->direita){
        t = t->direita;
    }
    return t;
}

/*tree *ParticaoLista(tree *inicio, tree *fim){
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
*/