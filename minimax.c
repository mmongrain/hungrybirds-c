/*******************************************************************************
* minimax.c - A minimax implementation for Hungry Birds
* by Matthew Mongrain, 11-11-2015
*******************************************************************************/

#include "hungrybirds.h"
#include "minimax.h"
#include <assert.h>
#include <glib.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

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
	assert(state);
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
	assert(state);
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

void generate_states(const State *state, GSList **states, int turn) {
	assert(state);
	GSList *moves = NULL;
	generate_moves(state, &moves, turn);
	GSList *elem = NULL;
	Move *single_move = NULL;
	for (elem = moves; elem; elem = elem->next) {
		State *child = g_new(State, 1);
		*child = *state;
		single_move = elem->data;
		move(child, single_move, turn);
		*states = g_slist_prepend(*states, child);
	}
	g_slist_free_full(moves, hb_destroy);
}

void hb_destroy(gpointer data)
{
	free(data);
}

int minimax(const State *state, State **result, int turn, int depth, int initial_depth) {
	int best = (turn == BIRD_TURN) ? LOTS : -LOTS;
	if (depth == 0) {
		best = naive_heuristic(state);
		if (options.debug) {
			//print_board(state, turn, depth);
			int i;
			for (i = 0; i < initial_depth - depth; i++) {
				printf("\t");
			}
			printf("Leaf node: %d\n", best);
		}
	} else {
		int val = 0;
		GSList *children = NULL;
		generate_states(state, &children, turn);
		GSList *iter = NULL;
		if (children != NULL) {
			for (iter = children; iter; iter = iter->next) {
				State *child = (State*)(iter->data);
				val = minimax(child, result, !turn, depth - 1, initial_depth);
				if (turn == LARVA_TURN && val > best && val != MINIMAX_ERROR) {
					if (depth == initial_depth) {
						**result = *child;
					}
					best = val;
				}
				if (turn == BIRD_TURN && val < best && val != MINIMAX_ERROR) {
					if (depth == initial_depth) {
						**result = *child;
						//print_board(*result, turn, depth);
					}
					best = val;
				}
			}
			if (options.debug) {
				int i = 0;
				for (; i < initial_depth - depth; i++) {
					printf("\t");
				}
				printf(
					"%s retrieved state with value: %d\n", 
					(turn == LARVA_TURN) ? "Larva" : "Bird",
					best
				);
			}
			g_slist_free_full(children, hb_destroy);
			g_slist_free(iter);
		} else if (options.debug) {
			int i;
			for (i = 0; i < initial_depth - depth; i++) {
				printf("\t");
			}
			printf("No valid children to this node! Returning %d\n", MINIMAX_ERROR);
		}
	}
	return best;
}

int alphabeta(const State *state, State **result, int alpha, int beta, int turn, int depth, int initial_depth) {
	int best = (turn == BIRD_TURN) ? LOTS : -LOTS;
	if (depth == 0) {
		best = naive_heuristic(state);
		if (options.debug) {
			int i;
			for (i = 0; i < initial_depth - depth; i++) {
				printf("\t");
			}
			printf("Leaf node: %d\n", best);
		}
	} else {
		int val = 0;
		GSList *children = NULL;
		generate_states(state, &children, turn);
		GSList *iter = NULL;
		for (iter = children; iter; iter = iter->next) {
			State *child = (State*)(iter->data);
			val = alphabeta(child, result, alpha, beta, !turn, depth - 1, initial_depth);
			if (turn == LARVA_TURN) {
				if (val > best) {
					if (depth == initial_depth) {
						**result = *child;
					}
					best = val;
				}
				if (best > alpha && beta <= best) {
					printf("Pruned...\n");
					break;
				}
			}
			if (turn == BIRD_TURN) {
				if (val < best) {
					if (depth == initial_depth) {
						**result = *child;
					}
					best = val;
				}
				if (beta < best && best <= alpha) {
					printf("Pruned...\n");
					break;
				}
			}
		}
		if (options.debug) {
			int i = 0;
			for (; i < initial_depth - depth; i++) {
				printf("\t");
			}
			printf(
				"%s retrieved state with value: %d\n", 
				(turn == LARVA_TURN) ? "Larva" : "Bird",
				best
			);
		}
		g_slist_free_full(children, hb_destroy);
		g_slist_free(iter);
	}
	return best;
}

int naive_heuristic(const State *state) {
	assert(state);
	int larva_value = nh_square_value(state->larva_row, state->larva_col); 
	int bird1_value = nh_square_value(state->bird1_row, state->bird1_col);
	int bird2_value = nh_square_value(state->bird2_row, state->bird2_col);
	int bird3_value = nh_square_value(state->bird3_row, state->bird3_col);
	int bird4_value = nh_square_value(state->bird4_row, state->bird4_col);
	return larva_value - bird1_value - bird2_value - bird3_value - bird4_value;
}

int nh_square_value(int row, int col) {
	assert(row >= 0 && row < 8);
	assert(col >= 0 && col < 8);
	row++;
	col++;
	switch (row) {
		case 1: return 56 + col;
		case 2: return 48 + col;
		case 3: return 40 + col;
		case 4: return 32 + col;
		case 5: return 24 + col;
		case 6: return 16 + col;
		case 7: return 8 + col;
		case 8: return col;
	}
	return 0;
}
