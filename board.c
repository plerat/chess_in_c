//
// Created by jeanm on 24/01/2025.
//

#include "board.h"

#include <stdio.h>
#include <stdlib.h>

void deleteBoard(Piece **board) {
    // Free all row before board
    for (int y = 0; y < 8; y++) {
        free(board[y]);
        board[y] = NULL;
    }
    free(board);
    board = NULL;
}

void placePiece(Piece **board, Column x, int y, Piece piece) {
    board[x - 1][y - 1] = piece;
}

char columnToString(Column column) {
    switch (column) {
        case A:
            return 'a';
        case B:
            return 'b';
        case C:
            return 'c';
        case D:
            return 'd';
        case E:
            return 'e';
        case F:
            return 'f';
        case G:
            return 'g';
        case H:
            return 'h';
        default:
            return '.';
    }
}


void displayBoard(Piece **board) {
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int i = 7; i >= 0; i--) {
        printf("%d |", i + 1);

        for (int j = 0; j < 8; j++) {
            //printf(" %c |", pieceToString(board[j][i]));
            printf(" %d  ", board[j][i]);
        }

        printf("\n  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    A   B   C   D   E   F   G   H\n");
}

void resetBoardPiece(Piece **board) {
    // Just placing at right position all pieces
    for (Column i = A; i <= H; i++) {
        placePiece(board, i, 7, BLACK_PAWN);
        placePiece(board, i, 2, WHITE_PAWN);
    }

    placePiece(board, A, 1, WHITE_ROOK);
    placePiece(board, H, 1, WHITE_ROOK);
    placePiece(board, A, 8, BLACK_ROOK);
    placePiece(board, H, 8, BLACK_ROOK);

    placePiece(board, B, 1, WHITE_KNIGHT);
    placePiece(board, G, 1, WHITE_KNIGHT);

    placePiece(board, B, 8, BLACK_KNIGHT);
    placePiece(board, G, 8, BLACK_KNIGHT);

    placePiece(board, C, 8, BLACK_BISHOP);
    placePiece(board, F, 8, BLACK_BISHOP);
    placePiece(board, C, 1, WHITE_BISHOP);
    placePiece(board, F, 1, WHITE_BISHOP);

    placePiece(board, D, 8, BLACK_QUEEN);
    placePiece(board, E, 8, BLACK_KING);
    placePiece(board, D, 1, WHITE_QUEEN);
    placePiece(board, E, 1, WHITE_KING);
}

Piece **generateEmptyBoard() {
    Piece **board = malloc(sizeof(Piece *) * 8);
    for (int i = 0; i < 8; i++) {
        Piece *row = malloc(sizeof(Piece) * 8);
        for (int j = 0; j < 8; j++) {
            row[j] = EMPTY;
        }
        board[i] = row;
    }

    return board;
}