//
// Created by User on 03/02/2025.
//
#include "move.h"
#include "piece.h"
#include <stdio.h>

Point askCoord() {
    int row= 0;
    char col = 0;
    scanf("%c%d", &col, &row);
    Point coord = { col, row-1};
    if (coord.col < 97) coord.col += 32;
    coord.col = coord.col % 97;
    while (!(coord.col <8 && coord.col >=0  && coord.row <=8 &&  coord.row >= 0 )) {
        printf("\n coordonnée invalide, veuillez réessayer\n");
        coord = askCoord();
    }
    return coord;
}

_Bool isPiece(Piece **board, int col, int row) {
    return board[col][row] != EMPTY;
}

int getPiece(Piece **board, int col, int row) {
    if (row >= 0 && col >= 0 && row < 8 && col < 8)
    {
        return board[col][row];
    }
    return EMPTY;
}

_Bool isPieceWhite(Piece **board, int nextCol, int nextRow) {
    if (getPiece(board, nextCol, nextRow) <= WHITE_ROOK && getPiece(board, nextCol, nextRow) > EMPTY) {
        return 1;
    } else {
        return 0;
    }
}

_Bool isPieceBlack(Piece **board, int nextCol, int nextRow) {
    if (getPiece(board, nextCol, nextRow) >= BLACK_PAWN) {
        return 1;
    } else {
        return 0;
    }
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

_Bool isEnemy(Piece **board, int col, int row, int nextCol,int nextRow) {
    if (isPieceWhite(board, col, row) && isPieceWhite(board, nextCol, nextRow)) {
        return 0;
    }
    if (isPieceBlack(board, col, row) && isPieceBlack(board, nextCol, nextRow)) {
        return 0;
    }
    return 1;
}

//      Check pieces movement function
_Bool whitePawnMove(Piece **board,int col,int row, int nextCol, int nextRow) {
    if (isPiece(board, nextCol, nextRow))
    {
        if (!(nextRow == row + 1 && (nextCol == col + 1 || nextCol == col - 1)))
        {
            return 0;
        }
        return 1;
    }

    if (col != nextCol) {
        return 0;
    }
    if (nextRow <= row) {
        return 0;
    }
    if (row != 1 && nextRow - row != 1) {
        return 0;
    }
    if (row == 1 &&  nextRow - row > 2 ) {
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
}
_Bool blackPawnMove(Piece **board, int col, int row, int nextCol, int nextRow)  {
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
    if (nextRow >= row) {
        return 0;
    }
    if (row != 6 && row - nextRow != 1) {
        return 0;
    }
    if (row == 6 && row - nextRow > 2 ) {
        return 0;
    }
    if (row == 6 && nextRow == 4 && isPiece(board, nextCol, nextRow + 1)) {
        return 0;
    }
    if (row == 6 && row - nextRow != 1 && row - nextRow != 2 ) {
        return 0;
    }
    return 1;
}
_Bool bishopMove(Piece** board, int col, int row, int nextCol, int nextRow){
    if (!isEnemy(board, col, row, nextCol, nextRow)) {
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
}
_Bool rookMove(Piece** board, int col, int row, int nextCol, int nextRow) {
        if (!isEnemy(board, col, row, nextCol, nextRow)) {
            return 0;
        }

        // vertical asc
        if (row < nextRow && col == nextCol) {

            // - 1 pour ne pas check la case d'arrivée car ça a déjà été fait
            for (; row < nextRow -1; row++) {
                // Ajout de row + 1 pour que la pièce ne se check pas elle-même
                if (isPiece(board, col, row + 1)) {
                    return 0;
                }
            }
            return 1;
        }
        // vertical desc
        if (row > nextRow && col == nextCol) {
            for (; row > nextRow + 1; row--) {
                if (isPiece(board, col, row - 1)) {
                    return 0;
                }
            }
            return 1;
        }
        // horizontal right
        if (row == nextRow && col < nextCol) {
            for (; col < nextCol - 1; col++) {

                if (isPiece(board, col + 1, row)) {
                    return 0;
                }
            }
            return 1;
        }
        // horizontal left
        if (row == nextRow && col > nextCol) {
            for (; col > nextCol + 1; col--) {
                if (isPiece(board, col - 1, row)) {
                    return 0;
                }
            }
            return 1;
        }
    return 1;
    }
_Bool knightMove(Piece** board, int col, int row, int nextCol, int nextRow){
    if (!isEnemy(board, col, row, nextCol, nextRow)) {
        return 0;
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


    return 0;
}
_Bool kingMove(Piece** board, int col, int row, int nextCol, int nextRow){
    if (!isEnemy(board, col, row, nextCol, nextRow)) {
        return 0;
    }

    if (!((-1 <= col - nextCol && col - nextCol <= 1 ) && (- 1 <= row - nextRow && row - nextRow <= 1))) {
        return 0;
    }

    return 1;
}


_Bool isLegalMove(Piece **board, int col, int row, int nextCol, int nextRow) {
    switch (getPiece(board, col, row)) {
        case WHITE_PAWN:

            return whitePawnMove(board, col, row, nextCol, nextRow);

        case BLACK_PAWN:

            return blackPawnMove(board, col, row, nextCol, nextRow);

        case WHITE_ROOK:
        case BLACK_ROOK:

            return rookMove(board, col, row, nextCol, nextRow);

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:

            return knightMove(board, col, row, nextCol, nextRow);

        case WHITE_BISHOP:
        case BLACK_BISHOP:

            return bishopMove(board,col,row,nextCol,nextRow);

        case WHITE_KING:
        case BLACK_KING:

        return kingMove(board,col,row,nextCol,nextRow);

        case WHITE_QUEEN:
        case BLACK_QUEEN:

            return bishopMove(board,col,row,nextCol,nextRow) || rookMove(board, col, row, nextCol, nextRow);

        default:
            return 0;
    }
}