#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "board.h"
#include "control.h"
#include "file.h"
#include "game.h"
#include "keystates.h"
#include "menu.h"
#include "variables.h"

volatile int exit_program;
volatile int timer;
Board *bd;
Paths *paths;
Volume *vol;

// Start the allegro screen. //
void initAllegro();

int main()
{
    initAllegro();                                  //Star the allegro functions.//
    exit_program=FALSE;                             //Set the exit variable to false.//
    LOCK_FUNCTION(fecha_programa);                  //Lock the function.//
    LOCK_VARIABLE(exit_program);                    //Lock the variable.//
    set_close_button_callback(fecha_programa);      //Set the close button to accept the close function.//
    LOCK_FUNCTION(incrementa_timer);                //Lock the increment timer function.//
    LOCK_VARIABLE(timer);                           //Lock the timer variable.//

    /// VARIABLES ///
    screen_state=MENUSCREEN;                        //Start the screen state with Menu screen.//
    mouse_x=1000;                                   //Put the mouse out the window.//
    mouse_y=1000;
    int help=0;                                     //Auxiliary variable.//
    vol=(Volume*)malloc(sizeof(Volume));            //Allocate space for the structures.//
    paths=(Paths*)malloc(sizeof(Paths));
    setSettings(vol,paths);                         //Set the start settings.//
    /// SOUNDS ///
    MIDI* musica=load_midi("sounds\\music.mid");    //Set the music pointer.//
    play_midi(musica,TRUE);                         //Start the music.//
    set_volume(vol->noise,vol->music);              //Set the volume
    /// GAME LOOP ///
    while(!exit_program)
    {
        /// INPUT ///
        keyboardInput();                            //Keyboard input.//
        if(unpressed(KEY_ESC))                      //Check for exiting program.//
            fecha_programa();
        /// UPDATE ///
        if(screen_state==MENUSCREEN)                //If screen state is equal to menu, call the menu function.//
            menu();
        else if(screen_state==BOARDS)               //If screen state is equal to tab, call the menuS function.//
            menuS(&help);
        else if(screen_state==GAMEI)                //If screen state is equal to Imprimi, call the game with 0 as argument.//
            game(0);
        else if(screen_state==GAMEF)                //If screen state is equal to Imprimi F, call the game with 1 as argument.//
            game(1);
        else if(screen_state==RULE)                 //If screen state is equal to regra, call the rules function.//
            rules();
        else if(screen_state==HISTORIC)             //If screen state is equal to estatisticas, call the historic function.//
            historic();
        else if(screen_state==RECORD)               //If screen state is equal to ranking, call the ranking function.//
            ranking();
        else if(screen_state==SETTINGS)             //If screen state is equal to ajustes, call the settings function.//
            settings();
        else if(screen_state==NAME)                 //If screen state is equal to nome, call the gamePlayerName function.//
            gamePlayerName(bd,help);
    }
    /// FINALIZATION ///
    stop_midi();                                    //If the loop ends, stop the music.//
    destroy_midi(musica);                           //Destroy the music mid.//
    return 0;                                       //Return 0 for the end of the main.//
}
END_OF_MAIN()                                       //MACRO for end of the main function.//

// Start the allegro screen. //
void initAllegro()
{
    setlocale(LC_ALL,"Portuguese");                         //Change the language to Portuguese.//
    system("MODE con cols=15 lines=1 ");                    //Change the size of the console.//
    system("title RestaUm");                                //Change the name of the console.//
    if(allegro_init())                                      //Check if it stats right.//
        exit(1);
    install_timer();                                        //Install the pattern timers.//
    install_mouse();                                        //Install the mouse.//
    install_keyboard();                                     //Install the keyboard.//
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);    //Install the sound.//
    set_color_depth(32);                                    //Set the color pattern.//
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);      //Set the window size.//
    set_uformat(U_UTF8);                                    //Set the character encoding.//
    set_window_title("Resta Um");                           //Set the window title.//
}
// ------------------------- //

// Function to close the program. //
void fecha_programa()
{
    saveSettings(vol,paths);      //Save the last settings used.//
    free(vol);                    //Deallocate the space.//
    free(paths);
    exit_program=TRUE;            //Exit variable set to true.//
}
END_OF_FUNCTION(fecha_programa);
// ------------------------------ //

// Function to increment the timer. //
void incrementa_timer()
{
    timer++;
}
END_OF_FUNCTION(incrementa_timer)
// -------------------------------- //
