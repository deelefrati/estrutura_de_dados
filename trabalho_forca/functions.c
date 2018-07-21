#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct tipo_lista{
	char nome[256];
	char dica1[256];
	char dica2[256];
	struct tipo_lista *prox;
}lista;

int hash(int dado){
	return dado % 26;
}


lista *alocar(char nome2[], char newDica[], char newDica2[]){
	lista *novo = (lista *) malloc (sizeof(lista));
	if(novo == NULL){
		printf("Erro na reserva de memoria");
	}
	else{
		 strcpy(novo->nome, nome2);
		 strcpy(novo->dica1, newDica);
		 strcpy(novo->dica2, newDica2);
		novo->prox = NULL;
	}
	return novo;
}

lista *criar(){		
	lista *L = (lista*) calloc(1,sizeof(lista));
	if (L != NULL){
		L -> prox = NULL;
	}
	return L;
}

void inserir_fim(lista* L, char nome2[], char newDica[], char newDica2[]){
	lista *aux, *novo;
	aux = L;
	novo = alocar(nome2,newDica,newDica2);
	while (aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = novo;
}		

void colocar_fim(lista *L){
	lista *aux = L->prox;
	lista *aux2 = L->prox;
	if(L->prox != NULL){
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = L->prox;
		L->prox = L->prox->prox;
		aux->prox->prox = NULL;
	}
}

void mostrar(lista* L){
	lista *aux;
	aux = L->prox; 
	if (aux == NULL){
		printf("Nome vazio!\n");
	}
	else{
		while (aux != NULL){
			printf("%s ", aux->nome);
			printf("\n");
			aux = aux->prox;
		}
	}
}

void mostrarTudo(lista *dicionario[]){
	char vetor[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int j=0;
	for(int i=97; i<123;++i){
		printf("Palavras que começam com a letra:  %c \n", vetor[j]);
		++j;
		mostrar(dicionario[hash(i)]);
	}
}

int sortear(){
	//srand(time(NULL));
	int num = rand() % 26;
	//printf("%d\n", num);
	return num;

}

lista *escolherPalavra(lista *dicionario[]){
	int x = sortear();
	while (dicionario[x]->prox == NULL){
		x = sortear();
	}
	lista *aux = alocar(dicionario[x]->prox->nome,dicionario[x]->prox->dica1,dicionario[x]->prox->dica2);
	colocar_fim(dicionario[x]);
	return aux;  
}

int listaVazia(lista *dicionario[]){
	for(int i=97; i<123;++i){
		if(dicionario[hash(i)]->prox != NULL){
			return 1;
		}
	}
	return 0;	
}

void inicializarPalavra(char word[], int count){
	for (int i = 0; i < count; ++i){
		word[i] = '_';
		}
}

void mostrarPalavra(char palavra[],int count){
	for (int i = 0; i < count; ++i){
		printf("%c ", palavra[i]);
		
	}
}

int comparar(char palavra[],char novaPalavra[], char letra, int count){
	int entrou=0;
	for (int i = 0; i < count; ++i){
		if(palavra[i] == letra) {
			entrou = 1;
			novaPalavra[i] = letra;
		}
	}
	return entrou;
}