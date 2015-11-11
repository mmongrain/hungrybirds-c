/*******************************************************************************
* hungrybirds.c - An adversarial game for two in C
* by Matthew Mongrain, 12-10-2015
*******************************************************************************/

#include "hungrybirds.h"
#include "minimax.h"
#include <glib.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VERSION "0.44"

void test_start();

int main()
{
	test_start();
	//twoplayer_start();
	return 0;
}

void test_start() 
{
	State initial_state;
	init_board(&initial_state);
	int turn_no = 1;
	Turn turn = LARVA_TURN;
	GSList *list = NULL;
	GSList *elem = NULL;
	generate_moves(&initial_state, &list, turn);
	Move *generated_move = NULL;
	for (elem = list; elem; elem = elem->next) {
		printf("============\nPARENT STATE\n============\n");
		init_board(&initial_state);
		generated_move = elem->data;
		move(&initial_state, generated_move, turn);
		print_board(&initial_state, turn, turn_no);
		GSList *inner_list = NULL;
		GSList *inner_elem = NULL;
		Move *inner_move = NULL;
		generate_moves(&initial_state, &inner_list, !turn);
		printf("============\nCHILD STATES\n============\n");
		for (inner_elem = inner_list; inner_elem; inner_elem = inner_elem->next) {
			State parent_state = initial_state;
			inner_move = inner_elem->data;
			move(&parent_state, inner_move, !turn);
			print_board(&parent_state, !turn, turn_no + 1);
		}
	}
}

/* birds_surround_larva: Returns 0 if birds do not surround larva, and 1 if 
 * they do. */
int birds_surround_larva(const State *state) 
{
	assert(state);
	int row = state->larva_row;
	int col = state->larva_col;
	if (get_square(state, row + 1, col + 1) == EMPTY ||
		get_square(state, row + 1, col - 1) == EMPTY ||
		get_square(state, row - 1, col - 1) == EMPTY ||
		get_square(state, row - 1, col + 1) == EMPTY) {
		return 0;
	}
	return 1;
}

/* flush_input_buffer: Flushes the input buffer by reading chars until EOL or 
 * EOF. Ref: http://c-faq.com/stdio/stdinflush2.html */
void flush_input_buffer() 
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

/* init_board: Sets starting piece positions. */
void init_board(State *state) 
{
	assert(state);
	state->larva_row = LARVA_ROW;
	state->larva_col = LARVA_COL;
	state->bird1_row = BIRD1_ROW;
	state->bird1_col = BIRD1_COL;
	state->bird2_row = BIRD2_ROW;
	state->bird2_col = BIRD2_COL;
	state->bird3_row = BIRD3_ROW;
	state->bird3_col = BIRD3_COL;
	state->bird4_row = BIRD4_ROW;
	state->bird4_col = BIRD4_COL;
}

/* move: Performs a single move. 
 * Board is passed by reference and is altered in place. */
void move(State *state, Move *move, int turn)
{
	assert(move_valid(state, move, turn));
	if (state->larva_row == move->src_row && 
		state->larva_col == move->src_col) {
		state->larva_row = move->dest_row;
		state->larva_col = move->dest_col;
	}
	if (state->bird1_row == move->src_row && 
		state->bird1_col == move->src_col) {
		state->bird1_row = move->dest_row;
		state->bird1_col = move->dest_col;
	}
	if (state->bird2_row == move->src_row && 
		state->bird2_col == move->src_col) {
		state->bird2_row = move->dest_row;
		state->bird2_col = move->dest_col;
	}
	if (state->bird3_row == move->src_row &&
		state->bird3_col == move->src_col) {
		state->bird3_row = move->dest_row;
		state->bird3_col = move->dest_col;
	}
	if (state->bird4_row == move->src_row &&
		state->bird4_col == move->src_col) {
		state->bird4_row = move->dest_row;
		state->bird4_col = move->dest_col;
	}
}

/* move_input_format: formats a move (whose valid format was verified by 
 * move_input_format_valid) into an array of four ints representing array
 * indices which can then be verified for validity using move_valid. */
void move_input_format(const char *move, Move *result) 
{
	assert(move_input_format_valid(move));
	if (move[0] < 'I') { /* if uppercase */
		result->src_col = move[0] - 'A';
	} else { /* if lowercase */
		result->src_col = move[0] - 'a';
	}
	result->src_row = move[1] - '1';
	if (move[3] < 'I') { /* if uppercase */
		result->dest_col = move[3] - 'A';
	} else { /* if lowercase */
		result->dest_col = move[3] - 'a';
	}
	result->dest_row = move[4] - '1';
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
int move_valid(const State *state, Move *move, int current_turn) 
{
	assert(state);
	assert(move);
	assert(move->src_row >= 0 && move->src_row < 8);
	assert(move->src_col >= 0 && move->src_col < 8);
	assert(move->dest_row >= 0 && move->dest_row < 8); 
	assert(move->dest_col >= 0 && move->dest_col < 8);
	if (current_turn == BIRD_TURN) {
		if (get_square(state, move->src_row, move->src_col) == BIRD && /* src is bird */
			get_square(state, move->dest_row, move->dest_col) == EMPTY && /* dest is empty */
			move->dest_row - move->src_row == 1 && /* movement forward by one row only */
			abs(move->dest_col - move->src_col) == 1) { /* lateral movement by one only */
			return 1;
		}
	} else if (current_turn == LARVA_TURN) {
		if (get_square(state, move->src_row, move->src_col) == LARVA && /* src is larva */
			get_square(state, move->dest_row, move->dest_col) == EMPTY && /* dest is empty */
			abs(move->dest_row - move->src_row) == 1 && /* back or forward one row only */
			abs(move->dest_col - move->src_col) == 1) { /* lateral movement by one only */
			return 1;
		}
	}
	return 0;
}

/* print_board: prints the game status and state to stdout . */
void print_board(const State *state, int turn, int turn_no)
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
void print_row(const State *state, int row)
{
	assert(state);
	assert(row >= 0 && row < 8);
	printf("%d |", row + 1);
	int i;
	for (i = 0; i < 8; i++) {
		switch (get_square(state, row, i)) {
			case EMPTY:
				printf("   |");
				break;
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
	State state;
	init_board(&state);
	int turn_no = 1;
	Turn turn = LARVA_TURN;
	Move current_move;

	int victory = 0;
	while (!victory) { /* main game loop */
		print_board(&state, turn, turn_no);
		printf("Enter move: ");
		char buffer[5]; /* for input format "A1 B2" */
		fgets(buffer, 6, stdin);
		if (move_input_format_valid(buffer)) {
			memset(&current_move, 0, 4 * sizeof(int));
			move_input_format(buffer, &current_move);
			if (move_valid(&state, &current_move, turn)) {
				move(&state, &current_move, turn);
			} else {
				printf("Invalid move!\n");
				flush_input_buffer();
				continue;
			}
		} else if (strcmp(buffer, "exit\n") == 0) {
			printf("Be seeing you...\n");
			return;
		} else {
			printf("Invalid format!\n");
			flush_input_buffer();
			continue;
		}
		victory = victory_condition(&state);
		switch (victory) {
			case BIRD_VICTORY: 
				print_board(&state, turn, turn_no);
				printf("\nBirds win!\n");
				break;
			case LARVA_VICTORY: 
				print_board(&state, turn, turn_no);
				printf("\nLarva wins!\n");
				break;
		}
		flush_input_buffer();
		turn = !turn;
		turn_no++;
	}
}

/* victory_condition: Assesses whether parameters constitute a victory
 * condition. */
int victory_condition(const State *state) 
{
	int row = state->larva_row;
	int col = state->larva_col;
	/* Larva wins */
	/* Larva on bottom row wins */
	if (row == 0) {
		return LARVA_VICTORY;
	}
	if (row <= state->bird1_row &&
		row <= state->bird2_row &&
		row <= state->bird3_row &&
		row <= state->bird4_row) {
		return LARVA_VICTORY;
	}
	/* Bird wins */
	if (get_square(state, row + 1, col + 1) != EMPTY &&
		get_square(state, row + 1, col - 1) != EMPTY &&
		get_square(state, row - 1, col - 1) != EMPTY &&
		get_square(state, row - 1, col + 1) != EMPTY) {
		return BIRD_VICTORY;
	}
	/* else no victory */
	return NO_VICTORY;
}


/* get_square: returns the contents of a single square on the state.
 * row and col assume 0-indexed 8x8 gamestate. */
Square get_square(const State *state, int row, int col) 
{
	assert(state);
	if (state->larva_row == row && state->larva_col == col) {
		return LARVA;
	}
	if (state->bird1_row == row && state->bird1_col == col) {
		return BIRD;
	}
	if (state->bird2_row == row && state->bird2_col == col) {
		return BIRD;
	}
	if (state->bird3_row == row && state->bird3_col == col) {
		return BIRD;
	}
	if (state->bird4_row == row && state->bird4_col == col) {
		return BIRD;
	}
	// If row or col < 0 || > 7, square is offboard and therefore invalid
	if (row < 0 || row > 7 || col < 0 || col > 7) {
		return INVALID;
	}
	/* If the sum of row and col is odd, the square is invalid */
	if ((row + col) % 2 == 1) {
		return INVALID;
	}
	return EMPTY;
}
