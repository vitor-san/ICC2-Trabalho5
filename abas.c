#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "node.h"

typedef struct {
	char url[1024];
	char titulo[30];
	int data[2];
	int hora[2];
} Aba;

void abrir(List lista);
void alterar(List lista);
void ordenar(List lista);
void exibir(List lista);
void sair(List lista);

int main (void) {
	
	int opt = 0;
	List abas = newList();
	
	do { 
		scanf("%d ", &opt);
		switch (opt) {
			
			case 1:
				abrir(abas);
			break;
			
			case 2:
				alterar(abas);
			break;
			
			case 3:
				ordenar(abas);
			break;
			
			case 4:
				exibir(abas);
			break;
			
			case 5:
				sair(abas);
			break;			
			
		}
	} while (opt != 5);
	
	delList(abas);
	return 0;
}

void abrir(List lista) {
	
	Aba *novaAba = malloc(sizeof(Aba));
	
	fgets(novaAba->titulo, 31, stdin);
	novaAba->titulo[strlen(novaAba->titulo)-1] = '\0';
	scanf("%s ", novaAba->url);
	scanf("%d %d ", novaAba->data, novaAba->data+1);
	scanf("%d %d  ", novaAba->hora, novaAba->hora+1);
	
	listInsert(lista, novaAba, nElemsList(lista)+1);	//só insere no final
	
	return;
}

void alterar(List lista) {
	
	char *chave = malloc(31*sizeof(char));
	int novaPos;
	Aba *abaTemp;
	int achou = 0;
	int i = 1;
	
	fgets(chave, 31, stdin);
	chave[strlen(chave)-1] = '\0';
	
	scanf("%d ", &novaPos);
	
	while (!achou && i <= nElemsList(lista)) {
		abaTemp = listElem(lista, i);
		
		if (!strcmp(abaTemp->titulo, chave)) {	//se os titulos sao iguais, entao...
			achou = 1;
			abaTemp = listRemove(lista, i);
			listInsert(lista, abaTemp, novaPos);
		}
		i++;
	}
	
	free(chave);
	return;
}

void ordenar(List lista) {
	
	
	
	return;
}

void exibir(List lista) {
	
	Aba *abaAtual;
	
	for (int i = 1; i <= nElemsList(lista); i++) {
		abaAtual = listElem(lista, i); 
		printf("%s %s %02d/%02d %02d:%02d\n", abaAtual->titulo, abaAtual->url, abaAtual->data[0], abaAtual->data[1], abaAtual->hora[0], abaAtual->hora[1]);
	}
	printf("\n");
	
	return;
}

void sair(List lista) {
	
	Aba *aux;
	int i = 1;
	
	while (!listIsEmpty(lista)) {
		aux = listRemove(lista, i++);
		free(aux);
	}
	
	return;
}
