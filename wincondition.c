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

_Bool checkWin(_Bool player, Piece** board) {
    // On cherche le roi ennemi : donc on inverse la valeur de player (on est joueur blanc, on cherche le roi noir)
    Point king = findKing(!player, board);
    if (king.col == -1 || king.row == -1) {
        return 1;
    }



    return 0;
}

