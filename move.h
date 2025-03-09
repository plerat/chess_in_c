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

typedef struct {
    Piece piece;
    int col;
    int row;
    int nextRow;
    int nextCol;
} LastMove;

typedef enum {
    FALSE,
    TRUE,
    EN_PASSANT,
    LONG_CASTLING,
    SHORT_CASTLING,
} Move_type;

Point askCoord();
void updatePieceHasMoved(Piece piece, int col, int row);
int* askCoords(int col, int row );
int move(Piece **board, int col, int row, int nextCol, int nextRow);
void setLastMove(LastMove *LastMove, Piece piece, int col, int row, int nextCol, int nextRow );
_Bool isEnemy(Piece **board, _Bool color, int nextCol,int nextRow);
_Bool isPiece(Piece** board, int col, int row);
int getPiece(Piece** board, int col, int row);
int setCase(Piece** board, int col, int row, Piece piece);
Move_type isLegalMove(Piece** board, _Bool player, LastMove LastMove, int col, int row, int nextCol, int nextRow);

#endif // MOVE_H
