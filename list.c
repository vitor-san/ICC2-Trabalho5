#include <stdlib.h>
#include "node.h"
#include "list.h"

struct list {
	Node beg;
	Node end;
	int size;
};


List newList() {
	List new = malloc(sizeof(LIST));
	new->beg = NULL;
	new->end = NULL;
	new->size = 0;
	return new;
}

Node findNode(List x, int pos) {
	Node aux;

	if (pos > nElemsList(x)) pos = nElemsList(x);
	else if (pos <= 0) pos = 1;

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

void listInsert(List x, elem data, int pos) {

	if (listIsEmpty(x)) {
		x->beg = newNode();
		x->end = x->beg;
		setInfo(x->beg, data);
	}

	else {
		
		Node new = newNode();
		setInfo(new, data);
		Node next = findNode(x, pos);
		
		if (pos > nElemsList(x)) {
			setNext(x->end, new);
			setPrev(new, x->end);
			x->end = new;
		}
		
		else if (pos > 1) {
			setPrev(new, getPrev(next));
			setNext(getPrev(next), new);
			setPrev(next, new);
			setNext(new, next);
		}
		
		else {
			setNext(new, x->beg);
			setPrev(x->beg, new);
			x->beg = new;
		}
	}

	x->size++;

	return;
}

elem listRemove(List x, int pos) {

	if (listIsEmpty(x)) return NULL;

	Node theOne = findNode(x, pos);
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
