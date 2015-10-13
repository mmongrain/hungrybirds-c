#ifndef HUNGRYBIRDS_H
#define HUNGRYBIRDS_H

/* Constants */
#define BOARD_SIZE 32
#define POSITION_SIZE 2
#define MOVE_SIZE 4
#define NO_VICTORY 0
#define BIRD_VICTORY 1
#define LARVA_VICTORY 2

/* Options */
struct {
	/* Whether or not visual board should be printed */
	int visual;
	/* Whether or not to print debug messages ("verbose" mode) */
	int debug;
} options;

/* Types */
typedef enum square { EMPTY, BIRD, LARVA, INVALID } Square;
typedef enum turn { BIRD_TURN, LARVA_TURN } Turn;

/* By convention, int[2], where 
 * [0]: row, 
 * [1]: col */
// typedef int* Position;
/* By convention, int[4], where 
 * [0]: src row, 
 * [1]: src col, 
 * [2]: dest row, 
 * [3]: dest col */
typedef int* Move;

/* Global variables */

/* Pointer to the global board, an int[32].
 * Initialized by init_board(). 
 * Accessed and mutated by set_square() and get_square(). */
Square* board;

/* Stores the current turn */
Turn turn = LARVA_TURN;
int* larva_pos;

/* Stores the current turn number */
int turn_no = 1;

/* Functions */ 

int birds_surround_larva(const Square* state, const int* larva_position);
void flush_input_buffer();
void init_board_data(Square* state, int* larva_position);
void init_board(Square** state, int** larva_position);
void move(Square* state, Move move);
void move_input_format(const char* move, int* result);
int move_input_format_valid(const char* move);
int move_valid(const Square* state, Move move, int current_turn);
void print_board(const Square* state);
void print_row(const Square* state, int row);
void start();
int victory_condition(const Square* state, const int* larva_position);

/* Accessors and mutators */
Square set_square(Square* state, int row, int col, Square square);
Square get_square(const Square* state, int row, int col);

#endif
