#include <stdio.h>
#include <stdbool.h>

#define COM_MOVE 'O'
#define USER_MOVE 'X'
#define ROW_SIZE 6
#define COL_SIZE 7

bool is_playing = true;
int num_spaces;

void createBoard(char board[ROW_SIZE][COL_SIZE]) {
    for (int row = 0; row < ROW_SIZE + 1; row++) {
        for (int col = 0; col < COL_SIZE; col++) {
            int actual_row = row - 1;

            printf("| ");
            if (row == 0)
                printf("%i ", col);
            else
                if (board[actual_row][col] == COM_MOVE || board[actual_row][col] == USER_MOVE)
                    printf("%c ", board[actual_row][col]);
                else
                    printf("  ");
            printf("|");
        }
        printf("\n");
    }
}

void start() {
    bool made_choice = false;
    
    char option;
    int output;

    printf("~Welcome to Four in a Row~\n");
    printf("Would you like to play? (Y/N)\n");

    while (!made_choice) {
        scanf(" %c", &option);

        if (option == 'Y' || option == 'y') 
        {
            printf("Game Start!\n");
            made_choice = true;
        }
        else if (option == 'N' || option == 'n') 
        {
            printf("Game Ended! Goodbye!\n");
            made_choice = true;
            is_playing = false;
        }
        else
            printf("Invalid Option: Try Again!\n");
    }
}

void instruct() {
    printf("Your Turn!\n");
    printf("Enter the column you'd like to be in.\n\n");
}

void pickCol(char (*board)[COL_SIZE]) {
    bool invalid_column = true;
    int picked_col;

    while (invalid_column)
    {
        scanf(" %i", &picked_col);

        for (int row = ROW_SIZE - 1; row >= 0; row--) {
            if (board[row][picked_col] != COM_MOVE && board[row][picked_col] != USER_MOVE) {
                invalid_column = false;
                board[row][picked_col] = USER_MOVE;
                break;
            }
        }

        if (!invalid_column)
            break;

        printf("This column is filled! Pick another!\n");
    }
    
    num_spaces--;
}

bool allFilled() {
    if (num_spaces > 0) 
        return true;
    return false;
}

void findBestMove(char (*board)[COL_SIZE]) {
    int picked_row;
    int best_col = -1;
    int best_value = -1;

    for (int col = 0; col < COL_SIZE; col++) {
        int possible_row = -1;

        for (int row = ROW_SIZE - 1; row >= 0; row--) {
            char current_space = board[row][col];

            if (current_space == ' ')
                possible_row = row;
        }

        if (possible_row == -1)
            continue;
        
        int current_space_value = findValue(board, col);
        
        if (current_space_value > best_value) {
            best_col = col;
            picked_row = possible_row;
        }
    }   

    board[picked_row][best_col] = COM_MOVE;
    num_spaces--;
}

int findValue(char board[ROW_SIZE][COL_SIZE], int chosen_col) {
    return 0;
}

void AITurn() {
    printf("\n");
    printf("COM Turn!\n");

    findBestMove();
}

void resetBoard(char (*board)[COL_SIZE]) {
    for (int row = 0; row < ROW_SIZE; row++) {
        for (int col = 0; col < COL_SIZE; col++) { 
            board[row][col] = ' ';
        }
    }

    num_spaces = ROW_SIZE * COL_SIZE;
}

void playGame() {
    char board[ROW_SIZE][COL_SIZE];

    while (is_playing) {
        resetBoard(board);
        start();

        if (!is_playing)
            break;
        
        bool not_finished = true;

        int count = 0;

        while (not_finished) {
            createBoard(board);

            instruct();
            pickCol(board);

            if (allFilled())
                break;

            count++;

            if (count >= 30) {
                not_finished = false;
            }
        }
    }
}

int main(void) 
{
    playGame();
    return 0;
}