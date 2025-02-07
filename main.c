
#include <stdio.h>

#include "piece.h"
#include "board.h"
#include "move.h"
#include "wincondition.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);

    _Bool player = 0;
    GameStatus status = ONGOING;
    while (status == ONGOING) {
        player = !player;
        printf("piece to move !\n");
        Point coord  = askCoord();
        printf("where ?\n");
        Point nextCoord = askCoord();
        _Bool haveMoveAPiece = 0;
        while (!haveMoveAPiece){
            if (isLegalMove(board, player, coord.col, coord.row, nextCoord.col, nextCoord.row)) {
                move(board, coord.col, coord.row, nextCoord.col, nextCoord.row);
                haveMoveAPiece = 1;
            } else {
                printf("\nIllegal move\n");
            }
        }
        displayBoard(board);
        status = checkWin(player, board);
    }
    deleteBoard(board);
    if (status == WINNING && player ) {
        printf("\nCongratulation white won !\n");
    }else if (status == WINNING) {
        printf("\nCongratulation black won !\n");
    }else if (status == STALEMATE) {
        printf("\nIt's a Draw !\n");
    }
    return 0;
}


