#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

#include <allegro.h>

// Structure for the main board. //
typedef struct
{
    int points;         //Move counter.//
    int piece;          //Pines counter.//
    char result[7];     //Result.//
    char player[21];    //Player name.//
    char name[15];      //Board name.//
    char board[9][9];   //Board matrix.//
}Board;

// Structure for board bitmaps. //
typedef struct
{
    BITMAP* bg;         //Background.//
    BITMAP* board;      //Board.//
    BITMAP* boardName;  //Board Name.//
    BITMAP* buffer;     //Buffer.//
    BITMAP* bufferAux;  //Auxiliary buffer.//
    BITMAP* buttonB;    //Button Big.//
    BITMAP* cursor;     //Cursor.//
    BITMAP* piece;      //Piece.//
    BITMAP* pieceBg;    //Piece background.//
    FONT* f1;           //Font.//
}Bitmaps;

// Function to set the board correctly. //
void setBoard(int*);

// Function to set board bitmaps. //
void setBoardBitmaps(Bitmaps*,int);

// Function to draw the board on the auxiliary buffer. //
void drawBoard(Bitmaps*);

// Function to destroy board bitmaps. //
void destroyBoardBitmaps(Bitmaps*);

// Function to play the game. //
void game(int);

#endif // board_H_INCLUDED
