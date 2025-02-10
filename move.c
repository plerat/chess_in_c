//
// Created by User on 03/02/2025.
//
#include "move.h"
#include "piece.h"
#include <stdio.h>

Point askCoord() {
    int row = 0;
    char col = 0;
    scanf(" %c%d", &col, &row); // magie du scanf numéro 1: ' ' avant %c pour ignorer les retours à la ligne '\n'
    // while (getchar() != '\n'); // magie du scanf numéro 2: vide le buffer s'il contient des résidues
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
    if (col > 7 || row > 7 || col < 0 || row < 0) {
        return 15;
    }
    return board[col][row];
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

int promotingPiece(Piece **board, int col, int row) {
    int piece = EMPTY;
    int userInput = 0;
    do {
    printf("Which piece do you want to replace your pawn ?\n 1 for Queen, 2 for Bishop, 3 for Knight, 4 for Rook : ");
    scanf (" %d", &userInput);
        if (isPieceWhite(board, col, row)) {
            piece = userInput + 2;
        } else {
            piece = userInput + 8;
        }
    } while (userInput < 1 || userInput > 4);
    return piece;
}


//   Piece movement
int move(Piece **board, int col, int row, int nextCol, int nextRow) {
    Piece piece = getPiece(board, col, row);
    if ((piece == WHITE_PAWN && nextRow == 7) || (piece == BLACK_PAWN && nextRow == 0)) {
        piece = promotingPiece(board, col, row);
    }
    setCase(board,col,row,EMPTY);
    return setCase(board, nextCol, nextRow, piece);
}

_Bool isEnemy(Piece **board,_Bool color, int nextCol,int nextRow) {
    if (color && isPieceWhite(board, nextCol, nextRow)) {
        return 0;
    }
    //!color because if not : black player is 0 so 0 && 1 == 0
    if (!color && isPieceBlack(board, nextCol, nextRow)) {
        return 0;
    }
    return 1;
}

//      Check pieces movement function
_Bool whitePawnMove(Piece **board,int col,int row, int nextCol, int nextRow) {
    if (isPiece(board, nextCol, nextRow) && isPieceBlack(board, nextCol, nextRow)) {
        if (!(nextRow == row + 1 && (nextCol == col + 1 || nextCol == col - 1))) {
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
    if (row == 1 && nextRow - row != 1 && nextRow - row != 2 ) {
        return 0;
    }

    return 1;
}
_Bool blackPawnMove(Piece **board, int col, int row, int nextCol, int nextRow)  {
    if (isPiece(board, nextCol, nextRow) && isPieceWhite(board, nextCol, nextRow))
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
_Bool bishopMove(Piece** board,_Bool player,  int col, int row, int nextCol, int nextRow){
    if (!isEnemy(board, player, nextCol, nextRow)) {
        return 0;
    }

    if (row == nextRow || col == nextCol) { //if move as rook or stay still
        return 0;
    }
    if (!(row - nextRow == col - nextCol || row - nextRow == -(col-nextCol))) { //if not diagonal
        return 0;
    }
    //i = 1 to skip itself and -1 to not check the aimed case
    if (row > nextRow && col > nextCol) { //diagonal down left
        for (int i = 1 ; i < row-nextRow -1 ; i++) {
            if (isPiece(board, col-i, row-i) != EMPTY) {
                return 0;
            }
        }
    }
    if (row > nextRow && col < nextCol) { //diagonal down right
        for (int i = 1 ; i < row-nextRow -1; i++) {
            if (isPiece(board, col+i, row-i) != EMPTY) {
                return 0;
            }
        }
    }
    if (row < nextRow && col > nextCol) { //diagonal up left
        for (int i = 1 ; i < nextRow-row -1 ; i++) {
            if (isPiece(board, col-i, row+i) != EMPTY) {
                return 0;
            }
        }
    }
    if (row < nextRow && col < nextCol) { //diagonal up right
        for (int i = 1 ; i < nextRow - row - 1 ; i++) {

            if (isPiece(board, col + i, row + i) != EMPTY) {
                return 0;
            }
        }
    }

    return 1;
}
_Bool rookMove(Piece** board, _Bool player, int col, int row, int nextCol, int nextRow) {
        if (!isEnemy(board, player, nextCol, nextRow)) {
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
    return 0;
    }
_Bool knightMove(Piece** board, _Bool player, int col, int row, int nextCol, int nextRow){
    if (!isEnemy(board, player, nextCol, nextRow)) {
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
_Bool kingMove(Piece** board, _Bool player, int col, int row, int nextCol, int nextRow){
    if (!isEnemy(board, player, nextCol, nextRow)) {
        return 0;
    }

    if (!((-1 <= col - nextCol && col - nextCol <= 1 ) && (- 1 <= row - nextRow && row - nextRow <= 1))) {
        return 0;
    }

    return 1;
}

_Bool isLegalMove(Piece **board, _Bool player, int col, int row, int nextCol, int nextRow) {

    if (col > 7 || row > 7 || col < 0 || row < 0) {
       return 0;
    }

    if (isEnemy(board, player, col, row)) {
        return 0;
    }

    switch (getPiece(board, col, row)) {

        case WHITE_PAWN:

            return whitePawnMove(board, col, row, nextCol, nextRow);

        case BLACK_PAWN:

            return blackPawnMove(board, col, row, nextCol, nextRow);

        case WHITE_ROOK:
        case BLACK_ROOK:

            return rookMove(board, player, col, row, nextCol, nextRow);

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:

            return knightMove(board, player, col, row, nextCol, nextRow);

        case WHITE_BISHOP:
        case BLACK_BISHOP:

            return bishopMove(board, player, col, row, nextCol, nextRow);

        case WHITE_KING:
        case BLACK_KING:

        return kingMove(board, player, col, row, nextCol, nextRow);

        case WHITE_QUEEN:
        case BLACK_QUEEN:

            return bishopMove(board, player, col, row, nextCol, nextRow) || rookMove(board, player, col, row, nextCol, nextRow);
        default:

            return 0;
    }
}