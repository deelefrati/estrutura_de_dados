#include <stdio.h>	
#include <stdlib.h>
#include "AVL.c"

int menu(){
	int opcao;
	printf("\nOpcoes:");
	printf("\n0. Sair");
	printf("\n1. Inserir um nó");
	printf("\n2. Mostrar a arvore");
	printf("\n3. Remover um elemento da arvore");
	printf("\n4. Buscar um elemento");
	printf("\nInforme a opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

int main() {
	int opcao, elemento, h;
	no *L;
	L = criar();
	
	do{
		opcao = menu();
		switch (opcao){
		case 1:
			printf("Digite o valor: \n");
			scanf("%d", &elemento);
			no *novo;
			novo = alocar(elemento);
			L = inserir(L, novo);
		break;
		case 2:
			h = 0;
			mostrarArvoreBinaria(L, h);
			/*printf("\n");
			printf("\n");
			printf("\n");
			mostrarLargura(L);
	*/
		break;
		case 3:	
			printf("\nInforme o valor a ser excluir: ");
			scanf("%d", &elemento);
			L = removerFusaoAntecessor(L, elemento);
			L = atualizarAlturas(L);
		break;
		case 4:
			printf("Digite o valor: \n");
			scanf("%d", &elemento);
			no *raiz;
			raiz = buscar(L, elemento);
			if(raiz == NULL){
				printf("\n O número não está na árvore\n");
			}else{
				printf("\n O número está na árvore\n");
			}
		break;	
		}
	}while(opcao);
		
		return 0;
}