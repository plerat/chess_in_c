cmake_minimum_required(VERSION 3.30)
project(chess C)

set(CMAKE_C_STANDARD 11)

add_executable(chess main.c
        board.c
        move.c
        piece.c
        board.h
        move.h
        piece.h)
