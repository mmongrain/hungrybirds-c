#ifndef HUNGRYBIRDS_H
#define HUNGRYBIRDS_H

/* Constants */
#define BOARD_SIZE 32
#define POSITION_SIZE 2
#define MOVE_SIZE 4

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
typedef enum victory { NO_VICTORY, BIRD_VICTORY, LARVA_VICTORY } Victory;
typedef Square* Board;
/* By convention, int[4], where 
 * [0]: src row, 
 * [1]: src col, 
 * [2]: dest row, 
 * [3]: dest col */
typedef int* Move;

/* Functions */ 

int birds_surround_larva(const Board state, const int* larva_position);
void flush_input_buffer();
void init_board_data(Board state, int* larva_position);
void init_board(Board* state, int** larva_position);
void move(Board state, Move move, int turn, int* larva_position);
void move_input_format(const char* move, int* result);
int move_input_format_valid(const char* move);
int move_valid(const Board state, Move move, int current_turn);
void print_board(const Board state, int turn, int turn_no);
void print_row(const Board state, int row);
void twoplayer_start();
int victory_condition(const Board state, const int* larva_position);

/* Accessors and mutators */
Square set_square(Board state, int row, int col, Square square);
Square get_square(const Board state, int row, int col);

#endif
