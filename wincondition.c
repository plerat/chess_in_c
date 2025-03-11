#include <stdlib.h>
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
    // If king is not find, return -1, -1 (out of board)
    Point invalid = {-1, -1};
    return invalid;
}

_Bool isCaseSafe(_Bool color, LastMove LastMove, Piece** board, int col, int row ){ // is case attacked
    // check all ennemy piece then check if one of them can attack here
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // reverse color to check enemy move
            if (isLegalMove(board, !color, LastMove, i, j, col, row)) {
                return 0;
            }
        }
    }
    return 1;
}

_Bool canKingMove(_Bool player, LastMove LastMove, Piece** board, int col, int row) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            // to be sure if the check is in the board
            if (col + i > 7 || row + j > 7 || col + i < 0 || row + j < 0) {
                continue;
            }
            if (i == 0 && j == 0) {
                continue;
            }
            // if same color false if empty
            if (isLegalMove(board, player, LastMove, col, row , col + i, row + j ) && isCaseSafe(player, LastMove, board, col + i, row + j)) {
            //if empty or enemy : check if case can be attacked
                return 1;
            }
        }
    }
    return 0;
}

_Bool canKnightMove(_Bool player, LastMove LastMove, Piece** board, int col, int row) {
    for (int i= -2; i <= 2; i++) {
        for (int j= -2; j <= 2; j++) {
            // to be sure if the check is in the board
            if (col + i > 7 || row + j > 7 || col + i < 0 || row + j < 0) {
                continue;
            }
            if (abs(i)+abs(j) != 3) {
                continue;
            }if (isLegalMove(board, player, LastMove, col, row, col + i, row + j)) {
                return 1;
            }
        }
    }
    return 0;
}


_Bool canPieceMove(_Bool player, LastMove LastMove, Piece** board, int col, int row) {
    // Check the knight separately because we cannot only check if it can move to adjacent squares
    if (getPiece(board,col,row) == WHITE_KNIGHT || getPiece(board,col,row) == BLACK_KNIGHT) {
        return canKnightMove(player, LastMove, board, col, row);

    }
    // Check the king separately because we check if he can move AND if cases around him are safe
    if (getPiece(board,col,row) == BLACK_KING || getPiece(board,col,row) == WHITE_KING) {
        return canKingMove(player, LastMove, board, col, row);
    }
    // check if all other pieces can move
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            // to be sure if the check is in the board
            if (col + i > 7 || row + j > 7 || col + i < 0 || row + j < 0) {
                continue;
            }

            return isLegalMove(board, player, LastMove, col, row, col + i, row + j);
        }
    }
    return 0;
}

GameStatus checkWin(_Bool player, Piece** board, LastMove LastMove) {
    // search enemy king : reverse player value (white player, search black king)
    Point king = findKing(!player, board);
    // (-1 ; -1) = out of board
    if (king.col == -1 || king.row == -1) {
        return WINNING;
    }

    if (canKingMove(!player, LastMove, board, king.col, king.row)) {
        return ONGOING;
    }
    int emptyCase = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j <8; j++) {
            if (board[i][j] == EMPTY) {
                emptyCase++;
                continue;
            }
            // If enemy can move one piece, he can still play
            if (isEnemy(board, player,i,j) && canPieceMove(!player, LastMove, board,i,j)) {
                return ONGOING;
            }
            // Check if only the 2 kings remains (64 cases by default on chessboard)
            if (emptyCase == 62) {
                return STALEMATE;
            }

        }
    }
    // Check if the enemy king is "mat"
   if (isCaseSafe(!player, LastMove, board,king.col,king.row)) {
       return STALEMATE;
   }
    return WINNING;
}