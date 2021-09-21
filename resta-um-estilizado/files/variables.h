#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <allegro.h>
#define  BRANCO   makecol(255,255,255)
#define  CINZA    makecol(196,196,192)
#define  PRETO    makecol(0,0,0)
#define  PRETIN   makecol(31,31,31)
#define  VERDE    makecol(253,98,8)
#define  VERDIN   makecol(24,133,196)
#define  VERMELHO makecol(253,38,41)
#define  VOLMAX   255
#define  VOLMIN   0

// Structure for sound control. //
typedef struct
{
    int noise;     //Sound effects.//
    int music;     //Sound music.//
}Volume;

// Structure for appearance control. //
typedef struct
{                       //Strings for the paths with the bitmaps.//
    char bg[30];        //Background.//
    char boardF[30];    //French Board.//
    char boardI[30];    //English Board.//
    char buttonB[30];   //Button Big.//
    char buttonM[30];   //Button Medium.//
    char buttonS[30];   //Button Small.//
    char logo[30];      //Logo.//
    char piece[30];     //Piece.//
    char pieceBg[30];   //Piece Background.//
    char pieceV[30];    //Piece Valid.//
    char title[30];     //Title.//
}Paths;

// Enumeration for screen type. --------------------------------------------------- //
enum {MENUSCREEN, RULE, HISTORIC, RECORD, SETTINGS, BOARDS, GAMEI, GAMEF, MOVE, NAME};

// Function to close the program. //
void fecha_programa();

// Function to increment the timer. //
void incrementa_timer();

// Screen control. //
int screen_state;

// Color control. //
int cor_state;

// Font color control. //
int fonte_state;

#endif // VARIABLES_H_INCLUDED
