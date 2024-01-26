#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>


#define X_SIZE 3
#define Y_SIZE 3
#define PLAYER 'X'
#define COMPUTER 'O'

//no worries just some globals :3
char board[X_SIZE][Y_SIZE];

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    //init ncurses
    initscr(); 
    curs_set(1); 
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE); 

    char winner = ' ';

    clear();

    resetBoard();
    while(winner == ' ' && checkFreeSpaces() != 0)
    {
        printBoard();

        playerMove();
        winner = checkWinner();
        if(winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }

        printBoard();

        computerMove();
        winner = checkWinner();
        if(winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
    }
    printWinner(winner);

    printw("Press enter to quit..");
    refresh();
    scanw("%d", NULL);
    endwin();
    return 0;
}
void resetBoard()
{
    for(int i = 0; i < X_SIZE; i++)
    {
        for(int j = 0; j < Y_SIZE; j++)
        {
            board[i][j] = ' '; // clear board
        }
    }
}
void printBoard()
{
    clear();
    printw("\n");
    printw(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printw("---|---|---\n");
    printw(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printw("---|---|---\n");
    printw(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);

    refresh();
}
int checkFreeSpaces()
{
    int freeSpaces = X_SIZE * Y_SIZE;
    for(int i = 0; i < X_SIZE ; i++)
    {
        for(int j = 0; j < Y_SIZE; j++)
        {
            if(board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}
void playerMove()
{
    int x;
    int y;

    while(1)
    {
        x = -1;
        y = -1;

        printw("Enter row #(1 - %d): ", Y_SIZE);
        refresh();
        scanw("%d", &x);
        
        x--; // 0 based array 

        printw("Enter column #(1 - %d): ", X_SIZE);
        refresh();
        scanw("%d", &y);
    
        y--;
        
        // Check if the cell is already occupied or if the move is out of bounds
        if (board[x][y] == ' ' && x >= 0 && x < X_SIZE && y >= 0 && y < Y_SIZE) 
        {
            // Valid move
            board[x][y] = PLAYER;
            break;
        } 
        else 
        {
            // Invalid move
            printw("Invalid Move!\n");
            refresh();
        }
        
    } 
    
}
void computerMove()
{
    // setup seed gen to time;
    srand(time(0));
    int x;
    int y;

    if(checkFreeSpaces() > 0)
    {
        while(1)
        {
            x = rand() % X_SIZE;
            y = rand() % Y_SIZE;

            if(y < 0)
            {
                y = 0;
            }
            if(x < 0)
            {
                x = 0;
            }

            if(board[x][y] == ' ' && board[x][y] != PLAYER)
            {
                break;
            }

        } 

        board[x][y] = COMPUTER;

        
        
    }

}
char checkWinner()
{
    // Row check
    for(int i = 0; i < Y_SIZE; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])//hardcoded 3x3
        {
            return board[i][0];
        }
    }

    // Column check
    for(int i = 0; i < Y_SIZE; i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])//hardcoded 3x3
        {
            return board[0][i];
        }
    }

    // Diag check
    if( board [0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if( board [0][2] == board[1][1] && board[0][0] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}
void printWinner(char winner)
{
    printBoard();
    switch(winner)
    {
        case PLAYER: printw("\nYOU WIN!\n");
            break;
        case COMPUTER: printw("\nYOU LOSE\n");
            break;
        default: printw("\nIts a tie\n"); 
    }
    refresh();
}