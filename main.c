
#include <stdio.h>

#include "piece.h"
#include "board.h"
#include "move.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);
   //if ( isLegalMove(1,1,3,1,board)) {
        whitePawnMove(1,1,3,1,board);
  // } else {
      // printf("Illegal move\n");
   //}


    displayBoard(board);
    deleteBoard(board);
    return 0;
}
