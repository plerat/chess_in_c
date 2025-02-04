
#include "piece.h"
#include "board.h"
#include "move.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);
    isLegalMove(2,2,4,2,board);
    whitePawnMove(2,2,4,2,board);


    displayBoard(board);
    deleteBoard(board);
    return 0;
}
