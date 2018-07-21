#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct tipo_ranking{
	char nome[256];
	int qntdAcertos;
	int pontuacao;
	struct tipo_ranking *prox;
}ranking;

int hashRanking(int dado){
	return dado % 5;
}

ranking *alocarRanking(char nome2[], int qntdAcertos2, int pontuacao2){
	ranking *novo = (ranking *) malloc (sizeof(ranking));
	if(novo == NULL){
		printf("Erro na reserva de memoria");
	}
	else{
		 strcpy(novo->nome, nome2);
		 novo->qntdAcertos = qntdAcertos2;
		 novo->pontuacao = pontuacao2;
		novo->prox = NULL;
	}
	return novo;
}

ranking *criarRanking(){		
	ranking *R = (ranking*) calloc(1,sizeof(ranking));
	if (R != NULL){
		R -> prox = NULL;
	}
	return R;
}

void inserir_fim_ranking(ranking* R, char nome2[], int qntdAcertos2, int pontuacao2){
	ranking *aux, *novo;
	aux = R;
	novo = alocarRanking(nome2, qntdAcertos2 ,pontuacao2);
	while (aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = novo;
}

void mostrarRanking(ranking* R){
	ranking *aux;
	aux = R->prox; 
	if (aux == NULL){
		printf("Nome vazio!\n");
	}
	else{
		while (aux != NULL){
			printf("\nNome: %s ", aux->nome);
			printf("\nQuantidade de acertos: %d ", aux->qntdAcertos);
			printf("\nPontuação: %d ", aux->pontuacao);
			printf("\n");
			aux = aux->prox;
		}
	}
}

void mostrarTudoRanking(ranking *tabelaRanking[]){
	int j=0;
	for(int i=0; i<5;++i){
		mostrarRanking(tabelaRanking[hashRanking(i)]);
	}
}

ranking *pesquisar(ranking* R, char nome2[]){
	ranking *aux;
	aux = R->prox;
	while (aux != NULL){
		if (strcmp(aux->nome,nome2) == 0){
			return aux;
		}else{
			aux = aux->prox;
		}
	}
	return NULL;	
}