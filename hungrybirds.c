/*******************************************************************************
* hungrybirds.c - An adversarial game for two in C
* by Matthew Mongrain, 12-10-2015
*******************************************************************************/

#include "hungrybirds.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VERSION "0.42"

int main()
{
	twoplayer_start();
	return 0;
}

/* birds_surround_larva: Returns 0 if birds do not surround larva, and 1 if 
 * they do. */
int birds_surround_larva(const Board state, const int* larva_position) 
{
	assert(state);
	assert(larva_position);
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

/* flush_input_buffer: Flushes the input buffer by reading chars until EOL or 
 * EOF. Ref: http://c-faq.com/stdio/stdinflush2.html */
void flush_input_buffer() 
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

/* init_board: initializes the state in memory and requests initialization of 
 * data */
void init_board(Board* state, int** larva_position) 
{
	*state = malloc(BOARD_SIZE * sizeof(**state));
	*larva_position = malloc(2 * sizeof(**larva_position));
	init_board_data(*state, *larva_position);
}

/* init_board_data: Sets starting piece positions. Assumes that the two
 * parameters (state and larve_position) have been malloc'd already. */
void init_board_data(Board state, int* larva_position) 
{
	assert(state);  
	assert(larva_position);
	memset(state, EMPTY, BOARD_SIZE * sizeof(*state));
	state[0] = BIRD;
	state[1] = BIRD;
	state[2] = BIRD;
	state[3] = BIRD;
	state[5] = LARVA;
	larva_position[0] = 3;
	larva_position[1] = 1;
}

/* move: Performs a single move. 
 * Board is passed by reference and is altered in place. */
void move(Board state, Move move, int turn, int* larva_pos)
{
	assert(move_valid(state, move, turn));
	if (get_square(state, move[0], move[1]) == LARVA) {
		larva_pos[0] = move[2];
		larva_pos[1] = move[3];
	}
	set_square(state, move[2], move[3], get_square(state, move[0], move[1]));
	set_square(state, move[0], move[1], EMPTY);
}

/* move_input_format: formats a move (whose valid format was verified by 
 * move_input_format_valid) into an array of four ints representing array
 * indices which can then be verified for validity using move_valid. */
void move_input_format(const char* move, Move result) 
{
	assert(move_input_format_valid(move));
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

/* move_input_format_valid: verifies that an entered move is valid in format 
 * (i.e. resembles A1 B2). Does not verify whether the move is legal. 
 * Returns 0 if the move is invalid, 1 if it is valid. */
int move_input_format_valid(const char* move) 
{
	assert(move);
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

/* move_valid: Verifies whether a move is valid. Performs basic bounds checking
 * on the move parameter.
 * Returns 1 if valid, 0 otherwise. */
int move_valid(const Board state, Move move, int current_turn) 
{
	assert(state);
	assert(move);
	assert(move[0] >= 0 && move[0] < 8 && move[1] >= 0 && move[1] < 8);
	assert(move[2] >= 0 && move[2] < 8 && move[3] >= 0 && move[3] < 8);
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

/* print_board: prints the game status and state to stdout . */
void print_board(const Board state, int turn, int turn_no)
{
	assert(state);
	printf("\n\n   Hungry Birds v%s\n   Turn %d, %s", VERSION, turn_no, 
		turn == BIRD_TURN ? "Birds' Move\n" : "Larva's Move\n");
	char* divider = "  +-------------------------------+";
	printf("%s\n", divider);
	int i;
	for (i = 7; i >= 0; i--) {
		print_row(state, i);			
		printf("%s\n", divider);
	}
	printf("    A   B   C   D   E   F   G   H\n");
}

/* print_row: prints a single row of the state to stdout. */
void print_row(const Board state, int row)
{
	assert(state);
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

/* twoplayer_start: starts the main game loop for the two-player game. */
void twoplayer_start() 
{
	Board state;
	int* larva_pos;
	init_board(&state, &larva_pos);
	int turn_no = 1;
	Turn turn = LARVA_TURN;
	Move current_move = malloc(MOVE_SIZE * sizeof(*current_move));

	int victory = 0;
	while (!victory) { /* main game loop */
		print_board(state, turn, turn_no);
		printf("Enter move: ");
		char buffer[5]; /* for input format "A1 B2" */
		fgets(buffer, 6, stdin);
		if (move_input_format_valid(buffer)) {
			memset(current_move, 0, 4 * sizeof(int));
			move_input_format(buffer, current_move);
			if (move_valid(state, current_move, turn)) {
				move(state, current_move, turn, larva_pos);
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
		victory = victory_condition(state, larva_pos);
		switch (victory) {
			case BIRD_VICTORY: 
				print_board(state, turn, turn_no);
				printf("\nBirds win!\n");
				break;
			case LARVA_VICTORY: 
				print_board(state, turn, turn_no);
				printf("\nLarva wins!\n");
				break;
		}
		flush_input_buffer();
		turn = !turn;
		turn_no++;
	}
	free(current_move);
	free(state);
	free(larva_pos);
}

/* victory_condition: Assesses whether parameters constitute a victory
 * condition. */
int victory_condition(const Board state, const int* larva_position) 
{
	/* Larva wins */
	/* Larva on bottom row wins */
	if (larva_position[0] == 0) {
		return LARVA_VICTORY;
	}
	int i;
	for (i = 0; i < BOARD_SIZE - 4; i++) {
		/* if Larva occurs before first Bird in state array, Larva wins */
		if (state[i] == LARVA) {
			return LARVA_VICTORY;
		} else if (state[i] == BIRD) {
			break;
		}
	}
	/* Bird wins */
	if (birds_surround_larva(state, larva_position)) {
		return BIRD_VICTORY;
	}
	/* else no victory */
	return NO_VICTORY;
}


/* get_square: returns the contents of a single square on the state.
 * row and col assume 0-indexed 8x8 gamestate. */
Square get_square(const Board state, int row, int col) 
{
	assert(row >= 0 && row < 8); 
	assert(col >= 0 && col < 8);
	/* If the sum of row and col is odd, the square is invalid */
	if ((row + col) % 2 == 1) {
		return INVALID;
	}
	/* Since the state is (effectively) eight rows of four squares each, we can
	 * get the index by multiplying row by 4 and adding col/2: */
	int index = row * 4 + col/2;
	return state[index];
}

/* set_square: sets a single square of the state to a specified type.
 * row and col assume 0-indexed 8x8 gamestate. */
Square set_square(Board state, int row, int col, Square square) 
{
	assert(row >= 0 && row < 8);
	assert(col >= 0 && col < 8);
	Square old = get_square(state, row, col);
	int index = row * 4 + col/2;
	state[index] = square;	
	return old;
}
