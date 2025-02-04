//
// Created by User on 03/02/2025.
//

#include "move.h"
#include <stdbool.h>
#include "piece.h"
#include <stdio.h>

_Bool isPiece(Piece **board, int row, int col)
{
    return board[row][col] >= WHITE_PAWN && board[row][col] <= BLACK_ROOK;
}

int getPiece(Piece **board, int row, int col)
{
    if (row > 0 || col > 0 || row < 8 || col < 8)
    {
        return board[row][col];
    }
    return EMPTY;
}

_Bool isLegalMove( int row, int col, int nextRow, int nextCol, Piece **board)
{
    switch (getPiece(board, row,col))
    {
        case WHITE_PAWN:
            if (isPiece(board, nextRow, nextCol))
            {
                if (!(nextRow == row + 1 && (nextCol == col + 1 || nextCol == col - 1)))
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
        if (nextRow <= row)
        {
            return 0;
        }
        if (row == 2 && nextRow - row > 2 || row == 2 && isPiece(board, nextRow - 1, col))
        {
            return 0;
        }
        if (nextRow - row != 1)
        {
            return 0;
        }

        return 1;

        case BLACK_PAWN:
            if (isPiece(board, nextRow, nextCol))
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
        if (row == 7 && nextRow - row > 2 || row == 2 && isPiece(board, nextRow + 1, col))
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