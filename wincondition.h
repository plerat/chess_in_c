//
// Created by anara on 05/02/2025.
//

#ifndef WINCONDITION_H
#define WINCONDITION_H
#include "move.h"

Point findKing(_Bool color, Piece** board );
_Bool checkWin(_Bool player, Piece** board);

#endif //WINCONDITION_H
