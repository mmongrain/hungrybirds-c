all:
	gcc `pkg-config --cflags --libs glib-2.0` hungrybirds.c minimax.c -g -Wall -Wextra -o a.o

run: ./a.o
	valgrind --leak-check=yes ./a.o
