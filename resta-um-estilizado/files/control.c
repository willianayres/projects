#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "control.h"
#include "keystates.h"

//Board *bd;

// Function to check if the mouse is in that position. //
int mouseIn(int xi,int xf,int yi,int yf)
{
    int v=0;                                            //It will return 1 with the mouse is on that position.//
    if(mouse_x>xi&&mouse_x<xf&&mouse_y>yi&&mouse_y<yf)
        v=1;
    return v;
}
// --------------------------------------------------- //

// Setter for mouse state. //
void mouseStates(int y,int x,int xi,int xf,int yi,int yf,int row,int col,int* at)
{
    // Mouse pressed on a valid button. //
    if((mouse_x>xi+x*col&&mouse_x<xf+x*col&&mouse_y>yi+y*row&&mouse_y<yf+y*row)&&(mouse_b==1))
        *at=1;

    // Mouse check to pressed and unpressed correctly. //
    if((mouse_x>xi+x*col&&mouse_x<xf+x*col&&mouse_y>yi+y*row&&mouse_y<yf+y*row)&&(mouse_b==0&&*at==1))
        *at=2;

    // Mouse set to unpressed if invalid command. //
    if(!(mouse_x>xi+x*col&&mouse_x<xf+x*col&&mouse_y>yi+y*row&&mouse_y<yf+y*row)&&(*at==1))
        *at=0;
}
// ----------------------- //

// Setter for mouse state in game. //
void mouseStatesMove(int* at,int row,int col,Board* bd)
{
    // Mouse pressed on a valid pine. //
    if(mouseIn(225+col*50,276+col*50,125+row*50,176+row*50)&&bd->board[row+1][col+1]=='I'&&mouse_b==1)
        *at=1;

    // Mouse check to pressed and unpressed correctly. //
    if(mouseIn(225+col*50,276+col*50,125+row*50,176+row*50)&&bd->board[row+1][col+1]=='I'&&mouse_b==0&&*at==1)
        *at=2;

    // Mouse set to unpressed if invalid command. //
    if(!mouseIn(225+col*50,276+col*50,125+row*50,176+row*50)&&*at==1)
        *at=0;
}
// ------------------------------- //

// Bip control to mouse states. //
void bipControl(int y,int x,int xi,int xf,int yi,int yf,int* bip,int row,int col)
{
    // Valid position for bip check. //
    if(mouse_x>xi+x*col&&mouse_x<xf+x*col&&mouse_y>yi+y*row&&mouse_y<yf+y*row)
    {
        if(*bip<3)
            (*bip)++;
    }
    // Set bip for 0 if invalid position. //
    if(!(mouse_x>xi+x*col&&mouse_x<xf+x*col&&mouse_y>yi+y*row&&mouse_y<yf+y*row))
        *bip=0;
}
// ---------------------------- //

// Function to set the selector with the keys. //
void selInput(int* sel_i,int* sel_j)
{
    if(pressed(KEY_UP))             //If UP pressed will climb a row.//
        (*sel_i)--;
    else if(pressed(KEY_DOWN))      //If DOWN pressed will go down a row.//
        (*sel_i)++;
    else if(pressed(KEY_LEFT))      //If LEFT pressed will go back a col.//
        (*sel_j)--;
    else if(pressed(KEY_RIGHT))     //If RIGHT pressed will go forward a col.//
        (*sel_j)++;
}
// ------------------------------------------- //

// Function to update the selectors on the menuS function. //
void selUpdateMenuS(int* sel_i,int* sel_j)
{
    if(*sel_i>14&&(*sel_j==0||*sel_j==1))                              //Selectors update.//
        *sel_i=0;
    else if(*sel_i<0&&(*sel_j==0||*sel_j==1))
        *sel_i=14;
    else if(*sel_i>12&&*sel_j==2&&pressed(KEY_DOWN))
        *sel_i=0;
    else if(*sel_i<0&&*sel_j==2)
        *sel_i=12;
    else if(*sel_j>2&&*sel_i<13)
        *sel_j=0;
    else if(*sel_j<0&&*sel_i<13)
        *sel_j=2;
    else if(*sel_j>1&&(*sel_i==13||*sel_i==14)&&pressed(KEY_RIGHT))
        *sel_j=0;
    else if(*sel_j<0&&(*sel_i==13||*sel_i==14))
        *sel_j=1;
    }
// ------------------------------------------------------- //

// Function to update the selectors on the menuS function with the mouse. //
void selUpdateMenuSMouse(int* sel_i,int* sel_j)
{
    int i,j;                    //Loop variables.//
    for(i=0;i<15;i++)           //Lines.//
    {
        for(j=0;j<3;j++)        //Cols.//
        {
            if(j==2)
            {
                if(i>12)        //Skip some.//
                    continue;
            }                   //If the mouse ins in one of those.//
            if(mouseIn(450+110*j,551+110*j,150+30*i,171+30*i))
            {
                *sel_i=i;       //Update the selectors.//
                *sel_j=j;
            }
        }
    }
}
// ---------------------------------------------------------------------- //

// Function to update the selectors on the game function. //
void selUpdateMove(int* sel_i,int* sel_j,int b)
{
    if(*sel_i<0&&(*sel_j>1&&*sel_j<5))                          //If it leaves the board on the top, will go back down.//
        *sel_i=6;
    else if(*sel_i>6 &&(*sel_j>1&&*sel_j<5))                    //If it leaves the board on the bottom, will go back top.//
        *sel_i=0;
    else if((*sel_i<5&&*sel_i>1)&&*sel_j<0)                     //If it leaves the board on the left, will go back right.//
        *sel_j=6;
    else if((*sel_i<5&&*sel_i>1)&&*sel_j>6)                     //If it leaves the board on the right, will go back left.//
        *sel_j=0;
    else if(*sel_i<2-b&&(*sel_j==1||*sel_j==5)&&pressed(KEY_UP))
        *sel_i =4+b;
    else if(*sel_i<2&&(*sel_j==0||*sel_j==6)&&pressed(KEY_UP))
        *sel_i=4;
    else if(*sel_i>4+b&&(*sel_j==1||*sel_j==5)&&pressed(KEY_DOWN))
        *sel_i=2-b;
    else if(*sel_i>4&&(*sel_j==0||*sel_j==6)&&pressed(KEY_DOWN))
        *sel_i=2;
    else if(*sel_j<2&&(*sel_i==0||*sel_i==6)&&pressed(KEY_LEFT))
        *sel_j=4;
    else if(*sel_j<2-b&&(*sel_i==1||*sel_i==5)&&pressed(KEY_LEFT))
        *sel_j=4+b;
    else if(*sel_j>4&&(*sel_i==0||*sel_i==6)&&pressed(KEY_RIGHT))
        *sel_j=2;
    else if(*sel_j>4+b&&(*sel_i==1||*sel_i==5)&&pressed(KEY_RIGHT))
        *sel_j=2-b;
}
// ------------------------------------------------------ //

// Function to update the selectors on the game function with the mouse. //
void selUpdateMoveMouse(int* sel_i,int* sel_j,int b)
{
    if(b)                                                       //Check to French board.//
    {
        if(mouseIn(275,326,175,226)){ *sel_i=1; *sel_j=1; }     //Set the selectors depending on the mouse position.//
        if(mouseIn(475,526,175,226)){ *sel_i=1; *sel_j=5; }
        if(mouseIn(275,326,375,426)){ *sel_i=5; *sel_j=1; }
        if(mouseIn(475,526,375,426)){ *sel_i=5; *sel_j=5; }
    }
    if(mouseIn(325,376,125,176)){ *sel_i=0; *sel_j=2; }
    if(mouseIn(375,426,125,176)){ *sel_i=0; *sel_j=3; }
    if(mouseIn(425,476,125,176)){ *sel_i=0; *sel_j=4; }
    if(mouseIn(325,376,175,226)){ *sel_i=1; *sel_j=2; }
    if(mouseIn(375,426,175,226)){ *sel_i=1; *sel_j=3; }
    if(mouseIn(425,476,175,226)){ *sel_i=1; *sel_j=4; }
    if(mouseIn(225,276,225,276)){ *sel_i=2; *sel_j=0; }
    if(mouseIn(275,326,225,276)){ *sel_i=2; *sel_j=1; }
    if(mouseIn(325,376,225,276)){ *sel_i=2; *sel_j=2; }
    if(mouseIn(375,426,225,276)){ *sel_i=2; *sel_j=3; }
    if(mouseIn(425,476,225,276)){ *sel_i=2; *sel_j=4; }
    if(mouseIn(475,526,225,276)){ *sel_i=2; *sel_j=5; }
    if(mouseIn(525,576,225,276)){ *sel_i=2; *sel_j=6; }
    if(mouseIn(225,276,275,326)){ *sel_i=3; *sel_j=0; }
    if(mouseIn(275,326,275,326)){ *sel_i=3; *sel_j=1; }
    if(mouseIn(325,376,275,326)){ *sel_i=3; *sel_j=2; }
    if(mouseIn(375,426,275,326)){ *sel_i=3; *sel_j=3; }
    if(mouseIn(425,476,275,326)){ *sel_i=3; *sel_j=4; }
    if(mouseIn(475,526,275,326)){ *sel_i=3; *sel_j=5; }
    if(mouseIn(525,576,275,326)){ *sel_i=3; *sel_j=6; }
    if(mouseIn(225,276,325,376)){ *sel_i=4; *sel_j=0; }
    if(mouseIn(275,326,325,376)){ *sel_i=4; *sel_j=1; }
    if(mouseIn(325,376,325,376)){ *sel_i=4; *sel_j=2; }
    if(mouseIn(375,426,325,376)){ *sel_i=4; *sel_j=3; }
    if(mouseIn(425,476,325,376)){ *sel_i=4; *sel_j=4; }
    if(mouseIn(475,526,325,376)){ *sel_i=4; *sel_j=5; }
    if(mouseIn(525,576,325,376)){ *sel_i=4; *sel_j=6; }
    if(mouseIn(325,376,375,426)){ *sel_i=5; *sel_j=2; }
    if(mouseIn(375,426,375,426)){ *sel_i=5; *sel_j=3; }
    if(mouseIn(425,476,375,426)){ *sel_i=5; *sel_j=4; }
    if(mouseIn(325,376,425,476)){ *sel_i=6; *sel_j=2; }
    if(mouseIn(375,426,425,476)){ *sel_i=6; *sel_j=3; }
    if(mouseIn(425,476,425,476)){ *sel_i=6; *sel_j=4; }
}
// ------------------------------------------------ //
