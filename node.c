#include <stdlib.h>
#include "node.h"

struct node {
	void *info; 	//memory adress
	Node prev;
	Node next;
};

Node newNode() {
	Node new = malloc(sizeof(NODE));
	
	new->info = NULL;
	new->prev = NULL;
	new->next = NULL;

	return new;
}

void setNext(Node self, Node next) {
	self->next = next;
	if (next != NULL) next->prev = self;
	return;
}

Node getNext(Node x) {
	return x->next;
}

void setPrev(Node self, Node prev) {
	self->prev = prev;
	if (prev != NULL) prev->next = self;
	return;
}

Node getPrev(Node x) {
	return x->prev;
}

void setInfo(Node x, void *data_ad) {
	x->info = data_ad;
	return;
}

void *getInfo(Node x) {
	return x->info;
}

void printInfo(Node x, void (*print_function)(void *)) {
	print_function(x->info);
	return;
}

size_t sizeofNode() {
	return sizeof(NODE);
}

void delNode(Node x, void (*free_function)(void *)) {
	if (x->prev != NULL)  x->prev->next = NULL;
	if (x->next != NULL)  x->next->prev = NULL;
	if (x->info != NULL)  {
		if (free_function == NULL) free(x->info);
		else free_function(x->info);
	}
	
	free(x);

	return;
}
