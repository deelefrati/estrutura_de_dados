#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_binaria_string.c"

int menu(){
	int opcao;
	//system("clear"); //Linux
	//system("cls"); //Windows
	printf("\n0. Sair");
	printf("\n1. Inserir dado");
	printf("\n2. Preencher arvore automaticamente");
	printf("\n3. Buscar elemento");
	printf("\n4. Mostrar arvore binaria");
	printf("\n5. Mostrar pre-ordem");
	printf("\n6. Remover elemento por copia do antecessor");
	printf("\n7. Remover elemento por fusao do antecessor");
	printf("\n8. Enviar mensagem");
	printf("\n9. Ler mensagens");
	printf("\nOpcao: ");
	scanf("%d", &opcao);
	return opcao;
}

no *preencher(no *raiz){
	int i;
	char vet[5][20] = {"juliana", "andre", "joao", "amanda" , "pedro"};
	for(i=0; i<5; i++){
		raiz = inserir(raiz, alocar(vet[i]));
	}
	return raiz;
}

int main(int argc, char *argv[]) {
	int opcao,escolha;
	char elemento[20];
	char *resultado;
	char name[20];
	char mensagem[280];
	char *amigo;
	pilha *friend;
	no *raiz; 
	no *aux;
	raiz = criar();
	arranjo *P = criarPilha();
	do{
		opcao = menu();
		switch (opcao){
			case 1: printf("Informe o nome a ser inserido: ");//insercao de nos manualmente
					scanf(" %[^\n]s", &elemento);
					raiz = inserir(raiz, alocar(elemento));
					break;
			case 2: raiz=preencher(raiz);//insercao de nos automaticamente
					if (!arvore_vazia(raiz)){
						printf("\nArvore preenchida com sucesso.");
					}
					break;
			case 3: printf("Informe o valor a ser buscado: ");
					scanf(" %[^\n]s", &elemento);
					//aux=buscar(raiz, elemento);
					resultado = buscar(raiz, elemento);
					if (resultado!=NULL){ //if(aux!=NULL)
						printf("%s encontrado.", resultado); //printf("%s encontrado.", aux->nome);
					}
					else{
						printf("Elemento inexistente.");
					}
					break;
			case 4: mostrar_arvore_binaria(raiz, 0); //raiz possui altura = 0
					break;
			case 5: mostrar_pre_ordem(raiz); //raiz possui altura = 0
					break;
			case 6: printf("Informe o valor a ser removido: ");
					scanf(" %[^\n]s", &elemento);
					raiz = remover_copia_antecessor(raiz, elemento);
					raiz = atualizarAlturas(raiz);
					break;
			case 7: printf("Informe o valor a ser removido: ");
					scanf(" %[^\n]s", &elemento);
					raiz = remover_fusao_antecessor(raiz, elemento);
					raiz = atualizarAlturas(raiz);
					break;
			case 8: printf("Escreva o seu nome: ");
					scanf(" %[^\n]s", &name);
					printf("Escreva a sua mensagem: ");
					scanf(" %[^\n]s", &mensagem);
					amigo = buscar(raiz, name);
					if(amigo != NULL){ //ele é seu amigo?
						empilhar(P,name, mensagem, 1);	
					}else{
						empilhar(P,name, mensagem, 0);
					}
					break;
			case 9 : if(pilha_vazia(P)){
						printf("Não ha mensagens\n");
					 }else{
						 friend = desempilhar(P);
						 printf("Nome: %s\n", friend->nome);
						 printf("Mensagem: %s\n", friend->mensagem);
						 if(friend->amigo == 0){
						 	printf("%s não está na sua lista de amigos, deseja adiciona-lo? [1-sim / 2-não]", friend->nome);
						 	scanf("%d",&escolha);
						 	if(escolha == 1){
						 		raiz = inserir(raiz, alocar(friend->nome));
						 	}
						 }
					 }
					break;									
		}
	}while(opcao);
	return 0;
}
