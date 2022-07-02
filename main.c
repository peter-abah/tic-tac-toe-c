    #include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 3

typedef struct {
    int x;
    int y;
} position;

void clear_stdin(void);
position *get_input_pos(char (*board)[BOARD_SIZE]);
int get_int(char *prompt, int min, int max);
bool check_winner(char (*board)[BOARD_SIZE], position *last_pos);
void print_board(char (*board)[BOARD_SIZE]);
void play_game(char (*board)[BOARD_SIZE]);
void reset_board(char (*board)[BOARD_SIZE]);


int main(void) {
    char board[BOARD_SIZE][BOARD_SIZE];
    char c;

    do {
        reset_board(board);
        play_game(board);

        // Ask user if they want to play again
        printf("Play again?(y/n) ");
        c = getchar();

        // Clear new line
        clear_stdin();
    } while (tolower(c) == 'y');
}

void play_game(char (*board)[BOARD_SIZE]) {
    char current = 'x';
    int cell_no = BOARD_SIZE * BOARD_SIZE;

    int i;
    // Loop nine times and after that all cells are filled so draw
    for (i = 0; i < cell_no; i++) {
        printf("\n");
        print_board(board);
        printf("\n");

        printf("Player %c turn\n", current);
        position *pos = get_input_pos(board);
        board[pos->y][pos->x] = current;

        if (check_winner(board, pos)) {
            free(pos);
            printf("\nPlayer %c wins!\n\n", current);
            break;
        }

        // Change players
        current = current == 'x' ? 'o' : 'x';
        free(pos);
        printf("\n");
    }

    // if the for loop runs to 9 then draw
    if (i == cell_no) {
        print_board(board);
        printf("\nDRAW!\n\n");
    }
}

bool check_winner(char (*board)[BOARD_SIZE], position *last_pos) {
    char current = board[last_pos->y][last_pos->x];

    // if count is equal to boarf size then player wins
    int count = 0;

    // Check row of pos
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[last_pos->y][i] != current) {
            break;
        }
        if (i == BOARD_SIZE - 1) {
            return true;
        }
    }

    //check column of pos
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][last_pos->x] != current) {
            break;
        }
        if (i == BOARD_SIZE - 1) {
            return true;
        }
    }

    // Check diagonal
    if (last_pos->x == last_pos->y) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][i] != current) {
                break;
            }
            if (i == BOARD_SIZE - 1) {
                return true;
            }
        }
    }

    // Check anti diagonal
    if (last_pos->x + last_pos->y == BOARD_SIZE - 1) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][BOARD_SIZE - 1 - i] != current) {
                break;
            }
            if (i == BOARD_SIZE - 1) {
                return true;
            }
        }
    }

    // At this point there is no winner
    return false;
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
    printf("     0   1   2\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Print horizontal separator
        if (i > 0) {
            printf("    -+-+-+-+-+-\n");
        }
        printf("  %i ", i);

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
        pos->y = get_int("Y: ", 0, BOARD_SIZE - 1);
        pos->x = get_int("X: ", 0, BOARD_SIZE - 1);
    } while (board[pos->y][pos->x] != '\0');

    return pos;
}

int get_int(char *prompt, int min, int max) {
    // Buffer to read int
    char input[11];
    char *temp;
    int n;

    do {
        printf("%s", prompt);
        // Get input
        fgets(input, sizeof(input), stdin);

        // Clear input buffer if there is no new line
        if (strchr(input, '\n') == NULL) {
            clear_stdin();
        }

        // Remove newline at end
        input[strcspn(input, "\n")] = 0;

        // Convert to int
        n = strtol(input, &temp, 10);
    }
    // Check input is valid
    while (*temp != '\0' || n < min || n > max);

    return n;
}

// Clears stdin buffer
void clear_stdin(void) {
    char c;
    while((c = getchar()) != '\n' && c != EOF) {}
}
