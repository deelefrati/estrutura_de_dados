#include <stdio.h>
#include <stdlib.h>

typedef struct tipo_pilha pilha;
typedef struct tipo_arranjo arranjo;

struct tipo_pilha { //representa a pilha
	char nome[20];
	char mensagem[280];
	int amigo; //se for 1 é amigo, se for 0 não é amigo
	struct tipo_pilha *prox;
};

struct tipo_arranjo { //representa a pilha (sequencia) e seu topo
	pilha *sequencia;
	pilha *topo;
};

//pilha do arranjo tem cabeca
arranjo *criarPilha(){
	arranjo *P = (arranjo*) malloc (sizeof(arranjo));
	P->sequencia = (pilha*) calloc(1, sizeof(pilha));
	P->topo = P->sequencia;
	return P;
}

int pilha_vazia(arranjo *P){
	if (P->sequencia == P->topo){
		return 1;
	}
	else{
		return 0;
	}
}

pilha *alocarPilha(char name[], char men[], int dado){
	pilha *novo = (pilha*) malloc (sizeof(pilha));
	if(novo != NULL){
		strcpy(novo->nome, name);
		strcpy(novo->mensagem, men);
		novo->amigo = dado;
		novo->prox = NULL;
	}
	else{
		printf("Erro na alocacao de memoria");
	}
	return novo;
}

void *empilhar(arranjo *P, char name[], char men[], int dado){
	pilha *novo = alocarPilha(name, men, dado);
	if(P->sequencia == NULL){
		P->sequencia = novo;
		P->topo = novo;
	}
	else{
		P->topo->prox = novo;
		P->topo = novo;
	}
}

pilha *desempilhar(arranjo *P){
	pilha *saida;
	pilha *aux;
	if (pilha_vazia(P)){
		printf("\n Não ha mensagens.");
	}
	else{
		aux = P->sequencia;
		saida = P->topo;
		while (aux->prox != P->topo){
			aux = aux->prox;
		}
		//atualizar o topo
		P->topo = aux;
		P->topo->prox = NULL;
		//free(P->topo->prox);
	}
	return saida;
}

void mostrar(arranjo *P){
	pilha *aux;
	if(P->sequencia->prox == NULL){ //ou P->sequencia == P->topo
		printf("Pilha vazia.");
	}
	else{
		aux = P->sequencia->prox; //aux aponta para o primeiro elemento
		while (aux != NULL){
			printf("Quem enviou a mensagem -> %s", aux->nome);
			printf("\nA mensagem -> %s\n", aux->mensagem);
			aux = aux->prox;
		}
	}
}

pilha *topo(arranjo *P){
	return P->topo;
}