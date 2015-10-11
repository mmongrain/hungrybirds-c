#include "hungrybirds.h"
#include <memory.h>
#include <stdio.h>
#include <assert.h>

#define INPUT_SIZE 5

int main()
{
	print_board();
	while (1) { /* main game loop */
		char buffer[INPUT_SIZE];
		fgets(buffer, INPUT_SIZE + 1, stdin);
		if (move_input_format_valid(buffer)) {
			printf("Valid!\n");
		} else {
			printf("Invalid!\n");
		}
		flush_input_buffer();
	}
	return 0;
}

/* 
 * Flushes the input buffer by reading chars until EOL or EOF.
 * ref: http://c-faq.com/stdio/stdinflush2.html
 */

void flush_input_buffer() {
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

/* 
 * Verifies that an entered move is valid in format (i.e. resembles A1 B2).
 * Does not verify whether the move is legal. No regexes in ANSI C!
 * Returns 0 if the move is invalid, 1 if it is valid.
 */
int move_input_format_valid(char* move) {
	/* source move */
	if (move[0] < 65 || /* not a letter */
		(move[0] > 72 && move[0] < 97) || /* not A-H */
		move[0] > 104 || /* not a-h */
		move[1] < 49 || /* <1 */
		move[1] > 56 || /* >8 */ 
		move[2] != 32 || /* not a space */
		move[3] < 65 || /* not a letter */
		(move[3] > 72 && move[3] < 97) || /* not A-H */
		move[3] > 104 || /* not a-h */
		move[4] < 49 || /* <1 */
		move[4] > 56) { /* >8 */ 
		return 0;
	} else return 1;
}

void print_board()
{
	char* divider = "  +-------------------------------+";
	printf("%s\n", divider);
	int i;
	for (i = BOARD_SIZE - 1; i >= 0; i--) {
		print_row(i);			
		printf("%s\n", divider);
	}
	printf("    A   B   C   D   E   F   G   H\n");
}

void print_row(int row)
{
	assert(row >= 0);
	assert(row < 8);
	printf("%d |", row + 1);
	int i;
	for (i = 0; i < BOARD_SIZE; i++) {
		switch (board[row][i]) {
			case INVALID:
			case EMPTY:
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
