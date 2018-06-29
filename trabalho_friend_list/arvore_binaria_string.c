#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhaFunctions.c"

typedef struct tipo_no no;
struct tipo_no{
	char nome[20];
	int altEsq;
	int altDir;
	struct tipo_no *esq;
	struct tipo_no *dir;
};

no *balancear(no *raiz);

no *criar(){
	return NULL;
}

no *alocar(char dado[]){
	no *novo = (no*)malloc(sizeof(no));
	if(novo){
		strcpy(novo->nome, dado);
		novo->esq = NULL;
		novo->dir = NULL;
	}
	else{
		printf("Sem memoria disponivel.");
	}
	return novo;
}

int arvore_vazia(no *raiz){
	if (raiz == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

no *inserir(no *raiz, no *novo){
	if (arvore_vazia(raiz)){
		raiz = novo;
	}
	else{
		if (strcmp(novo->nome, raiz->nome) < 0 ){
			raiz->esq = inserir(raiz->esq, novo);
			if(raiz->esq->altDir > raiz->esq->altEsq){
				raiz->altEsq = raiz->esq->altDir + 1;
			}else{
				raiz->altEsq = raiz->esq->altEsq + 1;
			}
		}
		else{
			raiz->dir = inserir(raiz->dir, novo);
			if(raiz->dir->altDir>raiz->dir->altEsq){
				raiz->altDir = raiz->dir->altDir + 1;
			}else{
				raiz->altDir = raiz->dir->altEsq + 1;
			}
		}
	}
	raiz = balancear(raiz);
	return raiz;
}

char *buscar(no *raiz, char dado[]){
	if(arvore_vazia(raiz)){
		return NULL;
	}
	else{
	    if (strcmp(dado, raiz->nome)<0){
            return buscar(raiz->esq, dado);
	    }
	    else if (strcmp(dado, raiz->nome)>0){
            return buscar(raiz->dir, dado);
       }
	}
	return raiz->nome;
}

void mostrar_pre_ordem(no *raiz){
	if(!arvore_vazia(raiz)){
		printf("%s ", raiz->nome);
		mostrar_pre_ordem(raiz->esq);
		mostrar_pre_ordem(raiz->dir);
	}
	else{
		printf("NULL ");
	}
}

void mostrar_arvore_binaria(no *raiz, int h){
	int i;
	if (raiz != NULL){
		mostrar_arvore_binaria(raiz->dir, h+1);
		for (i =0; i<h; i++){
            printf(" - ");
		}
		printf("%s \n", raiz->nome);//processa o no
		mostrar_arvore_binaria(raiz->esq, h+1);
	}
}

no *remover_copia_antecessor(no *raiz, char dado[]){
	no *aux;
	if(arvore_vazia(raiz)){
		return NULL;
	}
	else if(strcmp (dado, raiz->nome) < 0){
		raiz->esq = remover_copia_antecessor(raiz->esq, dado);
	}
	else if(strcmp (dado, raiz->nome) > 0){
		raiz->dir = remover_copia_antecessor(raiz->dir, dado);
	}
	else{ //encontrou o no que sera removido
		//no sem filhos
		if (raiz->esq == NULL && raiz->dir == NULL){
			free(raiz);
            raiz = NULL;
		}
		else if(raiz->esq == NULL){//so tem filho a direita
			aux = raiz;
			raiz = raiz->dir;
			free(aux);
		}
		else if(raiz->dir == NULL){//so tem filho a esquerda
			aux = raiz;
			raiz = raiz->esq;
			free(aux) ;
		}
		else { //tem os dois filhos
			aux = raiz->esq;
			//laco para buscar o maior valor da subarvore
			while(aux->dir!=NULL){
                aux = aux->dir;
			}
			//troca as informacoes;
			strcpy(raiz->nome, aux->nome);
			strcpy(aux->nome, dado);
			//agora remove o elemento
			raiz->esq = remover_copia_antecessor(raiz->esq, dado);
		}
	}
	return raiz;
}//fim da funcao

no *remover_fusao_antecessor(no *raiz, char dado[]){
	no *aux;
	no *pai = raiz;
	if(arvore_vazia(raiz)){
		return NULL;
	}
	else if(strcmp (dado, raiz->nome) < 0){
		pai = raiz->esq;
		raiz->esq = remover_fusao_antecessor(raiz->esq, dado);
	}
	else if(strcmp (dado, raiz->nome) > 0){
		pai = raiz->dir;
		raiz->dir = remover_fusao_antecessor(raiz->dir, dado);
	}
	else{ //encontrou o no que sera removido
		//no sem filhos
		if (raiz->esq == NULL && raiz->dir == NULL){
			free(raiz);
            raiz = NULL;
		}
		else if(raiz->esq == NULL){//so tem filho a direita
			aux = raiz;
			raiz = raiz->dir;
			free(aux);
		}
		else if(raiz->dir == NULL){//so tem filho a esquerda
			aux = raiz;
			raiz = raiz->esq;
			free(aux) ;
		}
		else { //tem os dois filhos
			aux = raiz->esq;
            while(aux->dir != NULL){
                aux = aux->dir;//pega o filho mais a direita da subarvore esquerda
            }
            //ajusta os ponteiros
            aux->dir = raiz->dir;
            //realiza a fusao
            if (pai == raiz){
            	raiz = raiz->esq;
            	free(pai);
			}
            else if(pai->esq == raiz){
                pai->esq = raiz->esq;
                free(raiz);
            }
            else{
                pai->dir = raiz->esq;
                free(raiz);
            }
		}
	}
	return raiz;
}//fim da funcao

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

no *atualizarAlturas(no *raiz){
	//atualiza da folha até a raiz
	if(!arvore_vazia(raiz)){
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