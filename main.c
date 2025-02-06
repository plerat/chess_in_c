
#include <stdio.h>

#include "piece.h"
#include "board.h"
#include "move.h"
#include "wincondition.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);

    Point coord = {0,0} ;
    _Bool player = 1;
    while (coord.col < 9) { // replace by while not win
        printf("piece a move ! \n");
        coord = askCoord();
        printf("tu la mets ou ?\n");
        Point nextCoord = askCoord(); //TODO qu ?, pour quit
        //TODO if illegal move, replay turn / ask again
        printf("%d %d ==> %d / %d",coord.col,coord.row,nextCoord.col,nextCoord.row);
        if (isLegalMove(board, player, coord.col, coord.row, nextCoord.col,nextCoord.row)) {
            int test = move(board, coord.col,coord.row, nextCoord.col,nextCoord.row);
            printf("\n%d\n",test);
        } else {
            printf("\nIllegal move\n");
        }
        displayBoard(board);
        if (checkWin(1, board)) {
            printf("\nCongratulation you won !\n");
            return 1;
        }

        player = !player;
    }
    deleteBoard(board);



    return 0;
}
