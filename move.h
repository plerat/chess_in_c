//
// Created by User on 03/02/2025.
//

#ifndef MOVE_H
#define MOVE_H
#include "piece.h"

typedef struct {
    int col;
    int row;
} Point;

Point askUser();
int* askCoords(int col, int row );
_Bool isPiece(Piece** board, int col, int row);
int getPiece(Piece** board, int col, int row);
int setCase(Piece** board, int col, int row, Piece piece);
_Bool isLegalMove(Piece** board, int col, int row, int nextCol, int nextRow);

#endif // MOVE_H
