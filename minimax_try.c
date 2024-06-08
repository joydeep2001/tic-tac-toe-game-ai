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
// int set_board(char* board_val) {
//     int row = 0;
//     for(int i = 0;i < 11;i++) 
//     {
//         if(board_val[i] == "/") 
//         {
//             int j;
//             for(j = row;j < i;j++)
//             {
                
//             }
//         }
//     }
// }

void printBoard(FILE* fp)
{
    
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if(fp != NULL)
                fprintf(fp, "%d ", board[i][j]);
            else printf("%d ", board[i][j]);
        }
        if(fp != NULL) fprintf(fp, "\n");
        else printf("\n");
    }
}

int computer_move_i;
int computer_move_j;

int mini_max(int player)
{

    int boardState = getBoardState();
    // if(boardState == PLAYER_O_WINING || boardState == PLAYER_X_WINING || boardState == MATCH_DRAW) {
    //         FILE* fp = fopen("result.txt", "a");
    //         printBoard(fp);
    //         fclose(fp);
    // }
    if (boardState == PLAYER_X_WINING) return -10;
    if (boardState == PLAYER_O_WINING) return 10;
    if (boardState == MATCH_DRAW) return 5;

    int score = player == X ? INT_MAX : INT_MIN;


    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if(board[i][j] != 0) continue;
            if (player == X) {
                board[i][j] = X;
                int cur_score = mini_max(O);
                if(cur_score < score) {
                    score = cur_score;
                    computer_move_i = i;
                    computer_move_j = j;
                }
                
                board[i][j] = 0;
            }
            else {
                board[i][j] = O;
                int cur_score = mini_max(X);
                if(cur_score > score) {
                    score = cur_score;
                    computer_move_i = i;
                    computer_move_j = j;
                }
                board[i][j] = 0;
            }
        }
    }

    return score;
}

int main()
{
    
    while(!is_all_square_filled()) {
        int choice;
        printBoard(NULL);
        printf("Enter your square: ");
        scanf("%d", &choice);
        board[choice / 3][choice % 3] = 1;
        mini_max(O);
        board[computer_move_i][computer_move_j] = 2;
    }
    
    printf("\nExecution finished\n");
}