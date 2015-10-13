#include "hungrybirds.h"
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define INPUT_SIZE 5

int main()
{
	options.visual = 1;
	options.debug = 1;
	init_board();
	if (options.visual) print_board();
	while (1) { /* main game loop */
		char buffer[INPUT_SIZE];
		fgets(buffer, INPUT_SIZE + 1, stdin);
		if (move_input_format_valid(buffer)) {
			if (options.debug) { 
				printf("Valid!\n");
			}
			Move move_f = malloc(MOVE_SIZE * sizeof(*move_f));
			move_input_format(buffer, move_f);
			if (options.debug) {
				printf("Formatted: ");
				int i;
				for (i = 0; i < 4; i++) {
					printf("[%d]", move_f[i]);
				}
				printf("\n");
				move(move_f);
				if (options.visual) print_board();
			}
			free(move_f);
		} else {
			printf("Invalid!\n");
		}
		flush_input_buffer();
	}
	free(board);
	return 0;
}

/* 
 * Flushes the input buffer by reading chars until EOL or EOF.
 * ref: http://c-faq.com/stdio/stdinflush2.html
 */
void flush_input_buffer() 
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

void init_board() 
{
	board = malloc(BOARD_SIZE * sizeof(Square));
	memset(board, EMPTY, BOARD_SIZE * sizeof(Square));
	board[0] = BIRD;
	board[1] = BIRD;
	board[2] = BIRD;
	board[3] = BIRD;
	board[5] = LARVA;
}

void move(Move move) 
{
	assert(move_valid(move));
	set_square(move[2], move[3], get_square(move[0], move[1]));
	set_square(move[0], move[1], EMPTY);
}

/* move_input_format: formats a move (whose validity was verified by 
 * move_input_format_valid) into an array of four ints representing array
 * indices which can then be verified for validity using move_valid. */
void move_input_format(const char* move, Move result) 
{
	assert(move_input_format_valid(move) == 1);
	if (move[0] < 'I') { /* if uppercase */
		result[1] = move[0] - 'A';
	} else { /* if lowercase */
		result[1] = move[0] - 'a';
	}
	result[0] = move[1] - '1';
	if (move[3] < 'I') { /* if uppercase */
		result[3] = move[3] - 'A';
	} else { /* if lowercase */
		result[3] = move[3] - 'a';
	}
	result[2] = move[4] - '1';
}

/* 
 * Verifies that an entered move is valid in format (i.e. resembles A1 B2).
 * Does not verify whether the move is legal. No regexes in ANSI C!
 * Returns 0 if the move is invalid, 1 if it is valid.
 */
int move_input_format_valid(const char* move) 
{
	/* source move */
	if (move[0] < 'A' || 
		(move[0] > 'H' && move[0] < 'a') || 
		move[0] > 'h' || 
		move[1] < '1' || 
		move[1] > '8' || 
		move[2] != 32 || /* not a space */
		/* dest move */
		move[3] < 'A' || 
		(move[3] > 'H' && move[3] < 'a') || /* not A-H */
		move[3] > 'h' || /* not a-h */
		move[4] < '1' || /* <1 */
		move[4] > '8') { /* >8 */ 
		return 0;
	} else return 1;
}

int move_valid(Move move) 
{
	return 1;
}

void print_board()
{
	if (options.visual) {
		char* divider = "  +-------------------------------+";
		printf("%s\n", divider);
		int i;
		for (i = 7; i >= 0; i--) {
			print_row(i);			
			printf("%s\n", divider);
		}
		printf("    A   B   C   D   E   F   G   H\n");
	}
}

void print_row(int row)
{
	assert(row >= 0 && row < 8);
	printf("%d |", row + 1);
	int i;
	for (i = 0; i < 8; i++) {
		switch (get_square(row, i)) {
			case EMPTY:
			case INVALID:
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

Square get_square(int row, int col) 
{
	assert(row >= 0 && row < 8 
		&& col >= 0 && col < 8);
	/* If the sum of row and col is odd, the square is invalid */
	if ((row + col) % 2 == 1) {
		return INVALID;
	}
	/* Since the board is (effectively) eight rows of four squares each, we can
	 * get the index by multiplying row by 4 and adding col/2: */
	int index = row * 4 + col/2;
	//printf("\nrow:%d-col:%d-square:%d-index:%d\n", row, col, board[index], index);
	return board[index];
}

Square set_square(int row, int col, Square square) 
{
	assert(row >= 0 && row < 8 
		&& col >= 0 && col < 8);
	Square old = get_square(row, col);
	int index = row * 4 + col/2;
	board[index] = square;	
	return old;
}
