
#include <stdio.h>

#include "piece.h"
#include "board.h"
#include "move.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);

    Point coord = {0,0} ;
    while (coord.col < 9) {
        Point nextCoord;
        printf("piece à move ! \n");
        coord = askCoord();
        printf("tu la mets ou ?\n");
        nextCoord = askCoord();
        printf("%d %d ==> %d / %d",coord.col,coord.row,nextCoord.col,nextCoord.row);
        if (isLegalMove(board, coord.col, coord.row, nextCoord.col,nextCoord.row)) {
            int test = move(board, coord.col,coord.row, nextCoord.col,nextCoord.row);
            printf("\n%d\n",test);
        } else {
            printf("\nIllegal move-whitepawnmove\n");
        }
        displayBoard(board);
    }
    deleteBoard(board);



    return 0;
}
