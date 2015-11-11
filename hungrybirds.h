#ifndef HUNGRYBIRDS_H
#define HUNGRYBIRDS_H

/* Constants */
#define MOVE_SIZE 4
/* Initial board state */
#define LARVA_ROW 1
#define LARVA_COL 3
#define BIRD1_ROW 0
#define BIRD1_COL 0
#define BIRD2_ROW 0
#define BIRD2_COL 2
#define BIRD3_ROW 0
#define BIRD3_COL 4
#define BIRD4_ROW 0
#define BIRD4_COL 6

/* Options */
struct {
	/* Whether or not visual board should be printed */
	int visual;
	/* Whether or not to print debug messages ("verbose" mode) */
	int debug;
} options;

/* Types */
typedef enum Square { EMPTY, BIRD, LARVA, INVALID } Square;
typedef enum Turn { BIRD_TURN, LARVA_TURN } Turn;
typedef enum Victory { NO_VICTORY, BIRD_VICTORY, LARVA_VICTORY } Victory;

typedef struct Move { 
	int src_row;
	int src_col;
	int dest_row;
	int dest_col;
	int value;
} Move;

/* The board state. Just stores the positions of the pieces (no need to keep
 * track of empty or invalid squares as those can be deduced from the below) */
typedef struct State {
	int larva_row;
	int larva_col;
	int bird1_row;
	int bird1_col;
	int bird2_row;
	int bird2_col;
	int bird3_row;
	int bird3_col;
	int bird4_row;
	int bird4_col;
} State;


/* Functions */ 
int birds_surround_larva(const State *state);
void flush_input_buffer();
void init_board(State *state);
void move(State *state, Move *move, int turn);
void move_input_format(const char* move, Move *result);
int move_input_format_valid(const char* move);
int move_valid(const State *state, Move *move, int current_turn);
void print_board(const State *state, int turn, int turn_no);
void print_row(const State *state, int row);
void twoplayer_start();
int victory_condition(const State *state);
Square get_square(const State *state, int row, int col);

#endif
