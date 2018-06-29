#include <stdio.h>
#include <stdlib.h>
#include "functions.c"
#include "colors.h"

int menu(){
	int opcao;		
	printf("\nOpcoes:");
	printf("\n1. Iniciar jogo");
	printf("\n2. Mostar mão");
	printf("\n3. Mostar mesa");
	printf("\n4. Comprar peça do monte");
	printf("\n5. Jogar peça da mão para a mesa");
	printf("\n0. Sair do jogo");
	printf("\nInforme a opcao: ");
	scanf("%d", &opcao);
	return opcao;
}		

int main(){
	monte * L;
	monte * M;
	monte * T;
	monte * mostrarCompra;
	int opcao;
	int elemento;
	do{
		opcao = menu();
		switch (opcao){
		case 1:
			L = criar(); //cria o monte 
			M = criar(); //cria a mão
			T = criar(); //cria a mesa
			preencher_pecas(L);
			gerarMao(L,M);
			iniciarJogo(L,T);
			printf("\e[H\e[2J");
			foreground(BLUE);
			printf("\t \nJogo iniciado !\n");
			style(RESETALL);
		break;
		case 2:
			if(num_mao == 0){  
				foreground(GREEN);
				printf("\t\t\t\t\t\t\t\nPARABÉNS, VOCÊ GANHOU !!!\n");
				style(RESETALL);
			}else{
				printf("\e[H\e[2J");
				printf("\nA mão atual do jogador é \n" );
				mostrarMao(M);
			}	
		break;
		case 3:	
			if(num_mao == 0){
				foreground(GREEN);
				printf("\t\t\t\t\t\t\t\nPARABÉNS, VOCÊ GANHOU !!!\n");
				style(RESETALL);
			}else{
				printf("\e[H\e[2J");
				printf("\nA mesa atual é\n" );
				mostrar(T);
			}	
		break;	
		case 4:
			printf("\e[H\e[2J");
			if(num_mao == 0){
				foreground(GREEN);
				printf("\t\t\t\t\t\t\t\nPARABÉNS, VOCÊ GANHOU !!!\n");
				style(RESETALL);
			}else{	
				if(num_mao < 27){
					printf("\n Você comprou uma peça do monte \n");
					mostrarCompra = comprarPeca(L,M);
					printf("A peça comprada foi [%d][%d] \n", mostrarCompra->left, mostrarCompra->right);
					printf("A qntd de peças na mão é %d\n", num_mao);
				}else{
					foreground(RED);
					printf("\nO monte está vazio !!! ");
					style(RESETALL);
				}
			}		
		break;
		case 5:
			if(num_mao == 0){
				foreground(GREEN);
				printf("\t\t\t\t\t\t\t\nPARABÉNS, VOCÊ GANHOU !!!\n");
				style(RESETALL);
			}else{
				printf("\e[H\e[2J");
				mostrarMao(M);
				printf("Qual o numero da peça que você quer jogar ? ");
				scanf("%d", &elemento);
				if(elemento <= num_mao){
					jogada(M,T,elemento);
				}else{
					foreground(RED);
					printf("\nNúmero inválido \n");
					style(RESETALL);
				}	
			}	
		break;
		}
	}while(opcao);
	return 0;	
}