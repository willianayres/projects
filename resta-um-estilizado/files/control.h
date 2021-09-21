#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

// Function to check if the mouse is in that position. //
int mouseIn(int,int,int,int);

// Setter for mouse state. //
void mouseStates(int,int,int,int,int,int,int,int,int*);

// Setter for mouse state in game. //
void mouseStatesMove(int*,int,int,Board*);

// Bip control to mouse states. //
void bipControl(int,int,int,int,int,int,int*,int,int);

// Function to set the selector with the keys. //
void selInput(int*,int*);

// Function to update the selectors on the menuS function. //
void selUpdateMenuS(int*,int*);

// Function to update the selectors on the menuS function with the mouse. //
void selUpdateMenuSMouse(int*,int*);

// Function to update the selectors on the game function. //
void selUpdateMove(int*,int*,int);

// Function to update the selectors on the game function with the mouse. //
void selUpdateMoveMouse(int*,int*,int);

#endif // CONTROL_H_INCLUDED
