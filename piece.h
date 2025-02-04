//
// Created by jeanm on 24/01/2025.
//

#ifndef PIECE_H
#define PIECE_H

typedef enum {
    EMPTY,
    WHITE_PAWN,
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_BISHOP,
    WHITE_KNIGHT,
    WHITE_ROOK,

    BLACK_PAWN,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_BISHOP,
    BLACK_KNIGHT,
    BLACK_ROOK,
} Piece;
char pieceToString(Piece piece);

void whitePawnMove(int row, int col,int nextRow, int nextCol, Piece** board);
void blackPawnMove(int row, int col,int nextRow, int nextCol);
#endif //PIECE_H
