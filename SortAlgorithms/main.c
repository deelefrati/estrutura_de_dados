#include <stdio.h>	
#include <stdlib.h>
#include "all.c"
//test 

int menu(){
	int opcao;
	printf("\n");
	printf("\nOpcoes:");
	printf("\n0. Sair");
	printf("\n1. Ṕreencher o vetor");
	printf("\n2. Bubble Sort ");
	printf("\n3. Insertion Sort");
	printf("\n4. Shell Sort");
	printf("\n5. Improved Bubble Sort");
	printf("\n6. Quick Sort");
	printf("\n7. Selection Sort");
	printf("\n8. Heap Sort");
	printf("\n9. Merge Sort");
	printf("\nInforme a opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

int main() {
	int n, opcao;
	do{
		opcao = menu();
		switch (opcao){
		case 1:
			printf("Digite a qntd de elementos do vetor: \n");
			scanf("%d", &n);
			int *A = (int*) malloc(n*sizeof(int));
			preencher(A, n);
			mostrar(A, n);
		break;
		case 2:
			bubbleSort(A, n);
			mostrar(A, n);
		break;
		case 3:	
			insertionSort(A, n);
			mostrar(A, n);
		break;
		case 4:
			shellSort(A, n);
			mostrar(A, n);
		break;	
		case 5:
			improvedBubbleSort(A,n);
			mostrar(A,n);
		break;
		case 6:
			quickSort(A,0,n-1);
			mostrar(A,n);
		break;
		case 7:
			selectionSort(A,n);
			mostrar(A,n);
		break;
		case 8:
			heapSort(A,n);
			mostrar(A,n);
		break;
		case 9:
			mergeSort(A,0,n-1);
			mostrar(A,n); 
		break;
		}
	}while(opcao);
		
		return 0;
}
