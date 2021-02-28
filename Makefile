.PHONY: all
all: lexer uniquelex

lexer: lexer.c
	gcc -o lexer lexer.c -Og -g

uniquelex: uniquelex.o avl_tree.o
	gcc -o uniquelex uniquelex.o avl_tree.o

uniquelex.o: uniquelex.c
	gcc -c uniquelex.c -O2

avl_tree.o: avl_tree.c avl_tree.h
	gcc -c avl_tree.c -O2

.PHONY: clean
clean:
	rm -f *.o
