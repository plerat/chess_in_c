//
// Created by User on 03/02/2025.
//
#include "move.h"
#include "piece.h"
#include <stdio.h>

#include "wincondition.h"
// Global var to check if castling is available / legalmove
_Bool whiteKingHasMoved;
_Bool blackKingHasMoved;
_Bool rightWhiteRookHasMoved;
_Bool leftWhiteRookHasMoved;
_Bool rightBlackRookHasMoved;
_Bool leftBlackRookHasMoved;

void updatePieceHasMoved(Piece piece, int col, int row) {
    if (whiteKingHasMoved != 1 && piece == WHITE_KING) {
        whiteKingHasMoved = 1;
    }
    if (blackKingHasMoved != 1 && piece == BLACK_KING) {
        blackKingHasMoved = 1;
    }
    if (leftWhiteRookHasMoved != 1 && (piece == WHITE_ROOK) && (col == 0) && (row == 0)) {
        leftWhiteRookHasMoved = 1;
    }
    if (rightWhiteRookHasMoved !=1 && (piece == WHITE_ROOK) && (col == 7) && (row == 0)) {
        rightWhiteRookHasMoved = 1;
    }
    if (leftBlackRookHasMoved != 1 && (piece == BLACK_ROOK) && (col == 0) && (row == 7)) {
        leftBlackRookHasMoved = 1;
    }
    if (rightBlackRookHasMoved != 1 && (piece == BLACK_ROOK) && (col == 7) && (row == 7)) {
        rightBlackRookHasMoved = 1;
    }
}

Point askCoord() {
    int row = 0;
    char col = 0;
    // before %c need to add a space to ignore cartdrige return \n
    scanf(" %c%d", &col, &row);
    // row - 1 because the board start at 0
    Point coord = { col, row-1};
    // format user input after the cast in the struct
    if (coord.col < 97) {
        coord.col += 32;
    }
    coord.col = coord.col % 97;
    while (!(coord.col <8 && coord.col >=0  && coord.row <=8 &&  coord.row >= 0 )) {
        printf("\nInvalid coordinate, retry please\n");
        coord = askCoord();
    }
    return coord;
}

_Bool isPiece(Piece **board, int col, int row) {
    return board[col][row] != EMPTY;
}

int getPiece(Piece **board, int col, int row) {
    /*if (col > 7 || row > 7 || col < 0 || row < 0) {
        printf("Should never appear : coordinate out of board");
        return 15;
    }*/
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

void setCase(Piece **board, int col, int row, Piece piece) {
    board[col][row] = piece;
}

int promotingPiece(Piece **board, int col, int row) {
    int piece = EMPTY;
    int userInput = 0;
    do {
    printf("Which piece do you want to replace your pawn ?\n 1 for Queen, 2 for Bishop, 3 for Knight, 4 for Rook : ");
    scanf (" %d", &userInput);
        if (isPieceWhite(board, col, row)) {
            // + 2 to match the white pieces in enum
            piece = userInput + 2;
        } else {
            // + 8 to match the black pieces in enum
            piece = userInput + 8;
        }
    } while (userInput < 1 || userInput > 4);
    return piece;
}


//   Piece movement
int move(Piece **board, int col, int row, int nextCol, int nextRow) {
    Piece piece = getPiece(board, col, row);
    // piece promotion
    if ((piece == WHITE_PAWN && nextRow == 7) || (piece == BLACK_PAWN && nextRow == 0)) {
        piece = promotingPiece(board, col, row);
    }
    // update if king and rook moved for the first time, use in castling function
    else if (piece == BLACK_KING || piece == WHITE_KING || piece == WHITE_ROOK || piece == BLACK_ROOK) {
        updatePieceHasMoved(piece, col, row);
    }
    setCase(board,col,row,EMPTY);
    setCase(board, nextCol, nextRow, piece);
    return piece;
}

// use for "en passant"
void setLastMove(LastMove *LastMove, Piece piece, int col, int row, int nextCol, int nextRow ) {
    LastMove->piece = piece;
    LastMove->col = col;
    LastMove->row = row;
    LastMove->nextCol = nextCol;
    LastMove->nextRow = nextRow;
}

_Bool isEnemy(Piece **board,_Bool color, int nextCol,int nextRow) {
    if (color == 1 && isPieceWhite(board, nextCol, nextRow)) {
        return 0;
    }
    if (color == 0 && isPieceBlack(board, nextCol, nextRow)) {
        return 0;
    }
    return 1;
}
// Legalmove for whitepawn
Move_type whitePawnMove(Piece **board, LastMove LastMove, int col,int row, int nextCol, int nextRow) {
    if (isPiece(board, nextCol, nextRow) && isPieceBlack(board, nextCol, nextRow)) {
        // if is enemy and we don't move diagonally, return false
        if (!(nextRow == row + 1 && (nextCol == col + 1 || nextCol == col - 1))) {
            return 0;
        }
        return 1;
    }

    // special case : en passant
    if (LastMove.piece == BLACK_PAWN && ( LastMove.row - row == 2) && nextCol == LastMove.nextCol) {
        // is left ?
        if (col - 1 == LastMove.nextCol && col - 1 >= 0) {
            return 2;
        }
        // is right ?
        if (col + 1 == LastMove.nextCol && col + 1 <= 7) {
            return 2;
        }
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

Move_type blackPawnMove(Piece **board, LastMove LastMove, int col, int row, int nextCol, int nextRow)  {
    if (isPiece(board, nextCol, nextRow) && isPieceWhite(board, nextCol, nextRow))
    {
        // if is enemy and we don't move diagonally, return false
        if (!(nextRow == row - 1 && (nextCol == col - 1 || nextCol == col + 1)))
        {
            return 0;
        }
        return 1;
    }

    // special case : en passant
    if (LastMove.piece == WHITE_PAWN && (row - LastMove.row == 2) && nextCol == LastMove.nextCol) {
        // is left ?
        if (col - 1 == LastMove.nextCol && col - 1 >= 0) {
            return 2;
        }
        // is right ?
        if (col + 1 == LastMove.nextCol && col + 1 <= 7) {
            return 2;
        }
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
    //if move as rook or stay still
    if (row == nextRow || col == nextCol) {
        return 0;
    }
    //if not diagonal
    if (!(row - nextRow == col - nextCol || row - nextRow == -(col-nextCol))) {
        return 0;
    }
    //i = 1 to skip itself and -1 to not check the aimed case
    // diagonal down left
    if (row > nextRow && col > nextCol) {
        for (int i = 1 ; i < row-nextRow -1 ; i++) {
            if (isPiece(board, col-i, row-i) != EMPTY) {
                return 0;
            }
        }
    }
    //diagonal down right
    if (row > nextRow && col < nextCol) {
        for (int i = 1 ; i < row-nextRow -1; i++) {
            if (isPiece(board, col+i, row-i) != EMPTY) {
                return 0;
            }
        }
    }
    //diagonal up left
    if (row < nextRow && col > nextCol) {
        for (int i = 1 ; i < nextRow-row -1 ; i++) {
            if (isPiece(board, col-i, row+i) != EMPTY) {
                return 0;
            }
        }
    }
    //diagonal up right
    if (row < nextRow && col < nextCol) {
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
            // - 1 to not check the aimed case (already done)
            for (; row < nextRow - 1; row++) {
                // row + 1 to don't check herself
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

_Bool longCastling(Piece** board, _Bool player, LastMove last_move, int col, int row, int nextCol) {
        for (int i = col - 1 ; i >= nextCol - 1 ; i--) {
            // Check if cases between left rook and king are empty
            if (isPiece(board, i, row)) {
                return 0;
            }
        }
        // Check if cases on the path's king are safe
        for (int j = col; j >= nextCol; j--) {
            if (!isCaseSafe(player, last_move, board, j, row)) {
                printf("case not safe");
                return 0;
            }
        }
    return 1;
    }

_Bool shortCastling(Piece** board, _Bool player, LastMove last_move, int col, int row, int nextCol) {
    // Check if cases between right rook and king are empty
    for (int i = col + 1 ; i <= nextCol; i++) {
        if (isPiece(board, i, row)) {
            return 0;
        }
    }
    // Check if cases on the path's king are safe
    for (int j = col ; j <= nextCol; j++) {
        if (!isCaseSafe(player, last_move, board, j, row)) {
            printf("case not safe");
            return 0;
        }
    }
    return 1;
}

Move_type kingMove(Piece** board, _Bool player, LastMove last_move, int col, int row, int nextCol, int nextRow){
    // Long castling (queen castling)
    if (nextCol == col - 2 && nextRow == row && ((player == 1 && whiteKingHasMoved == 0 && leftWhiteRookHasMoved == 0) || (player == 0 && blackKingHasMoved == 0 && leftBlackRookHasMoved == 0))) {
        if (longCastling(board, player, last_move, col, row, nextCol)) {
            return LONG_CASTLING;
        }
        return 0;
    }

    // Short castling
    if (nextCol == col + 2 && nextRow == row && ((player == 1 && whiteKingHasMoved == 0 && rightWhiteRookHasMoved == 0) || (player == 0 && blackKingHasMoved == 0 && rightBlackRookHasMoved == 0))) {
        if (shortCastling(board, player, last_move, col, row, nextCol)) {
            return SHORT_CASTLING;
        }
        return 0;
    }

    if (!isEnemy(board, player, nextCol, nextRow)) {
        return 0;
    }

    if (!((-1 <= col - nextCol && col - nextCol <= 1 ) && (- 1 <= row - nextRow && row - nextRow <= 1))) {
        return 0;
    }
    return 1;
}

Move_type isLegalMove(Piece **board, _Bool player, LastMove LastMove, int col, int row, int nextCol, int nextRow) {

    if (col > 7 || row > 7 || col < 0 || row < 0) {
       return 0;
    }

    if (isEnemy(board, player, col, row)) {
        return 0;
    }

    switch (getPiece(board, col, row)) {

        case WHITE_PAWN:

            return whitePawnMove(board, LastMove, col, row, nextCol, nextRow);

        case BLACK_PAWN:

            return blackPawnMove(board, LastMove, col, row, nextCol, nextRow);

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

        return kingMove(board, player, LastMove, col, row, nextCol, nextRow);

        case WHITE_QUEEN:
        case BLACK_QUEEN:

            return bishopMove(board, player, col, row, nextCol, nextRow) || rookMove(board, player, col, row, nextCol, nextRow);
        default:

            return 0;
    }
}