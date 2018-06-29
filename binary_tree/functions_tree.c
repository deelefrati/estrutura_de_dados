#include <stdio.h>
#include <stdlib.h>

//Declarar struct's 
typedef struct tipo_no no;
typedef struct tipo_fila fila;

struct tipo_no{
	int info;
	struct tipo_no *esq; //nó esquerdo
	struct tipo_no *dir; //nó direito
};

struct tipo_fila{
no *item;
struct tipo_fila *prox;
};

//funções de fila
fila *alocarFila(no *elemento){
	fila *novo=(fila *) malloc(sizeof(fila));
	if(novo != NULL){
		printf("Sem memoria disponivel");
	}else{
		novo->item = elemento;
		novo->prox = NULL;
		return novo;
	}
}

fila* enfileirar(fila *f, no *elemento){
	fila *novo = alocarFila(elemento);
	if(f == NULL){ //fila esta vazia
		f = novo; //primeiro da fila
	}else{
		fila *aux= f; //inserir no final da fila
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = novo;
	}
	return f;
}

fila *desenfileirar(fila *f, no **saida){
	fila *excluir;
	excluir = f; //elemento que deve ser excluído
	if (excluir!= NULL){
		f= f->prox;
		*saida = excluir->item;
		free(excluir);
	}
	return f;
}

//funções de arvores
	no *criar(){
		return NULL;
}

int arvoreVazia(no *raiz){
	if(raiz == NULL){
		return 1; //true
	}else{
		return 0; //false
	}
}

no *alocar(int dado){
	no *novo;
	novo = (no*) malloc(sizeof(no));
	if(novo == NULL){
		printf("Sem espaço na memória! \n");
	} else{
		novo->info = dado;
		novo->esq = NULL;
		novo->dir = NULL;
	}
	return novo;
}

no *inserir(no *raiz, no *novo){
	if(arvoreVazia(raiz)){
		raiz = novo;
	}else{
		if(novo->info < raiz->info){
			raiz->esq = inserir(raiz->esq, novo);
		}else{
			raiz->dir = inserir(raiz->dir, novo);
		}
	}
	return raiz;
}

no *buscar(no *raiz, int dado){
	if(arvoreVazia(raiz)){
		return NULL;
	}else{
		if(dado < raiz->info){
			return buscar(raiz->esq, dado);
		}else{
			return buscar(raiz->dir, dado);
		}
	}
	return raiz;
}

void mostrarPreOrdem(no *raiz){
	if(raiz != NULL){
		printf("%d\n", raiz->info);
		mostrarPreOrdem(raiz->esq);
		mostrarPreOrdem(raiz->dir);
	}
}

void mostarInOrdem(no *raiz){
	if(raiz != NULL){
		mostarInOrdem(raiz->esq);
		printf("%d\n", raiz->info);
		mostarInOrdem(raiz->dir);
	}
}

void mostrarPosOrdem(no *raiz){
		if(raiz != NULL){
			mostrarPreOrdem(raiz->esq);
			mostrarPreOrdem(raiz->dir);
			printf("%d\n", raiz->info);
		}
}

void mostrarLargura(no *raiz){
	fila *f = NULL; //cria uma fila vazia
	no *aux; //como a fila é sem cabeça, deve retornar a fila atualizada
	f = enfileirar(f, raiz);
	do{
		f = desenfileirar(f, &aux);
		if(aux != NULL){
			printf("%d ",aux->info);
			f = enfileirar(f, aux->esq);
			f = enfileirar(f, aux->dir);
		}
	}while (f!=NULL);
}

no *removerCopiaAntecessor(no *raiz, int dado){
	no *aux;
	if(arvoreVazia(raiz)){
		return NULL;
	}
	else if(dado < raiz->info){
		raiz->esq = removerCopiaAntecessor(raiz->esq, dado);
	}
	else if(dado > raiz->info){
		raiz->dir = removerCopiaAntecessor(raiz->dir, dado);
	}
	else{ //encontrou o nó que será removido
		if (raiz->esq == NULL && raiz->dir == NULL){ //no sem filhos
			free(raiz);
			raiz = NULL;
		}
		else if(raiz->esq == NULL){//só tem filho à direita
			aux = raiz;
			raiz = raiz->dir;
			free(aux);
		}
		else if(raiz->dir == NULL){//só tem filho à esquerda
			aux = raiz;
			raiz = raiz->esq;
			free(aux);
		}
		else{ //tem os dois filhos
			aux = raiz->esq;
			while(aux->dir!=NULL){ //laço para buscar o maior valor da subarvore
				aux = aux->dir;
			}
			raiz->info = aux->info; //troca as informações;
			aux->info = dado;
			raiz->esq = removerCopiaAntecessor(raiz->esq, dado); //agora remove o elemento
		}
	}
return raiz;
} //fim da função

no *removerCopiaSucessor(no *raiz, int dado){
	no *aux;
	if(arvoreVazia(raiz)){
		return NULL;
	}
	if(dado < raiz->info){
		raiz->esq = removerCopiaSucessor(raiz->esq, dado);
	}
	if(dado > raiz->info){
		raiz->dir = removerCopiaSucessor(raiz->dir, dado);
	}else{ //encontrou o nó que sera removido
		if (raiz->esq == NULL && raiz->dir == NULL){ //nó sem filhos
			free(raiz);
			raiz = NULL;
		}
		else if(raiz->esq == NULL){ //só tem filho a direita
			aux = raiz;
			raiz = raiz->esq;
			free(aux);
 		}else if(raiz->dir ==  NULL){ // só tem filho a esquerda
 			aux = raiz;
 			raiz = raiz->esq;
 			free(aux);
 		}else{ //tem 2 filhos
  			aux = raiz->dir;
 			while(aux->esq != NULL){
 				aux = aux->esq;
 			}
 			raiz->info = aux->info; //troca os dados
 			aux->info = dado;
 			raiz->dir = removerCopiaAntecessor(raiz->dir, dado);
 		}
	}
	return raiz;
}

no *removerFusaoEsquerda(no *raiz, int dado){
	no *aux;
	if(arvoreVazia(raiz)){
		return NULL;
	}
	else if(dado < raiz->info){
		raiz->esq = removerCopiaSucessor(raiz->esq, dado);
	}
	else if(dado > raiz->info){
		raiz->dir = removerCopiaSucessor(raiz->dir, dado);
	}
	else{ //encontrou o nó que sera removido
		if (raiz->esq == NULL && raiz->dir == NULL){ //nó sem filhos
			free(raiz);
			raiz = NULL;
		}
		else if(raiz->esq == NULL){ //só tem filho a direita
			aux = raiz;
			raiz = raiz->esq;
			free(aux);
 		}else if(raiz->dir == NULL ){ // só tem filho a esquerda
 			aux = raiz;
 			raiz = raiz->esq;
 			free(aux);
 		}
 		else{	//tem 2 filhos
 			aux = raiz->esq;
 			raiz->info = aux->info; //troca os dados
 			aux->info = dado;
 			raiz->esq = removerFusaoEsquerda(raiz->esq, dado);
 		}
 	}	
 	return raiz;
} 		

no *removerFusaoDireita(no *raiz, int dado){
	no *aux;
	if(arvoreVazia(raiz)){
		return NULL;
	}
	else if(dado < raiz->info){
		raiz->esq = removerCopiaSucessor(raiz->esq, dado);
	}
	else if(dado > raiz->info){
		raiz->dir = removerCopiaSucessor(raiz->dir, dado);
	}
	else{ //encontrou o nó que sera removido
		if (raiz->esq == NULL && raiz->dir == NULL){ //nó sem filhos
			free(raiz);
			raiz = NULL;
		}
		else if(raiz->esq == NULL){ //só tem filho a direita
			aux = raiz;
			raiz = raiz->esq;
			free(aux);
 		}else if(raiz->dir == NULL){ // só tem filho a esquerda
 			aux = raiz;
 			raiz = raiz->esq;
 			free(aux);
 		}
 		else{	//tem 2 filhos
 			aux = raiz->dir;
 			raiz->info = aux->info; //troca os dados
 			aux->info = dado;
 			raiz->dir = removerFusaoDireita(raiz->esq, dado);
 		}
 	}	
 	return raiz;
} 		