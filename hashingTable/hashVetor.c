#include<stdio.h>
#include<stdlib.h>

void inicializarVetor(int V[],int n){
	for(int i=0; i<=n; i++){
		V[i] = -1;
	}
}

void printarVetor(int V[],int n){
	for (int i = 0; i < n; ++i){
		printf("%d ", V[i]);
	}
	printf("\n");
}

int hash(int valor, int i, int tam){
	int x = ((valor + i) % tam);
	return x;
}

void inserir(int V[], int valor, int tam){
	int j,i=0;
	do{
		j = hash(valor, i, tam);
		//printf("%d\n", j); 
		if(V[j] == -1){
			V[j] = valor;
			i = tam +1;
		}else{
			i++;
		}
	}while(i <= tam);
}

int buscar(int V[],int valor, int tam){
	int i=0;
	if (V[hash(valor,i ,tam)] != -1){
		do{
			if(V[hash(valor,i,tam)] == valor){
				return 1;
			}else{
				i++;
			}
		}while(i<=tam);
	}else{
		return 0;
	}
}

int main(){
	int tam, elemento, res;
	printf("\nQntd de posições de vetor -> ");
	scanf("%d", &tam);
	int *V = (int*)malloc(tam*sizeof(int));	
	inicializarVetor(V,tam);
	//printarVetor(V, tam);
	for(int i=0; i< tam;i++){
		printf("Digite o valor que deseja inserir: \n");
		scanf("%d", &elemento);
		inserir(V, elemento, tam);
	}
	printarVetor(V, tam);	
	printf("Digite o valor que deseja buscar -> ");
	scanf("%d", &elemento);
	res = buscar(V, elemento, tam);
	if(res == 1){
		printf("Achou !!!\n");
	}else{
		printf("Não achou =( \n");
	}
	return 0;
}
