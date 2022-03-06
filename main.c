/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Torebayev Galym
 * Student ID    : 1155163273
 * Class/Section : ENGG1110B
 * Date          : 20 November 2021
 */

#include <stdio.h>
/* NO other header files are allowed */

/* NO global variables are allowed */

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2



/* Initialize the game board by setting all squares to EMPTY */
void initGameBoard(int gameBoard[6][7]) {
  for(int i=0; i<6; i++){
    for(int j=0; j<7; j++){
      gameBoard[i][j] = EMPTY;
    }
  }
}



/* Display the game board on the screen.
   You are required to exactly follow the output format stated in the project specification.
   IMPORTANT: Using other output format will result in mark deduction. */
void printGameBoard(int gameBoard[6][7]) {
  for(int i=0; i<6; i++){
    printf("|");
    for(int j=0; j<7; j++){
      if(gameBoard[i][j] == CIRCLE){
        printf("O");
      }else if(gameBoard[i][j] == CROSS){
        printf("X");
      }else{
        printf(" ");
      }
      printf("|");
    }
    printf("\n");
  }
  for(int i=1; i<=7; i++){
    printf(" %d", i);
  }
  printf(" \n");
}



/* Ask the human player to place the mark.
   You can assume that the user input must be an integer. */
void placeMarkByHumanPlayer(int gameBoard[6][7], int mark) {
  int place;
  while(1){
    scanf("%d", &place);
    if(place < 1 || place > 7){
    printf("Input out of range. Please input again:\n");
    continue;
    }else if(gameBoard[0][place - 1] != EMPTY){
    printf("Column is full. Please input again:\n");
    continue;
    }else{
      for(int i=5; i>=0; i--){
        if(gameBoard[i][place - 1] == EMPTY){
          gameBoard[i][place - 1] = mark;
          break;
        }
      }
      break;
    }
  }
}



/* Return 1 if there is a winner in the game, otherwise return 0.
   Note: the winner is the current player indicated in main(). */
int hasWinner(int gameBoard[6][7]){
  int counter = 0;
  for(int i=0; i<6; i++){
    for(int j=0; j<4; j++){
      if(gameBoard[i][j] != EMPTY && gameBoard[i][j] == gameBoard[i][j+1] && gameBoard[i][j] == gameBoard[i][j+2] && gameBoard[i][j] == gameBoard[i][j+3]){
        counter = 1;
      }
    }
    if(counter == 1){
      return 1;
    }
  }
  for(int j=0; j<7; j++){
    for(int i=0; i<3; i++){
      if(gameBoard[i][j] != EMPTY && gameBoard[i][j] == gameBoard[i+1][j] && gameBoard[i][j] == gameBoard[i+2][j] && gameBoard[i][j] == gameBoard[i+3][j]){
        counter = 1;
      }
    }
    if(counter == 1){
      return 1;
    }
  }
  for(int i=0; i<3; i++){
    for(int j=0; j<4; j++){
      if(gameBoard[i][j] != EMPTY && gameBoard[i][j] == gameBoard[i+1][j+1] && gameBoard[i][j] == gameBoard[i+2][j+2] && gameBoard[i][j] == gameBoard[i+3][j+3]){
        counter = 1;
      }
    }
    if(counter == 1){
      return 1;
    }
  }
  for(int i=0; i<3; i++){
    for(int j=6; j>2; j--){
      if(gameBoard[i][j] != EMPTY && gameBoard[i][j] == gameBoard[i+1][j-1] && gameBoard[i][j] == gameBoard[i+2][j-2] && gameBoard[i][j] == gameBoard[i+3][j-3]){
        counter = 1;
      }
    }
    if(counter == 1){
      return 1;
    }
  }
  return 0;
}



/* Return 1 if the game board is full, otherwise return 0. */
int isFull(int gameBoard[6][7]) {
  for(int i=0;i<6;i++){
    for(int j=0;j<7;j++){
      if(gameBoard[i][j] == EMPTY){
        return 0;
      }
    }
  }
  return 1;
}



/* Determine the next move of the computer player.
   You are required to exactly follow the strategy mentioned in the project specification.
   Using other strategies will result in mark deduction. */
void placeMarkByComputerPlayer(int gameBoard[6][7], int mark){
  int winningMoves = 0;
  int x, y;
  int losingMoves = 0;
  int a, b;
  int flag = 0;
  for(int j=0; j<7; j++){
    for(int i=5; i>0; i--){
      if(gameBoard[i][j] == EMPTY){
        gameBoard[i][j] = mark;
        if(hasWinner(gameBoard)){
          winningMoves++;
          x = i;
          y = j;
          gameBoard[i][j] = EMPTY;
          break;
        }
        gameBoard[i][j] = EMPTY;
        break;
      }
    }
  }
  for(int j=0; j<7; j++){
    for(int i=5; i>0; i--){
      if(gameBoard[i][j] == EMPTY){
        gameBoard[i][j] = CIRCLE;
        if(hasWinner(gameBoard)){
          losingMoves++;
          a = i;
          b = j;
          gameBoard[i][j] = EMPTY;
          break;
        }
        gameBoard[i][j] = EMPTY;
        break;
      }
    }
  }
  if(winningMoves > 0){
    gameBoard[x][y] = mark;
  }else if(winningMoves == 0 && losingMoves > 0){
    gameBoard[a][b] = mark;
  }else{
    for(int i=5; i>=0; i--){
      for(int j=6; j>=0; j--){
        if(gameBoard[i][j] == EMPTY){
          gameBoard[i][j] = mark;
          flag = 1;
          break;
        }
      }
      if(flag == 1){
        flag = 0;
        break;
      }
    }
  }
}



/* The main function */
int main()
{
    /* Local variables */
    int gameBoard[6][7];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1             2: Player 2
    int gameContinue;       // 1: The game continues   0: The game ends
    int numOfHumanPlayers;  // 1 or 2

    /* Initialize the local variables */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameContinue = 1;
    printf("Enter the number of human players [1-2]:\n");
    scanf("%d", &numOfHumanPlayers);    // You can assume that the user input must be valid

    /* Uncomment the following statements to test whether the printGameBoard() and the placeMarkByHumanPlayer() functions
       are implemented correctly.
       You can add more if you wish.
       After testing, you can delete them or move them elsewhere. */
    //printGameBoard(gameBoard);
    //printf("Player 1's turn:\n");
    //placeMarkByHumanPlayer(gameBoard, CIRCLE);
    //printGameBoard(gameBoard);
    //printf("Player 2's turn:\n");
    //placeMarkByHumanPlayer(gameBoard, CROSS);
    //printGameBoard(gameBoard);

    /* Game start
       If there are two human players, they are Player 1 and Player 2
       If there is only one human player, he/she is Player 1 and another player is the computer player
       For both cases, Player 1 moves first and places the CIRCLE mark; while Player 2 (or the computer player) places the CROSS mark
       Hint: use a while loop */
    while(gameContinue){
      printGameBoard(gameBoard);
      if(currentPlayer == 1){
        printf("Player 1's turn:\n");
        placeMarkByHumanPlayer(gameBoard, CIRCLE);
      }
      if(numOfHumanPlayers == 2){
        if(currentPlayer == 2){
          printf("Player 2's turn:\n");
          placeMarkByHumanPlayer(gameBoard, CROSS);
        }
      }else if(numOfHumanPlayers == 1){
        if(currentPlayer == 2){
          printf("Computer's turn:\n");
          placeMarkByComputerPlayer(gameBoard, CROSS);
        }
      }
      if(hasWinner(gameBoard)){
        printGameBoard(gameBoard);
        if(currentPlayer == 1){
          printf("Congratulations! Player 1 wins!");
        }else{
          if(numOfHumanPlayers == 1){
            printf("Computer wins!");
          }else{
            printf("Congratulations! Player 2 wins!");
          }
        }
        break;
      }else if(isFull(gameBoard) == 1){
        printGameBoard(gameBoard);
        printf("Draw game.");
        break;
      }else{
        if(currentPlayer == 1){
          currentPlayer = 2;
        }else{
          currentPlayer = 1;
        }
      }
    }
    return 0;
}