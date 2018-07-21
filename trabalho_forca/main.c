#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"
#include "ranking.c"

int tam,vida=7, entrou=0;

int menu(){
	int opcao;
	printf("\n0. Sair");
	printf("\n1. Inserir palavra (OBRIGATÓRIOS)");
	printf("\n2. Inserir jogador (OBRIGATÓRIOS)");
	printf("\n3. Escolher jogador (OBRIGATÓRIOS)");
	printf("\n4. Iniciar jogo (OBRIGATÓRIOS)");
	printf("\n5. Chutar uma letra");
	printf("\n6. Pedir uma dica");
	printf("\n7. Chutar palavra");
	printf("\n8. Mostrar palavra");
	printf("\n9. Mostrar dicionario");
	printf("\n10. Mostrar ranking");
	printf("\nOpcao: ");
	scanf("%d",&opcao);
	return opcao;
}

int main(int argc, char *argv[]) {
	int letra,opcao, acerto,tip; 
	char nome[256];
	char dica1[256];
	char dica2[256];
	char nomeJogador[256];
	char l;
	char *novaPalavra;
	char chute[256];
	lista *palavra;
	lista *dicionario[26];
	ranking *tabelaRanking[5];
	ranking *aux;
	for(int i=0; i<=25;++i){
		dicionario[i] = criar();
	}
	for (int i = 0; i < 5; ++i){
		tabelaRanking[i] = criarRanking();
	}
	do{
		opcao = menu();
		switch (opcao){
			case 1: 
					printf("Digite a palavra: \n");
					scanf(" %[^\n]s", nome);
					//__fpurge(stdin);
					letra = (int)nome[0];
					printf("Digite a primeira dica: \n");
					scanf(" %[^\n]s", dica1);
					//__fpurge(stdin);
					printf("Digite a segunda dica: \n");
					scanf(" %[^\n]s", dica2);
					//__fpurge(stdin);
					inserir_fim(dicionario[hash(letra)], nome, dica1, dica2);
					break;
			
			case 2: 
					printf("Qual o nome do jogador? \n");
					scanf(" %[^\n]s", nomeJogador);
					letra = (int)nomeJogador[0];
					inserir_fim_ranking(tabelaRanking[hashRanking(letra)], nomeJogador, 0, 0);
					break;
			
			case 3:	
					printf("Qual o nome do jogador que deseja jogar \n");
						scanf(" %[^\n]s", nomeJogador);
						letra = (int)nomeJogador[0];
						if(pesquisar(tabelaRanking[hashRanking(letra)],nomeJogador) != NULL){
							aux = pesquisar(tabelaRanking[hashRanking(letra)],nomeJogador);
						}else{
							printf("Esse jogador não existe! \n");
						}
					break;
			
			case 4: 
					if(listaVazia(dicionario) == 0){
						printf("O dicionario está vazio! \n");
						break;
					}else{
						palavra = escolherPalavra(dicionario);
					}
					tam = strlen(palavra->nome);
					printf("Sua palavra tem %d caracteres!\n", tam);
					novaPalavra = (char*)malloc(tam*sizeof(char));
					inicializarPalavra(novaPalavra,tam);
					vida = 7;
					entrou = 0;
					break;

			case 5:
					mostrarPalavra(novaPalavra,tam);
					printf("\n");
					printf("Sua quantidade de vidas eh %d", vida);
					printf("\n");
					printf("Digite a letra que gostaria de chutar: \n");
					scanf("%s", &l);
					acerto = comparar(palavra->nome, novaPalavra, l, tam);
					mostrarPalavra(novaPalavra,tam);
					if(acerto == 0){
						vida = vida -1;
						aux->pontuacao = aux->pontuacao - 2;
					}else{
						aux->pontuacao = aux->pontuacao + 2;
					}
					if(acerto == tam && vida > 0){
						printf("PARABÉNS VOCÊ GANHOU O JOGO!!!\n");
						aux->qntdAcertos = aux->qntdAcertos+1;
					}else if (vida <= 0){
						printf("Acabaram suas chances, você perdeu :( \n");
					}
					entrou = 0;
					break;	

			case 6:
					printf("Qual dica você deseja? (1 ou 2)"); 
					scanf("%d", &tip);
					if(tip == 1 ){
						printf("A primeira dica eh: %s\n", palavra->dica1);
						aux->pontuacao = aux->pontuacao - 3;
					}else if(tip == 2){
						printf("A segunda dica eh: %s\n", palavra->dica2);
						aux->pontuacao = aux->pontuacao - 3;
					}else{
						printf("Opção inválida \n");
					}
					break;	

			case 7: 
					printf("\nDigite a palavra: ");
					scanf(" %[^\n]s", chute);
					if (strcmp(chute,palavra->nome) == 0){
						printf("PARABÉNS VOCÊ GANHOU O JOGO\n");
						aux->qntdAcertos = aux->qntdAcertos+1;
						if(entrou <= tam/2 ){
							aux->pontuacao = aux->pontuacao + 10;
						}else{
							aux->pontuacao = aux->pontuacao + 5;
						}
					}else{
						printf("ERROU\n");
						aux->pontuacao = aux->pontuacao - 4;
					} 
					break;	
			case 8: 
					mostrarPalavra(novaPalavra,tam);
					break;	
			case 9:
					mostrarTudo(dicionario);
					break;	
			case 10:
					mostrarTudoRanking(tabelaRanking);
					break;											
		}
	}while(opcao);
	return 0;
}