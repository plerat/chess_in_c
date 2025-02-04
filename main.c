
#include <stdio.h>

#include "piece.h"
#include "board.h"
#include "move.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);
   if (isLegalMove(board, 1, 1, 2, 2)) {
        int test = whitePawnMove(board, 1, 1, 2, 2);
       printf("%d",test);
   } else {
      printf("Illegal move\n");
   }


    displayBoard(board);
    deleteBoard(board);
    return 0;
}
