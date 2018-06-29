#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <limits.h>

void bubbleSort(int A[],int n){
	int aux;
	for (int i = 0; i < n; ++i){
		for(int j = 0; j < n-1; ++j){
			if (A[j] > A[j+1]){
				aux = A[j+1];
				A[j+1] = A[j];
				A[j] = aux; 
			}
		}
	}
}

void improvedBubbleSort(int A[], int n){
	int aux;
	bool troca;
	for(int i = 0; i < n; ++i){
		troca = false;
		for(int j = 0; j < n-1-i; ++j){
			if (A[j] > A[j+1]){
				aux = A[j+1];
				A[j+1] = A[j];
				A[j] = aux;
				troca = true; 
			}	
		}
		if(!troca){
			break;
		}
	}
}

void insertionSort(int A[], int n){
	int key, j;
	for (int i = 1; i < n; ++i){
		key = A[i];
		j = i-1;
		while(j >= 0 && A[j] > key){
			A[j+1] = A[j];
			--j;
		}
		A[j+1] = key;
	}
}

void shellSort(int A[],int n){
	int key, i,h;
	for(h = 1; h < n; h = 3*h+1);
	while(h > 0){
		h = (h-1)/3;
		for(int j = h; j < n; ++j){
			key = A[j];
			i = j;
			while(i >= h && A[i - h] > key){
				A[i] = A[i - h];
				i = i - h;
			}
			A[i] = key;
		}
	}
}

void swap(int *x, int *y){ 
   int temp;
   temp=*x;
   *x=*y;
   *y=temp;
}

int partition(int A[], int p, int r){
	int pivo, i, j;
	pivo = A[r];
	i = p - 1;
	for(j = p; j<r; j++){
		if(A[j] <= pivo){
			i++;
			swap(&A[i], &A[j]);
		}
	}
	swap(&A[i+1], &A[r]);
	return i+1;
}

void quickSort(int A[], int p, int r){
	int q;
	if (p<r){
		q = partition(A, p, r);
		quickSort(A, p, q-1);
		quickSort(A, q+1, r);
	}
}

void selectionSort(int A[], int tamanho){
	int i, j, pos, menor;
	for (i=0; i < tamanho - 1; i++){//recupera o elemento para a troca
		pos = i;
		menor = A[i];
		for (j= i+1; j < tamanho; j++){
			if (A[j] < menor){//busca o menor elemento
				pos = j;
				menor = A[pos];
			}
		}
		A[pos] = A[i];//põe na posição correta
		A[i]= menor;
	}
}

void maxHeapify(int A[], int i, int tam){
	int maior;
	int e = 2*i+1; //índice do nó esquerdo (C:2*i+1)
	int d = 2*i+2; //índice do nó direito (c:2*i+2)
	if ((e < tam)&&(A[e] > A[i])){ 
		maior = e; //o índice "e" possui o maior
	}else{
		maior = i; //nada muda
	}
	if ((d < tam)&&(A[d] > A[maior])){ 
		maior = d; //o índice "d" possui o maior
	}
	if (maior != i) { //se existe um filho maior
	swap(&A[i], &A[maior]);
	maxHeapify(A,maior,tam);//repete p/ o trocado
	}
}

void buildMaxHeap(int A[], int tam){
	int i;
	for (i = tam/2; i>=0; i--){
		maxHeapify(A, i, tam);
	}
}

void heapSort(int A[], int tam){
	buildMaxHeap(A, tam);
	for (int i = tam - 1; i>=0; i--){
		swap(&A[0], &A[i]);
		tam--;//reduz o tamanho da heap considerada
		maxHeapify(A,0,tam);//corrige a heap
	}
}

void merge(int A[], int p, int q, int r){
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = (int*) malloc((n1+1)*sizeof(int)); //armazena a parte esquerda
	int *R = (int*) malloc((n2+1)*sizeof(int)); //armazena a parte direita
	for(i = 1; i <= n1; i++){
		L[i] = A[p+i-1];
	}
	for(j = 1; j <= n2; j++){
		R[j] = A[q+j];
	}
	L[n1+1]= INT_MAX; //usar a biblioteca <limits>
	R[n2+1]= INT_MAX;
	i = 1;
	j = 1;
	for(k=p; k<=r; k++){
		if(L[i] <= R[j] ){
			A[k]=L[i];
			i=i+1;
		}else{
			A[k]=R[j];
			j=j+1;
		}
	}
}

void mergeSort(int A[], int inicio, int fim){
	int meio; 
	if (inicio < fim){
		meio = (inicio+fim)/2;
		mergeSort (A, inicio, meio);
		mergeSort (A, meio+1, fim);
		merge (A, inicio, meio, fim);
	}
}

/*void mergeSort(int A[], int n){
   for (int curr_size=1; curr_size<=n-1; curr_size = 2*curr_size){
       for (int left_start=0; left_start<n-1; left_start += 2*curr_size){
           int mid = left_start + curr_size - 1;
           int right_end = min(left_start + 2*curr_size - 1, n-1);
           merge(A, left_start, mid, right_end);
       }
   }
}*/

int min(int x, int y) { return (x<y)? x :y; }

void preencher(int A[],int n){
	int i=1,j;
	srand(time(NULL));
	A[0] = rand()%n;
	while(i< n){
		A[i] = rand()%n;
		j=0;
		while(A[i] != A[j]) ++j;
			if(i == j) ++i;
	}
}	

void mostrar(int A[], int n){
	for (int i = 0; i < n; ++i){
		printf("%d ", A[i]);
	}
}