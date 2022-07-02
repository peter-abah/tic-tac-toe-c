#include <stdio.h>

#define BOARD_SIZE 3

void print_board(char (*board)[BOARD_SIZE]);
void reset_board(char (*board)[BOARD_SIZE]);


int main(void) {
    char board[BOARD_SIZE][BOARD_SIZE];
    reset_board(board);

    print_board(board);
}

void reset_board(char (*board)[BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '\0';
        }
    }
}

void print_board(char (*board)[BOARD_SIZE]) {
    // Print heading
    printf("  0 1 2\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%i ", i);

        for (int j = 0; j < BOARD_SIZE; j++) {
            char c = board[i][j];
            if (c == '\0') {
                printf(" ");
            } else {
                printf("%c", c);
            }

            // Print separator only if it is not the last cell on the row
            if (j != BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
    }
}
