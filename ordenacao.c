#include "ordenacao.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void getNome(char nome[]){
	//substitua por seu nome
	strncpy(nome, "Wilian Pereira dos Santos", MAX_CHAR_NOME);
	nome[MAX_CHAR_NOME-1] = '\0';//adicionada terminação manual para caso de overflow
}

unsigned int getGRR(){
	return 20203936;
}

//a função a seguir deve retornar o seu número de GRR
unsigned int getGRR();

void imprimeVetor(int vetor[], int tam){
    int i;
    for(i = 0; i < tam; i++){
        printf("%d ", vetor[i]);
    }    
	printf("\n");
}

/*realiza a busca e retorna a posição do elemento no vetor*/
int buscaSequencial(int vetor[], int tam, int valor, int* numComparacoes){
    if ((tam - 1) < 0)
        return -1;
    (*numComparacoes)++;
    if (valor == vetor[tam - 1])
        return tam - 1;
    return buscaSequencial(vetor, tam - 1, valor, numComparacoes);
}

/*realiza a busca e retorna a posição do elemento no vetor*/
int buscaBinaria2(int vetor[], int a, int b, int valor, int* numComparacoes){
    int m;
    if (a > b)
        return -1;
    m = floor((a + b)/2);
    (*numComparacoes)++;
    if (valor == vetor[m])
        return m;
    if (valor < vetor[m])
        return buscaBinaria2(vetor, a, m-1, valor, numComparacoes);
    return buscaBinaria2(vetor, m + 1, b, valor, numComparacoes);
}

int buscaBinaria(int vetor[], int tam, int valor, int* numComparacoes){
    return buscaBinaria2(vetor, 0, tam-1, valor, numComparacoes);
}

/*troca os elementos de posição*/
void troca(int vetor[], int a, int b){
        int x;
        x = vetor[a];
        vetor[a] = vetor[b];
        vetor[b] = x;
}

/*todos as funções de ordenação ordenam o vetor e retornam o número de comparações realizadas pela respectiva função*/
int insertionSort2(int vetor[], int a, int b){
    if (a >= b)
        return 0;
    int ultimo;
    int i;
    int numComp;
    numComp = insertionSort2(vetor, a, b - 1);
    ultimo = vetor[b];
    i = b - 1;
    while(i >=0 && vetor[i] > ultimo){
        (numComp)++;
        vetor[i+1] = vetor[i];
        i--;
    }
    vetor[i+1] = ultimo;
    return numComp;
}

int insertionSort(int vetor[], int tam){
    return insertionSort2(vetor, 0, tam - 1);
}

/*retorna o minimo do vetor*/
int min(int vetor[], int a, int b, int *numComp){
	if (a == b)
        return a;
    int menor;
    (*numComp)++;
    menor = min(vetor, a+1, b, numComp);
    if (vetor[a] < vetor[menor])
        return a;
    else
        return menor;
}

int selectionSort2(int vetor[], int a, int b){
    if (a >= b)
        return 0;
    int comp = 0;
	troca(vetor, a, min(vetor, a, b, &comp));
    return comp + selectionSort2(vetor, a+1, b);
}

int selectionSort(int vetor[], int tam){
    return selectionSort2(vetor, 0, tam-1);
}

/*copia um vetor em outro*/
void copiar(int vetor[], int v1[], int a, int b){
    int j = 0;
    for(int i=a; i <= b; i++){
        vetor[i] = v1[j];
        j++;
    }
}

int merge(int vetor[], int v1[], int a, int m, int b, int *numComp){
    int k = 0;
    int i = a;
    int j = m + 1;

    while(k < (b - a + 1)){
        (*numComp)++;
        if(j > b || (i <= m && vetor[i] <= vetor[j])){
            v1[k] = vetor[i];
            i++;
        }
        else{
            v1[k] = vetor[j];
            j++;
        }
        k++;
    }
    copiar(vetor, v1, a, b);
    return *numComp;
}
int mergeSort2(int vetor[], int v1[], int a, int b, int *numComparacoes){
    if(a >= b)
        return -1;
    int m;
    m = floor((a+b)/2);
    mergeSort2(vetor, v1, a, m, numComparacoes);
    mergeSort2(vetor, v1, m+1, b, numComparacoes);
    merge(vetor, v1, a, m, b, numComparacoes);
    return *numComparacoes;
} 
int mergeSort(int vetor[], int tam){
    int comp = 0;
    int* v1 = malloc(tam * sizeof(int));
    if(v1 == NULL){
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
	}
    comp = mergeSort2(vetor, v1, 0, tam-1, &comp);
    free(v1);
    return comp;
}

int particiona(int v[], int a, int b, int valor, int *numComp){
    int m = a -1;
    int i;
    for(i=a; i<=b; i++) {
        (*numComp)++;
        if(v[i] <= valor) {
            m++;
            troca(v, m, i);
        }
    }   
    return m;
}
int quickSort2(int vetor[], int a, int b){
    if(a >= b)
        return 0;
    int m; 
    int numComp = 0;
    m = particiona(vetor, a, b, vetor[b], &numComp);
    return numComp + quickSort2(vetor, a, m-1) + quickSort2(vetor, m+1, b);
}
int quickSort(int vetor[], int tam){
    return quickSort2(vetor, 0, tam-1);
}