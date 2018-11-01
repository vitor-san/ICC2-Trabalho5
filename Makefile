all:
	gcc -g -o exec node.c list.c abas.c -std=c99
run:
	./exec <test.in
