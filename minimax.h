#ifndef MINIMAX_H
#define MINIMAX_H

#include <glib.h>
#include "hungrybirds.h"

void generate_moves(const State *state, GSList **moves, int turn);
void generate_bird_moves(const State *state, GSList **moves); 
void generate_larva_moves(const State *state, GSList **moves);
void generate_states(const State *state, GSList **states, int turn);
int naive_heuristic(const State *state);
int nh_square_value(int row, int col);

#endif
