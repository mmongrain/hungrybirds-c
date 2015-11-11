all:
	gcc `pkg-config --cflags glib-2.0` hb_functions.c hungrybirds.c minimax.c `pkg-config --libs glib-2.0` -g -Wall -Wextra -o a.o

run: ./a.o
	valgrind --leak-check=yes ./a.o
