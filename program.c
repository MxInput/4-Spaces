#include <stdio.h>
#include <stdbool.h>

#define COM_MOVE 'O'
#define USER_MOVE 'X'
#define ROW_SIZE 6
#define COL_SIZE 7

struct Pos {
    int row, col;
};

void createBoard() {

}

void start() {
    bool made_choice = false;
    bool is_playing = false;

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
        }
        else
            printf("Invalid Option: Try Again!\n");
    }
}

void instruct() {

    printf("Enter the row you'd like to be in.\n\n");
    printf("Enter the column you'd like to be in.\n\n");
}

void playGame() {
    char board[ROW_SIZE][COL_SIZE];

    start();
}

int main(void) 
{
    playGame();
    return 0;
}