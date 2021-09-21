#ifndef JOGADA_H_INCLUDED
#define JOGADA_H_INCLUDED

#include "board.h"

// Function to check if there's still at least on move to be done. //
int checkGameOver();

// Function to check if the player won of lost the game. //
int checkGameResult();

// Function to execute the move. //
void gameMoveExecution(int,int,char);

// Function to see the possible moves. //
void gameMove(int,int,int);

// Function to get the name of the player. //
void gamePlayerName(Board*,int);

#endif // JOGADA_H_INCLUDED
