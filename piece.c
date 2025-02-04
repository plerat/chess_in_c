#include "piece.h"
#include <stdio.h>
#include <stdbool.h>


char pieceToString(Piece piece) {
    switch (piece) {
        case WHITE_PAWN:
            return 'p';
        case WHITE_KING:
            return 'k';
        case WHITE_QUEEN:
            return 'q';
        case WHITE_BISHOP:
            return 'b';
        case WHITE_KNIGHT:
            return 'n';
        case WHITE_ROOK:
            return 'r';
        case BLACK_PAWN:
            return 'P';
        case BLACK_KING:
            return 'K';
        case BLACK_QUEEN:
            return 'Q';
        case BLACK_BISHOP:
            return 'B';
        case BLACK_KNIGHT:
            return 'N';
        case BLACK_ROOK:
            return 'R';
        case EMPTY:
            default:
                return '.';
    }
};


void whitePawnMove(int row, int col,int nextRow, int nextCol, Piece **board) {
    if ( row == 2 ) {
        printf("ROW == 2");
        board[row][col] = EMPTY;
        board[nextRow][nextCol] = WHITE_PAWN;
    } else {

    }
}
void blackPawnMove(int row, int col, int nextRow, int nextCol) {
    if ( row == 7 ) {

    } else {

    }

}