#include <stdio.h>

#define MAX_N 10

void print_board(char board[MAX_N][MAX_N], int N);
int is_winner(char board[MAX_N][MAX_N], int N, int row, int col);
int is_tie(char board[MAX_N][MAX_N], int N);

int main(void) {
    int N;

    printf("Please enter the board size N [1-10]:\n");
    scanf("%d", &N);

    char board[MAX_N][MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            board[i][j] = '_';
        }
    }
    printf("Welcome to %dx%d Tic-Tac-Toe:\n", N, N);
    print_board(board, N);
    int player = 1;

    for (int moves = 0; moves < N * N; moves++) {
        printf("Player %d, please insert your move:\n", player);
        int row, col;

        while (1) {
            scanf(" %d , %d", &row, &col);
            row = row - 1;
            col = col - 1;

            if (row < 0 || row >= N || col < 0 || col >= N) {
                printf("Invalid indices (out of bounds), please choose your move again:\n");
                continue;
            }

            if (board[row][col] != '_') {
                printf("Invalid indices (occupied cell), please choose your move again:\n");
                continue;
            }

            break;
        }

        board[row][col] = (player == 1 ? 'X' : 'O');

        print_board(board, N);

        if (is_winner(board, N, row, col)) {
            printf("Player %d is the winner!\n", player);
            return 0;
        }

        if (is_tie(board, N)) {
            printf("There is a Tie!\n");
            return 0;
        }

        player = (player == 1 ? 2 : 1);
    }
    return 0;
}

void print_board(char board[MAX_N][MAX_N], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            putchar(board[i][j]);
            if (j < N - 1) {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

int is_winner(char board[MAX_N][MAX_N], int N, int row, int col) {
    char symbol = board[row][col];
    int win;
    /* Check entire row */
    win = 1;
    for (int j = 0; j < N; j++) {
        if (board[row][j] != symbol) {
            win = 0;
            break;
        }
    }
    if (win) {
        return 1;
    }
    /* Check entire column */
    win = 1;
    for (int i = 0; i < N; i++) {
        if (board[i][col] != symbol) {
            win = 0;
            break;
        }
    }
    if (win) {
        return 1;
    }
    /* Check main diagonal if applicable */
    if (row == col) {
        win = 1;
        for (int i = 0; i < N; i++) {
            if (board[i][i] != symbol) {
                win = 0;
                break;
            }
        }
        if (win) {
            return 1;
        }
    }
    /* Check anti‑diagonal if applicable */
    if (row + col == N - 1) {
        win = 1;
        for (int i = 0; i < N; i++) {
            if (board[i][N - 1 - i] != symbol) {
                win = 0;
                break;
            }
        }
        if (win) {
            return 1;
        }
    }
    return 0;
}

int is_tie(char board[MAX_N][MAX_N], int N) {
    int x_exists, o_exists;

    /*rows*/
    for (int i = 0; i < N; i++) {
        x_exists = 0;
        o_exists = 0;
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 'X') {
                x_exists = 1; 
            }
            else if (board[i][j] == 'O') {
                o_exists = 1;
            }
        }
        if (!x_exists || !o_exists) {
            return 0;
        }
    }

    /*columns*/
    for (int j = 0; j < N; j++) {
        x_exists = 0;
        o_exists = 0;
        for (int i = 0; i < N; i++) {
            if (board[i][j] == 'X'){
                x_exists = 1;
            }
            else if (board[i][j] == 'O'){
                o_exists = 1;
            }
        }
        if (!x_exists || !o_exists) {
            return 0;
        }
    }

    /*diagonals*/
    x_exists = 0;
    o_exists = 0;
    for (int i = 0; i < N; i++) {
        if (board[i][i] == 'X'){
            x_exists = 1;
        }
        else if (board[i][i] == 'O') {
            o_exists = 1;
        }
    }
    if (!x_exists || !o_exists) {
            return 0;
    }

    x_exists = 0;
    o_exists = 0;
    for (int i = 0; i < N; i++) {
        int j = N - 1 - i;
        if (board[i][j] == 'X') {
            x_exists = 1;
        }
        else if (board[i][j] == 'O') {
            o_exists = 1;
        }
    }
    if (!x_exists || !o_exists) {
            return 0;
    }

    return 1;
}

