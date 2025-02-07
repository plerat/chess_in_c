#include <stdlib.h>
#include "wincondition.h"

#include <stdio.h>

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
    // check all ennemy piece then check if one of them can attack here
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                if (isLegalMove(board, color, i, j, col, row)) {
                    return 0;
                }
        }
    }
    return 1;
}

_Bool canKingMove(_Bool player, Piece** board, int col, int row) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (col + i > 7 || row + j > 7 || col + i <= 0 || row + j <= 0) {
                continue;
            }
            if (i == 0 && j == 0) {
                continue;
            }
            // if same color false if empty
            if (!isLegalMove(board, player, col, row , col + i, row + j )) {
                continue;
            }
            //if empty or enemy : check if case can be attacked
            if (isCaseSafe(player, board, col + i, row + j)) {
                return 1;
            }
        }
    }
    return 0;
}

_Bool canKnightMove(_Bool player, Piece** board, int col, int row) {
    for (int i= -2; i <= 2; i++) {
        for (int j= -2; j <= 2; j++) {
            if (abs(i)+abs(j) != 3) {
                continue;
            }if (isLegalMove(board, player, col, row, i, j)) {
                return 1;
            }
        }
    }
    return 0;
}


_Bool canPieceMove(_Bool player, Piece** board, int col, int row) {
    if (getPiece(board,col,row) == WHITE_KNIGHT || getPiece(board,col,row) == BLACK_KNIGHT) {
        _Bool test = canKnightMove(player, board, col, row);
        return test;
    }
    if (getPiece(board,col,row) == BLACK_KING || getPiece(board,col,row) == WHITE_KING) {
        return 0;
    }
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (col + i > 7 || row + j > 7 || col + i <= 0 || row + j <= 0) {
                continue;
            }

            return isLegalMove(board, player,  col, row, i, j);
        }
    }
    return 0;
}

GameStatus checkWin(_Bool player, Piece** board) {
    // On cherche le roi ennemi : donc on inverse la valeur de player (on est joueur blanc, on cherche le roi noir)
    Point king = findKing(!player, board);
    if (king.col == -1 || king.row == -1) {
        return WINNING;
    }
    if (canKingMove(!player, board, king.col, king.row)) {
        return ONGOING;
    }
    int emptyCase = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j <8; j++) {
            if (board[i][j] == EMPTY) {
                emptyCase++;
                continue;
            }
            printf( "\nplayer = %d ,%d\n", player,canPieceMove(!player,board,i,j) );
            if (isEnemy(board,  player,i,j) && canPieceMove(!player,board,i,j)) {
                return ONGOING;
            }
            if (emptyCase == 62) {
                return STALEMATE;
            }
        }
    }

   if (isCaseSafe(!player,board,king.col,king.row)) {
       return STALEMATE;
   }
    return ONGOING;
}