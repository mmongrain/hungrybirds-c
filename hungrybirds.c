#include "hungrybirds.h"
#include <memory.h>
#include <stdio.h>
#include <assert.h>

#define INPUT_SIZE 5

int main()
{
	int turn = 0;
	int turncount = 0;
	print_board();
	while (1) { /* main game loop */
		char buffer[INPUT_SIZE];
		fgets(buffer, INPUT_SIZE + 1, stdin);
	}
	return 0;
}

void print_board()
{
	char* divider = "  +-------------------------------+";
	printf("%s\n", divider);
	int i;
	for (i = BOARD_SIZE - 1; i >= 0; i--) {
		print_row(i);			
		printf("%s\n", divider);
	}
	printf("    A   B   C   D   E   F   G   H\n");
}

void print_row(int row)
{
	assert(row >= 0);
	assert(row < 8);
	printf("%d |", row + 1);
	int i;
	for (i = 0; i < BOARD_SIZE; i++) {
		switch (board[row][i]) {
			case INVALID:
			case EMPTY:
				printf("   |");
				break;
			case LARVA:
				printf(" L |");
				break;
			case BIRD:
				printf(" B |");
				break;
		}
	}
	printf("\n");
}
