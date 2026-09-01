#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COM_MOVE 'O'
#define USER_MOVE 'X'
#define ROW_SIZE 6
#define COL_SIZE 7

bool is_playing = true;
bool random_AI = false;
int num_spaces = 0;

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

    printf("Would you like to play against easy or slightly smarter AI? (E/S)\n");
    
    while (!made_choice) {
        scanf(" %c", &option);

        if (option == 'E' || option == 'e') 
        {
            printf("The AI will be easy.\n");
            made_choice = true;
            random_AI = true;
        }
        else if (option == 'S' || option == 's') 
        {
            printf("The AI will be slightly smarter.\n");
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

void findRandomMove(char (*board)[COL_SIZE]) {
    int possible_cols[COL_SIZE];
    int picked_row = -1;
    int rand_col = -1;

    for (int col = 0; col < COL_SIZE; col++) {
        int possible_row = -1;

        for (int row = ROW_SIZE - 1; row >= 0; row--) {
            char current_space = board[row][col];

            if (current_space == ' ') 
            {
                possible_row = row;
                break;
            }  
        }

        possible_cols[col] = possible_row;
    }   

    while (picked_row == -1) {
        rand_col = rand() % COL_SIZE;
        picked_row = possible_cols[rand_col];
    }

    board[picked_row][rand_col] = COM_MOVE;
    
    num_spaces--;
}

bool filledBelow(char board[ROW_SIZE][COL_SIZE], int row, int col) {
    for (int current = ROW_SIZE - 1; current > row; current--) {
        char space = board[current][col];

        if (space == ' ')
            return false;
    }
    return true;
}

void findBestMove(char (*board)[COL_SIZE]) {
    for (int row = 0; row < ROW_SIZE; row++) {
        int num_com = 0;
        int num_user = 0;

        int start_com = -1;
        int start_user = -1;

        int end_com = -1;
        int end_user = -1;

        for (int col = 0; col < COL_SIZE; col++) {
            char space = board[row][col];

            if (space == COM_MOVE) {
                num_user = 0;
                num_com++;

                if (start_com == -1) {
                    start_com = col - 1;
                }

                start_user = -1;
            }
            else if (space == USER_MOVE) {
                num_com = 0;
                num_user++;
                
                if (start_user == -1) {
                    start_user = col - 1;
                }

                start_com = -1;
            }   
            else if (space == ' ') {
                num_user = 0;
                num_com = 0;
            }

            printf("%i %i\n", num_user, num_com);
                
            if (num_com >= 2) {
                end_com = col + 1;

                if (start_com >= 0) {
                    space = board[row][start_com];

                    if (space == ' ' && (row == ROW_SIZE - 1 || filledBelow(board, row, start_com))) {
                        board[row][start_com] = COM_MOVE;
                        printf("%i %i\n", start_com);

                        num_spaces--;
                        return;
                    }
                }

                if (end_com < COL_SIZE) {
                    space = board[row][end_com];

                    if (space == ' ' && (row == ROW_SIZE - 1 || filledBelow(board, row, end_com))) {
                        board[row][end_com] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            } 
            if (num_user >= 2) {
                end_user = col + 1;
    
                if (start_user >= 0 && (row == ROW_SIZE - 1 || filledBelow(board, row, start_user))) {
                    space = board[row][start_user];

                    if (space == ' ') {
                        board[row][start_user] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }

                if (end_user < COL_SIZE) {
                    space = board[row][end_user];

                    if (space == ' ' && (row == ROW_SIZE - 1 || filledBelow(board, row, end_user))) {
                        board[row][end_user] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            }
        }
    }

    printf("passed cross");

    for (int col = 0; col < COL_SIZE; col++) {
        int num_com = 0;
        int num_user = 0;

        int start_com = -1;
        int start_user = -1;

        int end_com = -1;
        int end_user = -1;

        for (int row = ROW_SIZE - 1; row >= 0; row--) {
            char space = board[row][col];

            if (space == COM_MOVE) {
                num_user = 0;
                num_com++;

                if (start_com == -1) {
                    start_com = row + 1;
                }

                start_user = -1;
            }
            else if (space == USER_MOVE) {
                num_com = 0;
                num_user++;
                
                if (start_user == -1) {
                    start_user = row + 1;
                }

                start_com = -1;
            }   
            else if (space == ' ') {
                num_user = 0;
                num_com = 0;
            }
                
            if (num_com >= 2) {
                end_com = row - 1;

                if (start_com < ROW_SIZE) {
                    space = board[start_com][col];

                    if (space == ' ') {
                        board[start_com][col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }

                if (end_com >= 0) {
                    space = board[end_com][col];

                    if (space == ' ') {
                        board[end_com][col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            } 
            if (num_user >= 2) {
                end_user = row - 1;

                if (start_user < ROW_SIZE) {
                    space = board[start_user][col];

                    if (space == ' ') {
                        board[start_user][col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }

                if (end_user >= 0) {
                    space = board[end_user][col];

                    if (space == ' ') {
                        board[end_user][col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            }
        }
    }

    printf("passed long");

    for (int row = 0; row < ROW_SIZE - 3; row++) {
        for (int col = 0; col < COL_SIZE; col++) {
            int num_com = 0;
            int num_user = 0;

            int start_com_row = -1;
            int start_com_col = -1;

            int start_user_row = -1;
            int start_user_col = -1;

            int end_com_row = -1;
            int end_com_col = -1;

            int end_user_row = -1;
            int end_user_col = -1;

            char space = board[row][col];
            
            if (space == COM_MOVE) {
                start_com_row = row - 1;
                start_com_col = col - 1;
                
                num_com++;
            }
            else if (space == USER_MOVE) {
                start_user_row = row - 1;
                start_user_col = col - 1;

                num_user++;
            }
            
            if (col + 1 < COL_SIZE && row + 1 < ROW_SIZE) {
                space = board[row + 1][col + 1];

                if (space == COM_MOVE) {
                    start_user_row = 0;
                    start_user_col = 0;

                    if (start_com_row == -1 && start_com_col == -1) {
                        start_com_row = row - 1;
                        start_com_col = col - 1;
                    }

                    num_com++;
                }
                else if (space == USER_MOVE) {
                    start_com_row = 0;
                    start_com_col = 0;

                    if (start_user_row == -1 && start_user_col == -1) {
                        start_user_row = row - 1;
                        start_user_col = col - 1;
                    }

                    num_user++;
                }
                else {
                    start_user_row = 0;
                    start_user_col = 0;

                    start_com_row = 0;
                    start_com_col = 0;
                }
            }  
            else
                continue;

            if (col + 2 < COL_SIZE && row + 2 < ROW_SIZE) {
                space = board[row + 2][col + 2];

                if (space == COM_MOVE) {
                    start_user_row = 0;
                    start_user_col = 0;

                    if (start_com_row == -1 && start_com_col == -1) {
                        start_com_row = row - 1;
                        start_com_col = col - 1;
                    }

                    num_com++;
                }
                else if (space == USER_MOVE) {
                    start_com_row = 0;
                    start_com_col = 0;

                    if (start_user_row == -1 && start_user_col == -1) {
                        start_user_row = row - 1;
                        start_user_col = col - 1;
                    }

                    num_user++;
                }
                else {
                    start_user_row = 0;
                    start_user_col = 0;

                    start_com_row = 0;
                    start_com_col = 0;
                }
            }
            else
                continue;
                
            if (num_com >= 2) {
                end_com_col = col + 1;
                end_com_row = row + 1;

                if (start_com_col >= 0 && start_com_row >= 0) {
                    space = board[start_com_row][start_com_col];

                    if (space == ' ' && (start_com_row == ROW_SIZE - 1 || filledBelow(board, start_com_row, start_com_col))) {
                        board[start_com_row][start_com_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }

                if (end_com_col < COL_SIZE && end_com_row < ROW_SIZE) {
                    space = board[end_com_row][end_com_col];

                    if (space == ' ' && (end_com_row == ROW_SIZE - 1 || filledBelow(board, end_com_row, end_com_col))) {
                        board[end_com_row][end_com_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            } 

            if (num_user >= 2) {
                end_user_col = col + 1;
                end_user_row = row + 1;


                if (start_user_col >= 0 && start_user_row >= 0) {
                    space = board[start_user_row][start_user_col];

                    if (space == ' ' && (start_user_row == ROW_SIZE - 1 || filledBelow(board, start_user_row, start_user_col))) {
                        board[start_user_row][start_user_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }

                if (end_user_col < COL_SIZE && end_user_row < ROW_SIZE) {
                    space = board[end_user_row][end_user_col];

                    if (space == ' ' && (end_user_row == ROW_SIZE - 1 || filledBelow(board, end_user_row, end_user_col))) {
                        board[end_user_row][end_user_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            }
        }
    }

    printf("passed cross 1");

    for (int row = ROW_SIZE - 1; row >= ROW_SIZE - 3; row--) {
        for (int col = 0; col < COL_SIZE; col++) {
            int num_com = 0;
            int num_user = 0;

            int start_com_row = -1;
            int start_com_col = -1;

            int start_user_row = -1;
            int start_user_col = -1;

            int end_com_row = -1;
            int end_com_col = -1;

            int end_user_row = -1;
            int end_user_col = -1;

            char space = board[row][col];
            
            if (space == COM_MOVE) {
                start_com_row = row + 1;
                start_com_col = col - 1;
                
                num_com++;
            }
            else if (space == USER_MOVE) {
                start_user_row = row + 1;
                start_user_col = col - 1;

                num_user++;
            }
            
            if (col + 1 < COL_SIZE && row - 1 >= 0) {
                space = board[row - 1][col + 1];

                if (space == COM_MOVE) {
                    start_user_row = 0;
                    start_user_col = 0;

                    if (start_com_row == -1 && start_com_col == -1) {
                        start_com_row = row + 2;
                        start_com_col = col - 2;
                    }

                    num_com++;
                }
                else if (space == USER_MOVE) {
                    start_com_row = 0;
                    start_com_col = 0;

                    if (start_user_row == -1 && start_user_col == -1) {
                        start_user_row = row + 2;
                        start_user_col = col - 2;
                    }

                    num_user++;
                }
                else {
                    start_user_row = 0;
                    start_user_col = 0;

                    start_com_row = 0;
                    start_com_col = 0;
                }
            }  
            else
                continue;

            if (col + 2 < COL_SIZE && row - 2 >= 0) {
                space = board[row - 2][col + 2];

                if (space == COM_MOVE) {
                    start_user_row = 0;
                    start_user_col = 0;

                    if (start_com_row == -1 && start_com_col == -1) {
                        start_com_row = row + 3;
                        start_com_col = col - 3;
                    }

                    num_com++;
                }
                else if (space == USER_MOVE) {
                    start_com_row = 0;
                    start_com_col = 0;

                    if (start_user_row == -1 && start_user_col == -1) {
                        start_user_row = row + 3;
                        start_user_col = col - 3;
                    }

                    num_user++;
                }
                else {
                    start_user_row = 0;
                    start_user_col = 0;

                    start_com_row = 0;
                    start_com_col = 0;
                }
            }
            else
                continue;
                
            if (num_com >= 3) {
                end_com_col = col + num_com;
                end_com_row = row - num_com;

                if (start_com_col >= 0 && start_com_row >= 0) {
                    space = board[start_com_row][start_com_col];

                    if (space == ' ' && (start_com_row == ROW_SIZE - 1 || filledBelow(board, start_com_row, start_com_col))) {
                        board[start_com_row][start_com_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }

                if (end_com_col < COL_SIZE && end_com_row < ROW_SIZE) {
                    space = board[end_com_row][end_com_col];

                    if (space == ' ' && (end_com_row == ROW_SIZE - 1 || filledBelow(board, end_com_row, end_com_col))) {
                        board[end_com_row][end_com_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            } 

            if (num_user >= 3) {
                end_user_col = col + num_user;
                end_user_row = row - num_user;

                if (start_user_col >= 0 && start_user_row >= 0) {
                    space = board[start_user_row][start_user_col];

                    if (space == ' ' && (start_user_row == ROW_SIZE - 1 || filledBelow(board, start_user_row, start_user_col))) {
                        board[start_user_row][start_user_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }

                if (end_user_col < COL_SIZE && end_user_row < ROW_SIZE) {
                    space = board[end_user_row][end_user_col];

                    if (space == ' ' && (end_user_row == ROW_SIZE - 1 || filledBelow(board, end_user_row, end_user_col))) {
                        board[end_user_row][end_user_col] = COM_MOVE;
                        num_spaces--;
                        return;
                    }
                }
            }
        }
    }

    printf("other options");
    findRandomMove(board);
}

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

            if (space == COM_MOVE) {
                num_user = 0;
                num_com++;
            }
            else if (space == USER_MOVE) {
                num_com = 0;
                num_user++;
            }   
            else if (space == ' ') {
                num_user = 0;
                num_com = 0;
            }
                
            if (num_com >= 4) {
                printf("1");
                return COM_MOVE;
            }
            if (num_user >= 4) {
                printf("1");
                return USER_MOVE;
            }
        }
    }

    for (int col = 0; col < COL_SIZE; col++) {
        int num_com = 0;
        int num_user = 0;

        for (int row = 0; row < ROW_SIZE; row++) {
            char space = board[row][col];

            if (space == COM_MOVE) {
                num_user = 0;
                num_com++;
            }
            if (space == USER_MOVE) {
                num_com = 0;
                num_user++;
            }
            if (space == ' ') {
                num_user = 0;
                num_com = 0;
            }

            if (num_com >= 4) {
                printf("2");
                return COM_MOVE;
            }
            if (num_user >= 4) {
                printf("2");
                return USER_MOVE;
            }
        }
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

            if (col + 1 < COL_SIZE && row + 1 < ROW_SIZE) {
                space = board[row + 1][col + 1];

                if (space == COM_MOVE) {
                    num_com++;
                    num_user = 0;
                }
                else if (space == USER_MOVE){
                    num_user++;
                    num_com = 0;
                }                
                else {
                    num_com = 0;
                    num_user = 0;
                }
            }  
            else
                continue;

            if (col + 2 < COL_SIZE && row + 2 < ROW_SIZE) {
                space = board[row + 2][col + 2];

                if (space == COM_MOVE){
                    num_com++;
                    num_user = 0;
                }
                else if (space == USER_MOVE){
                    num_user++;
                    num_com = 0;
                }                
                else {
                    num_com = 0;
                    num_user = 0;
                }
            }
            else
                continue;

            if (col + 3 < COL_SIZE && row + 3 < ROW_SIZE) {
                space = board[row + 3][col + 3];

                if (space == COM_MOVE){
                    num_com++;
                    num_user = 0;
                }
                else if (space == USER_MOVE){
                    num_user++;
                    num_com = 0;
                }                
                else {
                    num_com = 0;
                    num_user = 0;
                }
            }
            else
                continue;

            if (num_com >= 4) {
                printf("3");
                return COM_MOVE;
            }
            else if (num_user >= 4) {
                printf("3");
                return USER_MOVE;
            }
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

            if (col + 1 < COL_SIZE && row - 1 >= 0) {
                space = board[row - 1][col + 1];

                if (space == COM_MOVE){
                    num_com++;
                    num_user = 0;
                }
                else if (space == USER_MOVE){
                    num_user++;
                    num_com = 0;
                }                
                else {
                    num_com = 0;
                    num_user = 0;
                }
            }
            else
                continue;

            if (col + 2 < COL_SIZE && row - 2 >= 0) {
                space = board[row - 2][col + 2];

                if (space == COM_MOVE){
                    num_com++;
                    num_user = 0;
                }
                else if (space == USER_MOVE){
                    num_user++;
                    num_com = 0;
                }                
                else {
                    num_com = 0;
                    num_user = 0;
                }
            }
            else
                continue;

            if (col + 3 < COL_SIZE && row - 3 >= 0) {
                space = board[row - 3][col + 3];

                if (space == COM_MOVE){
                    num_com++;
                    num_user = 0;
                }
                else if (space == USER_MOVE){
                    num_user++;
                    num_com = 0;
                }
                else {
                    num_com = 0;
                    num_user = 0;
                }
            }
            else
                continue;

            if (num_com >= 4) {
                printf("4");
                return COM_MOVE;
            }
            else if (num_user >= 4) {
                printf("4");
                return USER_MOVE;
            }
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

            if (num_spaces <= 0 == true) {
                not_finished = false;
                printf("There are no more empty spaces! The game will restart.\n\n");
                break;
            }

            AITurn(board);

            winner_status = isWinner(board);

            if (winner_status == COM_MOVE){
                not_finished = false;
                printf("COM Wins!\n\n");
                break;
            }

            if (num_spaces <= 0 == true) {
                not_finished = false;
                printf("There are no more empty spaces! The game will restart.\n\n");
                break;
            }
                
        }
    }
}

int main(void) 
{
    playGame();
    return 0;
}