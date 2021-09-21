#include "keystates.h"

// Keyboard input function that compare key states. //
void keyboardInput()
{
   int i;
   for(i=0;i<KEY_MAX;i++)
     beforeKey[i]=key[i];
   poll_keyboard();
}
// ------------------------------------------------ //

// Function to check key pressed. //
int pressed(int TECLA)
{
    return(beforeKey[TECLA]==FALSE&&key[TECLA]==TRUE);
}
// ------------------------------ //

// Function to check key held. //
int hold(int TECLA)
{
    return(beforeKey[TECLA]==TRUE&&key[TECLA]==TRUE);
}
// --------------------------- //

// Function to check key let go. //
int unpressed(int TECLA)
{
    return(beforeKey[TECLA]==TRUE&&key[TECLA]==FALSE);
}
// ----------------------------- //

