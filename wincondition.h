//
// Created by anara on 05/02/2025.
//

#ifndef WINCONDITION_H
#define WINCONDITION_H
#include "move.h"

typedef enum  {
    ONGOING = 0,
    WINNING,
    STALEMATE
} GameStatus;
Point findKing(_Bool color, Piece** board );
_Bool isCaseSafe(_Bool player, Piece** board, int col, int row);
_Bool canKingMove(_Bool player, Piece** board, int col, int row);
_Bool canKnightMove(_Bool player, Piece** board, int col, int row);
_Bool canPieceMove(_Bool player, Piece** board, int col, int row);
GameStatus checkWin(_Bool player, Piece** board);
#endif //WINCONDITION_H
