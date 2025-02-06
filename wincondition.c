#include <stdio.h>
#include "wincondition.h"
#include "move.h"
#include "piece.h"

Point findKing(_Bool color, Piece** board ) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (color == 1) {
                if (getPiece(board, i, j) == WHITE_KING) {
                    Point king = {i, j};
                    return king;
                }
            } else {
                if (getPiece(board, i, j) == BLACK_KING) {
                    Point king = {i, j};
                    return king;
                }
            }
        }
    }
    // si le roi n'est pas trouvé, on retourne -1, -1 (hors du board)
    Point invalid = {-1, -1};
    return invalid;
}
_Bool isCaseSafe(_Bool color, Piece** board, int col, int row ){ // is case attacked
    // check all ennemy piece then check if one of them can here
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isEnemy(board, color, i, j)){

            }
        }
    }
}
_Bool checkWin(_Bool player, Piece** board) {
    // On cherche le roi ennemi : donc on inverse la valeur de player (on est joueur blanc, on cherche le roi noir)
    Point king = findKing(!player, board);
    if (king.col == -1 || king.row == -1) {
        return 1;
    }

    // Est-ce que le roi peut se déplacer ?
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (king.col + i > 8 || king.row + j > 8 || king.col + i < 0 || king.row + j < 0) {
                continue;
            }
            if (!isEnemy(board, player, king.row + j , king.col + i)) {
                continue;
            }
            if (isCaseSafe(player, board, king.col + i, king.row + j)) {
                return 0;
            }
        }
    }

    return 0;
}

