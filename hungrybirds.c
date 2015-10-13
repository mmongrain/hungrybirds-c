#include "hungrybirds.h"
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main()
{
	init_board(&board, &larva_pos);
	start();
	free(board);
	free(larva_pos);
	return 0;
}

/* Returns 0 if birds do not surround larva, and 1 if they do */
int birds_surround_larva(const Square* state, const int* larva_position) {
	/* Larva in top row */
	if (larva_position[0] == 7) {
		/* Larva in top right corner */
		if (larva_position[1] == 7 && get_square(state, 6, 6) == BIRD) {
			return 1;
		} else if (larva_position[1] != 7
				&& get_square(state, 6, larva_position[1] + 1) == BIRD
				&& get_square(state, 6, larva_position[1] - 1) == BIRD) {
			return 1;
		}
	}
	/* Larva on left edge */
	if (larva_position[1] == 0 &&
		get_square(state, larva_position[0] + 1, 1) == BIRD &&
		get_square(state, larva_position[0] - 1, 1) == BIRD) {
		return 1;
	}
	/* Larva on right edge */
	if (larva_position[1] == 7 &&
		larva_position[0] != 7 &&
		get_square(state, larva_position[0] + 1, 6) == BIRD &&
		get_square(state, larva_position[0] - 1, 6) == BIRD) {
		return 1;
	}
	/* Larva in middle */
	if (larva_position[0] > 0 && larva_position[0] < 7 &&
		larva_position[1] > 0 && larva_position[1] < 7 &&
		get_square(state, larva_position[0] + 1, larva_position[1] + 1) == BIRD &&
		get_square(state, larva_position[0] - 1, larva_position[1] + 1) == BIRD &&
		get_square(state, larva_position[0] + 1, larva_position[1] - 1) == BIRD &&
		get_square(state, larva_position[0] - 1, larva_position[1] - 1) == BIRD) {
		return 1;
	}
	return 0;
}

/* Flushes the input buffer by reading chars until EOL or EOF.
 * ref: http://c-faq.com/stdio/stdinflush2.html */
void flush_input_buffer() 
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

/* Initializes the board in memory and requests initialization of data */
void init_board(Square** state, int** larva_position) {
	*state = malloc(BOARD_SIZE * sizeof(*state));
	*larva_position = malloc(2 * sizeof(*larva_position));
	init_board_data(*state, *larva_position);
}

/* Sets starting piece positions */
void init_board_data(Square* state, int* larva_pos) 
{
	memset(state, EMPTY, BOARD_SIZE * sizeof(state));
	state[0] = BIRD;
	state[1] = BIRD;
	state[2] = BIRD;
	state[3] = BIRD;
	state[5] = LARVA;
	larva_pos[0] = 3;
	larva_pos[1] = 1;
}

/* move: Performs a single move. */
void move(Square* state, Move move)
{
	assert(move_valid(state, move, turn));
	if (get_square(state, move[0], move[1]) == LARVA) {
		larva_pos[0] = move[2];
		larva_pos[1] = move[3];
	}
	set_square(state, move[2], move[3], get_square(state, move[0], move[1]));
	set_square(state, move[0], move[1], EMPTY);
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

/* Verifies that an entered move is valid in format (i.e. resembles A1 B2).
 * Does not verify whether the move is legal. No regexes in ANSI C!
 * Returns 0 if the move is invalid, 1 if it is valid. */
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
		(move[3] > 'H' && move[3] < 'a') || 
		move[3] > 'h' || 
		move[4] < '1' || 
		move[4] > '8') { 
		return 0;
	} else return 1;
}

/* Verifies whether a move is valid. Performs basic bounds checking on the move
 * parameter.
 * Returns 1 if valid, 0 otherwise. */
int move_valid(const Square* state, Move move, int current_turn) 
{
	assert(move[0] >= 0 && move[0] < 8 && move[1] >= 0 && move[1] < 8
		&& move[2] >= 0 && move[2] < 8 && move[3] >= 0 && move[3] < 8);
	if (current_turn == BIRD_TURN) {
		if (get_square(state, move[0], move[1]) == BIRD && /* src is bird */
			get_square(state, move[2], move[3]) == EMPTY && /* dest is empty */
			move[2] - move[0] == 1 && /* movement forward by one row only */
			abs(move[3] - move[1]) == 1) { /* lateral movement by one only */
			return 1;
		}
	} else if (current_turn == LARVA_TURN) {
		if (get_square(state, move[0], move[1]) == LARVA && /* src is larva */
			get_square(state, move[2], move[3]) == EMPTY && /* dest is empty */
			abs(move[2] - move[0]) == 1 && /* back or forward one row only */
			abs(move[3] - move[1]) == 1) { /* lateral movement by one only */
			return 1;
		}
	}
	return 0;
}

/* Prints the game status and board to stdout and prompts input. */
void print_board(const Square* state)
{
	printf("\n\n   Hungry Birds v.0.42\n   Turn %d, %s", turn_no, 
		turn == BIRD_TURN ? "Birds' Move\n" : "Larva's Move\n");
	char* divider = "  +-------------------------------+";
	printf("%s\n", divider);
	int i;
	for (i = 7; i >= 0; i--) {
		print_row(state, i);			
		printf("%s\n", divider);
	}
	printf("    A   B   C   D   E   F   G   H\nEnter move: ");
}

/* Prints a single row of the board to stdout. */
void print_row(const Square* state, int row)
{
	assert(row >= 0 && row < 8);
	printf("%d |", row + 1);
	int i;
	for (i = 0; i < 8; i++) {
		switch (get_square(state, row, i)) {
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

/* Starts the main game loop. */
void start() 
{
	Move current_move = malloc(MOVE_SIZE * sizeof(*current_move));
	int victory = 0;
	while (!victory) { /* main game loop */
		print_board(board);
		char buffer[5]; /* for input format "A1 B2" */
		fgets(buffer, 6, stdin);
		if (move_input_format_valid(buffer)) {
			memset(current_move, 0, 4 * sizeof(int));
			move_input_format(buffer, current_move);
			if (move_valid(board, current_move, turn)) {
				move(board, current_move);
			} else {
				printf("Invalid move!\n");
				continue;
			}
		} else if (strcmp(buffer, "exit\n") == 0) {
			printf("Be seeing you...\n");
			return;
		} else {
			printf("Invalid format!\n");
			continue;
		}
		victory = victory_condition(board, larva_pos);
		switch (victory) {
			case 1: print_board(board);
					printf("\nBirds win!\n");
					break;
			case 2: print_board(board);
					printf("\nLarva wins!\n");
					break;
		}
		flush_input_buffer();
		turn = !turn;
		turn_no++;
	}
}

/* Assesses whether the current board is in a victory condition.
 * Returns 2 if Larva wins, 1 if Birds win, 0 otherwise. */
int victory_condition(const Square* state, const int* larva_position) 
{
	/* Larva wins */
	/* Larva on bottom row wins */
	if (larva_position[0] == 0) {
		return 2;
	}
	int i;
	for (i = 0; i < 28; i++) {
		/* if Larva occurs before Bird in board array, Larva wins */
		if (state[i] == LARVA) {
			return 2;
		} else if (state[i] == BIRD) {
			break;
		}
	}
	/* Bird wins */
	if (birds_surround_larva(state, larva_position)) {
		return 1;
	}
	/* else no victory */
	return 0;
}


/* Returns the contents of a single square on the board.
 * row and col assume 0-indexed 8x8 gameboard. */
Square get_square(const Square* state, int row, int col) 
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
	//printf("\nrow:%d-col:%d-square:%d-index:%d\n", row, col, 42, index);
	return state[index];
}

/* Sets a single square of the board to a specified type.
 * row and col assume 0-indexed 8x8 gameboard. */
Square set_square(Square* state, int row, int col, Square square) 
{
	assert(row >= 0 && row < 8 
		&& col >= 0 && col < 8);
	Square old = get_square(state, row, col);
	int index = row * 4 + col/2;
	state[index] = square;	
	return old;
}
