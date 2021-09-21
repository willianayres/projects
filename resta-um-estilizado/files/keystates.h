#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

#include <allegro.h>

// Arrays of keys that was pressed. //
int beforeKey[KEY_MAX];

// Keyboard input function that compare key states. //
void keyboardInput();

// Function to check key pressed. //
int pressed(int TECLA);

// Function to check key held. //
int hold(int TECLA);

// Function to check key let go. //
int unpressed(int TECLA);

#endif // TECLADO_H_INCLUDED
