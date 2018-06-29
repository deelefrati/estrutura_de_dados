#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "colors.h" 

typedef struct fila_Monte monte;

struct fila_Monte{ 
	int left;
	int right;
	struct fila_Monte *prox;
};

int count = 0;
int num_mao = 7;

monte *criar(){ //cria a cabeça da lista do monte 
	monte *L;
	L = (monte*)calloc(1, sizeof(monte));
	if (L != NULL){
		L -> prox = NULL;
	}else{
		printf("\nErro ao criar a lista do monte");
	}
}

monte *preencher_pecas(monte *L){ //preenche as 28 peças de 0 até 6
	monte *novo, *aux;
	aux = L;
	for(int i=0; i<=6; i++){
		for(int j=i; j<=6; j++){
			novo = (monte*)calloc(1,sizeof(monte)); //cria uma nova peça 
			novo->left = i;
			novo->right = j;
			while(aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = novo;
		}
	}
}

void iniciarJogo(monte *L, monte *T){
	monte *aux = L->prox;
	while(aux->prox->prox != NULL){ //percorre até o penultimo elemento do monte 
		aux = aux->prox;
	}
	T->prox = aux->prox; //Cabeça da mesa vai apontar pro ultimo elemento, ou seja a peça [6][6]
	aux->prox = NULL;
}

void mostrar(monte* L){ //mostra todas as peças de qualquer lista
	monte *aux;
	aux = L->prox; 
	if (aux == NULL){
		printf("Lista vazia!");
	}
	else{
		while (aux != NULL){
			printf("[%d][%d] ", aux->left, aux->right);
			aux = aux->prox;
		}
	}
}

void mostrarMao(monte* L){ //mostra todas as peças da mão
	monte *aux;
	aux = L->prox;
	int ordem = 1; 
	if (aux == NULL){
		foreground(RED);
		printf("Lista vazia!");
		style(RESETALL);
	}
	else{
		while (aux != NULL){
			printf("[%d , %d] %d \n", aux->left, aux->right, ordem);
			aux = aux->prox;
			ordem++;
		}
	}
}

int gerarAleatorios(int count){
  int pecas;
  srand(time(NULL));
  pecas = rand() % (27 - count); //intervalo da rand: [0,27]
  return pecas;
 }

void gerarMao(monte *L, monte *M){
	monte *aux = L;
	monte *aux2 = M;
	monte *jesus;
	int n;
	for(int i=0; i<7; i++){ //vai fazer a função 7 vezes 
		n = gerarAleatorios(count); //gera um numero random de 0 até o tamanho atual do monte 
		count = count + 1;
		//printf("%d\n", n);	
		aux = L; //reseta a var AUX
		aux2 = M; //reseta a var AUX2
		for(int j=0; j<n; j++){ //percorre o monte até a posição n-1
			aux = aux->prox;
		}
		jesus = aux->prox; //jesus é o elemento que vai ser inserido na mão 
		aux->prox = aux->prox->prox; 
		while(aux2->prox != NULL){ //percorre até o fim do mão
			aux2 = aux2->prox;
		}
		aux2->prox = jesus; //insere o elemento sorteado na ultima posição da mão
		jesus->prox = NULL; 
	}	
}

monte *comprarPeca(monte *L, monte *M){
	monte *aux = L;
	monte *aux2 = M;
	monte *jesus;
	int n;
	n = gerarAleatorios(count); //gera um numero random de 0 até o tamanho atual do monte 
	count = count + 1; 	
	aux = L; //reseta a var AUX
	aux2 = M; //reseta a var AUX
	for(int j=0; j<n; j++){ //percorre o monte até a posição n-1
		aux = aux->prox;
	}
	jesus = aux->prox; //jesus é o elemento que vai ser inserido na mão
	aux->prox = aux->prox->prox; 
	while(aux2->prox != NULL){ //percorre até o fim do mão
		aux2 = aux2->prox;
	}
	aux2->prox = jesus; //insere o elemento sorteado na ultima posição da mão
	jesus->prox = NULL;	
	num_mao ++;
	return jesus;
}


void jogada(monte *M, monte *T,int elemento){
	if(num_mao == 0){
				foreground(GREEN);
				printf("\t\t\t\t\t\t\t\nPARABÉNS, VOCÊ GANHOU !!!\n");
				style(RESETALL);
	}else{
		monte *aux = M;
		monte *table = T;
		int swap;
		int escolha;
		for(int i=1; i < elemento; i++){ //percorre a mão até a posição elemento-1
			aux = aux->prox;
		}
		monte *deus = aux->prox;
		printf("\nPara jogar a peça na esquerda digite 1, caso deseja jogar na direita, digite 0:\n ");
		scanf("%d",&escolha);
		if (escolha == 1){
			if (deus->left == T->prox->left){//lado esquerdo comparado com lado esquerdo  
				aux->prox = aux->prox->prox;
				deus->prox = table->prox;
				table->prox = deus;
				swap = deus->right;
				deus->right = deus->left;
				deus->left = swap;
				num_mao --;
				printf("\nA mesa atual é\n" );
				mostrar(T);
				printf("\n");
			}else if(deus->right == T->prox->left){ //lado direito comparado com o lado esquerdo
				aux->prox = aux->prox->prox;
				deus->prox = table->prox;
				table->prox = deus;
				num_mao --;
				printf("\nA mesa atual é\n" );
				mostrar(T);
				printf("\n");
			}
			else{
				foreground(RED);	
				printf("\t\nJogada inválida!\n");
				style(RESETALL);
			}
		}
		else if (escolha == 0){
			monte *fim = T;
			while (fim->prox != NULL){
				fim = fim->prox;
			}
			if(deus->right == fim->right){// lado direito comparado com o lado direito 
				while(table->prox != NULL){
					table = table->prox;
				} 
				aux->prox = aux->prox->prox;
				table->prox = deus;
				deus->prox = NULL;
				swap = deus->right;
				deus->right = deus->left;
				deus->left = swap;
				num_mao --;
				printf("\nA mesa atual é\n" );
				mostrar(T);
				printf("\n");
			}else if(deus->left == fim->right){ //lado esquerdo comparado com o lado direito 
				while(table->prox != NULL){
					table = table->prox;
				} 
				aux->prox = aux->prox->prox;
				table->prox = deus;
				deus->prox = NULL;
				num_mao --;
				printf("\nA mesa atual é\n" );
				mostrar(T);
				printf("\n");
			}
			else{
				foreground(RED);
				printf("\t\nJogada inválida\n");
				style(RESETALL);
			}
		}
	}	
}