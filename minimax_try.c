#include<stdio.h>
#include<limits.h>

#define X 1 /*@minimizer */
#define O 2 /*@maximizer */
#define PLAYER_X_WINING 1
#define PLAYER_O_WINING 2
#define MATCH_DRAW 0
#define GAME_IS_REMAINING -1
#define UNUSED 0
#define NO_WINNER_FOUND_YET -1

int board[3][3] = { 0 };

int min(int a, int b)
{
    return a > b ? b : a;
}
int max(int a, int b)
{
    return a > b ? a : b;
}

int vertical_scan()
{
    for (int col = 0; col < 3;col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] != 0) return board[0][col]; //winner found
        }
    }
    return NO_WINNER_FOUND_YET;
}
int horizontal_scan()
{
    for (int row = 0; row < 3;row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] != 0) return board[row][0]; //winner found
        }
    }
    return NO_WINNER_FOUND_YET;
}

int diagonal_scan()
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] != 0) return board[0][0]; //winner found
    }
    return NO_WINNER_FOUND_YET;
}
int rev_diagonal_scan()
{
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] != 0) return  board[0][2]; //winner found
    }
    return NO_WINNER_FOUND_YET;
}
int (*board_scanners[4])() = { vertical_scan, horizontal_scan, diagonal_scan, rev_diagonal_scan };

int is_all_square_filled()
{
    for(int i = 0;i < 3;i++) 
    {
        for(int j = 0;j < 3;j++)
        {
            if(board[i][j] == 0) return 0; 
        }
    }

    return 1;
}

int getBoardState()
{
    for (int i = 0;i < 4;i++) {
        int scan_result = (*board_scanners[i])();
        if (scan_result != NO_WINNER_FOUND_YET) return scan_result;
    }

    if(is_all_square_filled()) return MATCH_DRAW;

    return GAME_IS_REMAINING;

}

//board_val will be similar to FEN format used in chess
int set_board(char* board_val) {
    int row = 0;
    for(int i = 0;i < 11;i++) 
    {
        if(board_val[i] == "/") 
        {
            int j;
            for(j = row;j < i;j++)
            {
                
            }
        }
    }
}

void printBoard()
{
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}


int mini_max(int player)
{

    int boardState = getBoardState();

    if (boardState == PLAYER_X_WINING) return -10;
    if (boardState == PLAYER_O_WINING) return 10;
    if (boardState == MATCH_DRAW) return 5;

    int score = player == X ? INT_MAX : INT_MIN;


    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if (player == X) {
                board[i][j] = X;
                score = min(mini_max(O), score);
                board[i][j] = 0;
            }
            else {
                board[i][j] = O;
                score = max(mini_max(X), score);
                board[i][j] = 0;
            }
            printBoard();
            printf("%d\n", score);
        }
    }

    return score;
}

// int main()
// {
//     mini_max(X);
//     printf("\nExecution finished\n");
// }