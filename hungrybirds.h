#ifndef HUNGRYBIRDS_H
#define HUNGRYBIRDS_H

// Board constants
#define BOARD_SIZE 8
typedef enum Square { INVALID, EMPTY, BIRD, LARVA } Square;

// Game constants
#define LARVA_TURN = 0
#define BIRD_TURN = 1

Square board[BOARD_SIZE][BOARD_SIZE] = {
	{ BIRD, INVALID, BIRD, INVALID, BIRD, INVALID, BIRD, INVALID },
	{ INVALID, EMPTY, INVALID, LARVA, INVALID, EMPTY, INVALID, EMPTY },
	{ EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID },
	{ INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY },
	{ EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID },
	{ INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY },
	{ EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID },
	{ INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY, INVALID, EMPTY }
};

typedef struct move {
	int col_src;
	int row_src;
	int col_dest;
	int row_dest;
} Move;

// Function declarations

void flush_input_buffer();
int move_input_format_valid(char* move);
void print_board();
void print_row();

#endif
