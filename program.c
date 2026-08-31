#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COM_MOVE 'O'
#define USER_MOVE 'X'
#define ROW_SIZE 6
#define COL_SIZE 7

bool is_playing = true;
bool random_AI = false;
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

    made_choice = false;

    printf("Would you like to play against easy or hard AI? (E/H)\n");
    
    while (!made_choice) {
        scanf(" %c", &option);

        if (option == 'E' || option == 'e') 
        {
            printf("The AI will be easy.\n");
            made_choice = true;
            random_AI = true;
        }
        else if (option == 'H' || option == 'h') 
        {
            printf("The AI will be hard.\n");
            made_choice = true;
            random_AI = false;
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
    if (num_spaces <= 0) 
        return true;
    return false;
}

void findRandomMove(char (*board)[COL_SIZE]) {
    int possible_cols[COL_SIZE];
    int picked_row = -1;
    int randCol;

    for (int col = 0; col < COL_SIZE; col++) {
        int possible_row = -1;

        for (int row = ROW_SIZE - 1; row >= 0; row--) {
            char current_space = board[row][col];

            if (current_space == ' ')
                possible_row = row;
        }

        possible_cols[col] = possible_row;
    }   

    while (picked_row == -1) {
        randCol = rand() % COL_SIZE;
        picked_row = possible_cols[randCol];
    }

    board[randCol][picked_row] = COM_MOVE;
    
    num_spaces--;
}

/*
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
*/

void findBestMove(char (*board)[COL_SIZE]) {}

int findValue(char board[ROW_SIZE][COL_SIZE], int chosen_col) {
    return 0;
}

void AITurn(char (*board)[COL_SIZE]) {
    printf("\n");
    printf("COM Turn!\n");

    if (random_AI) 
        findRandomMove(board);
    else 
        findBestMove(board);
}

char isWinner(char board[ROW_SIZE][COL_SIZE]) {
    for (int row = 0; row < ROW_SIZE; row++) {
        int num_com = 0;
        int num_user = 0;

        for (int col = 0; col < COL_SIZE; col++) {
            char space = board[row][col];

            if (space == COM_MOVE)
                num_com++;
            if (space == USER_MOVE)
                num_user++;
        }

        if (num_com >= 4) 
            return COM_MOVE;
        if (num_user >= 4) 
            return USER_MOVE;
    }

    for (int col = 0; col < COL_SIZE; col++) {
        int num_com = 0;
        int num_user = 0;

        for (int row = 0; row < ROW_SIZE; row++) {
            char space = board[row][col];

            if (space == COM_MOVE)
                num_com++;
            if (space == USER_MOVE)
                num_user++;
        }

        if (num_com >= 4) 
            return COM_MOVE;
        if (num_user >= 4) 
            return USER_MOVE;
    }

    for (int row = 0; row < ROW_SIZE - 3; row++) {
        for (int col = 0; col < COL_SIZE; col++) {
            int num_com = 0;
            int num_user = 0;

            char space = board[row][col];
            
            if (space == COM_MOVE)
                num_com++;
            else if (space == USER_MOVE)
                num_user++;

            if (col + 1 < COL_SIZE && row + 1 < ROW_SIZE)
                space = board[row + 1][col + 1];

                if (space == COM_MOVE)
                    num_com++;
                else if (space == USER_MOVE)
                    num_user++;
            else
                continue;

            if (col + 2 < COL_SIZE && row + 2 < ROW_SIZE)
                space = board[row + 2][col + 2];

                if (space == COM_MOVE)
                    num_com++;
                else if (space == USER_MOVE)
                    num_user++;
            else
                continue;

            if (col + 3 < COL_SIZE && row + 3 < ROW_SIZE)
                space = board[row + 3][col + 3];

                if (space == COM_MOVE)
                    num_com++;
                else if (space == USER_MOVE)
                    num_user++;
            else
                continue;

            if (num_com >= 4)
                return COM_MOVE;
            else if (num_user >= 4)
                return USER_MOVE;
        }
    }

    for (int row = ROW_SIZE - 1; row >= ROW_SIZE - 3; row--) {
        for (int col = 0; col < COL_SIZE; col++) {
            int num_com = 0;
            int num_user = 0;

            char space = board[row][col];
            
            if (space == COM_MOVE)
                num_com++;
            else if (space == USER_MOVE)
                num_user++;

            if (col - 1 < COL_SIZE && row - 1 < ROW_SIZE)
                space = board[row - 1][col - 1];

                if (space == COM_MOVE)
                    num_com++;
                else if (space == USER_MOVE)
                    num_user++;
            else
                continue;

            if (col - 2 < COL_SIZE && row - 2 < ROW_SIZE)
                space = board[row - 2][col - 2];

                if (space == COM_MOVE)
                    num_com++;
                else if (space == USER_MOVE)
                    num_user++;
            else
                continue;

            if (col - 3 < COL_SIZE && row - 3 < ROW_SIZE)
                space = board[row - 3][col - 3];

                if (space == COM_MOVE)
                    num_com++;
                else if (space == USER_MOVE)
                    num_user++;
            else
                continue;

            if (num_com >= 4)
                return COM_MOVE;
            else if (num_user >= 4)
                return USER_MOVE;
        }
    }

    return ' ';
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

        while (not_finished) {
            createBoard(board);

            instruct();
            pickCol(board);

            char winner_status = isWinner(board);

            if (winner_status == USER_MOVE){
                not_finished = false;
                printf("You Win!\n\n");
                break;
            }

            printf("%i", num_spaces);
            if (allFilled())
                not_finished = false;
                printf("There are no more empty spaces! The game will restart.\n\n");
                break;

            AITurn(board);

            winner_status = isWinner(board);

            if (winner_status == COM_MOVE){
                not_finished = false;
                printf("COM Wins!\n\n");
                break;
            }

            if (allFilled())
                not_finished = false;
                printf("There are no more empty spaces! The game will restart.\n\n");
                break;
        }
    }
}

int main(void) 
{
    playGame();
    return 0;
}