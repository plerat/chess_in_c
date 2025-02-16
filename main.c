
#include <stdio.h>

#include "piece.h"
#include "board.h"
#include "move.h"
#include "wincondition.h"

int main() {
    Piece **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);
    LastMove LastMove;
    setLastMove(&LastMove,EMPTY, 0, 0, 0, 0);

    _Bool player = 0;
    GameStatus status = ONGOING;
    while (status == ONGOING) {
        player = !player;
        _Bool haveMoveAPiece = 0;
        while (!haveMoveAPiece) {
            printf("piece to move !\n");
            Point coord = askCoord();
            printf("where ?\n");
            Point nextCoord = askCoord();
            Move_type legalMove = isLegalMove(board, player, LastMove, coord.col, coord.row, nextCoord.col, nextCoord.row);
            if (legalMove == FALSE) {
                printf("\nIllegal move\n");
            } else {
                Piece pieceMoved = move(board, coord.col, coord.row, nextCoord.col, nextCoord.row);
                haveMoveAPiece = 1;
                if (legalMove == EN_PASSANT) {
                    printf("En passant\n");
                    setCase(board, LastMove.nextCol, LastMove.nextRow, EMPTY);
                }
                setLastMove(&LastMove, pieceMoved, coord.col, coord.row, nextCoord.col, nextCoord.row);
            }
            displayBoard(board);
            status = checkWin(player, board, LastMove);
        }
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


