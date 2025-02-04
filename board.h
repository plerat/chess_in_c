#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

typedef enum {
    A = 1,
    B,
    C,
    D,
    E,
    F,
    G,
    H
} Column;

void deleteBoard(Piece **board);

Piece **generateEmptyBoard();

void placePiece(Piece **board, Column x, int y, Piece piece);

char columnToString(Column column);

void resetBoardPiece(Piece **board);

void displayBoard(Piece **board);
#endif //BOARD_H
