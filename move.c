//
// Created by User on 03/02/2025.
//

#include "move.h"
#include "piece.h"
#include <stdio.h>

Point askCoord() {
    printf("\n (col row) :\n");
    int row, col;
    scanf("%d %d", &row, &col);
    Point coord = {row-1, col-1};
    while (!(coord.row <8 && coord.col <8 && coord.row >=0 && coord.col >=0)) {
        printf("\n coordonnée invalide, veuillez réessayer\n");
        coord = askCoord();
    }
    return coord;
}

_Bool isPiece(Piece **board, int col, int row)
{
    return board[col][row] != EMPTY;
}

int getPiece(Piece **board, int col, int row)
{
    if (row >= 0 && col >= 0 && row < 8 && col < 8)
    {
        return board[col][row];
    }
    return EMPTY;
}

int setCase(Piece **board, int col, int row, Piece piece) {
    int aimedCase = getPiece(board, col, row);
    board[col][row] = piece;
    return aimedCase;
}

//   Piece movement
int move(Piece **board, int col, int row, int nextCol, int nextRow) {
    Piece piece = getPiece(board, col, row);
    setCase(board,col,row,EMPTY);
    return setCase(board, nextCol, nextRow, piece);
}

_Bool isLegalMove(Piece **board, int col, int row, int nextCol, int nextRow)
{
    switch (getPiece(board, col, row))
    {
        case WHITE_PAWN:
            if (isPiece(board, nextCol, nextRow))
            {
                if (!(nextRow == row + 1 && (nextCol == col + 1 || nextCol == col - 1)))
                {
                    return 0;
                }
                    return 1;
            }
        if (col != nextCol)
        {
            return 0;
        }
        if (nextRow <= row)
        {
            return 0;
        }
        if (row == 1 &&  nextRow - row > 2 )
        {
            return 0;
        }
        if (row == 1 && nextRow == 3 && isPiece(board, nextCol, nextRow - 1)) {
            return 0;
        }
        if (row == 1 && nextRow - row != 1 && nextRow - row != 2 )
        {
            return 0;
        }

        return 1;

        case BLACK_PAWN:
            if (isPiece(board, nextCol, nextRow))
            {
                if (!(nextRow == row - 1 && (nextCol == col - 1 || nextCol == col + 1)))
                {
                    return 0;
                }
                return 1;
            }
            if (col != nextCol)
            {
                return 0;
            }
            if (nextRow >= row)
            {
                return 0;
            }
            if (row == 6 && row - nextRow > 2 )
            {
                return 0;
            }
            if (row == 6 && nextRow == 4 && isPiece(board, nextCol, nextRow + 1)) {
                return 0;
            }
            if (row == 6 && row - nextRow != 1 && row - nextRow != 2 )
            {
                return 0;
            }
            return 1;

        case WHITE_ROOK:
        case BLACK_ROOK:

            if (getPiece(board, col, row) == WHITE_ROOK) {
                if (getPiece(board, nextCol, nextRow > EMPTY)  && getPiece(board, nextCol, nextRow) <= WHITE_ROOK) {
                    return 0;
                }
            }

            if (getPiece(board, col, row) == BLACK_ROOK) {
                if (getPiece(board, nextCol, nextRow >= BLACK_ROOK)) {
                    return 0;
                }
            }
            // vertical asc
            if (row < nextRow && col == nextCol) {
                for (row; row < nextRow; row++) {
                    if (isPiece(board, col, row)) {
                        return 0;
                    }
                }
                return 1;
            }
            // vertical desc
            if (row > nextRow && col == nextCol) {
                for (row; row > nextRow; row--) {
                    if (isPiece(board, col, row)) {
                        return 0;
                    }
                }
                return 1;
            }
            // horizontal right
            if (row == nextRow && col < nextCol) {
                for (col; col < nextCol; col++) {
                    if (isPiece(board, col, row)) {
                        return 0;
                    }
                }
                return 1;
            }
            // horizontal left
            if (row == nextRow && col > nextCol) {
                for (col; col > nextCol; col--) {
                    if (isPiece(board, col, row)) {
                        return 0;
                    }
                }
                return 1;
            }

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            if (getPiece(board, col, row) == WHITE_KNIGHT)
                if (getPiece(board, nextCol, nextRow) <= WHITE_ROOK && getPiece(board, nextCol, nextRow) > EMPTY) {
                    return 0;
                }
            if (getPiece(board, col, row) == BLACK_KNIGHT) {
                if (getPiece(board, nextCol, nextRow >= BLACK_PAWN)) {
                    return 0;
                }
            }

            if (col + 1 == nextCol && row + 2 == nextRow) {
                return 1;
            }

            if (col + 2 == nextCol && row + 1 == nextRow) {
                return 1;
            }

            if (col + 2 == nextCol && row - 1 == nextRow) {
                return 1;
            }

            if (col + 1 == nextCol && row - 2 == nextRow) {
                return 1;
            }

            if (col - 1 == nextCol && row - 2 == nextRow) {
                return 1;
            }

            if (col - 2 == nextCol && row - 1 == nextRow) {
                return 1;
            }

            if (col - 2 == nextCol && row + 1 == nextRow) {
                return 1;
            }

            if (col - 1 == nextCol && row + 2 == nextRow) {
                return 1;
            }


        return 1;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            if (getPiece(board, col,row) == WHITE_BISHOP && getPiece(board, nextCol, nextRow) < BLACK_PAWN && getPiece(board, nextCol, nextRow) > EMPTY ){
                printf("terfs");
                return 0;
            }
            if (getPiece(board, col,row) == BLACK_BISHOP && getPiece(board, nextCol, nextRow) >= BLACK_PAWN){
                return 0;
            }
            if (row == nextRow || col == nextCol) { //if move as rook or stay still
                return 0;
            }
            if (!(row - nextRow == col - nextCol || row - nextRow == -(col-nextCol))) { //if not diagonal
                return 0;
            }
            if (row > nextRow && col > nextCol) { //diagonal up right
                for (int i = 0 ; i < row-nextRow -1 ; i++) {
                    if (isPiece(board, row+i, col+i) != EMPTY) {
                        return 0;
                    }
                }
            }
            if (row > nextRow && col < nextCol) { //diagonal up left
                for (int i = 0 ; i < row-nextRow -1; i++) {
                    if (isPiece(board, row+i, col-i) != EMPTY) {
                        return 0;
                    }
                }
            }
            if (row < nextRow && col > nextCol) { //diagonal down right
                for (int i = 0 ; i < row-nextRow -1 ; i++) {
                    if (isPiece(board, row-i, col+i) != EMPTY) {
                        return 0;
                    }
                }
            }
            if (row < nextRow && col < nextCol) { //diagonal down left
                for (int i = 0 ; i < row-nextRow -1 ; i++) {
                    if (isPiece(board, row-i, col-i)!= EMPTY) {
                        return 0;
                    }
                }
            }

        return 1;

        default:
            return 0;
    }
}