all:
	gcc hungrybirds.c -g -Wall -Wextra -o a.o

run: ./a.o
	valgrind --leak-check=yes ./a.o
