#ifndef TEXTOS_H_INCLUDED
#define TEXTOS_H_INCLUDED

#include "board.h"
#include "variables.h"

// Function to save the previously move. //
void saveMove(board*);

// Function to return the board to the previously move. //
void returnMove(board*);

// Function to save the information of the game after ends. //
void saveHistoric(board*);

// Function to check if the player bet the record. //
void checkRecord(board*,int);

// Function to divide the file in 2. //
void clearRecord(board*,int);

// Function to save the new record on the auxiliary file. //
void saveRecord(board*);

// Function to save the settings on a file. //
void saveSettings(volume*,bitmaps*);

// Function to get the appearance and sound settings from a file. //
void setSettings(volume*,bitmaps*);

#endif // TEXTOS_H_INCLUDED
