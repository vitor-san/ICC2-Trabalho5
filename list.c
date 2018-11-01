#include <stdlib.h>
#include "node.h"
#include "list.h"

struct list {
	Node beg;
	Node end;
	int size;
};


List newList () {
	List new = malloc(sizeof(LIST));
	new->beg = NULL;
	new->end = NULL;
	new->size = 0;
	return new;
}

void listInsert(List x, elem data) {

	if (listIsEmpty(x)) {
		x->beg = newNode();
		x->end = x->beg;
	}

	else {
		Node aux = newNode();
		setNext(x->end, aux);
		x->end = aux;
	}

	setInfo(x->end, data);
	x->size++;

	return;
}

Node findNode(List x, int pos) {
	Node aux;

	if (pos > nElemsList(x) || pos < 0) return NULL;
	else if (pos == 0) pos = 1;

	int center = nElemsList(x)/2;

	if (pos <= center) {
		aux = x->beg;

		while (aux != NULL && pos > 1) {
			pos--;
			aux = getNext(aux);
		}
	}

	else {
		aux = x->end;

		while (aux != NULL && pos != nElemsList(x)) {
			pos++;
			aux = getPrev(aux);
		}
	}

	return aux;
}

elem listRemove(List x, int pos) {

	if (listIsEmpty(x)) return NULL;

	Node theOne = findNode(x, pos);
	if (theOne == NULL) return NULL;	//error - not on list
	Node prevOne = getPrev(theOne);
	Node nextOne = getNext(theOne);

	elem info = getInfo(theOne);

	free(theOne);

	if (nElemsList(x) == 1) {
		x->beg = NULL;
		x->end = NULL;
		x->size--;
		return info;
	}

	if (theOne == x->beg) {
		x->beg = nextOne;
		setPrev(x->beg, NULL);
	}

	else if (theOne == x->end) {
		x->end = prevOne;
		setNext(x->end, NULL);
	}

	else {
		setNext(prevOne, nextOne);
		setPrev(nextOne, prevOne);
	}

	x->size--;

	return info;
}

elem listElem(List x, int pos) {
	return (getInfo( findNode(x, pos) ));
}

int nElemsList(List x) {
	return x->size;
}

size_t sizeofList(List x) {
	return nElemsList(x)*sizeofNode();
}

int listIsEmpty(List x) {
	return (x->beg == NULL);
}

void printList(List x, void (*print_function)(elem)) {

	Node aux = x->beg;

	while (aux != NULL) {
		printInfo(aux, print_function);
		aux = getNext(aux);
	}

	return;
}

void delList(List x) {
	free(x);
	return;
}
