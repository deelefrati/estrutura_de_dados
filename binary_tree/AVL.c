#include <stdio.h>
#include <stdlib.h>

typedef struct tipo_no no;
typedef struct tipo_fila fila;

struct tipo_no{
	int info;
	int altEsq;
	int altDir;
	struct tipo_no *esq;
	struct tipo_no *dir;
};

struct tipo_fila{
	no *item;
struct tipo_fila *prox;
};

//funções de fila
fila *alocarFila(no *elemento){
	fila *novo = (fila *) malloc(sizeof(fila));
	if(novo == NULL){
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

//funções arvore
no *criar(){
	return NULL;
}

no* alocar(int dado){
	no *novo;
	novo = (no*)calloc(1,sizeof(no));
	if(!novo){
		printf("ERRO\n");
	}else{
		novo->info = dado;
		novo->altEsq = 0;
		novo->altDir = 0;
		novo->esq = NULL;
		novo->dir = NULL;
	}
	return novo;
}

int arvoreVazia(no *raiz){
	if (raiz == NULL){
		return 1; //true
	}
	else{
		return 0; //false
	}
}

void mostrarArvoreBinaria(no *raiz, int h){
	if(raiz != NULL){
		mostrarArvoreBinaria(raiz->dir, h+1);
		for(int i=0; i < h; i++){
			printf(" - ");
		}
		printf("%d \n", raiz->info);
		mostrarArvoreBinaria(raiz->esq, h+1);
	}
}

void mostrar_pre_ordem(no *raiz){
	if (raiz != NULL){ //árvore não vazia
		printf("%d ", raiz->info); //processa o nó
		mostrar_pre_ordem(raiz->esq);
		mostrar_pre_ordem(raiz->dir);
	}
}

void mostrarLargura(no *raiz){
	fila *f = NULL; //cria uma fila vazia
	no *aux; //como a fila é sem cabeça, deve retornar a fila atualizada
	f = enfileirar(f, raiz);
	do{
		f = desenfileirar(f, &aux);
		if(aux != NULL){
			printf("%d ", aux->info);
			f = enfileirar(f, aux->esq);
			f = enfileirar(f, aux->dir);
		}
	}while (f != NULL);
}

no *girarEsq(no *raiz){
	no *novaRaiz; 
	no *subEsq;
	novaRaiz = raiz->dir;
	subEsq = novaRaiz->esq;
	raiz->dir = subEsq;
	novaRaiz->esq = raiz;
	if(raiz->dir == NULL){
		raiz->altDir = 0;
	}else if(raiz->dir->altEsq > raiz->dir->altDir){
		raiz->altDir = raiz->dir->altEsq + 1;
	}else{
		raiz->altDir = raiz->dir->altDir + 1;
	}
	if(novaRaiz->esq->altEsq > novaRaiz->esq->altDir){
		novaRaiz->altEsq = novaRaiz->esq->altEsq + 1;
	}else{
		novaRaiz->altEsq = novaRaiz->esq->altDir + 1;
	}
	return novaRaiz;
}

no *girarDir(no *raiz){
	no *nova_raiz, *sub_dir;
	nova_raiz = raiz->esq;
	sub_dir = nova_raiz->dir;
	raiz->esq = sub_dir;
	nova_raiz->dir = raiz;
	if(raiz->esq == NULL){
		raiz->altEsq = 0;
	}else if(raiz->esq->altEsq > raiz->esq->altDir){
		raiz->altEsq = raiz->esq->altEsq + 1;
	}else{
		raiz->altEsq = raiz->esq->altDir + 1;
	}
	if(nova_raiz->dir->altEsq > nova_raiz->dir->altDir){
		nova_raiz->altDir = nova_raiz->dir->altEsq + 1;
	}else{
	nova_raiz->altDir = nova_raiz->dir->altDir + 1;
	}
	return nova_raiz;
}

no *balancear(no *raiz){
	int balanceamento = raiz->altEsq - raiz->altDir;
	if(balanceamento == +2){
		int balanceamento2 = raiz->esq->altEsq - raiz->esq->altDir;
		if(balanceamento2 == -1){
			raiz->esq = girarEsq(raiz->esq);
	}
		raiz = girarDir(raiz);
	}else if(balanceamento == -2){
		int balanceamento2 = raiz->dir->altEsq - raiz->dir->altDir;
		if(balanceamento2 == +1){
			raiz->dir = girarDir(raiz->dir);
		}
		raiz = girarEsq(raiz);
	}
	return raiz;
}


no* inserir(no *raiz, no *novo){
	if(arvoreVazia(raiz)){
		raiz = novo;
	}else if(novo->info < raiz->info){
		raiz->esq = inserir(raiz->esq, novo); 
		//atualiza a altura de acordo com a maior subarvore
		if(raiz->esq->altDir > raiz->esq->altEsq){
			raiz->altEsq = raiz->esq->altDir + 1;
		}else{
			raiz->altEsq = raiz->esq->altEsq + 1;
		}
	}else{
		raiz->dir = inserir(raiz->dir, novo);
		//atualiza a altura de acordo com a maior subarvore
		if(raiz->dir->altDir>raiz->dir->altEsq){
			raiz->altDir = raiz->dir->altDir + 1;
		}else{
			raiz->altDir = raiz->dir->altEsq + 1;
		}
	}
	raiz = balancear(raiz);
	return raiz;
}

no* buscar(no *raiz, int dado){
	if(arvoreVazia(raiz)){
		return NULL;
	}else{
		if (dado < raiz->info){
			return buscar(raiz->esq, dado);
		}else if (dado > raiz->info){
			return buscar(raiz->dir, dado);
		}
	}
	return raiz;
}

no *removerFusaoAntecessor(no *raiz, int dado){
	no *aux;
	no *pai = raiz;
	if(arvoreVazia(raiz)){
		return NULL;
	}else if(dado < raiz->info){
		pai = raiz->esq;
		raiz->esq = removerFusaoAntecessor(raiz->esq, dado);
	}else if(dado > raiz->info){
		pai = raiz->dir;
		raiz->dir = removerFusaoAntecessor(raiz->dir, dado);
	}else{ //encontrou o nó que será removido
		if (raiz->esq == NULL && raiz->dir == NULL){ //no sem filhos
			free(raiz);
			raiz = NULL;
		}else if(raiz->esq == NULL){//só tem filho à direita
			aux = raiz;
			raiz = raiz->dir;
			free(aux);
		}else if(raiz->dir == NULL){//só tem filho à esquerda
			aux = raiz;
			raiz = raiz->esq;
			free(aux);
		}else{ //tem os dois filhos
			aux = raiz->esq;
			//laço para buscar o maior valor da subarvore
			while(aux->dir!=NULL){
				aux = aux->dir;
			}
			//ajusta os ponteiros
			//realoca a subarvore direita
			aux->dir = raiz->dir;
			//realiza a fusão
			if (pai == raiz){
				raiz = raiz->esq;
				free(pai);
			}else if(pai->esq == raiz){
				pai->esq = raiz->esq;
				free(raiz);
			}else{
				pai->dir = raiz->esq;
				free(raiz);
			}
		}
	}
	return raiz;
}//fim da função

no *atualizarAlturas(no *raiz){
	//atualiza da folha até a raiz
	if(!arvoreVazia(raiz)){
		raiz->esq = atualizarAlturas(raiz->esq);
	if(raiz->esq == NULL){
		raiz->altEsq = 0;
	}else if(raiz->esq->altEsq >
		raiz->esq->altDir){
		raiz->altEsq = raiz->esq->altEsq + 1;
	}else{
		raiz->altEsq = raiz->esq->altDir + 1;
	}
	raiz->dir = atualizarAlturas(raiz->dir);
	if(raiz->dir == NULL){
		raiz->altDir = 0;
	}else if(raiz->dir->altEsq > raiz->dir->altDir){
		raiz->altDir = raiz->dir->altEsq + 1;
	}else{
		raiz->altDir = raiz->dir->altDir + 1;
	}
	raiz = balancear(raiz);
	}
	return raiz;
}
