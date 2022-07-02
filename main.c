#include <stdio.h>

#define BOARD_SIZE 3

void reset_board(char (*board)[BOARD_SIZE]);

int main(void) {
    char board[BOARD_SIZE][BOARD_SIZE];
    reset_board(board);

    printf("TIC TAC TOE\n");
}

void reset_board(char (*board)[BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = -1;
        }
    }
}
