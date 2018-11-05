/* Trabalho 5 de Introdução à Ciência
 * de Computação II, curso ministrado
 * pelo Professor Dr. Moacir A. Ponti.
 * 
 * Autor do codigo: Vitor Santana Cordeiro
 * Nº USP: 10734345
 * 
 * Segundo Semestre de 2018
 * ICMC, USP - São Carlos
*/ 

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
int getMes(Aba x);
int getDia(Aba x);
int getHora(Aba x);
int getMinutos(Aba x);
void bucketSort(List lista, int (*criterio)(Aba x), int min, int max);
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
	novaAba->titulo[strlen(novaAba->titulo)-1] = '\0';	//substitui o "\n" (pego pelo fgets) no final da String por um "\0". Usei fgets aqui porque o nome pode ter espacos, o que nao me permite usar o scanf %s
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
			listInsert(lista, abaTemp, novaPos);	//retira da posicao antiga e coloca na posicao nova
		}
		i++;
	}
	
	free(chave);
	return;
}

int getMes(Aba x) {
	return x.data[1];
}

int getDia(Aba x) {
	return x.data[0];
}

int getHora(Aba x) {
	return x.hora[0];
}

int getMinutos(Aba x) {
	return x.hora[1];
}

void ordenar(List lista) {

	bucketSort(lista, getMinutos, 0, 59);
	bucketSort(lista, getHora, 0, 23);
	bucketSort(lista, getDia, 1, 31);
	bucketSort(lista, getMes, 1, 12);
	
	return;
}

void bucketSort(List lista, int (*criterio)(Aba x), int min, int max) {
	
	int tamVetor = max-min+1;
	int posNoVetor;
	int tamListaOriginal = nElemsList(lista);
	Aba *abaAtual;
	
	List *vetorDeListas = malloc(sizeof(List)*(tamVetor));
	
	for (int i = 0; i < tamVetor; i++) {	//inicializa as listas de cada posicao do vetor
		vetorDeListas[i] = newList();
	}
	
	for (int i = 1; i <= tamListaOriginal; i++) {
		abaAtual = (Aba *)listRemove(lista, 1);
		posNoVetor = criterio(*abaAtual) - min;
		
		listInsert(vetorDeListas[posNoVetor], abaAtual, nElemsList(vetorDeListas[posNoVetor]) + 1);		//vai sempre inserir no final da Lista (como se fosse uma fila)
	}
	
	for (int i = 0; i < tamVetor; i++) {	//remonta a fila original, agora ordenada
		if (listIsEmpty(vetorDeListas[i])) {
			delList(vetorDeListas[i]);
			continue;
		}
		
		while (!listIsEmpty(vetorDeListas[i])) {
			
			abaAtual = (Aba *)listRemove(vetorDeListas[i], 1);
			listInsert(lista, abaAtual, nElemsList(lista) + 1);
		}
		
		delList(vetorDeListas[i]);
	}
	
	free(vetorDeListas);
	
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
