//
// Created by User on 03/02/2025.
//

#include "move.h"
#include "piece.h"
#include <stdio.h>

Point askUser() {
    printf("\n coordonnée ciblée (col row) :\n");
    int row, col;
    scanf("%d %d", &row, &col);
    Point coord = {row-1, col-1};
    while (!(coord.row <8 && coord.col <8 && coord.row >=0 && coord.col >=0)) {
        printf("\n coordonnée invalide, veuillez réessayer\n");
        coord = askUser();
    }
    return coord;
}

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
        setCase(board,col,row,EMPTY);
        return setCase(board,nextCol,nextRow,WHITE_PAWN);
}

int blackPawnMove(Piece **board, int col, int row, int nextCol, int nextRow){
        setCase(board,col,row,EMPTY);
        return setCase(board,nextCol,nextRow,BLACK_PAWN);
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

        default:
            return 0;
    }
}