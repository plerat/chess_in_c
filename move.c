//
// Created by User on 03/02/2025.
//

#include "move.h"
#include <stdbool.h>
#include "piece.h"
#include <stdio.h>

_Bool isPiece(Piece **board, int col, int row)
{
    return board[col][row] != EMPTY;
}

int getPiece(Piece **board, int col, int row)
{
    if (row > 0 || col > 0 || row < 8 || col < 8)
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
int whitePawnMove(Piece **board, int col, int row, int nextCol, int nextRow) {
    if ( row == 1 ) {
        setCase(board,col,row,EMPTY);
        return setCase(board,nextCol,nextRow,WHITE_PAWN);

    } else {

    }
}

int blackPawnMove(Piece **board, int col, int row, int nextCol, int nextRow){
    if ( row == 6 ) {

    } else {

    }

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
                if (!(nextRow == row - 1 && (nextCol == col + 1 || nextCol == col - 1)))
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
        if (col != nextCol)
        {
            return 0;
        }
        if (nextRow >= row)
        {
            return 0;
        }
        if (row == 6 && nextRow - row > 2 || row == 2 && isPiece(board, col, nextRow + 1))
        {
            return 0;
        }
        if (nextRow - row != 1)
        {
            return 0;
        }

        return 1;

        default:
            return 0;
    }
}