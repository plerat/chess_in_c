//
// Created by anara on 05/02/2025.
//

#ifndef WINCONDITION_H
#define WINCONDITION_H
#include "move.h"

Point findKing(_Bool color, Piece** board );
_Bool checkWin(_Bool player, Piece** board);
_Bool isCaseSafe(_Bool player, Piece** board, int col, int row);
#endif //WINCONDITION_H
