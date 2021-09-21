#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "variables.h"

// Function to open a file that receives the name of the file and the way to open it. //
FILE* openFile(char[],char[]);

// Function to close the a file that receives the file that was open. //
void closeFile(FILE*);

// Function to clear the content that is in a file. //
void clearFile(char[],char[]);

// Function to copy a file to another. //
void copyFile(char[],char[],char[]);

// Function to save the previously move. //
void saveMove(Board*);

// Function to return the board to the previously move. //
void returnMove(Board*);

// Function to save the information of the game after ends. //
void saveHistoric(Board*);

// Function to check if the player bet the record. //
void checkRecord(Board*,int);

// Function to divide the file in 2. //
void clearRecord(Board*,int);

// Function to save the new record on the auxiliary file. //
void saveRecord(Board*);

// Function to save the settings on a file. //
void saveSettings(Volume*,Paths*);

// Function to get the appearance and sound settings from a file. //
void setSettings(Volume*,Paths*);

#endif // FILE_H_INCLUDED
