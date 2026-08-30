#include <stdio.h>
#include <stdbool.h>

#define COM_MOVE 'O'
#define USER_MOVE 'X'
#define ROW_SIZE 6
#define COL_SIZE 7

bool is_playing = true;

void createBoard(char board[ROW_SIZE][COL_SIZE]) {
    for (int row = 0; row < ROW_SIZE; row++) {
        for (int col = 0; col < COL_SIZE; col++) {
            if (board[row][col] == COM_MOVE || board[row][col] == USER_MOVE)
                printf(board[row][col]);
            if (col == 0)
                printf("| ");
            else 
                printf(" |");
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

void playGame() {
    char board[ROW_SIZE][COL_SIZE];

    while (is_playing) {
        start();

        if (!is_playing)
            break;
        
        createBoard();

        instruct();
    }
}

int main(void) 
{
    playGame();
    return 0;
}