#include <assert.h>
#include <glib.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"
#include "hungrybirds.h"

void generate_moves(const State *state, GSList **moves, int turn) 
{
	assert(state);
	if (turn == LARVA_TURN) {
		generate_larva_moves(state, moves);
	} else if (turn == BIRD_TURN) {
		generate_bird_moves(state, moves);
	}
}


void generate_bird_moves(const State *state, GSList **moves) {
	if (state->bird1_row < 7) {
		if (state->bird1_col < 7) {
			if (get_square(state, state->bird1_row + 1, state->bird1_col + 1)
				== EMPTY) {
				Move *upright = malloc(sizeof(Move));
				upright->src_row = state->bird1_row;
				upright->src_col = state->bird1_col;
				upright->dest_row = state->bird1_row + 1;
				upright->dest_col = state->bird1_col + 1;
				*moves = g_slist_prepend(*moves, upright);
			}
		}
		if (state->bird1_col > 0) {
			if (get_square(state, state->bird1_row + 1, state->bird1_col - 1)
				== EMPTY) {
				Move *upleft = malloc(sizeof(Move));
				upleft->src_row = state->bird1_row;
				upleft->src_col = state->bird1_col;
				upleft->dest_row = state->bird1_row + 1;
				upleft->dest_col = state->bird1_col - 1;
				*moves = g_slist_prepend(*moves, upleft);
			}
		}
	}

	if (state->bird2_row < 7) {
		if (state->bird2_col < 7) {
			if (get_square(state, state->bird2_row + 1, state->bird2_col + 1)
				== EMPTY) {
				Move *upright = malloc(sizeof(Move));
				upright->src_row = state->bird2_row;
				upright->src_col = state->bird2_col;
				upright->dest_row = state->bird2_row + 1;
				upright->dest_col = state->bird2_col + 1;
				*moves = g_slist_prepend(*moves, upright);
			}
		}
		if (state->bird2_col > 0) {
			if (get_square(state, state->bird2_row + 1, state->bird2_col - 1)
				== EMPTY) {
				Move *upleft = malloc(sizeof(Move));
				upleft->src_row = state->bird2_row;
				upleft->src_col = state->bird2_col;
				upleft->dest_row = state->bird2_row + 1;
				upleft->dest_col = state->bird2_col - 1;
				*moves = g_slist_prepend(*moves, upleft);
			}
		}
	}

	if (state->bird3_row < 7) {
		if (state->bird3_col < 7) {
			if (get_square(state, state->bird3_row + 1, state->bird3_col + 1)
				== EMPTY) {
				Move *upright = malloc(sizeof(Move));
				upright->src_row = state->bird3_row;
				upright->src_col = state->bird3_col;
				upright->dest_row = state->bird3_row + 1;
				upright->dest_col = state->bird3_col + 1;
				*moves = g_slist_prepend(*moves, upright);
			}
		}
		if (state->bird3_col > 0) {
			if (get_square(state, state->bird3_row + 1, state->bird3_col - 1)
				== EMPTY) {
				Move *upleft = malloc(sizeof(Move));
				upleft->src_row = state->bird3_row;
				upleft->src_col = state->bird3_col;
				upleft->dest_row = state->bird3_row + 1;
				upleft->dest_col = state->bird3_col - 1;
				*moves = g_slist_prepend(*moves, upleft);
			}
		}
	}

	if (state->bird4_row < 7) {
		if (state->bird4_col < 7) {
			if (get_square(state, state->bird4_row + 1, state->bird4_col + 1)
				== EMPTY) {
				Move *upright = malloc(sizeof(Move));
				upright->src_row = state->bird4_row;
				upright->src_col = state->bird4_col;
				upright->dest_row = state->bird4_row + 1;
				upright->dest_col = state->bird4_col + 1;
				*moves = g_slist_prepend(*moves, upright);
			}
		}
		if (state->bird4_col > 0) {
			if (get_square(state, state->bird4_row + 1, state->bird4_col - 1)
				== EMPTY) {
				Move *upleft = malloc(sizeof(Move));
				upleft->src_row = state->bird4_row;
				upleft->src_col = state->bird4_col;
				upleft->dest_row = state->bird4_row + 1;
				upleft->dest_col = state->bird4_col - 1;
				*moves = g_slist_prepend(*moves, upleft);
			}
		}
	}
}

void generate_larva_moves(const State *state, GSList **moves)
{
	if (state->larva_row < 7) {
		if (state->larva_col < 7) {
			if (get_square(state, state->larva_row + 1, state->larva_col + 1)
				== EMPTY) {
				Move *upright = malloc(sizeof(Move));
				upright->src_row = state->larva_row;
				upright->src_col = state->larva_col;
				upright->dest_row = state->larva_row + 1;
				upright->dest_col = state->larva_col + 1;
				*moves = g_slist_prepend(*moves, upright);

			}
		}
		if (state->larva_col > 0) {
			if (get_square(state, state->larva_row + 1, state->larva_col - 1)
				== EMPTY) {
				Move *upleft = malloc(sizeof(Move));
				upleft->src_row = state->larva_row;
				upleft->src_col = state->larva_col;
				upleft->dest_row = state->larva_row + 1;
				upleft->dest_col = state->larva_col - 1;
				*moves = g_slist_prepend(*moves, upleft);
			}
		}
	}
	if (state->larva_col < 7) {
		if (get_square(state, state->larva_row - 1, state->larva_col + 1)
			== EMPTY) {
			Move *downright = malloc(sizeof(Move));
			downright->src_row = state->larva_row;
			downright->src_col = state->larva_col;
			downright->dest_row = state->larva_row - 1;
			downright->dest_col = state->larva_col + 1;
			*moves = g_slist_prepend(*moves, downright);
		}
	}
	if (state->larva_col > 0) {
		if (get_square(state, state->larva_row - 1, state->larva_col - 1)
			== EMPTY) {
			Move *downleft = malloc(sizeof(Move));
			downleft->src_row = state->larva_row;
			downleft->src_col = state->larva_col;
			downleft->dest_row = state->larva_row - 1;
			downleft->dest_col = state->larva_col - 1;
			*moves = g_slist_prepend(*moves, downleft);
		}
	}
}
