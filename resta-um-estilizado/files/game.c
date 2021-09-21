#include <allegro.h>
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

// Function to check if there's still at least on move to be done. //
int checkGameOver()
{
    int i,j,v=1;                    //Auxiliary variables.//
    for(i=1;i<9;i++)                //If there's any pine that has a directly near pine, there's moves to do.
    {
        for(j=1;j<9;j++)
        {
            if((bd->board[i][j]!='*')&&(bd->board[i][j]=='I')&&
               ((bd->board[i+1][j]=='I'&&bd->board[i+2][j]!='*'&&bd->board[i+2][j]!='I')||
                (bd->board[i][j+1]=='I'&&bd->board[i][j+2]!='*'&&bd->board[i][j+2]!='I')||
                (bd->board[i-1][j]=='I'&&bd->board[i-2][j]!='*'&&bd->board[i-2][j]!='I')||
                (bd->board[i][j-1]=='I'&&bd->board[i][j-2]!='*'&&bd->board[i][j-2]!='I')))
                    v=0;
        }
    }
    return v;                       //Return 1 if there's no moves.
}
// --------------------------------------------------------------- //

// Function to check if the player won of lost the game. //
int checkGameResult()
{
    int i,j,v=0;                            //Auxiliary variables.//
    for(i=1;i<9;i++)
    {
        for(j=1;j<9;j++)                    //Loop on the matrix.//
        {
            if(bd->board[i][j]=='I')        //Count the pines.//
                v++;
        }
    }
    if(v>1)                                 //If there's more than 1 pine, return 0.
        v=0;
    return v;
}
// ----------------------------------------------------- //

// Function to execute the move. //
void gameMoveExecution(int row,int col,char d)
{
    clearFile("files\\returnboard.txt","");         //Clear the return move file.//
    saveMove(bd);                                   //Save the board of the previously move.//
    bd->points++;                                   //Count of move increases.//
    bd->piece--;                                    //Number of pines decreases.//
    switch(d)                                       //Switch direction.//
    {
        case 'U':                                   //Case UP.//
            bd->board[row+1][col+1]='O';            //Where the pine was, became a empty space.//
            bd->board[row][col+1]='O';              //The adjacent position became a empty space.//
            bd->board[row-1][col+1]='I';              //The position near to the adjacent became a pine.//
            break;
        case 'D':                                   //Case DOWN.//
            bd->board[row+1][col+1]='O';
            bd->board[row+2][col+1]='O';
            bd->board[row+3][col+1]='I';
            break;
        case 'R':                                   //Case RIGHT.//
            bd->board[row+1][col+1]='O';
            bd->board[row+1][col+2]='O';
            bd->board[row+1][col+3]='I';
            break;
        case 'L':                                   //Case LEFT.//
            bd->board[row+1][col+1]='O';
            bd->board[row+1][col]='O';
            bd->board[row+1][col-1]='I';
            break;
    }
}
// ----------------------------- //

// Function to see the possible moves. //
void gameMove(int row,int col,int b)
{
    /// BITMAPS ///
    BITMAP* pieceV=load_bitmap(paths->pieceV,NULL);             //Bitmap for valid moves.//
    Bitmaps* m=(Bitmaps*)malloc(sizeof(Bitmaps));               //Auxiliary board structure.//
    setBoardBitmaps(m,b);                                       //Set the structure.//
    /// SOUNDS ///
    set_volume(vol->noise,vol->music);                          //Set the volume.//
    /// VARIABLES ///
    int exit_screen=FALSE;                                      //Auxiliary variable to exit program.//
    int at1=0,at2=0,at3=0;                                      //Auxiliary valid mouse events.//
    char d='?';                                                 //Direction of the move.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        /// INPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))                                  //Close the program.//
        {
            free(bd);
            free(m);
            fecha_programa();
        }
                                                                //Check a valid move to RIGHT.//
        if((pressed(KEY_RIGHT)||(mouseIn(225+(col+2)*50,276+(col+2)*50,125+row*50,176+row*50)&&mouse_b==1))&&
            bd->board[row+1][col+1]=='I'&&bd->board[row+1][col+2]=='I'&&bd->board[row+1][col+3]=='O')
            d='R';                                              //Set the direction to RIGHT.//
                                                                //Check a valid move to DOWN.//
        if((pressed(KEY_DOWN)||(mouseIn(225+col*50,276+col*50,125+(row+2)*50,176+(row+2)*50)&&mouse_b==1))&&
            bd->board[row+1][col+1]=='I'&&bd->board[row+2][col+1]=='I'&&bd->board[row+3][col+1]=='O')
            d='D';                                              //Set the direction to DOWN.//
                                                                //Check a valid move to LEFT.//
        if((pressed(KEY_LEFT)||(mouseIn(225+(col-2)*50,276+(col-2)*50,125+row*50,176+row*50)&&mouse_b==1))&&
            bd->board[row+1][col+1]=='I'&&bd->board[row+1][col]=='I'&&bd->board[row+1][col-1]=='O')
            d='L';                                              //Set the direction to LEFT.//
                                                                //Check a valid move to UP.//
        if((pressed(KEY_UP)||(mouseIn(225+col*50,276+col*50,125+(row-2)*50,176+(row-2)*50)&&mouse_b==1))&&
            bd->board[row+1][col+1]=='I'&&bd->board[row][col+1]=='I'&&bd->board[row-1][col+1]=='O')
            d='U';                                              //Set the direction to UP.//
                                                                //Check if the player cancel the move.//
        if((mouseIn(225+col*50,276+col*50,125+row*50,176+row*50)&&(bd->board[row+1][col+1]=='I')&&(at1==2))||pressed(KEY_ENTER))
            d='b';
        if(pressed(KEY_V)||(mouseIn(625,701,420,476)&&(at3==2)))//Check if the player leave the actual game.//
        {
            free(bd);
            free(m);
            screen_state=MENUSCREEN;
            exit_screen=TRUE;
        }                                                       //Check if the player rollback a move.//
        if((bd->points>0)&&(pressed(KEY_R)||(mouseIn(625,701,345,401)&&at2==2)))
        {
            if(!b)
                screen_state=GAMEI;
            else
                screen_state=GAMEF;
            returnMove(bd);
            free(m);
            exit_screen=TRUE;
        }
        if(d!='?')
        {
            if(!b)
                screen_state=GAMEI;
            else
                screen_state=GAMEF;
            if(d!='b')
                gameMoveExecution(row,col,d);                   //Function to execute the move.//
            exit_screen=TRUE;
        }
        /// UPDATE ///
        mouseStatesMove(&at1,row,col,bd);
        mouseStates(0,0,625,701,345,401,0,0,&at2);              //Update the mouse events.//
        mouseStates(0,0,625,701,420,476,0,0,&at3);
        /// DRAW ///
        set_burn_blender(255,255,255,128);                      //Saturation of the position of the pine.//
        drawBoard(m);                                           //Draw the board.//
        draw_sprite(m->buffer,m->bufferAux,0,0);                //Draw everything on the buffer.//
                                                                //Draw the actual pine.//
        draw_sprite_ex(m->buffer,m->piece,225+col*50,125+row*50,DRAW_SPRITE_TRANS,DRAW_SPRITE_NO_FLIP);
                                                                //Draw the valid moves.//
        if(bd->board[row+1][col+1]=='I'&&bd->board[row+1][col+2]=='I'&&bd->board[row+1][col+3]=='O')
            draw_sprite_ex(m->buffer,pieceV,225+(col+2)*50,125+row*50,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        if(bd->board[row+1][col+1]=='I'&&bd->board[row+1][col]=='I'&&bd->board[row+1][col-1]=='O')
            draw_sprite_ex(m->buffer,pieceV,225+(col-2)*50,125+row*50,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        if(bd->board[row+1][col+1]=='I'&&bd->board[row+2][col+1]=='I'&&bd->board[row+3][col+1]=='O')
            draw_sprite_ex(m->buffer,pieceV,225+col*50,125+(row+2)*50,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        if(bd->board[row+1][col+1]=='I'&&bd->board[row][col+1]=='I'&&bd->board[row-1][col+1]=='O')
            draw_sprite_ex(m->buffer,pieceV,225+col*50,125+(row-2)*50,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        if(mouseIn(625,701,345,401))                            //Draw hover effects.//
            rectfill(m->buffer,630,350,694,394,cor_state);
        if(mouseIn(625,701,420,476))
            rectfill(m->buffer,630,425,694,469,cor_state);
        draw_sprite(m->buffer,m->cursor,mouse_x,mouse_y);       //Draw the cursor.//
        draw_sprite(screen,m->buffer,0,0);                      //Draw the buffer on the screen.//
    }
    /// FINALIZATION ///
    destroyBoardBitmaps(m);                                     //Destroy all the board bitmaps.//
    destroy_bitmap(pieceV);                                     //Destroy the valid bitmap.//
}
END_OF_FUNCTION(gameMove);
// ----------------------------------- //

// Function to get the name of the player. //
void gamePlayerName(Board* bd,int b)
{
    /// BITMAPS ///
    BITMAP* bg=load_bitmap(paths->bg,NULL);                         //Background.//
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);                //Buffer.//
    BITMAP* button=load_bitmap(paths->buttonS,NULL);                //Button.//
    BITMAP* cursor=load_bitmap("bitmaps\\Cursor.bmp",NULL);         //Cursor.//
    BITMAP* logo=load_bitmap(paths->logo,NULL);                     //Logo.//
    /// FONTS ///
    FONT* f14=load_font("fonts\\F14.pcx",NULL,NULL);                //Fonts for text printing.//
    FONT* f24=load_font("fonts\\F24.pcx",NULL,NULL);
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef2.wav");                     //Sounds for sound effects.//
    SAMPLE* ef2=load_sample("sounds\\ef5.wav");
    SAMPLE* ef3=load_sample("sounds\\ef4.wav");
    set_volume(vol->noise,vol->music);                              //Set the volume.//
    play_sample(ef3,vol->noise,0,1000,FALSE);                       //Entering sound.//
    /// VARIABLES ///
    int exit_screen=FALSE;                                          //Exit function variable.//
    int ch,index=0;                                                 //Printing auxiliary variables.//
    int j,at=0,bip=0,t=0,corfonte=PRETO;                            //Auxiliary variables.//
    char *read=(char*)calloc(21,sizeof(char));                      //Pointer to get the name.//
    if(paths->bg[13]=='2'||paths->bg[13]=='4')                      //Color font check.//
        corfonte=BRANCO;
    clear_keybuf();                                                 //Clear the key buffer for inputs.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        /// INPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))
            fecha_programa();
        while(keypressed())                                         //When a key is pressed.//
        {
            ch=readkey();                                           //Get the key from the buffer.//
            if((ch>>8)==KEY_BACKSPACE)                              //If the BACKSPACE was pressed, get the Scan code.//
            {
                if(index>0)                                         //The index must be higher than 0.//
                {
                    play_sample(ef2,vol->noise,0,1000,FALSE);       //Key pressing sound.//
                    read[index-1]='\0';                             //Erase the character.//
                    index--;                                        //Reduces the index.//
                }
            }
            else                                                    //If it's not BACKSPACE.//
            {
                if(index<20)                                        //Until index lesser than 20.//
                {
                    if((ch&0xff)>=32&&(ch&0xff)<=126)               //Check if it's a valid key.//
                    {
                        play_sample(ef2,vol->noise,0,1000,FALSE);   //Key pressing sound.//
                        read[index++]=(ch&0xff);                    //Put the ASCII valor character on the string.//
                    }
                }
            }
        }
        /// UPDATE ///
        mouseStates(0,0,349,450,550,571,0,0,&at);                   //Mouse events.//
        bipControl(0,0,349,450,550,571,&bip,0,0);                   //Sound controller.//
        if(bip==1)
            play_sample(ef1,vol->noise,0,1000,FALSE);
        if(pressed(KEY_ENTER)||(mouseIn(349,450,550,571)&&at==2))   //If the BACK button was pressed.//
        {
            strcpy(bd->player,read);                                //Copy to the players name.//
            saveHistoric(bd);                                       //Save the statics.//
            if(!strcmp(bd->result,"Ganhou"))                        //If the player won.//
                checkRecord(bd,b);                                  //Check if the player beat the record from that board.//
            free(bd);                                               //Deallocate the space.//
            free(read);
            screen_state=MENUSCREEN;                                //Change the screen state.//
            exit_screen=TRUE;
        }
        /// DRAW
        draw_sprite(buffer,bg,0,0);                                 //Draw the background.//
        draw_sprite(buffer,logo,235,50);                            //Draw the logo and print the result.//
        textprintf_centre_ex(buffer,f24,400,200,corfonte,-1,"Voce %s!!!",bd->result);
        textout_centre_ex(buffer,f24,"Digite seu nome:",400,300,corfonte,-1);
        draw_sprite(buffer,button,349,550);                         //Ask for the name and draw the button.//
        textout_centre_ex(buffer,f14,"ENTER",400,550,corfonte,-1);
        for(j=0;j<20;j++)                                           //Draw the character spaces.//
            rectfill(buffer,200+20*j,385,210+20*j,387,corfonte);

        for(j=0;read[j]!='\0';j++)                                  //Print the name typing.//
            textprintf_centre_ex(buffer,f24,202+20*j,350,corfonte,-1,"%c",read[j]);
        if(t>100)                                                   //Timer for blinking effect.//
            t=0;
        if(t<50)                                                    //Blinking effect.//
        {
            rectfill(buffer,354,553,443,565,cor_state);
            rectfill(buffer,195+20*index,360,196+20*index,380,corfonte);
        }
        if(mouseIn(349,450,550,571))                                //Hover effect.//
            rectfill(buffer,354,553,443,565,cor_state);
                                                                    //Print the count of rest letters that could be typed.//
        textprintf_centre_ex(buffer,f24,400,450,corfonte,-1,"Caracteres restantes: %d",20-index);
        draw_sprite(buffer,cursor,mouse_x,mouse_y);                 //Draw the cursor.//
        draw_sprite(screen,buffer,0,0);                             //Draw the buffer on the screen.//
        t++;
    }
    /// FINALIZATION ///
    destroy_bitmap(bg);                                             //Destroy all the bitmaps, fonts and samples.//
    destroy_bitmap(buffer);
    destroy_bitmap(button);
    destroy_bitmap(cursor);
    destroy_bitmap(logo);
    destroy_font(f14);
    destroy_font(f24);
    destroy_sample(ef1);
    destroy_sample(ef2);
    destroy_sample(ef3);
}
END_OF_FUNCTION(gamePlayerName);
// --------------------------------------- //
