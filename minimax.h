#ifndef MINIMAX_H
#define MINIMAX_H

#include <glib.h>
#include "hungrybirds.h"

#define LOTS 1337
#define MINIMAX_ERROR 666666

int alphabeta(const State *state, State **result, int alpha, int beta, int turn, int depth, int initial_depth);
void generate_moves(const State *state, GSList **moves, int turn);
void generate_bird_moves(const State *state, GSList **moves); 
void generate_larva_moves(const State *state, GSList **moves);
void generate_states(const State *state, GSList **states, int turn);
void hb_destroy(gpointer data);
int minimax(const State *state, State **result, int turn, int depth, int initial_depth);
int naive_heuristic(const State *state);
int nh_square_value(int row, int col);

#endif
