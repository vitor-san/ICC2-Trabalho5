#ifndef NODE_H
	#define NODE_H

	typedef struct node NODE;
	typedef NODE* Node;

	Node newNode();
	void setNext(Node self, Node next);
	Node getNext(Node x);
	void setPrev(Node self, Node prev);
	Node getPrev(Node x);
	void setInfo(Node x, void *data_ad);
	void *getInfo(Node x);
	void printInfo(Node x, void (*print_function)(void *));
	size_t sizeofNode();
	void delNode(Node x, void (*free_function)(void *));

#endif
