//
// Created by User on 03/02/2025.
//

#ifndef MOVE_H
#define MOVE_H
#include "piece.h"

int* askCoords(int row, int col);
_Bool isPiece(Piece **board, int row, int col);
int getPiece(Piece **board, int row, int col);
void move(int piece, int row, int col);
int attack(int piece,int row, int col);
_Bool isLegalMove(int row, int col, int nextRow, int nextCol, Piece **board);

#endif // MOVE_H
