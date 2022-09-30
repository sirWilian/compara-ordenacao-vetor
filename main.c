#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ordenacao.h"
#define TAM 1000
#define NUMTESTES 50

void preenche_vetor(int vetor[], int tam){
    int i;
    for (i=0; i<tam; i++)
        vetor[i] = rand()%200000; 
}

int verificaOrdenacao(int vetor[], int tam){
    int i;
    for (i=0; i<tam-1; i++){
        if (vetor[i] > vetor[i+1])
            return 0;
    }
    return 1;
}

void resultOrdenacao(double total, int start, int end, int vetor[], int tam, int *numComp, double *somaTempo){
    total = ((double)end - start)/CLOCKS_PER_SEC;
    if(!verificaOrdenacao(vetor, TAM))
        printf("Ordenação falhou!");
    printf("Tempo de execução: %f segundos\n", total);
    printf("Numero de comparaçoes: %d\n", *numComp);
    *somaTempo = *somaTempo + total;
    *numComp = 0;
}

void resultBusca(double total, int start, int end, int vetor[], int tam, int *numComp, double *somaTempo){
    total = ((double)end - start)/CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", total);
    printf("Numero de comparaçoes: %d\n", *numComp);
    *somaTempo = *somaTempo + total;
    *numComp = 0;
}

int main(){
	char nome[MAX_CHAR_NOME];
	int buscaBin, buscaSeq;
	int numComp = 0;

	int* vetor = malloc(TAM * sizeof(int));
	if(vetor == NULL){
		printf("Falha fatal. Impossível alocar memoria.");
		return 1;
	}
    preenche_vetor(vetor, TAM);
	getNome(nome);
	printf("Trabalho de %s\n", nome);
	printf("GRR %u\n", getGRR());

	clock_t start, end;
    double total = 0;
    double somaTempo = 0;
    double mediaTempo = 0;
    
    start = clock();//start recebe o "ciclo" corrente
    numComp = insertionSort(vetor, TAM);
    end = clock();//end recebe o "ciclo" corrente
    printf("\nINSERTION SORT\n");
    resultOrdenacao(total, start, end, vetor, TAM, &numComp, &somaTempo);
    preenche_vetor(vetor, TAM);
    mediaTempo = somaTempo / NUMTESTES;
    printf("Média de tempo com %d execuções: %f\n", NUMTESTES, mediaTempo);

    start = clock();
    numComp = selectionSort(vetor, TAM);
    end = clock();
    printf("\nSELECTION SORT\n");
    resultOrdenacao(total, start, end, vetor, TAM, &numComp, &somaTempo);
    preenche_vetor(vetor, TAM);
    mediaTempo = somaTempo / NUMTESTES;
    printf("Média de tempo com %d execuções: %f\n", NUMTESTES, mediaTempo);

    start = clock();
    numComp = mergeSort(vetor, TAM);
    end = clock();
    printf("\nMERGE SORT\n");
    resultOrdenacao(total, start, end, vetor, TAM, &numComp, &somaTempo);
    preenche_vetor(vetor, TAM);
    mediaTempo = somaTempo / NUMTESTES;
    printf("Média de tempo com %d execuções: %f\n", NUMTESTES, mediaTempo);

    start = clock();
    numComp = quickSort(vetor, TAM);
    end = clock();
    printf("\nQUICK SORT\n");
    resultOrdenacao(total, start, end, vetor, TAM, &numComp, &somaTempo);
    mediaTempo = somaTempo / NUMTESTES;
    printf("Média de tempo com %d execuções: %f\n", NUMTESTES, mediaTempo);

    numComp = 0;
    start = clock();
    buscaBin = buscaBinaria(vetor, TAM, 8, &numComp);
    end = clock();
    printf("\nBUSCA BINARIA\n");
    resultBusca(total, start, end, vetor, TAM, &numComp, &somaTempo);
    printf("Posição do elemento no vetor : %d\n", buscaBin);
    printf("\n");
    mediaTempo = somaTempo / NUMTESTES;
    printf("Média de tempo com %d execuções: %f\n", NUMTESTES, mediaTempo);


    numComp = 0;
    start = clock();
    buscaSeq = buscaSequencial(vetor, TAM, 8, &numComp);
    end = clock();
    printf("\nBUSCA SEQUENCIAL\n");
    resultBusca(total, start, end, vetor, TAM, &numComp, &somaTempo);
    printf("Posição do elemento no vetor : %d\n", buscaSeq);
    mediaTempo = somaTempo / NUMTESTES;
    printf("Média de tempo com %d execuções: %f\n", NUMTESTES, mediaTempo);

	//É obrigatório que você libere a memória alocada dinâmicamente via free
	free(vetor);
    vetor = NULL;
	return 0;
}
