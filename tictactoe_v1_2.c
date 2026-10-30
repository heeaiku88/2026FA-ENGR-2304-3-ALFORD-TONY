/*
2026FA-ENGR-2304-3-ALFORD-TONY-P07
*/

/*
AI Disclosure:
This code was written by chatgpt
*/

/*
Chatgpt queeries

1. How could we go about accomplishing the following in C: Get the number of players (1 vs computer) or 2 player mode.

- Present a Tic-Tac-Toe board to the user and allow them to select whether they are X’s or O’s.
- Randomly determine who is allowed to go first.
- Take input from the user and display the updated board with their move displayed.
- After a slight delay (pause), the board is updated with the move made by the computer or allow the 2nd player to input their move.
- If either player is successful in creating a winning pattern then notify 
    of the result and prompt to pay again or end. If the choice is to play again, then return to step 1.

2.i like the structure you prepose lets build a first draft of this outlined
     structure
    
3. please run each of the 1.0 tests and report their outcome

4.one thing that i found during testing, no pattern is generated when the 
player wins

5.thats not exactly what i mean, what i mean is when someone wins 
i would like there to be something that notates it perhaps it is something 
like displaying "You Win!" But made entrirly of '*'s
     */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void initializeBoard(char board[3][3]);
void displayBoard(char board[3][3]);
int getPlayerMove(char board[3][3]);
int getComputerMove(char board[3][3]);
int checkWinner(char board[3][3], char symbol);
void displayResultBanner(const char *message);
int boardFull(char board[3][3]);
void clearInput(void);
int main(void)
{
    char board[3][3];
    char player1Symbol, player2Symbol;
    char currentSymbol;
    char playAgain = 'Y';
    int gameMode;
    int currentPlayer;
    int position;
    int row, col;
    int gameOver;
    srand((unsigned int)time(NULL));
    while (playAgain == 'Y' || playAgain == 'y')
    {
        printf("\n=== TIC-TAC-TOE ===\n");
        do
        {
            printf("\nSelect game mode:\n");
            printf("1. Player vs Computer\n");
            printf("2. Player vs Player\n");
            printf("Enter choice: ");
            if (scanf("%d", &gameMode) != 1)
            {
                gameMode = 0;
                clearInput();
            }
            if (gameMode != 1 && gameMode != 2)
                printf("Invalid choice. Try again.\n");
        } while (gameMode != 1 && gameMode != 2);
        do
        {
            printf("\nPlayer 1, choose X or O: ");
            scanf(" %c", &player1Symbol);
            clearInput();
            if (player1Symbol == 'x')
                player1Symbol = 'X';
            if (player1Symbol == 'o')
                player1Symbol = 'O';
            if (player1Symbol != 'X' && player1Symbol != 'O')
                printf("Please choose X or O.\n");
        } while (player1Symbol != 'X' && player1Symbol != 'O');
        initializeBoard(board);
        currentPlayer = rand() % 2 + 1;
        gameOver = 0;
        printf("\nPlayer 1 is %c.\n", player1Symbol);
        if (gameMode == 1)
            printf("Computer is %c.\n", player2Symbol = (player1Symbol == 'X') ? 'O' : 'X');
        else
            printf("Player 2 is %c.\n", player2Symbol = (player1Symbol == 'X') ? 'O' : 'X');
        printf("\nPlayer %d goes first!\n", currentPlayer);
        while (!gameOver)
        {
            displayBoard(board);
            if (currentPlayer == 1)
                currentSymbol = player1Symbol;
            else
                currentSymbol = player2Symbol;
            if (gameMode == 1 && currentPlayer == 2)
            {
                printf("\nComputer is thinking...\n");
                sleep(1);
                position = getComputerMove(board);
                printf("Computer chooses %d.\n", position);
            }
            else
            {
                printf("\nPlayer %d (%c), your turn.\n", currentPlayer, currentSymbol);
                position = getPlayerMove(board);
            }
            row = (position - 1) / 3;
            col = (position - 1) % 3;
            board[row][col] = currentSymbol;
            if (checkWinner(board, currentSymbol))
            {
                displayBoard(board);
                if (gameMode == 1 && currentPlayer == 2)
                    displayResultBanner("COMPUTER WINS!");
                else if (gameMode == 1)
                    displayResultBanner("YOU WIN!");
                else if (currentPlayer == 1)
                    displayResultBanner("PLAYER 1 WINS!");
                else
                    displayResultBanner("PLAYER 2 WINS!");
                gameOver = 1;
            }
            else if (boardFull(board))
            {
                displayBoard(board);
                displayResultBanner("DRAW!");
                gameOver = 1;
            }
            else
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &playAgain);
        clearInput();
    }
    printf("\nThanks for playing!\n");
    return 0;
}
void initializeBoard(char board[3][3])
{
    int row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            board[row][col] = ' ';
}
void displayBoard(char board[3][3])
{
    int row, col;
    char square;
    printf("\n");
    for (row = 0; row < 3; row++)
    {
        for (col = 0; col < 3; col++)
        {
            square = board[row][col];
            if (square == ' ')
                square = '1' + row * 3 + col;
            printf(" %c ", square);
            if (col < 2)
                printf("|");
        }
        printf("\n");
        if (row < 2)
            printf("---+---+---\n");
    }
}
int getPlayerMove(char board[3][3])
{
    int position;
    int row, col;
    while (1)
    {
        printf("Choose a position (1-9): ");
        if (scanf("%d", &position) != 1)
        {
            printf("Please enter a number.\n");
            clearInput();
            continue;
        }
        clearInput();
        if (position < 1 || position > 9)
        {
            printf("Position must be between 1 and 9.\n");
            continue;
        }
        row = (position - 1) / 3;
        col = (position - 1) % 3;
        if (board[row][col] != ' ')
        {
            printf("That square is already occupied.\n");
            continue;
        }
        return position;
    }
}
int getComputerMove(char board[3][3])
{
    int position;
    int row, col;
    do
    {
        position = rand() % 9 + 1;
        row = (position - 1) / 3;
        col = (position - 1) % 3;
    } while (board[row][col] != ' ');
    return position;
}
int checkWinner(char board[3][3], char symbol)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return 1;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return 1;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return 1;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return 1;
    return 0;
}
// Render large letters using only asterisks and spaces.
void displayResultBanner(const char *message)
{
    int row;
    const char *p;
    printf("\n");
    for (row = 0; row < 5; row++)
    {
        for (p = message; *p != '\0'; p++)
        {
            const char *pattern = "     ";
            switch (*p)
            {
                case '!':
                    {
                        static const char *glyph[5] = { "  *  ", "  *  ", "  *  ", "     ", "  *  " };
                        pattern = glyph[row];
                    }
                    break;
                case '1':
                    {
                        static const char *glyph[5] = { "  *  ", " **  ", "  *  ", "  *  ", " *** " };
                        pattern = glyph[row];
                    }
                    break;
                case '2':
                    {
                        static const char *glyph[5] = { " *** ", "*   *", "  ** ", " *   ", "*****" };
                        pattern = glyph[row];
                    }
                    break;
                case 'A':
                    {
                        static const char *glyph[5] = { " *** ", "*   *", "*****", "*   *", "*   *" };
                        pattern = glyph[row];
                    }
                    break;
                case 'C':
                    {
                        static const char *glyph[5] = { " ****", "*    ", "*    ", "*    ", " ****" };
                        pattern = glyph[row];
                    }
                    break;
                case 'D':
                    {
                        static const char *glyph[5] = { "**** ", "*   *", "*   *", "*   *", "**** " };
                        pattern = glyph[row];
                    }
                    break;
                case 'E':
                    {
                        static const char *glyph[5] = { "*****", "*    ", "**** ", "*    ", "*****" };
                        pattern = glyph[row];
                    }
                    break;
                case 'I':
                    {
                        static const char *glyph[5] = { "*****", "  *  ", "  *  ", "  *  ", "*****" };
                        pattern = glyph[row];
                    }
                    break;
                case 'L':
                    {
                        static const char *glyph[5] = { "*    ", "*    ", "*    ", "*    ", "*****" };
                        pattern = glyph[row];
                    }
                    break;
                case 'M':
                    {
                        static const char *glyph[5] = { "*   *", "** **", "* * *", "*   *", "*   *" };
                        pattern = glyph[row];
                    }
                    break;
                case 'N':
                    {
                        static const char *glyph[5] = { "*   *", "**  *", "* * *", "*  **", "*   *" };
                        pattern = glyph[row];
                    }
                    break;
                case 'O':
                    {
                        static const char *glyph[5] = { " *** ", "*   *", "*   *", "*   *", " *** " };
                        pattern = glyph[row];
                    }
                    break;
                case 'P':
                    {
                        static const char *glyph[5] = { "**** ", "*   *", "**** ", "*    ", "*    " };
                        pattern = glyph[row];
                    }
                    break;
                case 'R':
                    {
                        static const char *glyph[5] = { "**** ", "*   *", "**** ", "*  * ", "*   *" };
                        pattern = glyph[row];
                    }
                    break;
                case 'S':
                    {
                        static const char *glyph[5] = { " ****", "*    ", " *** ", "    *", "**** " };
                        pattern = glyph[row];
                    }
                    break;
                case 'T':
                    {
                        static const char *glyph[5] = { "*****", "  *  ", "  *  ", "  *  ", "  *  " };
                        pattern = glyph[row];
                    }
                    break;
                case 'U':
                    {
                        static const char *glyph[5] = { "*   *", "*   *", "*   *", "*   *", " *** " };
                        pattern = glyph[row];
                    }
                    break;
                case 'W':
                    {
                        static const char *glyph[5] = { "*   *", "*   *", "* * *", "** **", "*   *" };
                        pattern = glyph[row];
                    }
                    break;
                case 'Y':
                    {
                        static const char *glyph[5] = { "*   *", " * * ", "  *  ", "  *  ", "  *  " };
                        pattern = glyph[row];
                    }
                    break;
                default: break;
            }
            printf("%s ", pattern);
        }
        printf("\n");
    }
    printf("\n");
}

int boardFull(char board[3][3])
{
    int row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            if (board[row][col] == ' ')
                return 0;
    return 1;
}
void clearInput(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}
