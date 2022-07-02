#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 3

typedef struct {
    int x;
    int y;
} position;

position *get_input_pos(char (*board)[BOARD_SIZE]);
int get_int(char *prompt, int min, int max);
void print_board(char (*board)[BOARD_SIZE]);
void reset_board(char (*board)[BOARD_SIZE]);


int main(void) {
    char board[BOARD_SIZE][BOARD_SIZE];
    reset_board(board);

    print_board(board);
    position *pos = get_input_pos(board);
    printf("%i %i\n", pos->x, pos->y);
    free(pos);
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
    printf("   0   1   2\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Print horizontal separator
        if (i > 0) {
            printf("  -+-+-+-+-+-\n");
        }
        printf("%i ", i);

        for (int j = 0; j < BOARD_SIZE; j++) {
            // Print separator only if it is not the last cell on the row
            if (j > 0) {
                printf("|");
            }

            char c = board[i][j];
            if (c == '\0') {
                printf("   ");
            } else {
                printf(" %c ", c);
            }

        }
        printf("\n");
    }
}

position *get_input_pos(char (*board)[BOARD_SIZE]) {
    position *pos = malloc(sizeof(position));

    do {
        pos->x = get_int("X: ", 0, BOARD_SIZE - 1);
        pos->y = get_int("Y: ", 0, BOARD_SIZE - 1);
    } while (board[pos->y][pos->x] != '\0');

    return pos;
}

int get_int(char *prompt, int min, int max) {
    // Buffer to read int
    char input[10];
    char *temp;
    int n;

    do {
        printf("%s", prompt);
        // Get input
        fgets(input, sizeof(input), stdin);

        // Remove newline at end
        input[strcspn(input, "\n")] = 0;

        // Convert to int
        n = strtol(input, &temp, 10);
    }
    // Check input is valid
    while (*temp != '\0' || n < min || n > max);

    return n;
}

