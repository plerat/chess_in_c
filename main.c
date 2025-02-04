
#include <stdio.h>

#include "piece.h"
#include "board.h"
#include "move.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);
   if (isLegalMove(board, 2, 1, 2, 3)) {
        int test = whitePawnMove(board, 2, 1, 2, 3);
       printf("\n%d\n",test);
   } else {
      printf("\nIllegal move-whitepawnmove\n");
   }

    if (isLegalMove(board, 1, 6, 1, 4)) {
        int test = blackPawnMove(board, 1, 6, 1, 4);
        printf("\n%d\n",test);
    } else {
        printf("\nIllegal move-blackpawnmove\n");
    }
    displayBoard(board);

    displayBoard(board);
    deleteBoard(board);
    Point coord = askUser();
    printf("%d %d",coord.col, coord.row);


    return 0;
}
